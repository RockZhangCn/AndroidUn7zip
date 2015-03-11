package com.rock.jnitest;


import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import com.hu.andun7z.R;
import com.tencent.smtt.util.XZInputStream;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

@SuppressLint("SdCardPath")
public class MainActivity extends Activity {
	static
	{
		System.loadLibrary("un7z");
	}
	Button btnExecute;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		btnExecute = (Button) findViewById(R.id.button1);
		btnExecute.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				File xzFile = new File("/sdcard/README.xz");
				InputStream in = null;
		        try {
		            Log.e("ROCKXZ", "My Test Here");
		            // 一次读一个字节
		            in = new FileInputStream(xzFile);
		            XZInputStream xzInput = new XZInputStream(in);
		            Log.e("ROCKXZ", "After the constructor.");
		            byte[] buf = new byte[512];
		            xzInput.read(buf, 0, 512);
		            
		            xzInput.close();
		            in.close();
		        } catch (IOException e) {
		            e.printStackTrace();
		            return;
		        }
			}
		});
	}
}
