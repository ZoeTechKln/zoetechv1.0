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

import java.util.Objects;


public class HomeFragment extends Fragment {

    TextView moneyTextView,noOfCansTextView,todayOilPriceTextView,oilTextView,emergencyOilTextView;


    public HomeFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_home, container, false);

        moneyTextView = (TextView) view.findViewById(R.id.totalMoney);
        noOfCansTextView = (TextView) view.findViewById(R.id.canAmount);
        todayOilPriceTextView = (TextView) view.findViewById(R.id.todayOilPrice);
        oilTextView=(TextView) view.findViewById(R.id.Remaining_Oil_Amount);
        emergencyOilTextView=(TextView) view.findViewById(R.id.emergencyOil);


        //firebaseToApp
        FirebaseDatabase database = FirebaseDatabase.getInstance();
//can amount eka wadak nee
        DatabaseReference cansRef = database.getReference("Function_1/CanAmount");
        DatabaseReference moneyCol = database.getReference("Function_1/Price");
        DatabaseReference todayOilPrice = database.getReference("TodayOilPrice");


        todayOilPrice.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long todayOilPrice = (long) snapshot.getValue();
                todayOilPriceTextView.setText("Rs. " + Long.toString(todayOilPrice));

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });
        moneyCol.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long moneyCollection = (long) snapshot.getValue();
                moneyTextView.setText("Rs. " + Long.toString(moneyCollection));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        cansRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long numOfCans = (long) snapshot.getValue();
                //update the text with value from database
                noOfCansTextView.setText(Long.toString(numOfCans));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });
        return view;
    }
}