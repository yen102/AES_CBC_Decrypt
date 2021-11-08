package com.example.aes;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.example.aes_cbc.CustomCipher;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d("Main", CustomCipher.decrypt("XRx8HmR+KLQH9VPfUUaM6g==", "aaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaa"));

    }
}