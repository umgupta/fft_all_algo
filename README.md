run ./build to get list of commands.
the commands are self explanatory.

It builds kiss_fft all three formats (32,16,float)
Note: 16 is of no use
It builds gst and algo fft too
Run the exectuables to get the result.


use ./cmp.py file1 file2 to comapre the fft outputs. 
It has a tolerance difference of 2 (i.e it ignores the abs difference of two or less than two )
It is defined as tol parameter at the top of cmp.py. You can change it by changing cmp.py

INPUTS FOLDER HAS SOME INPUT FILES
RESULTS: in order of performance. 
ALLGO>KISS16pt>GST>KISS32pt>KISS_float_with_neon>KISS_FLOAT_with_vfp

it is thoroughly tested on big_file_mono.wav
