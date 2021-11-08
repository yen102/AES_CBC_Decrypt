package com.example.aes_cbc;

public class CustomCipher {
    static {
        System.loadLibrary("aes_cbc");
    }
    public static native String decrypt(String ciphertext, String key, String iv);
}
