package com.example.zoetechv10;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;



import android.os.Bundle;

import android.view.MenuItem;

import android.widget.Toast;

import com.google.android.material.navigation.NavigationView;



public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {



    DrawerLayout drawerLayout;
    Toolbar toolbar;
    NavigationView navigationView;

    //session time out



        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);

            //permission


            //start of toolbar
            toolbar = findViewById(R.id.toolbar);
            setSupportActionBar(toolbar);

            drawerLayout = findViewById(R.id.drawerLayout);
            navigationView = findViewById(R.id.nav);
            navigationView.setNavigationItemSelectedListener(this);


            //navigationBar
            ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawerLayout, toolbar, R.string.open, R.string.close);
            drawerLayout.addDrawerListener(toggle);
            toggle.syncState();

            if (savedInstanceState == null) {
                getSupportFragmentManager().beginTransaction().replace(R.id.frameLayout, new HomeFragment()).commit();
                navigationView.setCheckedItem(R.id.home);
            }
            //toggle.getDrawerArrowDrawable().setColor(getResources().getColor(R.color.white));
        }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()) {

            case R.id.home:
                fragmentR(new HomeFragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Home", Toast.LENGTH_SHORT).show();
                break;

            case R.id.function1:
                fragmentR(new Function1Fragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Function1", Toast.LENGTH_SHORT).show();
                break;
            case R.id.function2:
                fragmentR(new Function2Fragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Function2", Toast.LENGTH_SHORT).show();
                break;
            case R.id.function3:
                fragmentR(new Function3Fragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Function3", Toast.LENGTH_SHORT).show();
                break;
            case R.id.function4:
                fragmentR(new Function4Fragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Function4", Toast.LENGTH_SHORT).show();
                break;
            case R.id.function5:
                fragmentR(new Function5Fragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Function5", Toast.LENGTH_SHORT).show();
                break;
            case R.id.function6:
                fragmentR(new PriceSetFragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Today oil price", Toast.LENGTH_SHORT).show();
                break;
            case R.id.reportGen:
                fragmentR(new ReportFragment());
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Report Generate", Toast.LENGTH_SHORT).show();
                break;

            case R.id.messages:
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Messages", Toast.LENGTH_SHORT).show();
                break;

            case R.id.explore:
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Explore", Toast.LENGTH_SHORT).show();
                break;

            case R.id.comment:
                drawerLayout.closeDrawer(GravityCompat.START);
                Toast.makeText(MainActivity.this, "Comment", Toast.LENGTH_SHORT).show();
                break;

        }


        return true;
    }


    private void fragmentR(Fragment fragment){

        FragmentManager fragmentManager=getSupportFragmentManager();
        FragmentTransaction fragmentTransaction=fragmentManager.beginTransaction();
        fragmentTransaction.replace(R.id.frameLayout,fragment );
        fragmentTransaction.commit();

    }

}