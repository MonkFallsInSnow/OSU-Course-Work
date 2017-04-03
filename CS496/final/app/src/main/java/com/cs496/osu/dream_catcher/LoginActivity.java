package com.cs496.osu.dream_catcher;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.Scopes;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.Scope;

import org.json.JSONException;
import org.json.JSONObject;


public class LoginActivity extends AppCompatActivity implements
        GoogleApiClient.OnConnectionFailedListener,
        View.OnClickListener{

    private static final String TAG = "SignInActivity";
    private static final int SIGN_IN_RESULT_CODE = 1;
    private static final String API_LOGIN = "https://cs-496-hw4.appspot.com/dream-catcher/v1/user/login";

    private Intent optionsIntent;
    public GoogleApiClient mGoogleApiClient;
    public static SessionController session;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        findViewById(R.id.signInBtn).setOnClickListener(this);

        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestScopes(new Scope(Scopes.PLUS_LOGIN))
                .requestEmail()
                .requestIdToken(getString(R.string.serverClientID))
                .build();

        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .enableAutoManage(this, this)
                .addApi(Auth.GOOGLE_SIGN_IN_API, gso)
                .build();

        session = new SessionController(getApplicationContext());
    }


    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {

    }

    @Override
    public void onClick(View view)
    {
        if (view.getId() == R.id.signInBtn)
        {
            signIn();
        }
    }

    @Override
    public void onBackPressed()
    {
        new AlertDialog.Builder(this)
                .setTitle("Exit Application")
                .setMessage("Are you sure you want exit Dreamcatcher?")
                .setPositiveButton(android.R.string.yes, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int choice) {
                        System.exit(0);
                    }
                })
                .setNegativeButton(android.R.string.no, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int choice) {
                        // do nothing
                    }
                })
                .setIcon(android.R.drawable.ic_dialog_alert)
                .show();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == SIGN_IN_RESULT_CODE)
        {
            GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
            handleSignInResult(result);

            if(resultCode == RESULT_OK && data != null)
            {
                optionsIntent = new Intent(this,OptionsActivity.class);
            }
            else
            {
                Context context = getApplicationContext();
                CharSequence msg = "Invalid credentials recieved";
                Toast toast = Toast.makeText(context,msg,Toast.LENGTH_SHORT);
                toast.show();
            }
        }
    }

    private void signIn()
    {
        session.logoutUser(false);

        if (mGoogleApiClient.isConnected())
        {
            mGoogleApiClient.clearDefaultAccountAndReconnect();
        }
        else
        {
            mGoogleApiClient.connect();
        }

        Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mGoogleApiClient);
        startActivityForResult(signInIntent, SIGN_IN_RESULT_CODE);
    }

    private void handleSignInResult(GoogleSignInResult result)
    {
        Log.d(TAG, "handleSignInResult:" + result.isSuccess());
        if (result.isSuccess())
        {
            GoogleSignInAccount account = result.getSignInAccount();
            String idToken = account.getIdToken();
            validateToken(idToken);
        }
        else
        {
            Toast.makeText(getApplicationContext(), "Sign in failed", Toast.LENGTH_SHORT).show();
        }
    }

    private void validateToken(String token)
    {
        RequestQueue queue = Volley.newRequestQueue(this);

        JSONObject req = new JSONObject();

        try
        {
            req.put("token", token);
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }

        JsonObjectRequest jsReq = new JsonObjectRequest(Request.Method.POST, API_LOGIN,req,
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        try
                        {
                            String name = response.getString("fname") + " " + response.getString("lname");
                            session.createLoginSession(name,response.getString("email"),
                                    response.getString("account"),response.getString("user"));
                            Toast.makeText(getApplicationContext(),"Signed in as: " + response.getString("email"),
                                    Toast.LENGTH_SHORT).show();
                            startActivity(optionsIntent);
                            finish();
                        }
                        catch (JSONException e)
                        {
                            e.printStackTrace();
                            Toast.makeText(getApplicationContext(),"Unable to sign in. Try again.", Toast.LENGTH_SHORT).show();
                        }

                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError e) {
                e.printStackTrace();
            }
        });

        jsReq.setShouldCache(false);
        queue.add(jsReq);
    }
}
