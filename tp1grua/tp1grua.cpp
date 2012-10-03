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

Shader* textureShader;
int transform_matrix_index;

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
GLuint textureCoordBufferHandle;

// Handle to the vertex array object
GLuint vaoHandle;

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

void glut_display() {
  // do display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    glBindVertexArray( vaoHandle );

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
	glUniformMatrix4fv(transform_matrix_index, 1, 0, glm::value_ptr(Projection * View * Model));

	textureShader->use();
    glDrawArrays( GL_TRIANGLES, 0, 36);

    //gluLookAt(0.0, 200.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glutWireTeapot(1.0);
    glutSwapBuffers();
   // glFlush();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glFlush();
}

void assignvec3(float* data, glm::vec4 vect) {
	data[0] = glm::vec3(vect)[0];
	data[1] = glm::vec3(vect)[1];
	data[2] = glm::vec3(vect)[2];
}

void square(float* data, glm::mat4 matrix) {
	assignvec3(data, matrix * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
	assignvec3(data+3, matrix * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f));
	assignvec3(data+6, matrix * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f));
	assignvec3(data+9, matrix * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f));
	assignvec3(data+12, matrix * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f));
	assignvec3(data+15, matrix * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void init_buffers() {
	GLuint vboHandles[20];
    glGenBuffers(2, vboHandles);
    positionBufferHandle = vboHandles[0];
    textureCoordBufferHandle = vboHandles[1];

	float vertexdata[36*3];
	float colordata[36*2];
	int i;

	for (i=0; i<6; i++) {
		colordata[i*12] = 0.0;
		colordata[i*12+1] = 0.0;

		colordata[i*12+2] = 1.0;
		colordata[i*12+3] = 0.0;

		colordata[i*12+4] = 0.0;
		colordata[i*12+5] = 1.0;

		colordata[i*12+6] = 1.0;
		colordata[i*12+7] = 0.0;

		colordata[i*12+8] = 0.0;
		colordata[i*12+9] = 1.0;

		colordata[i*12+10] = 1.0;
		colordata[i*12+11] = 1.0;
	}

	glm::mat4 reflection = glm::scale(glm::vec3(1.0,1.0,-1.0));
	glm::mat4 xrotation = glm::rotate(glm::mat4(1.0),90.0f, glm::vec3(1.0f,0.0f,0.0f));
	glm::mat4 yrotation = glm::rotate(glm::mat4(1.0),90.0f, glm::vec3(0.0f,1.0f,0.0f));
	square(vertexdata, glm::mat4(1.0));
	square(vertexdata+6*3, reflection);
	square(vertexdata+12*3, xrotation  * reflection);
	square(vertexdata+18*3, xrotation);
	square(vertexdata+24*3, yrotation  * reflection);
	square(vertexdata+30*3, yrotation);

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 36*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

    // Create and set-up the vertex array objet
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

    // Enable the vertex attributes array
    glEnableVertexAttribArray(0);


    // Map index 0 to the position buffer
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	
    glEnableVertexAttribArray(1);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, 36*2 * sizeof (float), colordata, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);


}

GLuint textureid;

void init_shaders() {
	textureShader = new Shader("TextureFShader.frag", "TextureVShader.vert");
	textureShader->bindAttribLocation(0, "VertexPosition" );
    textureShader->bindAttribLocation(1, "VertexColor" );
	textureShader->link();
	transform_matrix_index = textureShader->getUniformLocation("TransformMatrix");
	//loadAndInitTexture("test");

	Texture* texture = new Texture("e:\\imagen.bmp");
  
    // Set the Tex1 sampler uniform to refer to texture unit 0
    int loc = textureShader->getUniformLocation("texture1");
    
    if( loc >= 0 )
    {
        glUniform1i(loc, 0);
    }
    else
    {
        fprintf(stderr, "Uniform variable Tex1 not found!\n");
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
  glutIdleFunc(glut_animate);

  init();

  glutMainLoop();
}

