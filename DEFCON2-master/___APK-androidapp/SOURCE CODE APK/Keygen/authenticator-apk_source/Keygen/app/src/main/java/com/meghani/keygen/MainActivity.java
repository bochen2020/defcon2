package com.meghani.keygen;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.TextView;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class MainActivity extends AppCompatActivity {
     private String time, srandStr = "528491";
     EditText challengeCode;
     TextView authCode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        challengeCode = findViewById(R.id.challengeCode);
        authCode = findViewById(R.id.authCode);

        DateFormat df = new SimpleDateFormat("yyyyMMddHHmm"); // Format time
        time = df.format(Calendar.getInstance().getTime());

        challengeCode.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if(charSequence.length() > 0)
                    getAuthCode(charSequence);
                else
                    authCode.setText("");
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
    }

    public void getAuthCode(CharSequence challengeCode){
        MessageDigest md = null;
        try {
            md = MessageDigest.getInstance("SHA-512");
            /*float a = 7 % 10;
            char b = (char) a;
            char[] chars = new char[3];
            int[] nums = {1,7,4};
            for (int i=0; i<3; i++){
                chars[i] = (char) (nums[i] % 10);
            }
            String abc = String.valueOf(chars);

            System.out.println(abc);*/


            try {
                String message = srandStr + time + challengeCode.toString().toUpperCase();
                byte[] digest = md.digest(message.getBytes(StandardCharsets.UTF_8));
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < digest.length; i++) {
                    sb.append(Integer.toString((digest[i] & 0xff) + 0x100, 16).substring(1));
                }
                authCode.setText(sb.substring(0,5).toUpperCase() + "-" + sb.substring(5,10).toUpperCase());
            } catch (Exception e) {
                e.printStackTrace();
            }


        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }
}
