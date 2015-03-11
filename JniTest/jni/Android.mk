JNI_PATH := $(call my-dir)

LOCAL_PATH := $(JNI_PATH)/un7z

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/un7z/src/

LOCAL_MODULE := un7z

LOCAL_SRC_FILES := \
		src/xz_crc32.cpp \
		src/xz_crc64.cpp \
		src/xz_dec_bcj.cpp \
		src/xz_dec_lzma2.cpp \
		src/xz_dec_stream.cpp \
		JniLoad.cpp
        
LOCAL_CFLAGS := -DXZ_DEC_X86 -DXZ_DEC_POWERPC -DXZ_DEC_IA64 -DXZ_DEC_ARM -DXZ_DEC_ARMTHUMB \
				-DXZ_DEC_SPARC  -DXZ_USE_CRC64 -DXZ_DEC_ANY_CHECK 

LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)

