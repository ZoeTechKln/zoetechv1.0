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

    TextView totalMoneyTextView,totalOilAmountTextView,todayOilPriceTextView,remainingOilTextView,totalEmergencyOilTextView;


    public HomeFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_home, container, false);

        todayOilPriceTextView = (TextView) view.findViewById(R.id.todayOilPrice);
        remainingOilTextView=(TextView) view.findViewById(R.id.Remaining_Oil_Amount);
        totalOilAmountTextView = (TextView) view.findViewById(R.id.oilAmount);
        totalMoneyTextView = (TextView) view.findViewById(R.id.totalMoney);
        totalEmergencyOilTextView=(TextView) view.findViewById(R.id.emergencyOil);


        //firebaseToApp
        FirebaseDatabase database = FirebaseDatabase.getInstance();

        DatabaseReference todayOilPriceRef = database.getReference("TodayOilPrice");
        DatabaseReference remainingOilRef = database.getReference("RemainingOil");
        DatabaseReference totalOilAmountRef = database.getReference("TotalOilAmount");
        DatabaseReference totalMoneyRef = database.getReference("TotalMoney");
        DatabaseReference totalEmergencyOilAmountRef = database.getReference("TotalEmergencyOil");

        todayOilPriceRef.addValueEventListener(new ValueEventListener() {
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
        remainingOilRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long remainingOilAmount = (long) snapshot.getValue();
                remainingOilTextView.setText(Long.toString(remainingOilAmount)+" Kg");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                remainingOilTextView.setText("Error!!");
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        totalOilAmountRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long totalOilAmount = (long) snapshot.getValue();
                totalOilAmountTextView.setText(Long.toString(totalOilAmount)+" Kg");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        totalMoneyRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long totalMoney = (long) snapshot.getValue();
                totalMoneyTextView.setText("Rs. "+Long.toString(totalMoney));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });

        totalEmergencyOilAmountRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                long totalEmergencyOil = (long) snapshot.getValue();
                totalEmergencyOilTextView.setText(Long.toString(totalEmergencyOil)+" Kg");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(getActivity(), "Database Error!!", Toast.LENGTH_SHORT).show();

            }
        });
        return view;
    }
}