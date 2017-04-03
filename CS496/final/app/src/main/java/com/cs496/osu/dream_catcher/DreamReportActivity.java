package com.cs496.osu.dream_catcher;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.webkit.JavascriptInterface;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;

import java.util.HashMap;

public class DreamReportActivity extends AppCompatActivity {

    private HashMap<String,Integer> typeMap = new HashMap<String,Integer>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LoginActivity.session.checkLogin();
        setContentView(R.layout.activity_dream_report);

        getDreams();

        WebView webview = (WebView) findViewById(R.id.reportView);
        webview.addJavascriptInterface(new ChartData(),"ChartData");

        WebSettings webSettings = webview.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setBuiltInZoomControls(true);
        webview.loadUrl("file:///android_asset/html/chart.html");
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
                            JSONArray dreams = response;
                            int dataLen = dreams.length();

                            if(dataLen > 0)
                            {
                                for (int i = 0; i < dataLen; i++)
                                {
                                    String curType = dreams.getJSONObject(i).getString("dreamType");

                                    if (!typeMap.containsKey(curType))
                                    {
                                        typeMap.put(curType, 1);
                                    }
                                    else
                                    {
                                        int count = typeMap.get(curType);
                                        typeMap.put(curType, ++count);
                                    }
                                }
                            }
                            else
                            {
                                Toast.makeText(getApplicationContext(),"No dream data", Toast.LENGTH_SHORT).show();
                            }

                        }
                        catch (Exception e)
                        {
                            e.printStackTrace();
                        }

                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError e) {
                Toast.makeText(getApplicationContext(),"Unable to get dream data", Toast.LENGTH_SHORT).show();
            }
        });

        jsReq.setShouldCache(false);
        queue.add(jsReq);
    }

    public class ChartData
    {
        @JavascriptInterface
        public String getData()
        {
            int count = 0;
            String str = "{";

            for(String key : typeMap.keySet())
            {
                if(count != typeMap.size() - 1)
                {
                    str += "\"" + key + "\":\"" + typeMap.get(key) + "\",";
                }
                else
                {
                    str += "\"" + key + "\":\"" + typeMap.get(key) + "\"";
                }

                count++;
            }

            str += "}";
            return str;
        }
    }
}
