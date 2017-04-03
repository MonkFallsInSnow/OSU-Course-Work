package com.cs496.osu.dream_catcher;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.speech.RecognizerIntent;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;


public class DisplaySpeechActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {

    private static final int SPEECH_REQUEST_CODE = 1;
    private static final String API_ADD_DREAM = "https://cs-496-hw4.appspot.com/dream-catcher/v1/accounts/users/dreams/queries/1";

    private EditText speechResults;
    private EditText detailsTitle;
    private Spinner detailsType;
    private String dreamType;
    private String dreamTitle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_HIDDEN);
        LoginActivity.session.checkLogin();
        setContentView(R.layout.activity_display_speech);

        switch (getResources().getConfiguration().orientation)
        {
            case Configuration.ORIENTATION_PORTRAIT:
                setContentView(R.layout.activity_display_speech);
                break;
        }

        Intent intent = getIntent();
        String summary = intent.getStringExtra(SpeechActivity.EXTRA_MESSAGE);

        speechResults = (EditText) findViewById(R.id.speechResults);
        speechResults.setText(summary);
        speechResults.setSelection(summary.length());

        dreamType = "None";
        dreamTitle = "None";
    }

    @Override
    protected  void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);

        if(requestCode == SPEECH_REQUEST_CODE)
        {
            if(resultCode == RESULT_OK && data != null)
            {
                ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                int pos = speechResults.getSelectionStart();
                speechResults.getText().insert(pos," " + result.get(0).toString());

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

    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id)
    {
        dreamType = parent.getItemAtPosition(pos).toString();
    }

    public void onNothingSelected(AdapterView<?> parent)
    {

    }

    protected void recordMore(View view)
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

    protected void addDetails(View view)
    {
        dialogInit().create().show();
    }

    protected void saveSummary(View view)
    {
        if(speechResults.getText().length() > 0)
        {
            final RequestQueue queue = Volley.newRequestQueue(this);

            JSONObject req = new JSONObject();

            try
            {
                req.put("summary", speechResults.getText());
                req.put("account", LoginActivity.session.getUserDetails().get(SessionController.KEY_ACCOUNT));
                req.put("user", LoginActivity.session.getUserDetails().get(SessionController.KEY_USER));
                req.put("type", dreamType);
                req.put("title", dreamTitle);
            }
            catch (JSONException e)
            {
                e.printStackTrace();
            }

            JsonObjectRequest jsReq = new JsonObjectRequest(Request.Method.POST, API_ADD_DREAM, req,
                    new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try
                            {
                                Toast.makeText(getApplicationContext(), response.getString("message"), Toast.LENGTH_LONG).show();
                            }
                            catch (JSONException e)
                            {
                                e.printStackTrace();

                            }

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError e) {
                    e.printStackTrace();
                    Toast.makeText(getApplicationContext(), "Unable to save summary. Try again.", Toast.LENGTH_SHORT).show();

                }
            });

            jsReq.setShouldCache(false);
            queue.add(jsReq);

            Intent intent = new Intent(this, OptionsActivity.class);
            startActivity(intent);
            finish();
        }
        else
        {
            Toast.makeText(getApplicationContext(), "Cannot save an empty description", Toast.LENGTH_SHORT).show();
        }
    }

    private AlertDialog.Builder dialogInit()
    {
        LayoutInflater inflater = LayoutInflater.from(this);
        View v = inflater.inflate(R.layout.edit_details_layout, null);

        AlertDialog.Builder dialogBuilder = new AlertDialog.Builder(this);
        dialogBuilder.setTitle("Dream Details");
        dialogBuilder.setView(v);

        detailsType = (Spinner) v.findViewById(R.id.dreamTypeSelector);
        detailsTitle = (EditText) v.findViewById(R.id.dreamDetailsTitle);

        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.dreamTypes, R.layout.spinner_layout);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        detailsType.setAdapter(adapter);
        detailsType.setOnItemSelectedListener(this);

        dialogBuilder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                if(!detailsTitle.getText().toString().equals(""))
                {
                    dreamTitle = detailsTitle.getText().toString();
                }
                else
                {
                    dreamTitle = "None";
                }
            }
        });

        dialogBuilder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                dreamTitle = "None";
                dreamType = "None";
            }
        });

        return dialogBuilder;
    }
}
