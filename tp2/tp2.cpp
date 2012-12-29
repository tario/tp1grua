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
#include "curva_bezier.h"

// elementos necesarios para la escena
#include "model_object.h"

#define M_PI       3.14159265358979323846
#define VELOCIDAD_PEATON 0.05

std::list<Dibujable*> objects;
bool fullscreen = false;
int xresolution, yresolution;

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
CurvaBezier* curva_bezier;
Dibujable* light_sphere;
Dibujable* misil;

float distancia_p1 = 1.0;
float distancia_p2 = 1.0;
bool bezier_misil_configuracion = false;

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


class Objetivo {
	public:

	glm::vec3 position;
	std::string name;
	float distancia_camara;
};


int objetivo_actual = -1;
std::vector<Objetivo*> objetivos;

const float velocidadGiro = 0.2;
class Nave {
	public:
		Nave() : front(1.0,0.0,0.0,1.0), up(0.0,0.0,1.0,1.0), position(0.0,0.0,0.0,1.0), giro(1.0),
			desplazamiento(0.0,0.0,0.0), misil_lado_derecho(false) {

				objetivos.push_back(new Objetivo());
				this->objetivo = objetivos.at(objetivos.size()-1);
				this->objetivo->distancia_camara = 0.5;
		}


		void processFrame() {
			if (control_avanzar)	{
				desplazamiento = desplazamiento + glm::vec3(front[0] * 0.001, front[1] * 0.001, front[2] * 0.001);
			}

			if (control_retroceder)	{
				desplazamiento = desplazamiento - glm::vec3(front[0] * 0.0004, front[1] * 0.0004, front[2] * 0.0004);
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

			objetivo->position = glm::vec3(position);
			objetivo->name = "Nave de combate";
		}

		glm::vec3 origen_misil() {
			glm::vec3 left = glm::cross(glm::vec3(up), glm::vec3(front));

			if (misil_lado_derecho) {
				return glm::vec3(position) - left*0.12f;
			} else {
				return glm::vec3(position) + left*0.12f;
			}
		}

		bool control_avanzar;
		bool control_retroceder;
		bool control_giroizquierdo;
		bool control_giroderecho;
		bool control_giroarriba;
		bool control_giroabajo;
		bool control_girobarril1;
		bool control_girobarril2;
		bool misil_lado_derecho;

		glm::vec4 position;
		glm::vec4 up;
		glm::vec4 front;

		glm::vec3 desplazamiento;
		glm::mat4 giro;

		Objetivo* objetivo;
};

#include "bezier.h"
class ModeloMisil {
	public:
	ModeloMisil(glm::vec3 position, std::vector<glm::vec3> v) : position(position), v(v), t(0.0) {
		velocidad = 0.0001;
	}

	void processFrame() {
		glm::vec3 last_position = position;
		position = bezier_eval(v,t);

		float distance = glm::distance(last_position, position);
		if (distance > 0.0) {
			velocidad =  velocidad * 0.025 / distance;
		}
		direction = glm::normalize(position - last_position);
		if (t<1.0) t = t + velocidad;
	}

