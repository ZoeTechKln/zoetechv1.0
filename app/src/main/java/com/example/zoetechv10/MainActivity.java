package com.example.zoetechv10;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends AppCompatActivity {


    TextView moneyTextView,noOfCansTextView,todayOilPriceTextView;


        protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

            moneyTextView=findViewById(R.id.Collected_Money);
            noOfCansTextView=findViewById(R.id.numberOfCans);
            todayOilPriceTextView=findViewById(R.id.todayOilPrice);



        //firebaseToApp
            FirebaseDatabase database =FirebaseDatabase.getInstance();

            DatabaseReference cansRef=database.getReference("Function_1/CanAmount");
            DatabaseReference moneyCol=database.getReference("Function_1/Price");
            DatabaseReference todayOilPrice=database.getReference("TodayOilPrice");



            todayOilPrice.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    long todayOilPrice=(long) snapshot.getValue();
                    todayOilPriceTextView.setText("Rs. "+Long.toString(todayOilPrice));

                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                    Toast.makeText(MainActivity.this, "Database Error!!", Toast.LENGTH_SHORT).show();

                }
            });
            moneyCol.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    long moneyCollection=(long) snapshot.getValue();
                    moneyTextView.setText("Rs. "+Long.toString(moneyCollection));
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                    Toast.makeText(MainActivity.this, "Database Error!!", Toast.LENGTH_SHORT).show();

                }
            });

            cansRef.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    long numOfCans=(long) snapshot.getValue();
                    //update the text with value from database
                    noOfCansTextView.setText(Long.toString(numOfCans));
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                    Toast.makeText(MainActivity.this, "Database Error!!", Toast.LENGTH_SHORT).show();

                }
            });
    }
}