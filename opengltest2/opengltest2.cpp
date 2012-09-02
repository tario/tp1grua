// opengltest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <fstream>

#define wglewGetContext() (&_wglewctx)

float positionData[] = 
{
    -0.8f, -0.8f, 0.0f,
     0.8f, -0.8f, 0.0f,
     0.0f,  0.8f, 0.0f
};
GLuint positionBufferHandle;

float colorData[] = 
{
     1.0f,  0.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
     0.0f,  0.0f, 1.0f
};
GLuint colorBufferHandle;

// Handle to the vertex array object
GLuint vaoHandle;

void glut_process_keys(unsigned char key, int x, int y) {    
    if (key == 27) 
    {
        exit(0);
    }
}

void glut_reshape(int w, int h) {
  // do nothing
}

void glut_display() {
  // do display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindVertexArray( vaoHandle );
    glDrawArrays( GL_TRIANGLES, 0, 3);

    //gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glutWireTeapot(1.0);
    glutSwapBuffers();
   // glFlush();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glFlush();
}

void init_buffers() {

	GLuint vboHandles[20];
    glGenBuffers(2, vboHandles);
    positionBufferHandle = vboHandles[0];
    colorBufferHandle = vboHandles[1];

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), positionData, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), colorData, GL_STATIC_DRAW );

    // Create and set-up the vertex array objet
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    // Map index 1 to the color buffer
    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);


}

void init_shaders() {
	// ********************************************
    // Compiling the shader programms
    //*********************************************
	// Do your GLEW experiments here:
    if (GLEW_ARB_shading_language_100) 
    { 
        std::cout << "GLEW_ARB_shading_language_100" << std::endl;
        int major, minor, revision;
        const GLubyte* sVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
        if (glGetError() == GL_INVALID_ENUM)
        {
            major = 1; minor = 0; revision=51;
        }
        else
        {
            std::string version((char*)sVersion);
            std::cout << version.c_str() << std::endl;
        }

        // Load vertex Shader
        GLuint vertShader = glCreateShader (GL_VERTEX_SHADER);
        if ( 0 == vertShader )
        {
            std::cout << "Error creating vertex shader" << std::endl;
        }

        std::ifstream v_shader_file("PassThroughVShader.vert", std::ifstream::in);
        std::string v_str((std::istreambuf_iterator<char>(v_shader_file)), std::istreambuf_iterator<char>());
        const char* vs_code_array[] = {v_str.c_str()};
        
        glShaderSource( vertShader, 1, vs_code_array, NULL);

        // Compilar el shader
        glCompileShader( vertShader );

        // verificar resultado de la compilacion
        GLint vs_compilation_result;
        glGetShaderiv( vertShader, GL_COMPILE_STATUS, &vs_compilation_result );
        if( GL_FALSE == vs_compilation_result )
        {
            std::cout << "Vertex shader compilation failed!\n" << std::endl;
            GLint logLen;
            glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );
            if( logLen > 0 )
            {
                char * log = (char *)malloc(logLen);
                GLsizei written;
                glGetShaderInfoLog(vertShader, logLen, &written, log);
                std::cout << "Shader log: " << log << std::endl;
                free(log);
            }
        }

         // Load fragment Shader
        GLuint fragShader = glCreateShader (GL_FRAGMENT_SHADER);
        if ( 0 == fragShader )
        {
            std::cout << "Error creating fragment shader" << std::endl;
        }

        std::ifstream f_shader_file("BasicFShader.frag", std::ifstream::in);
        std::string f_str((std::istreambuf_iterator<char>(f_shader_file)), std::istreambuf_iterator<char>());
        const char* fs_code_array[] = {f_str.c_str()};
        
        glShaderSource( fragShader, 1, fs_code_array, NULL);

        // Compilar el shader
        glCompileShader( fragShader );

        // verificar resultado de la compilacion
        GLint fs_compilation_result;
        glGetShaderiv( fragShader, GL_COMPILE_STATUS, &fs_compilation_result );
        if( GL_FALSE == fs_compilation_result )
        {
            std::cout << "Fragment shader compilation failed!\n" << std::endl;
            GLint logLen;
            glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );
            if( logLen > 0 )
            {
                char * log = (char *)malloc(logLen);
                GLsizei written;
                glGetShaderInfoLog(fragShader, logLen, &written, log);
                std::cout << "Shader log: " << log << std::endl;
                free(log);
            }
        }
	// *******************************************

    // *******************************************
    // Linking the shader programms
    // *******************************************
        GLuint programHandle = glCreateProgram();
        if ( 0 == programHandle )
        {
            std::cout << "Error creating program object" << std::endl;
        }
        else
        {
            glAttachShader( programHandle, vertShader );
            glAttachShader( programHandle, fragShader );

            // *******************************************
            // Binding Input Data with input variables
            // *******************************************
        
                // Bind index 0 to the shader input variable "VertexPosition"
                glBindAttribLocation( programHandle, 0, "VertexPosition" );

                // Bind index 1 to the shader input variable "VertexColor"
                glBindAttribLocation( programHandle, 1, "VertexColor" );

            // *******************************************

            glLinkProgram( programHandle );

            GLint status;
            glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
            if( GL_FALSE == status )
            {
                std::cout << "Failed to link shader program!\n" << std::endl;
                GLint logLen;
                glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
                if( logLen > 0 )
                {
                    char * log = (char *)malloc(logLen);
                    GLsizei written;
                    glGetProgramInfoLog(programHandle, logLen, &written, log);
                    std::cout << "Program log: \n%s" << std::endl;
                    free(log);
                }
            }
            else
            {
                glUseProgram( programHandle );
            }
        }
    }
}

