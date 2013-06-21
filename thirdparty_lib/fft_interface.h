/******************************************************************************
*   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY                         
*                                                                           
* (C) 2011 ALLGO EMBEDDED SYSTEMS PVT. LTD                                  
*                                                                           
* FILE NAME : fft_interface.h                                               
*******************************************************************************
* CHANGE HISTORY
*
* dd/mm/yy   Code Ver     Description                        Author
* --------   -------      -----------                        ------
* 05/01/11    01          initial revision                   Namitha M
* 24/01/11    02          Removed unwanted typedefs          Namitha M
* 14/03/11    03          Changed declaration of FFT and     Namitha M 
*                         IFFT to include extra buffers
* 15/03/11    04          Added Int_16 data type for the     Namitha M
*                         coefficients
* 22/03/11    06          Added error enum if points are     Namitha M
*                         other than 1024 or 2048
******************************************************************************
* DESCRIPTION
*   This file contains the types of data used and prototypes of functions
*   called in main.c
*   
******************************************************************************/

#ifndef _FFT_INTERFACE_H_
#define _FFT_INTERFACE_H_

typedef int     Int_32;
typedef long int I32;
typedef I32 CoefType;
typedef long long Int_64;

typedef enum
{
    FFT_NO_ERROR,
    FFT_ERROR_POINT_UNSUPPORTED
} eTagFftError;

/**
* function_name: FFT
* @par1 :  pointer to data array
* @par2 :  number of samples
*
* function description:
* Calcutalate s the FFT of the given data array
* for the number of points specified 
* return value: none.
* Output written back to data array
*/

eTagFftError FFT(CoefType *data, Int_32 inSamples);

/**
* function_name: IFFT
* @par1 :  pointer to fft out array
* @par2 :  number of samples
*
* function description:
* Calcutalate s the IFFT of the given fft array
* for the number of points specified 
* return value: none.
* Output written to the given data location
*/

eTagFftError IFFT(CoefType *data, Int_32 inSamples );
#endif