	glm::vec3 direction;
	glm::vec3 position;
	std::vector<glm::vec3> v;
	float t;
	float velocidad;
};

#define NAVES_EN_ESCUADRON 3
Nave escuadron[NAVES_EN_ESCUADRON];
Nave* nave_seleccionada = escuadron+0;
std::list<ModeloMisil*> misiles;

class Camara {
	public:
		void actualizar_parametros(
			const glm::vec3& new_direction, 
			const glm::vec3& new_position,
			const glm::vec3& new_up) {

			if (position[0] != position[0]) {
				position = new_position;
			}
			if (direction[0] != direction[0]) {
				direction = new_direction;
			}
			if (up[0] != up[0]) {
				up= new_up;
			}

			if (glm::distance(position, new_position) < 0.05) {
				position = new_position;
			} else {
				position = position + (new_position - position) * 0.2f;
			}

			glm::vec3 eje;
			if (glm::dot(direction, new_direction) > 0.9) {
				direction = new_direction;
			} else {
				if (glm::distance(direction, glm::vec3(0.0,0.0,0.0))<0.5) {
					direction = new_direction;
				} else {
					eje = glm::cross(direction, new_direction);
					float angle = abs(acos(glm::dot(direction,new_direction)));
					direction = glm::vec3(
						glm::rotate(glm::mat4(1.0), angle*10.0f, eje) * glm::vec4(direction,1.0));
				}
			}
			if (glm::dot(up,new_up) > 0.9) {
				up = new_up;
			} else {
				if (glm::distance(up, glm::vec3(0.0,0.0,0.0))<0.5) {
					up = new_up;
				} else {
					eje = glm::cross(up, new_up);
					float angle = abs(acos(glm::dot(up,new_up)));
					up = glm::vec3(
						glm::rotate(glm::mat4(1.0), angle*10.0f, eje) * glm::vec4(up,1.0));
				}
			}
		}

		glm::mat4 view() {
			Shader::cameraDirection = direction;
			Shader::cameraPosition = position;
			Shader::cameraUp = up;

			return glm::lookAt(
				Shader::cameraPosition, 
				Shader::cameraPosition + Shader::cameraDirection, 
				Shader::cameraUp
			);
		}

	private:

