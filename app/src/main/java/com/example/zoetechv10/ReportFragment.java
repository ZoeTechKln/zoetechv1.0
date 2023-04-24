package com.example.zoetechv10;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;

import com.itextpdf.text.Document;
import com.itextpdf.text.DocumentException;
import com.itextpdf.text.Paragraph;
import com.itextpdf.text.pdf.PdfWriter;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class ReportFragment extends Fragment {

    private static final int PERMISSION_REQUEST_CODE = 101;

    private Button reportGenBtn;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_report, container, false);

        reportGenBtn = view.findViewById(R.id.reportGenButton);

        reportGenBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                    // Check if write permission is granted
                    if (ContextCompat.checkSelfPermission(requireContext(),
                            Manifest.permission.WRITE_EXTERNAL_STORAGE)
                            != PackageManager.PERMISSION_GRANTED) {
                        // Permission not granted, request it
                        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                                PERMISSION_REQUEST_CODE);
                    } else {
                        // Permission already granted, create and save the PDF
                        createMyPDF2();
                    }
                } else {
                    // Pre-Marshmallow, create and save the PDF
                    createMyPDF2();
                }
            }
        });

        return view;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == PERMISSION_REQUEST_CODE) {
            // Check if permission is granted
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // Permission granted, create and save the PDF
                createMyPDF2();
            } else {
                // Permission not granted, show a message or do something else
                Toast.makeText(requireContext(), "Permission denied", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void createMyPDF2() {
        if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            // Permission is not granted, request for the permission
            ActivityCompat.requestPermissions(getActivity(),
                    new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                    PERMISSION_REQUEST_CODE);
            return;
        }
        // Permission is granted, continue with PDF creation and saving
        try {
            String FILE_NAME = "mypdf.pdf";
            File folder = new File(getActivity().getFilesDir() + "/PDF");
            boolean success = true;
            if (!folder.exists()) {
                success = folder.mkdir();
            }
            if (success) {
                File file = new File(getActivity().getFilesDir() + "/PDF/" + FILE_NAME);
                if (!file.exists()) {
                    success = file.createNewFile();
                }
                if (success) {
                    // PDF creation and saving code goes here
                    Document document = new Document();
                    PdfWriter.getInstance(document, new FileOutputStream(file));
                    document.open();
                    document.add(new Paragraph("Hello World!"));
                    document.close();
                    Toast.makeText(getActivity(), "PDF created and saved successfully!", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(getActivity(), "PDF file creation failed!", Toast.LENGTH_SHORT).show();
                }
            } else {
                Toast.makeText(getActivity(), "PDF folder creation failed!", Toast.LENGTH_SHORT).show();
            }
        } catch (IOException | DocumentException e) {
            e.printStackTrace();
        }
    }


}

