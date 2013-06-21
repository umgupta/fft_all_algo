CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(FFT_TEST C CXX)

SET (CMAKE_C_COMPILER arm-none-linux-gnueabi-gcc)


IF(OP STREQUAL FLOAT)
	ADD_DEFINITIONS(-O3 -mfpu=vfp -mcpu=cortex-a8)
ELSE(OP STREQUAL FLOAT)
	ADD_DEFINITIONS(-O3 -mfpu=neon -mcpu=cortex-a8 -mfloat-abi=softfp)
ENDIF(OP STREQUAL FLOAT)




ADD_DEFINITIONS(-DKISS_FFT_USE_ALLOCA -Wall)

ADD_DEFINITIONS(-ffast-math -fomit-frame-pointer)
SET(CMAKE_INSTALL_PREFIX ${FFT_TEST_SOURCE_DIR}/)
MESSAGE(STATUS "*********${FFT_TEST_SOURCE_DIR}")    

IF(ALGO STREQUAL KISS_FFT)
	MESSAGE("FFT ALGO : " ${ALGO})
	ADD_DEFINITIONS(-DKISS_FFT)
	IF (OP STREQUAL FIXED32)
		MESSAGE("32-FIXED POINT OPERATIONS")
		ADD_DEFINITIONS(-DFIXED_POINT=32)
	ENDIF(OP STREQUAL FIXED32)
	IF (OP STREQUAL FIXED16)
        MESSAGE("16-FIXED POINT OPERATIONS")
        ADD_DEFINITIONS(-DFIXED_POINT=16)
    ENDIF(OP STREQUAL FIXED16)
	LINK_DIRECTORIES(${FFT_TEST_SOURCE_DIR}/thirdparty_lib/arm9/)
	INCLUDE_DIRECTORIES(${FFT_TEST_SOURCE_DIR}/inc)
ELSEIF(ALGO STREQUAL GST_FFT)
	MESSAGE("FFT ALGO : " ${ALGO})
    ADD_DEFINITIONS(-DGST_FFT -DFIXED_POINT=32)
	SET(LIB /home/umang/ti-ezsdk_dm816x-evm_5_05_02_00/linux-devkit/arm-none-linux-gnueabi/usr/lib)
    LINK_DIRECTORIES(${LIB})
	SET(INC /home/umang/ti-ezsdk_dm816x-evm_5_05_02_00/linux-devkit/arm-none-linux-gnueabi/usr)
	INCLUDE_DIRECTORIES(${INC}/include/gstreamer-0.10
        				${INC}/include/glib-2.0
        				${INC}/lib/glib-2.0/include
        				${INC}/include/glib-2.0/glib
        				${INC}/include/libxml2)
ELSEIF(ALGO STREQUAL ALLGO_FFT)
	MESSAGE("FFT ALGO : " ${ALGO})
    ADD_DEFINITIONS(-DALLGO_FFT -DFIXED_POINT=32)
    LINK_DIRECTORIES(${FFT_TEST_SOURCE_DIR}/thirdparty_lib/arm9/)
    INCLUDE_DIRECTORIES(${FFT_TEST_SOURCE_DIR}/thirdparty_lib)
ENDIF(ALGO STREQUAL KISS_FFT)

INCLUDE_DIRECTORIES(${FFT_TEST_SOURCE_DIR}/wav_io)
# WavIO library
SET(afp_wavio_SRCS wav_io/wav_read.c wav_io/wav_write.c)
ADD_LIBRARY(afpwavio ${afp_wavio_SRCS})

IF(ALGO STREQUAL KISS_FFT)
	IF(OP STREQUAL FIXED32)
		ADD_EXECUTABLE(kiss_fft_test_fixed32  ${FFT_TEST_SOURCE_DIR}/fft_compare.c
									 		${FFT_TEST_SOURCE_DIR}/src/kiss_fft.c
									   		${FFT_TEST_SOURCE_DIR}/src/kiss_fftr.c)
		TARGET_LINK_LIBRARIES(kiss_fft_test_fixed32 afpwavio m)	
	ENDIF(OP STREQUAL FIXED32)
	
	IF(OP STREQUAL FIXED16)
        ADD_EXECUTABLE(kiss_fft_test_fixed16  ${FFT_TEST_SOURCE_DIR}/fft_compare.c
                                            ${FFT_TEST_SOURCE_DIR}/src/kiss_fft.c
                                            ${FFT_TEST_SOURCE_DIR}/src/kiss_fftr.c)
        TARGET_LINK_LIBRARIES(kiss_fft_test_fixed16 afpwavio m)
    ENDIF(OP STREQUAL FIXED16)
	
	IF(OP STREQUAL FLOAT)
		ADD_EXECUTABLE(kiss_fft_test_float 	${FFT_TEST_SOURCE_DIR}/fft_compare.c
                	                 	   	${FFT_TEST_SOURCE_DIR}/src/kiss_fft.c
                                 		   	${FFT_TEST_SOURCE_DIR}/src/kiss_fftr.c)
    	TARGET_LINK_LIBRARIES(kiss_fft_test_float afpwavio m)
	ENDIF(OP STREQUAL FLOAT)

ELSEIF(ALGO STREQUAL GST_FFT)
	ADD_EXECUTABLE(gst_fft_test ${FFT_TEST_SOURCE_DIR}/fft_compare.c)
	TARGET_LINK_LIBRARIES(gst_fft_test afpwavio m gstfft-0.10)
ELSEIF(ALGO STREQUAL ALLGO_FFT)
	ADD_EXECUTABLE(allgo_fft_test ./fft_compare.c)
	TARGET_LINK_LIBRARIES(allgo_fft_test afpwavio fft_lib_arm9e m)
ENDIF(ALGO STREQUAL KISS_FFT)
