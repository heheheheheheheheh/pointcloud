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
    //opengl字段
    GLint m_PointSizeLoc;
    GLint m_MVPMatLoc;
    //opengl vao vbo
    GLuint m_VaoId;
    GLuint m_VboIds[1];
    //图形变换信息
    glm::mat4 m_MVPMatrix;
    //手势变换信息
    int m_AngleX;
    int m_AngleY;
    float m_ScaleX;
    float m_ScaleY;

    float m_PreScale = 1.0f;
//    glm::vec3 Gravity;
    //点云信息
    glm::vec3 minCoordinate;//xyz最小值
    glm::vec3 maxCoordinate;//xyz最大值
//    glm::vec3 bounding;
    unsigned numberOfpoints;//顶点数
    float *m_Points;//顶点信息


    PointCloud();
    virtual ~PointCloud();

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();

/*    //add Point
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
    }*/
    virtual void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ);
    void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);
    virtual void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);
    void initVAO();
};


#endif //MY_APPLICATION_POINTCLOUD_H
