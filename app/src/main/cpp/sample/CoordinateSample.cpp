//
// Created by zane on 2023/6/16.
//
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"
#include "CoordinateSample.h"
CoordinateSample::CoordinateSample()
{

}

CoordinateSample::~CoordinateSample()
{
}

void CoordinateSample::Init()
{
    if(m_ProgramObj != 0)
        return;
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec3 vPosition;  \n"
            "layout (location = 1) in vec3 color;\n"
            "out vec3 f_color;\n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vec4 ( vPosition, 1.0 );\n"
            "   f_color = color;\n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "in vec3 f_color;                          \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( f_color, 1.0 );  \n"
            "}                                            \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
    GLfloat vVertices[] = {
            0.0f,  0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
            100.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 100.0f, 0.0f,0.0f, 1.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 100.0f,0.0f, 0.0f, 1.0f
    };
    glGenBuffers(1, m_VboIds);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
//    glBufferData(GL_ARRAY_BUFFER, numberOfpoints * sizeof(float), vVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
    // Generate VAO Ids
    glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);


    GO_CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)( 3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);
}

void CoordinateSample::Draw(int screenW, int screenH)
{
    LOGCATE("CoordinateSample::Draw");


    if(m_ProgramObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Use the program object
    glUseProgram (m_ProgramObj);
    glBindVertexArray(m_VaoId);
    // Load the vertex data
//	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
//	glEnableVertexAttribArray (0);

//	glDrawArrays (GL_TRIANGLES, 0, 3);
    glLineWidth(5);
    glDrawArrays (GL_LINES, 0, 6);
    glUseProgram (GL_NONE);

}

void CoordinateSample::Destroy()
{
    if (m_ProgramObj)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }

}