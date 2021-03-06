// opengltest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <fstream>
#include <list>
#include "math.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "prisma.h"
#include "windows.h"
#include "shader.h"

// elementos necesarios para la escena
#include "agua.h"
#include "piso.h"
#include "grua.h"
#include "model_object.h"

#define M_PI       3.14159265358979323846
#define VELOCIDAD_PEATON 0.05

std::list<Dibujable*> objects;

ModelObject* agua;
ModelObject* piso;
ModelObject* model_object_grua;
Grua* grua;

#define wglewGetContext() (&_wglewctx)

float camara_dist = 10;
float angle_camera = 1.0;
float angle_camera2 = 0.1;

// angulos para camara de vista en primera persona
float fp_angle_camera = 1.0;
float fp_angle_camera2 = 0.1;

glm::vec3 posicion_camara = glm::vec3(camara_dist*cos(angle_camera),camara_dist*sin(angle_camera),3);
glm::vec3 posicion_peaton_camara2 = glm::vec3(-1.5, 0.0, 0.65);
glm::mat4 View;

int camara_mode = 1;
int mouse_last_x = 0;
int mouse_last_y = 0;

void update_view_matrix2() {

	View       = glm::lookAt(
		posicion_peaton_camara2, // Camera is at (4,3,3), in World Space
		glm::vec3(
			posicion_peaton_camara2[0]+cos(fp_angle_camera)*cos(fp_angle_camera2),
			posicion_peaton_camara2[1]+sin(fp_angle_camera)*cos(fp_angle_camera2),
			posicion_peaton_camara2[2]+sin(fp_angle_camera2)),
		glm::vec3(0,0,1)  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

void update_view_matrix() {

	posicion_camara = glm::vec3(-0.75,1.25,3.0) + glm::vec3(
			camara_dist*cos(angle_camera)*cos(angle_camera2),
			camara_dist*sin(angle_camera)*cos(angle_camera2),
			camara_dist*sin(angle_camera2));

	View       = glm::lookAt(
		posicion_camara, // Camera is at (4,3,3), in World Space
		glm::vec3(-0.75,1.25,1.5), // mirar a la cabina de la grua
		glm::vec3(0,0,1)  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

void glut_process_mouse(int button, int state, int x, int y) {
	if (camara_mode == 1) {
		if (button == 3 || button == 4) {
			if (state == GLUT_UP) {
				if (button == 3) {
					camara_dist -= 0.5;
				} else {
					camara_dist += 0.5;
				}
			}

			if (camara_dist < 1.0) camara_dist = 1.0;

			update_view_matrix();
		}
	}
}

void glut_process_passive_mouse_motion(int x, int y) {
	if (camara_mode == 2) {
		if (abs(mouse_last_x - x) > 100 || abs(mouse_last_y - y) > 100) {
			mouse_last_x = x;
			mouse_last_y = y;
			return;
		}

		fp_angle_camera = fp_angle_camera + 0.01 * (mouse_last_x-x);
		fp_angle_camera2 = fp_angle_camera2 + 0.01 * (mouse_last_y-y);

		mouse_last_x = x;
		mouse_last_y = y;

		if (fp_angle_camera2 > M_PI/3) fp_angle_camera2 = M_PI/3;
		if (fp_angle_camera2 < -M_PI/3) fp_angle_camera2 = -M_PI/3;

		if (fp_angle_camera < 0.0) fp_angle_camera += M_PI*2;
		if (fp_angle_camera > M_PI*2) fp_angle_camera -= M_PI*2;

		update_view_matrix2();

	}
}

void glut_process_mouse_motion(int x, int y) {
	if (camara_mode == 1) {
		if (abs(mouse_last_x - x) > 100 || abs(mouse_last_y - y) > 100) {
			mouse_last_x = x;
			mouse_last_y = y;
			return;
		}

		angle_camera = angle_camera + 0.01 * (mouse_last_x-x);
		angle_camera2 = angle_camera2 + 0.01 * (mouse_last_y-y);

		mouse_last_x = x;
		mouse_last_y = y;

		if (angle_camera2 > M_PI/3) angle_camera2 = M_PI/3;
		if (angle_camera2 < -M_PI/3) angle_camera2 = -M_PI/3;

		if (angle_camera < 0.0) angle_camera += M_PI*2;
		if (angle_camera > M_PI*2) angle_camera -= M_PI*2;

		update_view_matrix();
	}	
}

void glut_process_keys(unsigned char key, int x, int y) {    
    if (key == 27) 
    {
        exit(0);
    }

	if (key == 't') {
		// agregar suciedad a la grua
		grua->cambiar_suciedad(0.05);
	}
	if (key == 'g') {
		// quitar suciedad a la grua
		grua->cambiar_suciedad(-0.05);
	}

	if (key == 'y') {
		// girar cabina de la grua
		grua->girar_cabina(-10.0);
	}
	if (key == 'h') {
		// girar cabina de la grua
		grua->girar_cabina(10.0);
	}

	if (key == 'u') {
		// girar brazo de la grua
		grua->girar_brazo(2.0);
	}
	if (key == 'j') {
		// girar brazo de la grua
		grua->girar_brazo(-2.0);
	}
	if (key == 'l') {
		// aumentar la longitud del cable
		grua->longitud_cable(0.1);
	}
	if (key == 'k') {
		// disminuir la longitud del cable
		grua->longitud_cable(-0.1);
	}

	if (key == '1') {
		camara_mode = 1;
		update_view_matrix();
	}
	if (key == '2')	{
		camara_mode = 2;
		update_view_matrix2();
	}

	if (camara_mode == 1) {
		if (key == 'w') {
			camara_dist -= 0.1;
		}
		if (key == 's') {
			camara_dist += 1.0;
		}
	}

	if (camara_mode == 2) {
		if (key == 'a') {
			posicion_peaton_camara2 = posicion_peaton_camara2 + 
				glm::vec3(cos(fp_angle_camera+M_PI/2)*VELOCIDAD_PEATON, sin(fp_angle_camera+M_PI/2)*VELOCIDAD_PEATON, 0.0);

			update_view_matrix2();
		}
		if (key == 'd') {
			posicion_peaton_camara2 = posicion_peaton_camara2 + 
				glm::vec3(cos(fp_angle_camera-M_PI/2)*VELOCIDAD_PEATON, sin(fp_angle_camera-M_PI/2)*VELOCIDAD_PEATON, 0.0);

			update_view_matrix2();
		}

		if (key == 'w') {
			posicion_peaton_camara2 = posicion_peaton_camara2 + 
				glm::vec3(cos(fp_angle_camera)*VELOCIDAD_PEATON, sin(fp_angle_camera)*VELOCIDAD_PEATON, 0.0);

			update_view_matrix2();
		}
		if (key == 's') {
			posicion_peaton_camara2 = posicion_peaton_camara2 + 
				glm::vec3(-cos(fp_angle_camera)*VELOCIDAD_PEATON, -sin(fp_angle_camera)*VELOCIDAD_PEATON, 0.0);

			update_view_matrix2();
		}
	}
}

void glut_reshape(int w, int h) {
  // do nothing
}

float angle = 0;


void init() {
  glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	//Texture* texture = new Texture("e:\\imagen.bmp");
	//cubo2 = new CuboTexturado(texture);
	//cubo = new CuboColor(glm::vec3(1.0,0.0,0.0));
	agua = new ModelObject(new Agua());
	piso = new ModelObject(new Piso());
	grua = new Grua();
	model_object_grua = new ModelObject(grua);

	agua->set_model_matrix(ModelObject::cell_matrix(0.0, 3.0, -2.0, 2.0, -0.5, 0.0));
	piso->set_model_matrix(ModelObject::cell_matrix(-3.0, 0.0, -2.0, 2.0, -0.5, 0.5));
	model_object_grua->set_model_matrix(ModelObject::cell_matrix(-1.0, -0.5, 1.0, 1.5, 0.5, 2.0));

	objects.push_front(agua);
	objects.push_front(piso);
	objects.push_front(model_object_grua);

	update_view_matrix();
}

void glut_animate() {
	glutPostRedisplay();
	Sleep(25);
}
int loc;
void glut_display() {

  // do display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix

	Dibujable* dibujable;
	for (std::list<Dibujable*>::iterator it = objects.begin(); it!=objects.end();it++) {
		dibujable = (*it);
		dibujable->dibujar(Projection * View);
	}


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

  glutInitWindowSize(800, 600);
  glutInitWindowPosition ( 100, 100 );
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

  glutCreateWindow( "OpenGL Output" );

  glutDisplayFunc(glut_display);
  glutReshapeFunc(glut_reshape);
  glutKeyboardFunc(glut_process_keys);
  glutIdleFunc(glut_animate);
  glutMotionFunc(glut_process_mouse_motion);
  glutMouseFunc(glut_process_mouse);
  glutPassiveMotionFunc(glut_process_passive_mouse_motion);

  init();

  glutMainLoop();
}

