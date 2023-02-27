package com.example.zoetechv10;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    CardView cardPrice_per_1kg;
    CardView cardNumber_of_Cans;
    CardView cardRemaining_Oil_Amount;
    CardView cardMoney;

    TextView noOfCans;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        cardPrice_per_1kg = findViewById(R.id.cardPrice_per_1kg);
        cardNumber_of_Cans = findViewById(R.id.cardNumber_of_Cans);
        cardRemaining_Oil_Amount = findViewById(R.id.cardRemaining_Oil_Amount);
        cardMoney = findViewById(R.id.cardMoney);

        cardPrice_per_1kg.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showToast("Price_per_1kg Clicked");
            }
        });
        cardNumber_of_Cans.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showToast("Number_of_Cans Clicked");
            }
        });
        cardRemaining_Oil_Amount.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showToast("Remaining_Oil_Amount Clicked");
            }
        });
        cardMoney.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showToast("Money Clicked");
            }
        });

    }

    private void showToast(String message){
        Toast.makeText(this,"message", Toast.LENGTH_SHORT).show();
    }
}