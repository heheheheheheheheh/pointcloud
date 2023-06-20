//
// Created by ByteFlow on 2019/7/9.
//

#ifndef NDK_OPENGLES_3_TRIANGLESAMPLE_H
#define NDK_OPENGLES_3_TRIANGLESAMPLE_H


#include "GLSampleBase.h"

class TriangleSample : public GLSampleBase
{
public:
	GLuint m_VaoId;
	GLuint m_VboIds[1];

	TriangleSample();
	virtual ~TriangleSample();

	virtual void Init();

	virtual void Draw(int screenW, int screenH);

	virtual void Destroy();
	void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ){
	}
};


#endif //NDK_OPENGLES_3_TRIANGLESAMPLE_H
