//
// Created by zane on 2023/6/5.
//

#include <iostream>
#include "PointCloud.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"
#include "gtc/matrix_transform.hpp"

PointCloud::PointCloud() {

}

PointCloud::~PointCloud() {
}

void PointCloud::Init() {
    LOGCATE("PointCloud::Init");
    if (m_ProgramObj == 0) {
        char vShaderStr[] =
                "#version 300 es\n"
                "layout (location = 0) in vec3 position;\n"
                "layout (location = 1) in vec3 color;\n"
                "layout(std140)uniform mvpMatrix\n"
                "{\n"
                "mat4 matrix;\n"
                "};\n"
                "uniform float vPointSize;\n"
                "out vec3 f_color;\n"
                "void main()\n"
                "{\n"
                "   gl_Position = matrix*vec4(position, 1.0f);\n"
                "   gl_PointSize = vPointSize;\n"
                "   f_color = color;\n"
                "}\n";
        char fShaderStr[] =
                "#version 300 es                              \n"
                "precision mediump float;                     \n"
                "in vec3 f_color;                          \n"
                "out vec4 fragColor;                          \n"
                "void main()                                  \n"
                "{                                            \n"
                "   fragColor = vec4 (f_color, 1.0 );  \n"
                "}                                            \n";
        m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
        if (m_ProgramObj) {
            m_PointSizeLoc = glGetUniformLocation(m_ProgramObj, "vPointSize");
            m_MVPMatLoc = glGetUniformBlockIndex(m_ProgramObj, "mvpMatrix");
            glUniformBlockBinding(m_ProgramObj, m_MVPMatLoc, uboBindPoint0);
            GO_CHECK_GL_ERROR();
        }
    }
    if (!VAOInited) {
        initVAO();
    }
}

void PointCloud::Draw(int screenW, int screenH) {
    LOGCATE("PointCloud::Draw");
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    if (m_ProgramObj == 0 || !VAOInited)
        return;
    // Use the program object
    glUseProgram(m_ProgramObj);
    glBindVertexArray(m_VaoId);
    glUniform1f(m_PointSizeLoc, 5.0f);
    updatePoint();
    UpdateMVPMatrix(m_MVPMatrix, m_AngleX, m_AngleY, (float) screenW / screenH);
    glDrawArrays(GL_POINTS, 0, numberOfpoints);
    glBindBuffer(GL_UNIFORM_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
}
void PointCloud::updatePoint(){
    if (VAORefresh){
//        glBindVertexArray(m_VaoId);
        glBindBuffer(GL_ARRAY_BUFFER, m_VboId[0]);
//        glBufferData(GL_ARRAY_BUFFER, numberOfpoints * 3 * sizeof(float), m_Points, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, numberOfpoints * 3 * sizeof(float), m_Points);
        glBindBuffer(GL_ARRAY_BUFFER, m_VboId[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, otherMessage.length * otherMessage.singleSize * sizeof(float), otherMessage.data);
//        glBufferData(GL_ARRAY_BUFFER, otherMessage.length * otherMessage.singleSize * sizeof(float),
//                     otherMessage.data, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }
    VAORefresh = false;
}
void PointCloud::UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio) {
//    LOGCATE("AvatarSample::UpdateMVPMatrix angleX = %d, angleY = %d, ratio = %f", angleX, angleY,
//            ratio);
    angleX = angleX % 360;
    angleY = angleY % 360;
    //转化为弧度角
    float radiansX = static_cast<float>(MATH_PI / 180.0f * angleX);
    float radiansY = static_cast<float>(MATH_PI / 180.0f * angleY);
    // Projection matrix
//    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    //glm::mat4 Projection = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 4.0f, 100.0f);
    glm::mat4 Projection = glm::perspective(45.0f, ratio, 0.1f, 100.f);
    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, -4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, -1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::scale(Model, glm::vec3(m_PreScale * m_ScaleX, m_PreScale * m_ScaleY,
                                        m_PreScale * m_ScaleX));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    float transX = -(minCoordinate.x + maxCoordinate.x) / 2;
    float transY = -(minCoordinate.y + maxCoordinate.y) / 2;
    float transZ = -(minCoordinate.z + maxCoordinate.z) / 2;
    glm::mat4 Model2 = glm::mat4(Model);
    Model = glm::translate(Model, glm::vec3(transX, transY, transZ));

    mvpMatrix = Projection * View * Model;
    Model2 = Projection * View * Model2;
    glBindBuffer(GL_UNIFORM_BUFFER, m_UboId[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &mvpMatrix[0][0]);
    glBindBuffer(GL_UNIFORM_BUFFER, m_UboId[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &Model2[0][0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void PointCloud::Destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}

void PointCloud::setPointData(float *points, int i, float minX, float minY, float minZ, float maxX,
                              float maxY, float maxZ) {
    VAORefresh = true;
    m_Points = points;
    numberOfpoints = i;
    minCoordinate.x = minX;
    minCoordinate.y = minY;
    minCoordinate.z = minZ;
    maxCoordinate.x = maxX;
    maxCoordinate.y = maxY;
    maxCoordinate.z = maxZ;
    float maxDitance = maxX - minX;
    maxDitance = fmaxf(maxDitance, maxY - minY);
    maxDitance = fmaxf(maxDitance, maxZ - minZ);
    m_PreScale = 1 / maxDitance;
    m_PreScale *= 4;
}

void PointCloud::setPointOtherData(float *pData, int length, int singleSize) {
    VAORefresh = true;
    otherMessage.data = pData;;
    otherMessage.length = length;
    otherMessage.singleSize = singleSize;
}

void PointCloud::initVAO() {
    LOGCATE("PointCloud::initVAO");
    if (numberOfpoints == 0)return;
    glGenVertexArrays(1, &m_VaoId);
    glGenBuffers(2, m_VboId);
    glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId[0]);
    glBufferData(GL_ARRAY_BUFFER, numberOfpoints * 3 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboId[1]);
    glBufferData(GL_ARRAY_BUFFER, otherMessage.length * otherMessage.singleSize * sizeof(float),
                 NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboId[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboId[1]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, otherMessage.singleSize, GL_FLOAT, GL_FALSE, otherMessage.singleSize * sizeof(GLfloat), (const void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);


    glGenBuffers(2, m_UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, m_UboId[0]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, uboBindPoint0, m_UboId[0]);

    glBindBuffer(GL_UNIFORM_BUFFER, m_UboId[1]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, uboBindPoint1, m_UboId[1]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    VAOInited = true;
    VAORefresh = false;
}

void PointCloud::UpdateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY) {
    GLSampleBase::UpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
    m_AngleX = static_cast<int>(rotateX);
    m_AngleY = static_cast<int>(rotateY);
    m_ScaleX = scaleX;
    m_ScaleY = scaleY;
}
