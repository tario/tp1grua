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
#include "nave_combate.h"
#include "nave_nodriza.h"
#include "target_quad.h"

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
Dibujable* esfera_del_cielo;
Dibujable* planeta;
Dibujable* basuraEspacial;
ModelObject* nave_combate;
TargetQuad* targetQuad;

glm::mat4 main_object_matrix = glm::mat4(1.0);
bool mouserotation = false;
bool mousechangesize = false;
bool mostrarInstrucciones = true;
float posicionInstrucciones = 0;

#define wglewGetContext() (&_wglewctx)

float camara_dist = 0.0;
float angle_camera = 0.0;
float angle_camera2 = 0.0;

// angulos para camara de vista en primera persona
float fp_angle_camera = 1.0;
float fp_angle_camera2 = 0.1;

glm::vec3 posicion_camara;
glm::vec3 posicion_peaton_camara2 = glm::vec3(-1.5, 0.0, 0.65);
glm::mat4 View;

int camara_mode = 2;
int mouse_last_x = 0;
int mouse_last_y = 0;

const float velocidadGiro = 0.5;
class Nave {
	public:
		Nave() : front(1.0,0.0,0.0,1.0), up(0.0,0.0,1.0,1.0), position(0.0,0.0,0.0,1.0), giro(1.0),
			desplazamiento(0.0,0.0,0.0) {

		}


		void processFrame() {
			if (control_avanzar)	{
				desplazamiento = desplazamiento + glm::vec3(front[0] * 0.0025, front[1] * 0.0025, front[2] * 0.0025);
			}

			if (control_retroceder)	{
				desplazamiento = desplazamiento - glm::vec3(front[0] * 0.001, front[1] * 0.001, front[2] * 0.001);
			}

			if (control_giroderecho){ 
				giro = glm::rotate(giro, velocidadGiro, glm::vec3(up));
			}

			if (control_giroizquierdo){ 
				giro = glm::rotate(giro, -velocidadGiro, glm::vec3(up));
			}

			glm::vec3 left = glm::cross(glm::vec3(up), glm::vec3(front));
			if (control_giroarriba){ 
				giro = glm::rotate(giro, -velocidadGiro, left);
			}

			if (control_giroabajo){ 
				giro = glm::rotate(giro,velocidadGiro, left);
			}

			if (control_girobarril1){ 
				giro = glm::rotate(giro, -velocidadGiro, glm::vec3(front));
			}

			if (control_girobarril2){ 
				giro = glm::rotate(giro, velocidadGiro, glm::vec3(front));
			}
			position = position + glm::vec4(desplazamiento,0.0);
			up = giro * up;
			front = giro * front;
			
			glm::mat3 giro2 = glm::mat3(glm::mat4(1.0) * 0.1 + giro * 0.9);
			
			glm::vec3 v1 = glm::normalize(glm::vec3(giro2[0][0], giro2[0][1], giro2[0][2]));
			glm::vec3 v2 = glm::normalize(glm::vec3(giro2[1][0], giro2[1][1], giro2[1][2]));
			glm::vec3 v3 = glm::normalize(glm::vec3(giro2[2][0], giro2[2][1], giro2[2][2]));
			giro = glm::mat4(glm::mat3(
				v1[0],v1[1],v1[2],
				v2[0],v2[1],v2[2],
				v3[0],v3[1],v3[2]
				));

				left = glm::normalize(glm::cross(glm::vec3(up),glm::vec3(front)));
				up = -glm::vec4(glm::normalize(glm::cross(left,glm::vec3(front))), 1.0);
				front = glm::vec4(glm::normalize(glm::vec3(front)),1.0);
				//up = glm::vec4(glm::normalize(glm::vec3(up)),1.0);
			glm::vec3 d = desplazamiento; 
			desplazamiento = glm::vec3(d[0]*0.99,d[1]*0.99, d[2]*0.99);
			//giro = glm::mat4(1.0)
		}

		bool control_avanzar;
		bool control_retroceder;
		bool control_giroizquierdo;
		bool control_giroderecho;
		bool control_giroarriba;
		bool control_giroabajo;
		bool control_girobarril1;
		bool control_girobarril2;

