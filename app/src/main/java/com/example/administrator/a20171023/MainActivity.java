package com.example.administrator.a20171023;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

    public class MainActivity extends AppCompatActivity {

        private ImageView show_image;
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);
            initView();
        }

        private void initView() {
            show_image = (ImageView) findViewById(R.id.show_image);
            show_image.setImageResource(R.drawable.cat);
            findViewById(R.id.pic).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    //恢复
                    backPic();
                }
            });
            findViewById(R.id.gray_pic).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    //变灰
                    grayPic();
                }
            });
        }
        private void backPic(){
            show_image.setImageResource(R.drawable.cat);
        }
        private void grayPic(){
            Bitmap bmp = BitmapFactory.decodeResource(getResources(),R.drawable.cat);
            int w = bmp.getWidth();
            int h = bmp.getHeight();
            int[] pixels = new int[w*h];
            bmp.getPixels(pixels, 0, w, 0, 0, w, h);
            //recall JNI
            int[] resultInt = NDKloader.getGrayImage(pixels, w, h);
            Bitmap resultImg = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
            resultImg.setPixels(resultInt, 0, w, 0, 0, w, h);
            show_image.setImageBitmap(resultImg);
        }


    }

