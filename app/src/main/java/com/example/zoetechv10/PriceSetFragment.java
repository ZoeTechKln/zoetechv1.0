package com.example.zoetechv10;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;
import java.util.Map;

public class PriceSetFragment extends Fragment {

    private EditText priceEnterBox;
    private Button setPriceButton;

    private DatabaseReference priceSetRef;



    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view= inflater.inflate(R.layout.fragment_price_set, container, false);

        priceEnterBox=view.findViewById(R.id.priceEnterBox);
        setPriceButton=view.findViewById(R.id.setPriceButton);

        priceSetRef= FirebaseDatabase.getInstance().getReference("TodayOilPrice");

        setPriceButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String priceEntered=priceEnterBox.getText().toString().trim();
                if(TextUtils.isEmpty(priceEntered)) {
                    priceEnterBox.setError("Please enter a price");
                    return;

                }
                try{
                    double price = Double.parseDouble(priceEntered);

                    if (price < 0) {
                        priceEnterBox.setError("Price cannot be negative");
                        return;
                    }

                    //Map<String, Object> priceMap = new HashMap<>();
                    //priceMap.put("TodayOilPrice",price);
                    //priceMap.put("price", price);
                    priceSetRef.setValue(price);

                    Toast.makeText(getActivity(), "Price set to " + price, Toast.LENGTH_SHORT).show();

                }catch (NumberFormatException e){
                    priceEnterBox.setError("Invalid price format");

                }
            }
        });

        return view;
    }
}