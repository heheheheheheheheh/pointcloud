/**
 *
 * Created by 公众号：字节流动 on 2021/3/12.
 * https://github.com/githubhaohao/NDK_OpenGLES_3_0
 * 最新文章首发于公众号：字节流动，有疑问或者技术交流可以添加微信 Byte-Flow ,领取视频教程, 拉你进技术交流群
 *
 * */

package com.example.myapplication;

public class MyNativeRender {
    public static final int SAMPLE_TYPE  =  200;
    public static final int SAMPLE_TYPE_SET_TOUCH_LOC           = SAMPLE_TYPE + 999;
    public static final int SAMPLE_TYPE_SET_GRAVITY_XY          = SAMPLE_TYPE + 1000;
    static {
        System.loadLibrary("native-render");
    }

    public native void native_Init();

    public native void native_UnInit();

//    public native void native_SetParamsInt(int paramType, int value0, int value1);

    public native void native_SetParamsFloat(int paramType, float value0, float value1);

    public native void native_UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

/*    public native void native_SetImageData(int format, int width, int height, byte[] bytes);

    public native void native_SetImageDataWithIndex(int index, int format, int width, int height, byte[] bytes);

    public native void native_SetAudioData(short[] audioData);*/

    public native void native_OnSurfaceCreated();

    public native void native_OnSurfaceChanged(int width, int height);

    public native void native_OnDrawFrame();
    public native void native_setPointData(float[] pointData,float minX,float minY,float minZ,float maxX,float maxY,float maxZ);
    public native void native_setPointOtherData(float[] pointData,int singleSize);
}