void init() {
  glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

  init_buffers();
  init_shaders();

}

HWND wnd = NULL;
HDC dc = NULL;
HGLRC rc = NULL;

GLboolean glewCreateContext (int* pixelformat)
{
  WNDCLASS wc;
  PIXELFORMATDESCRIPTOR pfd;
  /* register window class */

  ZeroMemory(&wc, sizeof(WNDCLASS));
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpfnWndProc = DefWindowProc;
  wc.lpszClassName = "GLEW";

  if (0 == RegisterClass(&wc)) return GL_TRUE;
  /* create window */
  wnd = CreateWindow("GLEW", "GLEW", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                     CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);

  if (NULL == wnd) return GL_TRUE;
  /* get the device context */
  dc = GetDC(wnd);

  if (NULL == dc) return GL_TRUE;

  /* find pixel format */

  ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
  if (*pixelformat == -1) /* find default */
  {
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    *pixelformat = ChoosePixelFormat(dc, &pfd);
    if (*pixelformat == 0) return GL_TRUE;
  }

  /* set the pixel format for the dc */

  if (FALSE == SetPixelFormat(dc, *pixelformat, &pfd)) return GL_TRUE;
  /* create rendering context */

  rc = wglCreateContext(dc);
  if (NULL == rc) return GL_TRUE;
  if (FALSE == wglMakeCurrent(dc, rc)) return GL_TRUE;
  return GL_FALSE;
}

void glewDestroyContext ()
{
  if (NULL != rc) wglMakeCurrent(NULL, NULL);
  if (NULL != rc) wglDeleteContext(rc);
  if (NULL != wnd && NULL != dc) ReleaseDC(wnd, dc);
  if (NULL != wnd) DestroyWindow(wnd);
  UnregisterClass("GLEW", GetModuleHandle(NULL));
}



int _tmain(int argc, char* argv[])
{
  char* display = NULL;
  int visual = -1;

  GLuint err;
  glewExperimental = GL_TRUE;

  if (GL_TRUE == glewCreateContext(&visual))
  {
    fprintf(stderr, "Error: glewCreateContext failed\n");
    glewDestroyContext();
    return 1;
  }

  err = glewInit();

  glutInit(&argc, argv);

  glutInitWindowSize(640, 480);
  glutInitWindowPosition ( 100, 100 );
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

  glutCreateWindow( "OpenGL Output" );

  glutDisplayFunc(glut_display);
  glutReshapeFunc(glut_reshape);
  glutKeyboardFunc(glut_process_keys);

  init();

  glutMainLoop();
	return 0;
}

