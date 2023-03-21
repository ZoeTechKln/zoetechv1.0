package com.example.zoetechv10;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    CardView cardPrice_per_1kg,cardNumber_of_Cans,cardRemaining_Oil_Amount,cardMoney;

    //TextView noOfCans,collectedMoney;


        protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        cardPrice_per_1kg = findViewById(R.id.cardPrice_per_1kg);
        cardNumber_of_Cans = findViewById(R.id.cardNumber_of_Cans);
        cardRemaining_Oil_Amount = findViewById(R.id.cardRemaining_Oil_Amount);
        cardMoney = findViewById(R.id.cardMoney);
        //firebaseToApp
            FirebaseDatabase database =FirebaseDatabase.getInstance();
            DatabaseReference cansRef=database.getReference("canAmount");
            DatabaseReference moneyCol=database.getReference("money");

            moneyCol.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    long moneycollection=(long) snapshot.getValue();
                    TextView moneyTextView=findViewById(R.id.);
                    moneyTextView.setText(Long.toString(moneycollection));
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {

                }
            });

            cansRef.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    long numOfCans=(long) snapshot.getValue();
                    //update the text with value from database
                    TextView noOfCansTextView=findViewById(R.id.numberOfCans);
                    noOfCansTextView.setText(Long.toString(numOfCans));
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                    Toast.makeText(MainActivity.this, "Database Error!!", Toast.LENGTH_SHORT).show();

                }
            });
        //noOfCans=(TextView) findViewById(R.id.numberOfCans);
        //collectedMoney=(TextView) findViewById(R.id.Collected_Money);







    }
}