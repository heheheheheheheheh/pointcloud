package com.example.myapplication

import android.opengl.GLSurfaceView
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.ViewGroup
import android.widget.RelativeLayout
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private val mGLRender = MyGLRender()
    private var mGLSurfaceView: MyGLSurfaceView? = null
    private var mData: FloatArray? = null
    private var mDataColor: FloatArray? = null
    private var mBounds:FloatArray = FloatArray(6){0.0f}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val lp = RelativeLayout.LayoutParams(
            ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT
        )
        lp.addRule(RelativeLayout.CENTER_IN_PARENT)
        startRender.setOnClickListener {
            if (mGLSurfaceView == null) {
                mGLSurfaceView = MyGLSurfaceView(this, mGLRender)
                mRootView.addView(mGLSurfaceView, lp)
                mGLSurfaceView!!.renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
//        mGLSurfaceView.renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY
                getPointData()
                //fixme:耗时操作
                mGLRender.setPointData(mData,mBounds)
                mGLRender.setPointOtherData(mDataColor,3)
                Thread.sleep(100)
                mGLSurfaceView!!.requestRender()
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        mGLRender.unInit()
    }

    //fixme:耗时操作 子线程
    fun getPointData() {
        if (mData == null) {
            val data = FileUtil.readPointCloud(this, "PointVoxel_3_1.txt",mBounds)
            //fixme://减少转换次数
            mData = data.toTypedArray().toFloatArray()
        }
        if(mDataColor == null){
            val dataColor = FileUtil.readPointCloudColor(this, "PointVoxelRGB_3.txt")
            mDataColor = dataColor.toTypedArray().toFloatArray()
        }
    }
}