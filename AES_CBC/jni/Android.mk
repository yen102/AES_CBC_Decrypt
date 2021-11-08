LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := aes_cbc
LOCAL_SRC_FILES         := Cipher.cpp
LOCAL_CPP_EXTENSION     := .cpp


# LOCAL_STATIC_LIBRARIES := curl-library

include $(BUILD_SHARED_LIBRARY)