		glm::vec4 position;
		glm::vec4 up;
		glm::vec4 front;

		glm::vec3 desplazamiento;
		glm::mat4 giro;
};

#define NAVES_EN_ESCUADRON 3
Nave escuadron[NAVES_EN_ESCUADRON];
Nave* nave_seleccionada = escuadron+0;
Nave* nave_objetivo = 0;

void update_view_matrix() {
	glm::vec3 look_at, up;

	if (camara_mode == 2) {
		up = glm::vec3(nave_seleccionada->up);

		if (camara_dist<=0.0) {
			look_at = glm::vec3(nave_seleccionada->position) + glm::vec3(nave_seleccionada->front);
			posicion_camara = glm::vec3(nave_seleccionada->position);
		} else {
			float f = camara_dist * 0.9;
			look_at = glm::vec3(nave_seleccionada->position) + glm::vec3(nave_seleccionada->front[0]*f,nave_seleccionada->front[1]*f,nave_seleccionada->front[2]*f);
			posicion_camara = -glm::vec3(
					camara_dist*cos(angle_camera)*cos(angle_camera2),
					camara_dist*sin(angle_camera)*cos(angle_camera2),
					camara_dist*sin(angle_camera2));
			glm::vec3 left = glm::cross(glm::vec3(nave_seleccionada->front),glm::vec3(nave_seleccionada->up));
			glm::mat3 rotacion_nave(
				nave_seleccionada->front[0], nave_seleccionada->front[1], nave_seleccionada->front[2],
				left[0], left[1], left[2],
				nave_seleccionada->up[0], nave_seleccionada->up[1], nave_seleccionada->up[2]);

			posicion_camara = glm::vec3(nave_seleccionada->position) + rotacion_nave * posicion_camara;
		}

	} else {
		look_at = glm::vec3(nave_seleccionada->position);
	}

	View       = glm::lookAt(
		posicion_camara, 
		look_at, 
		up
	);

	Shader::cameraDirection = glm::normalize(look_at - posicion_camara );
	Shader::cameraPosition = posicion_camara;
}

