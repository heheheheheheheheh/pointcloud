//
// Created by ByteFlow on 2019/7/9.
//
#include "util/LogUtil.h"
#include <MyGLRenderContext.h>
#include <EGLRender.h>
#include "jni.h"

#define NATIVE_RENDER_CLASS_NAME "com/example/myapplication/MyNativeRender"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_Init
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_Init(JNIEnv *env, jobject instance)
{
	MyGLRenderContext::GetInstance();

}

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_UnInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_UnInit(JNIEnv *env, jobject instance)
{
	MyGLRenderContext::DestroyInstance();
}

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_SetParamsInt
 * Signature: (III)V
 */
/*JNIEXPORT void JNICALL native_SetParamsInt
		(JNIEnv *env, jobject instance, jint paramType, jint value0, jint value1)
{
	MyGLRenderContext::GetInstance()->SetParamsInt(paramType, value0, value1);
}*/

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_SetParamsFloat
 * Signature: (IFF)V
 */
/*JNIEXPORT void JNICALL native_SetParamsFloat
		(JNIEnv *env, jobject instance, jint paramType, jfloat value0, jfloat value1)
{
	MyGLRenderContext::GetInstance()->SetParamsFloat(paramType, value0, value1);
}*/

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_UpdateTransformMatrix
 * Signature: (FFFF)V
 */
JNIEXPORT void JNICALL native_UpdateTransformMatrix(JNIEnv *env, jobject instance, jfloat rotateX, jfloat rotateY, jfloat scaleX, jfloat scaleY)
{
	MyGLRenderContext::GetInstance()->UpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
}

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_OnSurfaceCreated
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_OnSurfaceCreated(JNIEnv *env, jobject instance)
{
	MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_OnSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL native_OnSurfaceChanged
(JNIEnv *env, jobject instance, jint width, jint height)
{
	MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);

}

/*
 * Class:     com_byteflow_app_MyNativeRender
 * Method:    native_OnDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_OnDrawFrame(JNIEnv *env, jobject instance)
{
	MyGLRenderContext::GetInstance()->OnDrawFrame();

}

JNIEXPORT void JNICALL native_setPointData(JNIEnv *env, jobject instance,jfloatArray jdate,jfloat minX,jfloat minY,jfloat minZ,jfloat maxX,jfloat maxY,jfloat maxZ)
{
	jfloat* pointData = (jfloat*)env->GetFloatArrayElements(jdate, 0);
	jsize length = env->GetArrayLength(jdate);
	MyGLRenderContext::GetInstance()->setPointData(pointData,length/3,minX,minY,minZ,maxX,maxY,maxZ);
	env->ReleaseFloatArrayElements(jdate, pointData, 0);
}
JNIEXPORT void JNICALL native_setPointOtherData(JNIEnv *env, jobject instance,jfloatArray jdate,jint singleSize)
{
	jfloat* pointData = (jfloat*)env->GetFloatArrayElements(jdate, 0);
	jsize length = env->GetArrayLength(jdate);
	MyGLRenderContext::GetInstance()->setPointOtherData(pointData,length/singleSize,singleSize);
	env->ReleaseFloatArrayElements(jdate, pointData, 0);
}

#ifdef __cplusplus
}
#endif

static JNINativeMethod g_RenderMethods[] = {
		{"native_Init",                      "()V",       (void *)(native_Init)},
		{"native_UnInit",                    "()V",       (void *)(native_UnInit)},
		{"native_setPointData",              "([FFFFFFF)V",       (void *)(native_setPointData)},
		{"native_setPointOtherData",              "([FI)V",       (void *)(native_setPointOtherData)},
		//{"native_SetImageData",              "(III[B)V",  (void *)(native_SetImageData)},
		//{"native_SetImageDataWithIndex",     "(IIII[B)V", (void *)(native_SetImageDataWithIndex)},
//		{"native_SetParamsInt",              "(III)V",    (void *)(native_SetParamsInt)},
//		{"native_SetParamsFloat",            "(IFF)V",    (void *)(native_SetParamsFloat)},
		//{"native_SetAudioData",              "([S)V",     (void *)(native_SetAudioData)},
		{"native_UpdateTransformMatrix",     "(FFFF)V",   (void *)(native_UpdateTransformMatrix)},
		{"native_OnSurfaceCreated",          "()V",       (void *)(native_OnSurfaceCreated)},
		{"native_OnSurfaceChanged",          "(II)V",     (void *)(native_OnSurfaceChanged)},
		{"native_OnDrawFrame",               "()V",       (void *)(native_OnDrawFrame)},
};

static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum)
{
	LOGCATE("RegisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == NULL)
	{
		LOGCATE("RegisterNativeMethods fail. clazz == NULL");
		return JNI_FALSE;
	}
	if (env->RegisterNatives(clazz, methods, methodNum) < 0)
	{
		LOGCATE("RegisterNativeMethods fail");
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className)
{
	LOGCATE("UnregisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == NULL)
	{
		LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
		return;
	}
	if (env != NULL)
	{
		env->UnregisterNatives(clazz);
	}
}

// call this func when loading lib
extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p)
{
	LOGCATE("===== JNI_OnLoad =====");
	jint jniRet = JNI_ERR;
	JNIEnv *env = NULL;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return jniRet;
	}

	jint regRet = RegisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME, g_RenderMethods,
										sizeof(g_RenderMethods) /
										sizeof(g_RenderMethods[0]));
	if (regRet != JNI_TRUE)
	{
		return JNI_ERR;
	}

	return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p)
{
	JNIEnv *env = NULL;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK)
	{
		return;
	}

	UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);
}
