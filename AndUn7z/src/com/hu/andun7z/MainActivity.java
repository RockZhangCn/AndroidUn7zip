package com.hu.andun7z;


import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import com.tencent.smtt.util.XZInputStream;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

	static
	{
		System.loadLibrary("un7z");
	}
	
	ProgressDialog dialog = null;
	EditText etFile = null;
	EditText etOut = null;
	Handler handler = null;
	Button btnSrc, btnDst, btnExecute;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		dialog = new ProgressDialog(this);
		dialog.setCancelable(false);
		dialog.setTitle(R.string.dialog_title);
		dialog.setMessage(getText(R.string.dialog_content));
		
		etFile = (EditText)findViewById(R.id.editText1);
		etOut = (EditText)findViewById(R.id.editText2);
		btnSrc = (Button) findViewById(R.id.button_src_file);
		btnDst = (Button) findViewById(R.id.button_out_path);
		btnExecute = (Button) findViewById(R.id.button1);
		
		handler = new Handler(new Handler.Callback() {
			@Override
			public boolean handleMessage(Message msg) {
				dialog.dismiss();
				return false;
			}
		});
		
		btnSrc.setOnClickListener(new OnClickListener() {
			@SuppressLint("SdCardPath")
			@Override
			public void onClick(View v) {
				File xzFile = new File("/sdcard/README.xz");
				InputStream in = null;
		        try {
		            Log.e("ROCKXZ", "My Test Here");
		            // 一次读一个字节
		            in = new FileInputStream(xzFile);
		            XZInputStream xzInput = new XZInputStream(in);
		            /*
		            byte[] buf = new byte[512];
		            xzInput.read(buf, 0, 512);
		            */
		            xzInput.close();
		            in.close();
		        } catch (IOException e) {
		            e.printStackTrace();
		            return;
		        }
			}
		});
		
		btnDst.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
	
			}
		});
		
		btnExecute.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				dialog.show();
				new Thread(){
					public void run() {
						handler.sendEmptyMessage(0);
					};
				}.start();
			}
		});
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
