package com.example.myapplication

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private var mGLRender: MyGLRender? = null
    private var mGLSurfaceView: MyGLSurfaceView? = null

    //储存点的坐标数据
    private var mData: FloatArray? = null

    //储存点的颜色数据
    private var mDataColor: FloatArray? = null

    //点是最大最小xyz值
    private var mBounds: FloatArray = FloatArray(6) { 0.0f }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mGLSurfaceView = findViewById(R.id.mGLSurfaceView)
        mGLRender = mGLSurfaceView?.getRender()
        val thread = Thread() {
            var intLoop = 0
            while (true) {
                getPointData(intLoop)
                mGLRender?.setPointData(mData, mBounds)
                mGLRender?.setPointOtherData(mDataColor, 3)
                //通知view执行渲染
                mGLSurfaceView!!.requestRender()
                intLoop++
                Thread.sleep(100)
            }
        }
        thread.start()
    }

    override fun onDestroy() {
        super.onDestroy()
        mGLRender?.unInit()
    }

    //fixme:耗时操作
    fun getPointData() {
        if (mData == null) {
            val data = FileUtil.readPointCloud(this, "PointVoxel_3_1.txt", mBounds)
            mData = data.toFloatArray()
        }
        if (mDataColor == null) {
            val dataColor = FileUtil.readPointCloudColor(this, "PointVoxelRGB_3.txt")
            mDataColor = dataColor.toFloatArray()
        }
    }

    fun getPointData(loop: Int) {
//        if (mData == null) {
            val data = FileUtil.readPointCloud(this, "PointVoxel_3_1.txt", mBounds)
            mData = data.toFloatArray()
//        }
//        if (mDataColor == null) {
            val dataColor = FileUtil.readPointCloudColor(this, "PointVoxelRGB_3.txt", loop)
            mDataColor = dataColor.toFloatArray()
//        }
    }
}