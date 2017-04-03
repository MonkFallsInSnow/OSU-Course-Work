package com.cs496.osu.dream_catcher;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.speech.RecognizerIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import java.util.ArrayList;

public class SpeechActivity extends AppCompatActivity {

    public final static String EXTRA_MESSAGE = "com.example.dream_catcher.MESSAGE";
    protected static final int SPEECH_REQUEST_CODE = 1;

    private ImageButton recordBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        LoginActivity.session.checkLogin();

        switch (getResources().getConfiguration().orientation)
        {
            case Configuration.ORIENTATION_PORTRAIT:
                setContentView(R.layout.activity_speech);
                break;
            case Configuration.ORIENTATION_LANDSCAPE:
                setContentView(R.layout.activity_speech_landscape);
                break;
            default:
                setContentView(R.layout.activity_speech);
        }

        recordBtn = (ImageButton) findViewById(R.id.recordBtn);
    }

    protected void recordSpeech(View view)
    {
        Intent speechIntent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        speechIntent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,"en-US");

        try
        {
            startActivityForResult(speechIntent,SPEECH_REQUEST_CODE);
        }
        catch(ActivityNotFoundException e)
        {
            Context context = getApplicationContext();
            CharSequence msg = "Your device does not support speech to text.";
            Toast toast = Toast.makeText(context,msg,Toast.LENGTH_SHORT);
            toast.show();
        }
    }

    @Override
    protected  void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);

        Intent displaySpeechIntent = new Intent(this,DisplaySpeechActivity.class);

        if(requestCode == SPEECH_REQUEST_CODE)
        {
            if(resultCode == RESULT_OK && data != null)
            {
                ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                displaySpeechIntent.putExtra(EXTRA_MESSAGE,result.get(0).toString());
                startActivity(displaySpeechIntent);
            }
            else
            {
                Context context = getApplicationContext();
                CharSequence msg = "Unable to record your description. Try again.";
                Toast toast = Toast.makeText(context,msg,Toast.LENGTH_SHORT);
                toast.show();
            }
        }
    }
}
