//
// Created by zane on 2023/6/20.
//

#ifndef MY_APPLICATION_TEMPSAMPLE_H
#define MY_APPLICATION_TEMPSAMPLE_H

#include "GLSampleBase.h"
class TempSample  : public GLSampleBase
{
public:

    TempSample();
    virtual ~TempSample();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();
    void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ){
    }
};


#endif //MY_APPLICATION_TEMPSAMPLE_H
