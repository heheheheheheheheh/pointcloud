package com.example.myapplication;

import android.opengl.GLSurfaceView;
import android.util.Log;
import org.jetbrains.annotations.Nullable;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRender implements GLSurfaceView.Renderer {
    private static final String TAG = "MyGLRender";
    private  MyNativeRender mNativeRender;

    MyGLRender() {
        mNativeRender = new  MyNativeRender();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mNativeRender.native_OnSurfaceCreated();
        Log.e(TAG, "onSurfaceCreated() called with: GL_VERSION = [" + gl.glGetString(GL10.GL_VERSION) + "]");
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mNativeRender.native_OnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        mNativeRender.native_OnDrawFrame();
    }

    public void init() {
        mNativeRender.native_Init();
    }

    public void unInit() {
        mNativeRender.native_UnInit();
    }

    public void updateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY)
    {
        mNativeRender.native_UpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
    }

    public void setPointData(@Nullable float[] pointData,float[] bounds) {
        mNativeRender.native_setPointData(pointData,bounds[0],bounds[1],bounds[2],bounds[3],bounds[4],bounds[5]);
    }
    public void setPointOtherData(@Nullable float[] pointData,int singleSize) {
        mNativeRender.native_setPointOtherData(pointData,singleSize);
    }
}