void glut_process_mouse(int button, int state, int x, int y) {
	if (camara_mode == 2) {
		if (button == 3 || button == 4) {
			if (state == GLUT_UP) {
				if (button == 3) {
					camara_dist -= 0.3;
				} else {
					camara_dist += 0.3;
				}
			}

			if (camara_dist < 0.0) camara_dist = 0.0;

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

//	nave.front = glm::rotate(nave.front, float((x - mouse_last_x)*0.5), nave.up);
//	glm::vec3 left = glm::cross(nave.front, nave.up);
//	nave.up = glm::rotate(nave.up, float((mouse_last_y - y)*0.5), left);
//	nave.front = glm::rotate(nave.front, float((mouse_last_y - y)*0.5), left);

	mouse_last_x = x;
	mouse_last_y = y;
}

void glut_process_mouse_motion(int x, int y) {
	if (camara_mode == 2) {
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
	}	
}


void keyboardUp(unsigned char key, int x, int y)
{
    currentSetter = nullSetter;
	if (key == 'i')	nave_seleccionada->control_avanzar = false;
	if (key == 'k')	nave_seleccionada->control_retroceder = false;
	if (key == 'a') nave_seleccionada->control_giroderecho = false;
	if (key == 'd') nave_seleccionada->control_giroizquierdo = false;
	if (key == 'w') nave_seleccionada->control_giroarriba = false;
	if (key == 's') nave_seleccionada->control_giroabajo = false;
	if (key == 'q') nave_seleccionada->control_girobarril1 = false;
	if (key == 'e') nave_seleccionada->control_girobarril2 = false;
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
#include "asteroide.h"

std::vector<Texture*> textureVector;
int currentTextureIndex = 0;
TextureSwitch* textureSwitch;

void glut_special_process_keys(int key, int x, int y) {
	if (key == 1) {
		mostrarInstrucciones = true;
	}
}
void glut_process_keys(unsigned char key, int x, int y) {

	if (key == 't') {
		nave_seleccionada++;
		if (nave_seleccionada-escuadron > 2) nave_seleccionada = escuadron;
	}
	if (key == 9) {
		if (nave_objetivo == 0) {
			nave_objetivo = escuadron;
		} else {
			nave_objetivo++;
		}
		if (nave_objetivo-escuadron > 2) nave_objetivo = escuadron;
		if (nave_objetivo == nave_seleccionada) nave_objetivo++;
		if (nave_objetivo-escuadron > 2) nave_objetivo = escuadron;
	}
    if (key == 27) 
    {
        exit(0);

    }
	if (key == 'i')	nave_seleccionada->control_avanzar = true;
	if (key == 'k')	nave_seleccionada->control_retroceder = true;
	if (key == 'a') nave_seleccionada->control_giroderecho = true;
	if (key == 'd') nave_seleccionada->control_giroizquierdo = true;
	if (key == 'w') nave_seleccionada->control_giroarriba = true;
	if (key == 's') nave_seleccionada->control_giroabajo = true;
	if (key == 'q') nave_seleccionada->control_girobarril1 = true;
	if (key == 'e') nave_seleccionada->control_girobarril2 = true;

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

	Texture* background = new BitmapTexture("background.bmp");
	Material* material;
	Material* materialTexturaSimple = new MaterialTextura(textura_instrucciones);

	instrucciones = new ModelObject(
		new CuboTexturado(materialTexturaSimple, caras2),
		glm::scale(glm::mat4(1.0), glm::vec3(2.0, 2.0, 2.0))
		);
	

	esfera_del_cielo = new ModelObject(
		new Esfera(new MaterialTextura(background), 50, false),
		glm::rotate(
				glm::scale(glm::mat4(1.0),glm::vec3(100.0,100.0,100.0)),
				90.0f, 
				glm::vec3(0.0,0.0,1.0)
				)
		);

	Texture* textura_planeta = new BitmapTexture("planeta.bmp");
	MaterialTP3* materialtp3 = new MaterialTP3(textura_planeta, NullTexture::instance(),NullTexture::instance());
	materialtp3->kaSetter->set(0.0);
	materialtp3->kdSetter->set(1.0);
	materialtp3->ksSetter->set(0.0);
	materialtp3->intensidadDifusoSetter->set(1.0);
	materialtp3->intensidadGrisSetter->set(0.0);
	materialtp3->intensidadRelieveSetter->set(0.0);
	materialtp3->intensidadReflexionSetter->set(0.0);

	planeta = new ModelObject(
		new Esfera(materialtp3, 20, false),
			glm::scale(
				glm::translate(glm::mat4(1.0), glm::vec3(40.0, 40.0, 0.0)),
				glm::vec3(55,55,55)
				)
		);

	Material* material_color_blanco = new MaterialColorSolido(glm::vec3(1.0,1.0,1.0));
	ModelObject* light_sphere = new ModelObject(new Esfera(material_color_blanco, 10));
	light_sphere->set_model_matrix(
			glm::scale(
				glm::translate(glm::mat4(1.0), glm::vec3(-10.0, 10.0, 0.0)),
				glm::vec3(0.2,0.2,0.2)
				)
		);

	Material* material_color_gris_oscuro = new MaterialColorSolido(glm::vec3(0.2,0.2,0.2));
	basuraEspacial = new Esfera(material_color_gris_oscuro, 5);
	objects.push_front(light_sphere);

	objects.push_front(new ModelObject(new NaveNodriza(), glm::translate(glm::mat4(1.0), glm::vec3(5.0,0.0,0.0))));
	objects.push_front(new ModelObject(new Asteroide(), glm::translate(glm::mat4(1.0), glm::vec3(2.3,1.0,4.0))));
	objects.push_front(new ModelObject(new Asteroide(), glm::translate(glm::mat4(1.0), glm::vec3(-2.3,1.0,4.0))));
	objects.push_front(new ModelObject(new Asteroide(), glm::translate(glm::mat4(1.0), glm::vec3(-2.3,1.0,-4.0))));


	nave_combate = new ModelObject(new NaveCombate(background));

	escuadron[1].position = glm::vec4(-1.0,-1.0,0.0,1.0);
	escuadron[2].position = glm::vec4(-1.0,1.0,0.0,1.0);

	targetQuad = new TargetQuad();

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

	glm::mat4 prMatrix;
	prMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 centerView       = glm::lookAt(
		glm::vec3(0.0,0.0,0.0), 
		glm::vec3(0.0,0.0,0.0) + Shader::cameraDirection, 
		glm::vec3(nave_seleccionada->up)
	);

	Shader::projectionMatrix = prMatrix * centerView;
	esfera_del_cielo->dibujar(glm::mat4(1.0));
	planeta->dibujar(glm::mat4(1.0));

    glClear(GL_DEPTH_BUFFER_BIT);

	for (int i=0; i<NAVES_EN_ESCUADRON; i++) {
	escuadron[i].processFrame();
	}
	

	update_view_matrix();

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	// Camera matrix

	Shader::projectionMatrix = prMatrix * View;
	//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	Dibujable* dibujable;
	for (std::list<Dibujable*>::iterator it = objects.begin(); it!=objects.end();it++) {
		dibujable = (*it);
		dibujable->dibujar(glm::mat4(1.0));
	}

	glm::mat4 matriz_scala = glm::scale(glm::mat4(1.0), glm::vec3(0.02,0.02,0.02));
	
	glm::vec3 origin = posicion_camara + Shader::cameraDirection * 1.0f;
	origin = glm::vec3(floor(origin[0]),floor(origin[1]), floor(origin[2]));

	for (int i=-1; i<1; i++) {
	for (int j=-1; j<1; j++) {
	for (int k=-1; k<1; k++) {
	//basuraEspacial->dibujar(glm::translate(glm::mat4(1.0),origin + glm::vec3(i,j,k)) * matriz_scala);
	}
	}
	}

	for (int i=0; i<NAVES_EN_ESCUADRON; i++) {
		glm::vec3 left = glm::cross(glm::vec3(escuadron[i].up), glm::vec3(escuadron[i].front));
		glm::mat3 idd(
			escuadron[i].front[0], escuadron[i].front[1], escuadron[i].front[2],
			left[0], left[1], left[2],
			escuadron[i].up[0], escuadron[i].up[1], escuadron[i].up[2]);

		glm::mat4 rotacion_nave(idd);
		glm::mat4 escalado_nave = glm::scale(glm::mat4(1.0), glm::vec3(0.2,0.2,0.2));
		glm::mat4 transform_matrix =
			glm::translate(glm::mat4(1.0), glm::vec3(escuadron[i].position)) * rotacion_nave * escalado_nave
			;

		if (camara_mode != 2 || camara_dist > 0.0 || nave_seleccionada != escuadron+i) {
			nave_combate->dibujar(
		 		 transform_matrix
			);
		}
	}

	// esto asegura de que lo que se dibuje se haga encima de todo sin importar su distancia
	glClear(GL_DEPTH_BUFFER_BIT);

	if (nave_objetivo != 0) {
			glm::vec3 left = glm::normalize(glm::cross(glm::vec3(nave_seleccionada->up), Shader::cameraDirection));
			glm::vec3 front = glm::normalize(Shader::cameraDirection);
			glm::vec3 up = glm::vec3(nave_seleccionada->up);
			glm::mat3 idd(
				front[0], front[1], front[2],
				left[0], left[1], left[2],
				up[0], up[1], up[2]);

			glm::mat4 rotacion_hacia_camara(idd);
			float f = glm::distance(posicion_camara, glm::vec3(nave_objetivo->position))*0.05;
			if (f < 1.0) f = 1.0;
			glm::mat4 escalado = glm::scale(glm::mat4(1.0), glm::vec3(f,f,f));
			glm::mat4 transform_matrix =
				glm::translate(glm::mat4(1.0), glm::vec3(nave_objetivo->position)) * rotacion_hacia_camara * escalado
				;

			targetQuad->dibujar(
		 		 transform_matrix
			);
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
  glutSpecialFunc(glut_special_process_keys);
  glutIdleFunc(glut_animate);
  glutMotionFunc(glut_process_mouse_motion);
  glutMouseFunc(glut_process_mouse);
  glutPassiveMotionFunc(glut_process_passive_mouse_motion);
  glutKeyboardUpFunc(keyboardUp);
  init();

  glutMainLoop();
}