		glm::vec3 up, direction, position;
};

Camara camara_principal;
Camara camara_objetivo;

void update_view_matrix() {
	glm::vec3 look_at, up;

	if (camara_mode == 2) {
		up = glm::vec3(nave_seleccionada->up);

		if (camara_dist<=0.0) {
			look_at = glm::vec3(nave_seleccionada->position) + glm::vec3(nave_seleccionada->front);
			posicion_camara = glm::vec3(nave_seleccionada->position);
		} else {
			float f = camara_dist * 0.9;
			look_at = glm::vec3(nave_seleccionada->position); /* + glm::vec3(nave_seleccionada->front[0]*f,nave_seleccionada->front[1]*f,nave_seleccionada->front[2]*f) */;
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

	camara_principal.actualizar_parametros( glm::normalize(look_at - posicion_camara ), posicion_camara, up);
	View = camara_principal.view();


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

	if (key == 9) {
		nave_seleccionada++;
		if (nave_seleccionada-escuadron > 2) nave_seleccionada = escuadron;
	}
	if (key == 't') {
		objetivo_actual++;
		if (objetivo_actual+1 > objetivos.size()) objetivo_actual = 0;
	}

	if (key == 'g') {
		distancia_p1 = distancia_p1 + 0.05;
	}
	if (key == 'b') {
		distancia_p1 = distancia_p1 - 0.05;
	}
	if (key == 'h') {
		distancia_p2 = distancia_p2 - 0.05;
	}
	if (key == 'n') {
		distancia_p2 = distancia_p2 + 0.05;
	}
	if (key == 'm') {
		bezier_misil_configuracion = !bezier_misil_configuracion; 
	}

	if (key == 0x20) /*space bar*/ {
		// calcular los puntos de control para la curva de bezier del misil
		glm::vec3 p0 = nave_seleccionada->origen_misil();
		glm::vec3 p1 = p0 + glm::vec3(nave_seleccionada->front)*distancia_p1;
		glm::vec3 p2 = glm::vec3(objetivos.at(objetivo_actual)->position) - glm::vec3(nave_seleccionada->front)*distancia_p2;
		glm::vec3 p3 = glm::vec3(objetivos.at(objetivo_actual)->position);

		std::vector<glm::vec3> v;
		v.push_back(p0);
		v.push_back(p1);
		v.push_back(p2);
		v.push_back(p3);

		misiles.push_back(new ModeloMisil(nave_seleccionada->origen_misil(),v));
		nave_seleccionada->misil_lado_derecho = !nave_seleccionada->misil_lado_derecho;
	}

	if (key == 'y') {
		int mejor_objetivo = -1;
		float mejor_distancia = -1.0f;
		for (int i=0; i<objetivos.size();i++){
			Objetivo* objetivo = objetivos.at(i);
			float distance = glm::dot(
				glm::normalize(objetivo->position- glm::vec3(nave_seleccionada->position)),
				glm::normalize(glm::vec3(nave_seleccionada->front))
				);

			if (distance > mejor_distancia) {
				mejor_distancia = distance;
				mejor_objetivo = i;
			}
		}

		objetivo_actual = mejor_objetivo;
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
	if (key == 'f') {
		glutFullScreenToggle();
		fullscreen = !fullscreen;
		
		if (fullscreen) {
			xresolution = 1600; yresolution = 900;
		} else {
			xresolution = 1360; yresolution = 768;
		}
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

#include "material_difuso_relieve.h"

void init() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	Texture* background = new BitmapTexture("background.bmp");
	Material* material;

	esfera_del_cielo = new ModelObject(
		new Esfera(new MaterialTextura(background), 20, false),
				glm::scale(glm::mat4(1.0),glm::vec3(100.0,100.0,100.0))
		);

	Texture* textura_planeta = new BitmapTexture("planeta.bmp");
	Texture* normal_planeta = new BitmapTexture("planeta_normals.bmp");
	MaterialDifusoRelieve* material_planeta = new MaterialDifusoRelieve(textura_planeta, normal_planeta);
	material_planeta->kaSetter->set(0.0);
	material_planeta->kdSetter->set(1.0);
	material_planeta->ksSetter->set(0.0);
	material_planeta->intensidadDifusoSetter->set(1.0);
	material_planeta->intensidadRelieveSetter->set(0.0);

	planeta = new ModelObject(
		new Esfera(material_planeta, 20, false),
			glm::scale(
				glm::translate(glm::mat4(1.0), glm::vec3(50.0, 10.0, 16.0)),
				glm::vec3(55,55,55)
				)
		);


	escuadron[1].position = glm::vec4(-1.0,-1.0,0.0,1.0);
	escuadron[2].position = glm::vec4(-1.0,1.0,0.0,1.0);


	Material* material_color_blanco = new MaterialColorSolido(glm::vec3(1.0,1.0,1.0),false);
	light_sphere = new Esfera(material_color_blanco, 10);


	Material* material_color_gris_oscuro = new MaterialColorSolido(glm::vec3(0.2,0.2,0.2));
	basuraEspacial = new Esfera(material_color_gris_oscuro, 5);

	objects.push_front(new ModelObject(new NaveNodriza(background), 
		
		glm::rotate(
			glm::translate(glm::mat4(1.0), glm::vec3(15.0,0.0,0.0)),
			32.0f,
			glm::vec3(0.0,0.0,1.0)
			)
		
		));

		Objetivo* objetivo = new Objetivo;
		objetivo->position = glm::vec3(15.0,0.0,0.0);
		objetivo->distancia_camara = 4.0;
		objetivos.push_back(objetivo);

	 srand ( time(NULL) );
	for (int i=0; i<10; i++) {
		glm::vec3 desplazamiento = glm::normalize(glm::vec3(rand()%10000/1000.0 - 5.0,rand()%10000/1000.0 - 5.0,rand()%10000/1000.0 - 5.0));
		glm::vec3 eje = glm::normalize(glm::vec3(rand()%10000/1000.0 - 5.0,rand()%10000/1000.0 - 5.0,rand()%10000/1000.0 - 5.0));
		float angle = rand()%10000 / 1000.0;
		float distancia = rand()%100/100.0 + 2.5;
		glm::vec3 position = glm::vec3(15.0,0.0,0.0) + distancia * desplazamiento;

		Objetivo* objetivo = new Objetivo;
		objetivo->position = position;
		objetivo->distancia_camara = 1.0;
		objetivos.push_back(objetivo);

		objects.push_front(new ModelObject(new Asteroide(), 
			glm::rotate(
				glm::translate(glm::mat4(1.0), position),
				70.0f,
				eje
				)
			));
	}

	nave_combate = new ModelObject(new NaveCombate(background));
	curva_bezier = new CurvaBezier();

	std::vector<glm::vec3> v;

	v.push_back(glm::vec3(0.0,0.0,0.0));
	v.push_back(glm::vec3(2.0,0.0,0.0));
	v.push_back(glm::vec3(4.0,2.0,0.0));
	v.push_back(glm::vec3(7.0,2.0,0.0));

	curva_bezier->actualizar_puntos_de_control(v);

	targetQuad = new TargetQuad();
	misil = new Misil(true);

	update_view_matrix();
}

void glut_animate() {
	glutPostRedisplay();
	Sleep(15);
}
int loc;

#include "cubo_texturado.h"


void render_scene(
	int viewportx,
	int viewporty,
	int width,
	int height,
	bool target_quad);

void glut_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render_scene(0,0,xresolution,yresolution,true);
	if (objetivo_actual != -1) {
		// limpiar el DEPTH buffer para asegurarse de que la escena se renderize encima de todo
		glClear(GL_DEPTH_BUFFER_BIT);
		render_scene(0,0,xresolution/5,yresolution/5,false);
	}
	
	glFlush();
    glutSwapBuffers();
}


void render_scene(
	int viewportx,
	int viewporty,
	int width,
	int height,
	bool target_quad) {

  // do display
	glViewport(viewportx,viewporty,width,height);

	if (target_quad) {
		update_view_matrix();
	} else {
		Objetivo* objetivo = objetivos.at(objetivo_actual);

		glm::vec3 look_at, up, direction;

		direction = glm::normalize(glm::vec3(nave_seleccionada->position) - objetivo->position);
		up = glm::vec3(nave_seleccionada->up);
		look_at = objetivo->position;
		posicion_camara = look_at + direction * objetivo->distancia_camara;

		camara_objetivo.actualizar_parametros( glm::normalize(look_at - posicion_camara ), posicion_camara, up);
		View = camara_objetivo.view();
	}

	glm::mat4 prMatrix;
	prMatrix = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	glm::mat4 centerView       = glm::lookAt(
		glm::vec3(0.0,0.0,0.0), 
		glm::vec3(0.0,0.0,0.0) + Shader::cameraDirection, 
		glm::vec3(Shader::cameraUp)
	);

	Shader::projectionMatrix = prMatrix * centerView;
	esfera_del_cielo->dibujar(glm::mat4(1.0));
	planeta->dibujar(glm::mat4(1.0));

    glClear(GL_DEPTH_BUFFER_BIT);

	for (int i=0; i<NAVES_EN_ESCUADRON; i++) {
	escuadron[i].processFrame();
	}

	std::list<ModeloMisil*> remove_list;
	for (std::list<ModeloMisil*>::iterator it = misiles.begin();
		it != misiles.end();
		it++) {

		ModeloMisil* modelo_misil = (*it);
		modelo_misil->processFrame();
		if (modelo_misil->t>0.99) {
			remove_list.push_back(modelo_misil);
		}
	}

	for (std::list<ModeloMisil*>::iterator it = remove_list.begin();
		it != remove_list.end();
		it++) {

		ModeloMisil* modelo_misil = (*it);

		misiles.remove(modelo_misil);
		delete modelo_misil;
	}

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

	for (int i=-2; i<2; i++) {
	for (int j=-2; j<2; j++) {
	for (int k=-2; k<2; k++) {
	basuraEspacial->dibujar(glm::translate(glm::mat4(1.0),origin + glm::vec3(i,j,k)) * matriz_scala);
	}
	}
	}

	for (std::list<ModeloMisil*>::iterator it = misiles.begin();
		it != misiles.end();
		it++) {
		ModeloMisil* modelo_misil = (*it);
		glm::vec3 front = modelo_misil->direction;
		glm::vec3 up = glm::normalize(glm::cross(front,glm::vec3(0.0,1.0,0.0)));

		if (glm::distance(up,glm::vec3(0.0,0.0,0.0))<0.2) {
			up = glm::normalize(glm::cross(front,glm::vec3(1.0,0.0,0.0)));
		}

		glm::vec3 left = glm::normalize(glm::cross(up,front));

		glm::mat3 rotation_matrix(
			front,
			left,
			up);

		misil->dibujar(
			glm::translate(glm::mat4(1.0),modelo_misil->position) *
			glm::scale(glm::mat4(1.0), glm::vec3(0.2,0.2,0.2)) *
			glm::mat4(rotation_matrix)
			);
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

	if (target_quad) {

		if (objetivo_actual != -1) {
				if (bezier_misil_configuracion) {
					// calcular los puntos de control para la curva de bezier del misil
					glm::vec3 p0 = nave_seleccionada->origen_misil();
					glm::vec3 p1 = p0 + glm::vec3(nave_seleccionada->front)*distancia_p1;
					glm::vec3 p2 = glm::vec3(objetivos.at(objetivo_actual)->position) - glm::vec3(nave_seleccionada->front)*distancia_p2;
					glm::vec3 p3 = glm::vec3(objetivos.at(objetivo_actual)->position);


					std::vector<glm::vec3> v;
					v.push_back(p0);
					v.push_back(p1);
					v.push_back(p2);
					v.push_back(p3);

					curva_bezier->actualizar_puntos_de_control(v);

					curva_bezier->dibujar(glm::mat4(1.0));
					glm::mat4 matriz_escala = glm::scale(glm::mat4(1.0), glm::vec3(0.05,0.05,0.05));

					light_sphere->dibujar(glm::translate(glm::mat4(1.0), p1) * matriz_escala);
					light_sphere->dibujar(glm::translate(glm::mat4(1.0), p2) * matriz_escala);
				}

				glm::vec3 objetivo_cercano;

				float f = glm::distance(posicion_camara, glm::vec3(objetivos.at(objetivo_actual)->position));
				glm::vec3 original_direction = glm::normalize(glm::vec3(objetivos.at(objetivo_actual)->position) - posicion_camara);
				if (f>20.0) {
					f = 20.0;
				}

				glm::vec3 direction = original_direction;

				float angle = acos(glm::dot(original_direction, Shader::cameraDirection));
				glm::vec3 eje = glm::cross(original_direction, Shader::cameraDirection);
			
				if (angle > 0.1) { 
					if (angle > 1.0) angle = 1.0;
					if (angle < -1.0) angle = -1.0;
					direction = glm::vec3( glm::rotate(glm::mat4(1.0), -angle*180.0f/3.1415926536f, eje) * glm::vec4(Shader::cameraDirection,1.0));
				}

				objetivo_cercano = Shader::cameraPosition + direction * f;

				glm::vec3 left = glm::normalize(glm::cross(glm::vec3(nave_seleccionada->up), Shader::cameraDirection));
				glm::vec3 front = glm::normalize(Shader::cameraDirection);
				glm::vec3 up = glm::vec3(nave_seleccionada->up);
				glm::mat3 idd(
					front[0], front[1], front[2],
					left[0], left[1], left[2],
					up[0], up[1], up[2]);
				glm::mat4 rotacion_hacia_camara(idd);

				glm::mat4 transform_matrix =
					glm::translate(glm::mat4(1.0), glm::vec3(objetivo_cercano)) * rotacion_hacia_camara
					;

				targetQuad->dibujar(
		 			 transform_matrix
				);
		}
	}
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

  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  fullscreen = false;
  glutInitWindowSize(1360, 768);
  glutInitWindowPosition ( 0, 0 );
  glutCreateWindow("OpenGL APP TP3");

  if (fullscreen) {
	  xresolution = 1600; yresolution = 900;
  } else {
	  xresolution = 1360; yresolution = 768;
  }

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

  //glutGameModeString("1600x900:32");
//  glutLeaveGameMode(); 

//  glutFullScreen();
  std::cout << "carga completa" << std::endl;
  glutMainLoop();
}

