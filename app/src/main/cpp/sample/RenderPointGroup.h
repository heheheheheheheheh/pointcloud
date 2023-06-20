//
// Created by zane on 2023/6/16.
//

#ifndef MY_APPLICATION_RENDERPOINTGROUP_H
#define MY_APPLICATION_RENDERPOINTGROUP_H
#include "GLSampleBase.h"
#include <list>

class RenderPointGroup : public GLSampleBase
{
public:
    std::list<GLSampleBase *> renders;

    RenderPointGroup();
    virtual ~RenderPointGroup();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();
    virtual void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);
    virtual void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ);
    virtual void setPointOtherData(float *pData, int length, int singleSize);
};


#endif //MY_APPLICATION_RENDERPOINTGROUP_H
