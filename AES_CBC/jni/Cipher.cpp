//
// Created by Admin on 11/5/2021.
//
#include <android/log.h>
#include <jni.h>
#include "aes.c"
#include <stdio.h>
#include <iostream>
#include "base64.c"

unsigned char* padData(std::string data);
std::string encryptData(std::string data, std::string key, std::string iv);
std::string decryptData(const char *data, std::string key, std::string iv);
std::string unpad(const char* data);
void j2std(JNIEnv *AEnv, jstring strSrc, std::string &strDes) {
    if (!strSrc) {
        strDes.clear();
        return;
    }
    strDes.clear();
    const char *s = AEnv->GetStringUTFChars(strSrc, NULL);
    strDes = s;
    AEnv->ReleaseStringUTFChars(strSrc, s);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_aes_1cbc_CustomCipher_decrypt(JNIEnv *env, jclass clazz, jstring data,
                                        jstring key,
                                        jstring iv) {
    std::string dataStr, keyStr, ivStr;
    j2std(env, data, dataStr);
    j2std(env, key, keyStr);
    j2std(env, iv, ivStr);
    const char* dataConst = dataStr.c_str();
    std::string result = decryptData(dataConst, keyStr, ivStr);
    return env->NewStringUTF(result.c_str());
}
std::string decryptData(const char* data, std::string key, std::string iv) {
    std::string result = "";
    unsigned char* b64DecodeData = b64_decode(data, strlen(data));
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, (unsigned char*)key.c_str(), (unsigned char*) iv.c_str());
    AES_CBC_decrypt_buffer(&ctx, b64DecodeData, strlen(reinterpret_cast<const char *>(b64DecodeData)));

    return unpad(reinterpret_cast<const char *>(b64DecodeData));
}

std::string unpad(const char* data) {
    int padLen = data[strlen(data) - 1];
    int len = strlen(data) - padLen;
    unsigned char* realData = new unsigned char[len+1];
    int i = 0;
    for (i = 0; i < len; i++) {
        realData[i] = data[i];
    }
    realData[len] = 0; // null terminated

    return std::string (reinterpret_cast<const char*>(realData));
}
std::string encryptData(std::string data, std::string key, std::string iv) {
    std::string realKey = key.substr(0, 16);
    std::string realIv = iv.substr(0, 16);
    unsigned char* paddedData = padData(data);
    int len = data.length() + 16 - data.length()%16;
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, (unsigned char*)realKey.c_str(), (unsigned char*) realIv.c_str());
    AES_CBC_encrypt_buffer(&ctx, paddedData, len);
    std::string result = b64_encode(paddedData,len);
    return result;
}

unsigned char* padData(std::string data) {
    int length = data.length();
    int padLength = 16 - length%16;
    unsigned char* res = new unsigned char[length + padLength];
    int i = 0;
    for (i = 0; i < length; i++) {
        res[i] = data[i];
    }
    for (int j = i; j < length + padLength; j++) {
        res[j] = (unsigned char) padLength;
    }
    return res;
}



