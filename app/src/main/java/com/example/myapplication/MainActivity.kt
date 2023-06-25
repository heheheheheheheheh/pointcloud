package com.example.myapplication

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private var mGLRender : MyGLRender?=null
    private var mGLSurfaceView: MyGLSurfaceView? = null
    private var mData: FloatArray? = null
    private var mDataColor: FloatArray? = null
    private var mBounds:FloatArray = FloatArray(6){0.0f}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mGLSurfaceView = findViewById(R.id.mGLSurfaceView)
        mGLRender = mGLSurfaceView?.getRender()
        startRender.setOnClickListener {
            val thread = Thread(){
                getPointData()
                mGLRender?.setPointData(mData,mBounds)
                mGLRender?.setPointOtherData(mDataColor,3)
                mGLSurfaceView!!.requestRender()
                startRender.isEnabled = false;
            }
            thread.start()
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        mGLRender?.unInit()
    }

    //fixme:耗时操作
    fun getPointData() {
        if (mData == null) {
            val data = FileUtil.readPointCloud(this, "PointVoxel_3_1.txt",mBounds)
            mData = data.toFloatArray()
        }
        if(mDataColor == null){
            val dataColor = FileUtil.readPointCloudColor(this, "PointVoxelRGB_3.txt")
            mDataColor = dataColor.toFloatArray()
        }
    }
}