//
// Created by zane on 2023/6/16.
//

#include "RenderPointGroup.h"

#include "../util/GLUtils.h"
#include "../util/LogUtil.h"
#include "PointCloud.h"
#include "CoordinateSample.h"


RenderPointGroup::RenderPointGroup()
{
    renders.push_back(new PointCloud());
    renders.push_back(new CoordinateSample());
}

RenderPointGroup::~RenderPointGroup()
{
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        delete *it;
    }
}

void RenderPointGroup::Init()
{
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        (*it)->Init();
    }
}

void RenderPointGroup::Draw(int screenW, int screenH)
{
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        (*it)->Draw(screenW,screenH);
    }
}

void RenderPointGroup::Destroy()
{
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        (*it)->Destroy();
    }
}

void RenderPointGroup::UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY)
{
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        (*it)->UpdateTransformMatrix(rotateX,rotateY,scaleX,scaleY);
    }
}
void RenderPointGroup::setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ){
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        (*it)->setPointData(pDouble,i,minX,minY,minZ,maxX,maxY,maxZ);
    }
}
void RenderPointGroup::setPointOtherData(float *pData, int length, int singleSize){
    for(std::list<GLSampleBase *>::iterator it = renders.begin(); it != renders.end(); it++){
        (*it)->setPointOtherData(pData,length,singleSize);
    }
}