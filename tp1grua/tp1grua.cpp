// opengltest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "prisma.h"
#include "windows.h"
#include "shader.h"
#include "cubo_texturado.h"

Dibujable* cubo;

#define wglewGetContext() (&_wglewctx)

float positionData[] = 
{
     -0.8f, -0.8f, 0.0f,
    0.8f, -0.8f, 0.0f,
     -0.8f,  0.8f, 0.0f,
     0.8f,  0.8f, 0.0f

};
GLuint positionBufferHandle;

float textureCoordData[] = 
{
     1.0f,  0.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
     0.0f,  0.0f
};

float profundidad = 0.0;

void glut_process_keys(unsigned char key, int x, int y) {    
    if (key == 27) 
    {
        exit(0);
    }

	if (key == 'a') profundidad = profundidad + 0.1;
	if (key == 'w') profundidad = profundidad - 0.1;
}

void glut_reshape(int w, int h) {
  // do nothing
}

float angle = 0;

void glut_animate() {
	angle = angle + 5.1;
	if (angle > 360) angle = 0;

	glutPostRedisplay();
	Sleep(25);
}
int loc;
void glut_display() {
  // do display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

	glm::mat4 rotate_matrix = glm::scale(glm::vec3(1.25,1.25,1.25)); //glm::mat4(1.0); //glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.4, 1.0, 0.3));
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
		glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.4, 1.0, 0.3));;

	//rotate_matrix = glm::lookAt(glm::vec3(0.0,200.0,2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(200.0, 200.0, 200.0)) * rotate_matrix;
	//glUniformMatrix4fv(transform_matrix_index, 1, 0, glm::value_ptr(Projection * View * Model));
	cubo->dibujar(Projection * View * Model);
	//textureShader->use();
  //  glUniform1i(loc, 1);
//	glDrawArrays( GL_TRIANGLES, 0, 36);

    //gluLookAt(0.0, 200.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glutWireTeapot(1.0);
    glutSwapBuffers();
   // glFlush();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glFlush();
}

void init() {
  glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	Texture* texture = new Texture("e:\\imagen.bmp");
	cubo = new CuboTexturado(texture);

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
  glutIdleFunc(glut_animate);

  init();

  glutMainLoop();
}

