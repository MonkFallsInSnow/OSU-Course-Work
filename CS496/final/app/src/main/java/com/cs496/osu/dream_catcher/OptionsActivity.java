package com.cs496.osu.dream_catcher;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class OptionsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LoginActivity.session.checkLogin();
        setContentView(R.layout.activity_options);

    }

    @Override
    public void onBackPressed()
    {
        //pass
    }

    protected void getSpeech(View view)
    {
        Intent intent = new Intent(this,SpeechActivity.class);
        startActivity(intent);
    }

    protected void getDreams(View view)
    {
        Intent intent = new Intent(this,ViewDreamsActivity.class);
        startActivity(intent);
    }

    protected void getReport(View view)
    {
        Intent intent = new Intent(this,DreamReportActivity.class);
        startActivity(intent);
    }

    protected void signOutApp(View view)
    {
        LoginActivity.session.logoutUser(true);
        finish();
    }
}
