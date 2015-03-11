package com.hu.andun7z;


import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

	static
	{
		System.loadLibrary("browsertest");
	}
	
    public static native void c(String s);
    public static native void p();
    public static native void r();
    public static native void d();

    public static native void sc();
    public static native void sc(int w, int h);

    public static native void t(int a, float x, float y);
    public static native void a(String p);

    public static native void df();
	
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
			@Override
			public void onClick(View v) {
				
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
						AndUn7z.extract7z(etFile.getText().toString(), etOut.getText().toString());
						//AndUn7z.extractAssets(MainActivity.this, etFile.getText().toString(), etOut.getText().toString());
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
