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
//        mGLSurfaceView.setAspectRatio(mRootView.width, mRootView.height)
                mGLRender.init()
                mGLRender.setPointData(getPointData(),mBounds)
                mGLSurfaceView!!.requestRender()
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        mGLRender.unInit()
    }

    private var mData: FloatArray? = null
    private var mBounds:FloatArray = FloatArray(6){0.0f}
    fun getPointData():FloatArray? {
        if (mData == null) {
            val data = FileUtil.readPointCloud(this, "PointVoxel_3.txt",mBounds)
//            mData = data.toArray()
//            mData = arrayOf(data)
            //fixme://
            mData = data.toTypedArray().toFloatArray()
        }
        return mData
    }
}