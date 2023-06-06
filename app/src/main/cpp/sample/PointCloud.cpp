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
    if (m_ProgramObj != 0)
        return;
    char vShaderStr[] =
            "#version 300 es\n"
            "layout (location = 0) in vec3 position;\n"
            "uniform mat4 mvpMatrix;\n"
            "uniform float vPointSize;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = mvpMatrix*vec4(position, 1.0f);\n"
            "   gl_PointSize = vPointSize;\n"
            "}\n";
    char vShaderStr1[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "uniform float vPointSize;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "   gl_PointSize = vPointSize;\n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.1, 1.0 );  \n"
            "}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
    if (m_ProgramObj) {
        m_PointSizeLoc = glGetUniformLocation(m_ProgramObj, "vPointSize");
        m_MVPMatLoc = glGetUniformLocation(m_ProgramObj, "mvpMatrix");
        GO_CHECK_GL_ERROR();
    }
/*    float vVertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };
    m_Points = vVertices;
    numberOfpoints =3;
    m_Scale = 1;*/
    initVAO();

}

void PointCloud::Draw(int screenW, int screenH) {
    LOGCATE("PointCloud::Draw");
    if (m_ProgramObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
/*    if(!VAOInited){
        initVAO();
    }*/
//    glEnable(GL_DEPTH);
    // Use the program object
    glUseProgram(m_ProgramObj);
//    GO_CHECK_GL_ERROR();
    glBindVertexArray(m_VaoId);
//    GO_CHECK_GL_ERROR();
    // Load the vertex data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_Points );
//    glEnableVertexAttribArray(0);
//    GO_CHECK_GL_ERROR();
    glUniform1f(m_PointSizeLoc, 15.0f);

    UpdateMVPMatrix(m_MVPMatrix, 0, 0, (float) screenW / screenH);
    glUniformMatrix4fv(m_MVPMatLoc, 1, GL_FALSE, &m_MVPMatrix[0][0]);

//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_POINTS, 0, numberOfpoints);
//    glDrawElements(GL_POINTS, numberOfpoints, GL_UNSIGNED_SHORT, (const void *) 0);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
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
    glm::mat4 Projection = glm::perspective(45.0f,ratio, 0.1f,100.f);

    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 4, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::scale(Model, glm::vec3(m_Scale, m_Scale, m_Scale));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    float transX = -(minCoordinate.x + maxCoordinate.x) / 2;
    float transY = -(minCoordinate.y + maxCoordinate.y) / 2;
    float transZ = -(minCoordinate.z + maxCoordinate.z) / 2;
    Model = glm::translate(Model, glm::vec3(transX, transY, transZ));

    mvpMatrix = Projection * View * Model;
}

void PointCloud::Destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}

void PointCloud::setPointData(float *points, int i, float minX, float minY, float minZ, float maxX,
                              float maxY, float maxZ) {
    LOGCATE("PointCloud::setPointData");
/*    GLfloat vVertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    m_Points = vVertices;
    numberOfpoints =3;
    m_Scale = 1;*/
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
    m_Scale = 1 / maxDitance;

}
void PointCloud::initVAO(){
    LOGCATE("PointCloud::initVAO");
    glGenBuffers(1, m_VboIds);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, numberOfpoints*3 * sizeof(float), m_Points, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
    // Generate VAO Ids
    glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);

    GO_CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);
    VAOInited = true;
}
