package com.example.zoetechv10;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class Function5Fragment extends Fragment {

    TextView canAmountTextView,oilAmountTextView,moneyTextView,emergencyTextView;

    public Function5Fragment() {
        // Required empty public constructor
    }



    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_function5, container, false);

        canAmountTextView = (TextView) view.findViewById(R.id.Func5canAmount);
        oilAmountTextView=(TextView)view.findViewById(R.id.Func5OilAmount);
        moneyTextView = (TextView) view.findViewById(R.id.Func5Money);
        emergencyTextView = (TextView) view.findViewById(R.id.Func5emergencyOil);


        //firebaseToApp
        FirebaseDatabase database = FirebaseDatabase.getInstance();

        DatabaseReference cansAmountRef = database.getReference("Function_5/CanAmount");
        DatabaseReference oilAmountRef=database.getReference("Function_5/OilAmount");
        DatabaseReference priceRef = database.getReference("Function_5/Price");
        DatabaseReference emergencyOilRef = database.getReference("Function_5/EmergencyOil");




        cansAmountRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long func1canAmount = (long) snapshot.getValue();
                //update the text with value from database
                canAmountTextView.setText(Long.toString(func1canAmount));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        oilAmountRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long func1oilAmount = (long) snapshot.getValue();
                //update the text with value from database
                oilAmountTextView.setText(Long.toString(func1oilAmount)+" Kg");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        priceRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long func1Money = (long) snapshot.getValue();
                moneyTextView.setText("Rs. " + Long.toString(func1Money));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        emergencyOilRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long func1emergencyOil = (long) snapshot.getValue();
                //update the text with value from database
                emergencyTextView.setText(Long.toString(func1emergencyOil)+" Kg");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });


        return view;
    }
}