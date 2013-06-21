#include<stdio.h>
#include<stdlib.h>
#include "wav_read.h"
#ifdef FIXED_POINT
#include<arm_neon.h>
#endif
#include <sys/time.h>

#ifdef KISS_FFT
	#include "kiss_fftr.h"
	#define USAGE  "./kiss_fft_test  <input wav file>  <out_fft_txt_val> <no of samples> \n"
#endif

#ifdef ALLGO_FFT
#include <fft_interface.h>
#define USAGE  "./allgo_fft_test  <input wav file>  <out_fft_txt_file> <no of samples> \n"
#endif

#ifdef GST_FFT
	#include<gst/fft/gstffts16.h>
	#define USAGE  "./gst_fft_test  <input wav file>  <out_fft_txt_val> <no of samples> \n"
#endif

int main(int argc,  char *argv[]){
	if(argc < 4){
        printf(USAGE);
        exit(1);
    }

    pcmfile_t   *wav_inp;
    
	wav_inp = wav_open_read(argv[1], 0);
    if(wav_inp == NULL){
        printf("wav_open_read failed\n");
        exit(1);
    }
    if(wav_inp->channels == 2){
        printf("Input file is stereo. NOT SUPPRTED\n");
        exit(1);
    }
	int         block_size 	= atoi(argv[3]);
	FILE        *fp_fft_out	= fopen(argv[2],"w");
// 	FILE		*fp_ifft_out= fopen(argv[4],"w");	
	short       *pcm 		= malloc(block_size*wav_inp->channels*sizeof(short));

#ifdef KISS_FFT
    void        		*fft_cfg	= 	kiss_fftr_alloc(block_size ,0,0,0 );
	kiss_fft_scalar*    fft_in		= 	(kiss_fft_scalar*)malloc(sizeof(kiss_fft_scalar)*(block_size));
	kiss_fft_cpx*      	fft_out		= 	(kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx)*(block_size));
#elif GST_FFT
	gint16* 			fft_in		= 	(gint16*)malloc(sizeof(gint16)*block_size);		
	GstFFTS16Complex*	fft_out		= 	(GstFFTS16Complex*)malloc(sizeof(GstFFTS16Complex*)*block_size);
	GstFFTS16*			fft_self	=	gst_fft_s16_new(block_size,FALSE);
#elif ALLGO_FFT
	int     *fft_in					=	(int*)malloc(sizeof(int)*block_size);
//	int     *fft_out				=	(int*)malloc(2*sizeof(int)*block_size);
//	short   *out_pcm				=	(short*)malloc(sizeof(short)*block_size);
#endif

    int 			i;
	int         	num_samples_read;
	long 			time=0;
	struct timeval 	start,end;

    while(1){
        num_samples_read = wav_read_int16(wav_inp, pcm, (block_size*wav_inp->channels), NULL);
		if(num_samples_read != block_size){
            printf("END of wav file reached\n");
            break;
        }
	
		for(i=0;i<block_size;i++){
#ifdef ALLGO_FFT
			fft_in[i] = (int)((pcm[i]));
	    //    fft_in[2*i+1] = 0;
#elif KISS_FFT
        	fft_in[i] =(kiss_fft_scalar)pcm[i];
#elif GST_FFT
			fft_in[i] =(gint16)pcm[i];		
#endif	
		}

		gettimeofday(&start,NULL);
#ifdef KISS_FFT
    	kiss_fftr(fft_cfg , fft_in, fft_out);
#elif GST_FFT
        gst_fft_s16_fft(fft_self,fft_in,fft_out);
#elif ALLGO_FFT
		FFT(fft_in, block_size);
#endif
		gettimeofday(&end,NULL);   

		time=time+(end.tv_usec+end.tv_sec*1000000-start.tv_usec-start.tv_sec*1000000);

#ifdef FIXED_POINT
#ifdef ALLGO_FFT
		for(i = 0; i < (block_size); i+=2){
        	fprintf(fp_fft_out, "%d\t", fft_in[i]);
        	fprintf(fp_fft_out, "%d\n", fft_in[i+1]);
        }
#else	
		for(i=0;i<(block_size/2);i++){
        	fprintf(fp_fft_out,"%d\t%d\n",(int)fft_out[i].r,(int)fft_out[i].i);
		}
#endif
#else
	for(i=0;i<(block_size/2);i++){
            fprintf(fp_fft_out,"%d\t%d\n",(int)((fft_out[i].r)/block_size),(int)((fft_out[i].i/block_size)));
	}
#endif
    }

   	printf("%ld time elapsed\n\n",time); 
	wav_close(wav_inp);
    fclose(fp_fft_out);
return 0;
}
