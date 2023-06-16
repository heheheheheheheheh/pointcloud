//
// Created by zane on 2023/6/16.
//

#ifndef MY_APPLICATION_COORDINATESAMPLE_H
#define MY_APPLICATION_COORDINATESAMPLE_H
#include "GLSampleBase.h"

class CoordinateSample : public GLSampleBase
{
public:
    GLuint m_VaoId;
    GLuint m_VboIds[1];

    CoordinateSample();
    virtual ~CoordinateSample();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();
    void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ){
    }
};


#endif //MY_APPLICATION_COORDINATESAMPLE_H
