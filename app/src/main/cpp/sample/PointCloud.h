//
// Created by zane on 2023/6/5.
//

#ifndef MY_APPLICATION_POINTCLOUD_H
#define MY_APPLICATION_POINTCLOUD_H


#include "GLSampleBase.h"
#include "glm.hpp"
class PointCloud : public GLSampleBase
{
public:
    bool VAOInited = false;
    GLint m_PointSizeLoc;
    GLint m_MVPMatLoc;
    GLuint m_VaoId;
    GLuint m_VboIds[1];
    glm::mat4 m_MVPMatrix;

    float m_Scale = 1.0f;
//    glm::vec3 Gravity;
    glm::vec3 minCoordinate;
    glm::vec3 maxCoordinate;
    glm::vec3 bounding;
    unsigned numberOfpoints;
    float *m_Points;
//    Octree* octree;

    PointCloud();
    virtual ~PointCloud();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();

//   virtual glm::vec3& computeGravity();
//   virtual void getBounding(glm::vec3&min,glm::vec3&max);
//   virtual const glm::vec3* getPoint(unsigned);
//   virtual void ConstructMinCube(glm::vec3& dimMin, glm::vec3& dimMax, double enlargeFactor/*=0.01*/);
    //add Point
    float getWidth()
    {
        return maxCoordinate.x - minCoordinate.x;
    }
    float getLength()
    {
        return maxCoordinate.y - minCoordinate.y;
    }
    float getHeight()
    {
        return maxCoordinate.z - minCoordinate.z;
    }
    virtual void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ);
    void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);
    void initVAO();
};


#endif //MY_APPLICATION_POINTCLOUD_H
