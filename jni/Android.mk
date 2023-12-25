ifneq ($(TARGET_SIMULATOR),true)



LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libsdcore
LOCAL_EXPORT_C_INCLUDES := libsimdsp/include
LOCAL_SRC_FILES := libsimdsp/lib/libsimdsp.so

include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libhttp
LOCAL_EXPORT_C_INCLUDES := libcurl/include
LOCAL_SRC_FILES := libcurl/lib/libcurl.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := simdsp

LOCAL_CFLAGS += -ggdb -Wall -fPIC -mfloat-abi=softfp -mfpu=neon


LOCAL_LDLIBS :=  -lz -llog -lOpenSLES -g -pie


LOCAL_C_INCLUDES := bionic
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libsimdsp/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libcurl/include

LOCAL_SHARED_LIBRARIES := libsdcore
LOCAL_STATIC_LIBRARIES := libhttp
LOCAL_SRC_FILES:=    sketch.cpp


include $(BUILD_EXECUTABLE)

endif  # TARGET_SIMULATOR != true
