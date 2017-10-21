package com.androidmka.webview;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    WebView webView;
    Button im;
    TextView tv;
    @Override
   public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
tv =(TextView)findViewById(R.id.tv);
        im =(Button) findViewById(R.id.swipe);
        //swipe = (Button) findViewById(R.id.swipe);

        im.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                webView = (WebView) findViewById(R.id.webview);
                webView.getSettings().setJavaScriptEnabled(true);
                webView.getSettings().setAppCacheEnabled(true);
                webView.loadUrl("http://192.168.4.1");
             


            }
        });


    }




    @Override
    public void onBackPressed(){

        if (webView.canGoBack()){
            webView.goBack();
        }else {
            finish();
        }
    }
}
