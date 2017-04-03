package com.cs496.osu.dream_catcher;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
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

import java.util.Arrays;

public class ViewPageActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener{

    private static final String API_UPDATE_DREAM = "https://cs-496-hw4.appspot.com/dream-catcher/v1/accounts/users/dreams/queries/2";

    private EditText titleView;
    private EditText summaryView;
    private Spinner typeSpinner;
    private String dreamType;
    private String dreamId;
    private String dreamDate;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_page);
        titleView = (EditText) findViewById(R.id.dreamTitle);
        summaryView = (EditText) findViewById(R.id.speechResults);

        typeSpinner = (Spinner) findViewById(R.id.dreamTypeSelector);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.dreamTypes, R.layout.spinner_layout_2);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        typeSpinner.setAdapter(adapter);
        typeSpinner.setOnItemSelectedListener(this);
        getDream();
    }

    @Override
    public void onBackPressed()
    {
        super.onBackPressed();
        Intent intent = new Intent(this,ViewDreamsActivity.class);
        startActivity(intent);
        finish();
    }

    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id)
    {
        dreamType = parent.getItemAtPosition(pos).toString();
    }

    public void onNothingSelected(AdapterView<?> parent)
    {

    }

    private void getDream()
    {
        Intent intent = getIntent();
        String[] types = getResources().getStringArray(R.array.dreamTypes);
        int pos = Arrays.asList(types).indexOf(intent.getStringExtra("type"));

        titleView.setText(intent.getStringExtra("title"));
        summaryView.setText(intent.getStringExtra("summary"));
        typeSpinner.setSelection(pos);
        dreamType = intent.getStringExtra("type");
        dreamId = intent.getStringExtra("id");
        dreamDate = intent.getStringExtra("date");
    }

    protected void updateDream(View view) {
        if (summaryView.getText().length() > 0 && titleView.getText().length() > 0)
        {
            final RequestQueue queue = Volley.newRequestQueue(this);
            JSONObject req = new JSONObject();

            try
            {
                req.put("summary", summaryView.getText());
                req.put("type", dreamType);
                req.put("title",titleView.getText());
                req.put("account", LoginActivity.session.getUserDetails().get(SessionController.KEY_ACCOUNT));
                req.put("user", LoginActivity.session.getUserDetails().get(SessionController.KEY_USER));
                req.put("dream",dreamId);
                req.put("date",dreamDate);
            }
            catch (JSONException e)
            {
                e.printStackTrace();
            }

            JsonObjectRequest jsReq = new JsonObjectRequest(Request.Method.PUT, API_UPDATE_DREAM, req,
                    new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try
                            {
                                Toast.makeText(getApplicationContext(), response.getString("message"), Toast.LENGTH_SHORT).show();
                                returnToList();
                            }
                            catch (JSONException e)
                            {
                                e.printStackTrace();
                                Toast.makeText(getApplicationContext(), "Unable to update dream. Try again.", Toast.LENGTH_SHORT).show();
                            }

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError e) {
                    e.printStackTrace();
                    Toast.makeText(getApplicationContext(), "Unable to update summary. Try again.", Toast.LENGTH_SHORT).show();

                }
            });

            jsReq.setShouldCache(false);
            queue.add(jsReq);
        }
        else
        {
            Toast.makeText(getApplicationContext(), "Cannot save an empty description", Toast.LENGTH_SHORT).show();
        }
    }

    protected void removeDream(View view)
    {
        String url = "https://cs-496-hw4.appspot.com/dream-catcher/v1/accounts/" +
                LoginActivity.session.getUserDetails().get(SessionController.KEY_ACCOUNT) + "/users/" +
                LoginActivity.session.getUserDetails().get(SessionController.KEY_USER) + "/dreams/" +
                dreamId;

        final RequestQueue queue = Volley.newRequestQueue(this);

        JSONObject req = new JSONObject();

        JsonObjectRequest jsReq = new JsonObjectRequest(Request.Method.DELETE, url,(String) null,
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        try
                        {
                            Toast.makeText(getApplicationContext(),response.getString("message"), Toast.LENGTH_SHORT).show();
                            returnToList();
                        }
                        catch (JSONException e)
                        {
                            e.printStackTrace();
                            Toast.makeText(getApplicationContext(),"Unable to delete dream. Try again.", Toast.LENGTH_LONG).show();
                        }

                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError e) {
                e.printStackTrace();
                Toast.makeText(getApplicationContext(),"Unable to delete summary. Try again.", Toast.LENGTH_LONG).show();

            }
        });

        jsReq.setShouldCache(false);
        queue.add(jsReq);
    }

    private void returnToList()
    {
        Intent intent = new Intent(this,ViewDreamsActivity.class);
        startActivity(intent);
        finish();
    }
}


