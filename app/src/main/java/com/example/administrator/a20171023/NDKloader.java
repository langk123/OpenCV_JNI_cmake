package com.example.administrator.a20171023;

/**
 * Created by Administrator on 2017/10/23.
 */

public class NDKloader {

    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("opencv_java3");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    //图像处理
    public static native int[] getGrayImage(int[] pixels, int w, int h);
}
