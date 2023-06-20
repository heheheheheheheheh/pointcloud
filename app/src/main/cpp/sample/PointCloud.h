//
// Created by zane on 2023/6/5.
//

#ifndef MY_APPLICATION_POINTCLOUD_H
#define MY_APPLICATION_POINTCLOUD_H


#include "GLSampleBase.h"
#include "glm.hpp"
#include "DataMessage.hpp"
class PointCloud : public GLSampleBase
{
public:
    DataMessage otherMessage;
    bool VAOInited = false;
    //opengl字段
    GLint m_PointSizeLoc;
    GLint m_MVPMatLoc;
    //opengl vao vbo
    GLuint m_VaoId;
    GLuint m_UboId;
    GLuint uboBindPoint1 = 1;
    //图形变换信息
    glm::mat4 m_MVPMatrix = glm::mat4(1.0f);
    //手势变换信息
    int m_AngleX = 0.0f;
    int m_AngleY = 0.0f;
    float m_ScaleX = 1.0f ;
    float m_ScaleY = 1.0f;

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

    virtual void setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ);
    virtual void setPointOtherData(float *pData, int length, int singleSize);
    void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);
    virtual void UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);
    void initVAO();
};


#endif //MY_APPLICATION_POINTCLOUD_H
