package com.cs496.osu.dream_catcher;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

public class ViewDreamsActivity extends AppCompatActivity{

    private ListView listView;
    private JSONArray dreams;
    private ArrayList<String> dreamLabels = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_HIDDEN);
        LoginActivity.session.checkLogin();
        setContentView(R.layout.activity_view_dreams);

        listView = (ListView) findViewById(R.id.dreamList);
        getDreams();
    }

    private void getDreams()
    {
        String accId = LoginActivity.session.getUserDetails().get(SessionController.KEY_ACCOUNT);
        String userId = LoginActivity.session.getUserDetails().get(SessionController.KEY_USER);
        String url = "https://cs-496-hw4.appspot.com/dream-catcher/v1/accounts/" +
                accId + "/users/" + userId + "/dreams";

        final RequestQueue queue = Volley.newRequestQueue(this);

        JsonArrayRequest jsReq = new JsonArrayRequest(Request.Method.GET, url,(String) null,
                new Response.Listener<JSONArray>() {
                    @Override
                    public void onResponse(JSONArray response) {
                        try
                        {
                            dreams = response;
                            for(int i = 0; i < dreams.length(); i++)
                            {
                                dreamLabels.add(dreams.getJSONObject(i).getString("date") + "     " +
                                        dreams.getJSONObject(i).getString("title"));
                            }
                            showDreams(dreamLabels);
                        }
                        catch (Exception e)
                        {
                            e.printStackTrace();
                        }

                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError e) {
                Toast.makeText(getApplicationContext(),"No dreams to view.", Toast.LENGTH_SHORT).show();
            }
        });

        jsReq.setShouldCache(false);
        queue.add(jsReq);
    }

    private void showDreams(ArrayList<String> labels)
    {
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.list_item_layout, labels);
        listView.setAdapter(adapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent = new Intent(view.getContext(),ViewPageActivity.class);

                try
                {
                    JSONObject curDream = dreams.getJSONObject(position);
                    intent.putExtra("title", curDream.getString("title"));
                    intent.putExtra("summary", curDream.getString("summary"));
                    intent.putExtra("type", curDream.getString("dreamType"));
                    intent.putExtra("id",curDream.getString("dream"));
                    intent.putExtra("date",curDream.getString("date"));
                }
                catch (JSONException e)
                {
                    Toast.makeText(getApplicationContext(),"Unable to select dream", Toast.LENGTH_SHORT).show();
                }

                startActivity(intent);
                finish();
            }
        });
    }
}
