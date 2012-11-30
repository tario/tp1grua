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
#include "model_object.h"

#define M_PI       3.14159265358979323846
#define VELOCIDAD_PEATON 0.05

std::list<Dibujable*> objects;

class MaterialObject : public Dibujable {
public:
	MaterialObject(Material* material, Dibujable* object) : object(object), material(material) {
	}
	void dibujar(const glm::mat4& m) {
		object->dibujar(m);
	};

	Material* material;
	Dibujable* object;
};

#include "texture.h"
class TextureSwitch : public Texture {
	public:
		TextureSwitch(Texture* texture) : texture(texture) {
		}

		void load(int unit) {
			texture->load(unit);
		}

		void set(Texture* texture_){
			this->texture = texture_;
		}
	private:
		Texture* texture;
};

MaterialObject* main_object;
MaterialObject* cubo;
MaterialObject* toroide;
MaterialObject* esfera;
MaterialObject* cilindro;
Dibujable* instrucciones;

glm::mat4 main_object_matrix = glm::mat4(1.0);
bool mouserotation = false;
bool mousechangesize = false;
bool mostrarInstrucciones = true;
float posicionInstrucciones = 0;

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

void update_view_matrix() {

	posicion_camara = glm::vec3(
			camara_dist*cos(angle_camera)*cos(angle_camera2),
			camara_dist*sin(angle_camera)*cos(angle_camera2),
			camara_dist*sin(angle_camera2));

	glm::vec3 look_at(0.0,0.0,0.0); 
	View       = glm::lookAt(
		posicion_camara, // Camera is at (4,3,3), in World Space
		look_at, // mirar a la cabina de la grua
		glm::vec3(0,0,1)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	Shader::cameraDirection = glm::normalize(look_at - posicion_camara );
	Shader::cameraPosition = posicion_camara;
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

Shader::ConcreteSetter<float> *nullSetter = new Shader::ConcreteSetter<float>(0.0);
Shader::ConcreteSetter<float> *currentSetter = nullSetter;
float tope_maximo = 1.0;
float tope_minimo = 0.0;

void glut_process_passive_mouse_motion(int x, int y) {
	if (abs(mouse_last_x - x) > 100 || abs(mouse_last_y - y) > 100) {
		mouse_last_x = x;
		mouse_last_y = y;
		return;
	}

	if (mouserotation) {
		glm::vec3 yaxis = glm::normalize(glm::cross(glm::vec3(0.0,0.0,1.0), Shader::cameraDirection));
		glm::vec3 xaxis = glm::normalize(glm::cross(yaxis, Shader::cameraDirection));

		main_object_matrix = glm::rotate(glm::mat4(1.0), (mouse_last_y - y)*0.5f, yaxis) * main_object_matrix;
		main_object_matrix = glm::rotate(glm::mat4(1.0), (mouse_last_x - x)*0.5f, xaxis) * main_object_matrix;
		mouse_last_x = x;
		mouse_last_y = y;

		return;
	}

	if (mousechangesize) {
		float scalefactor = exp((mouse_last_y - y)*0.01f);
		main_object_matrix = glm::scale(glm::mat4(1.0), glm::vec3(scalefactor,scalefactor,scalefactor)) * main_object_matrix;

		mouse_last_x = x;
		mouse_last_y = y;
	}

	float current_value = currentSetter->get();
	current_value = current_value + (float(mouse_last_y) - float(y)) * 0.01;
	if (current_value > tope_maximo) current_value = tope_maximo;
	if (current_value < tope_minimo) current_value = tope_minimo;

	currentSetter->set(current_value);

	mouse_last_x = x;
	mouse_last_y = y;
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


void keyboardUp(unsigned char key, int x, int y)
{
    currentSetter = nullSetter;
	mouserotation = false;
	mousechangesize = false;
}

#include "bump_mapping_material.h"
#include "toroide.h"
#include "material_color_solido.h"
#include "material_tp2.h"
#include "esfera.h" 
#include "cubo_texturado.h" 
#include "prisma.h"
#include "bitmap_texture.h"
#include "material_textura.h"

std::vector<Texture*> textureVector;
int currentTextureIndex = 0;
TextureSwitch* textureSwitch;

void glut_special_process_keys(int key, int x, int y) {
	if (key == 1) {
		mostrarInstrucciones = true;
	}
}
void glut_process_keys(unsigned char key, int x, int y) {    
    if (key == 27) 
    {
        exit(0);

    }
	mostrarInstrucciones = false;

	MaterialTP2* material = (MaterialTP2*)main_object->material;
	tope_maximo = 1.0;
	tope_minimo = 0.0;
	if (key == 'z')	currentSetter = material->kaSetter;
	if (key == 'x')	currentSetter = material->kdSetter;
	if (key == 'c')	currentSetter = material->ksSetter;
	if (key == 'v') {
		currentSetter = material->glossinessSetter;
		tope_maximo = 100.0;
		tope_minimo = 1.0;
	}
	if (key == 'b') currentSetter = material->intensidadGrisSetter;
	if (key == 'n') currentSetter = material->intensidadDifusoSetter;
	if (key == 'm') currentSetter = material->intensidadRelieveSetter;
	if (key == 'k') currentSetter = material->intensidadReflexionSetter;
	if (key == 9) {
		currentTextureIndex++;
		if (currentTextureIndex > textureVector.size() - 1) {
			currentTextureIndex=0;
		}

		textureSwitch->set(textureVector.at(currentTextureIndex));
	}

	if (key == 'r') mouserotation = true;
	if (key == 't') mousechangesize = true;

	if (key == '1') {
		main_object = toroide;
	}
	if (key == '2')	{
		main_object = cubo;
	}
	if (key == '3')	{
		main_object = esfera;
	}
	if (key == '4')	{
		main_object = cilindro;
	}
}

void glut_reshape(int w, int h) {
  // do nothing
}

float angle = 0;


static float cara1[] = {0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0};
static CuboTexturado::Cara caras[] = {
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1),
	CuboTexturado::Cara(cara1)
};

static float cara2[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
static CuboTexturado::Cara caras2[] = {
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2),
	CuboTexturado::Cara(cara2)
};

void init() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	Texture* donut = new BitmapTexture("donut.bmp");
	Texture* tierra = new BitmapTexture("tierra.bmp");
	Texture* brickmap = new BitmapTexture("ladrillos_normal.bmp");
	Texture* brick = new BitmapTexture("brick.bmp");
	Texture* normaldonut = new BitmapTexture("normal-donut.bmp");
	Texture* textura_instrucciones = new BitmapTexture("instrucciones.bmp");

	textureVector.push_back(new BitmapTexture("Milkyway_BG.bmp"));
	textureVector.push_back(new BitmapTexture("chateau_TM.bmp"));
	textureVector.push_back(new BitmapTexture("Road_to_MonumentValley_8k.bmp"));
	textureVector.push_back(new BitmapTexture("Zion_7_Sunsetpeek_8k_Bg.bmp"));
	Material* material;
	Material* materialTexturaSimple = new MaterialTextura(textura_instrucciones);

	instrucciones = new ModelObject(
		new CuboTexturado(materialTexturaSimple, caras2),
		glm::scale(glm::mat4(1.0), glm::vec3(2.0, 2.0, 2.0))
		);
	
	textureSwitch = new TextureSwitch(textureVector.at(0));

	material = new MaterialTP2(donut, normaldonut, textureSwitch);
	toroide = new MaterialObject(
		material,
		new Toroide(material, 0.7, 50));

	material = new MaterialTP2(brick, brickmap, textureSwitch);
	cubo = new MaterialObject(
		material,
		new CuboTexturado(material, caras));

	material = new MaterialTP2(tierra, brickmap, textureSwitch);
	esfera = new MaterialObject(
		material,
		new Esfera(material, 50));

	material = new MaterialTP2(brick, brickmap, textureSwitch);
	cilindro = new MaterialObject(material,
		new Prisma(material, 100));

	main_object = cubo;

	Material* material_color_blanco = new MaterialColorSolido(glm::vec3(1.0,1.0,1.0));
	ModelObject* light_sphere = new ModelObject(new Esfera(material_color_blanco, 10));
	light_sphere->set_model_matrix(
			glm::scale(
				glm::translate(glm::mat4(1.0), glm::vec3(-1.0, 1.0, 1.0)),
				glm::vec3(0.2,0.2,0.2)
				)
		);
	objects.push_front(light_sphere);

	update_view_matrix();
}

void glut_animate() {
	glutPostRedisplay();
	Sleep(25);
}
int loc;

#include "cubo_texturado.h"
void glut_display() {

  // do display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	// Camera matrix
	Shader::projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f) * View;
	//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	Dibujable* dibujable;
	for (std::list<Dibujable*>::iterator it = objects.begin(); it!=objects.end();it++) {
		dibujable = (*it);
		dibujable->dibujar(glm::mat4(1.0));
	}

	main_object->dibujar(main_object_matrix);

	if (mostrarInstrucciones) {
		if (posicionInstrucciones > 0) {
			posicionInstrucciones -= 0.2;
			if (posicionInstrucciones < 0.0) posicionInstrucciones = 0.0;
		}
	} else {
		if (posicionInstrucciones < 2.0) {
			posicionInstrucciones += 0.2;
		}
	}
	Shader::projectionMatrix = glm::mat4(1.0);
	instrucciones->dibujar(
		glm::translate(glm::mat4(1.0), glm::vec3(0.0,posicionInstrucciones,0.0))
		);
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
  glutSpecialFunc(glut_special_process_keys);
  glutIdleFunc(glut_animate);
  glutMotionFunc(glut_process_mouse_motion);
  glutMouseFunc(glut_process_mouse);
  glutPassiveMotionFunc(glut_process_passive_mouse_motion);
  glutKeyboardUpFunc(keyboardUp);
  init();

  glutMainLoop();
}

