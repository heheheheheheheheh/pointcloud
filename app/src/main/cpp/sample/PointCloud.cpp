//
// Created by zane on 2023/6/5.
//

#include <iostream>
#include "PointCloud.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"

PointCloud::PointCloud() {

}

PointCloud::~PointCloud() {
}

void PointCloud::Init() {
    if (m_ProgramObj != 0)
        return;
    char vShaderStr[] =
            "#version 330 core\n"
            "layout (location = 0) in vec3 position;\n"
            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = projection*view* model*vec4(position, 1.0f);\n"
            "}\n";


    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 1.0, 0.1, 1.0 );  \n"
            "}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

}

void PointCloud::Draw(int screenW, int screenH) {
    LOGCATE("PointCloud::Draw");
    GLfloat vVertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    if (m_ProgramObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Use the program object
    glUseProgram(m_ProgramObj);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_POINTS, 0, numberOfpoints);
    glUseProgram(GL_NONE);

}

void PointCloud::Destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}


/*void PointCloud::getBounding(glm::vec3 &min, glm::vec3 &max) {
    min = minCoordinate;
    max = maxCoordinate;
}*/

unsigned PointCloud::size() {
    return numberOfpoints;
}

/*glm::vec3 &PointCloud::computeGravity() {
    for (unsigned i = 0; i < size(); i++) {
        Gravity.x += c1[i].x;
        Gravity.y += c1[i].y;
        Gravity.z += c1[i].z;
    }
    Gravity.x = Gravity.x / numberOfpoints;
    Gravity.y = Gravity.y / numberOfpoints;
    Gravity.z = Gravity.z / numberOfpoints;
    return Gravity;
}*/

/*void PointCloud::ConstructMinCube(glm::vec3 &dimMin, glm::vec3 &dimMax, double enlargeFactor*//*=0.01*//*) {
    float maxDD = 0;
    getBounding(dimMin, dimMax);
    {
        glm::vec3 diag = dimMax - dimMin;
        maxDD = std::max(diag.x, diag.y);
        maxDD = std::max(maxDD, diag.z);
    }
    if (enlargeFactor > 0)
        maxDD = static_cast<float>(static_cast<double>(maxDD) * (1.0 + enlargeFactor));
    //build corresponding 'square' box
    {
        glm::vec3 dd(maxDD, maxDD, maxDD);
        glm::vec3 md = dimMax + dimMin;

        dimMin = (md - dd) * static_cast<float>(0.5);
        dimMax = dimMin + dd;
    }
}*/

void PointCloud::setPointData(float *pDouble, int i,float minX,float minY,float minZ,float maxX,float maxY,float maxZ) {
    numberOfpoints= i;
    minCoordinate.x = minX;
    minCoordinate.y = minY;
    minCoordinate.z = minZ;
    maxCoordinate.x = maxX;
    maxCoordinate.y = maxY;
    maxCoordinate.z = maxZ;
}
