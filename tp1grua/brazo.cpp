#include "stdafx.h" 
#include "brazo.h"

static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);
static CuboTexturado::Cara cara1(0.0,0.1,0.0,0.0,0.1,0.0,0.1,0.1);

static CuboTexturado::Cara caras[] = {
	cara1,cara1,cara1,cara1,cara1,cara1
};

static float z_factor = 4.0;
static void calcular_viga_cruzada(ModelObject& model_object, const glm::vec3& p0, const glm::vec3& p1){
	model_object.set_model_matrix(
		ModelObject::adjust_z(
			ModelObject::line(
				glm::vec3(p0[0], p0[1], p0[2]*z_factor),
				glm::vec3(p1[0], p1[1], p1[2]*z_factor),
				0.1, 
				0.1,
				1.0/z_factor),
				z_factor
			)
			);
}

Brazo::Brazo() : 
	material(&texture, &mapa_suciedad, &mapa_specular, 0.2),
	cubo(&material, caras), 
	texture("textura.bmp"), 
	mapa_suciedad("mapa-suciedad.bmp"),
	mapa_specular("mapa-specular.bmp"),
	columna11(&cubo, ModelObject::line(glm::vec3(-0.4, -0.4, -0.5), glm::vec3(-0.2, -0.2, 0.5), 0.1, 0.1)),
	columna12(&cubo, ModelObject::line(glm::vec3(-0.4, 0.4, -0.5), glm::vec3(-0.2, 0.2, 0.5), 0.1, 0.1)),
	columna21(&cubo, ModelObject::line(glm::vec3(0.4, -0.4, -0.5), glm::vec3(0.2, -0.2, 0.5), 0.1, 0.1)),
	columna22(&cubo, ModelObject::line(glm::vec3(0.4, 0.4, -0.5), glm::vec3(0.2, 0.2, 0.5), 0.1, 0.1)),
	viga_lateral_1(&cubo),
	viga_lateral_2(&cubo),
	viga_lateral_3(&cubo),
	viga_lateral_4(&cubo)
	{

	calcular_viga_cruzada(viga_lateral_1, glm::vec3(-0.35, -0.35, -0.25), glm::vec3(-0.35, 0.35, -0.25));
	calcular_viga_cruzada(viga_lateral_2, glm::vec3(-0.35, 0.35, -0.25), glm::vec3(0.35, 0.35, -0.25));
	calcular_viga_cruzada(viga_lateral_3, glm::vec3(0.35, 0.35, -0.25), glm::vec3(0.35, -0.35, -0.25));
	calcular_viga_cruzada(viga_lateral_4, glm::vec3(0.35, -0.35, -0.25), glm::vec3(-0.35, -0.35, -0.25));
}

void Brazo::dibujar_vigas_laterales(const glm::mat4& m) {
	viga_lateral_1.dibujar(m);
	viga_lateral_2.dibujar(m);
	viga_lateral_3.dibujar(m);
	viga_lateral_4.dibujar(m);
}

void Brazo::dibujar(const glm::mat4& m) {
	columna11.dibujar(m);
	columna12.dibujar(m);
	columna21.dibujar(m);
	columna22.dibujar(m);

	dibujar_vigas_laterales(m);

	dibujar_vigas_laterales(
		glm::scale(
			glm::translate(m,glm::vec3(0.0,0.0,0.25)),
			glm::vec3(0.7, 0.7, 1.0)
		));

	dibujar_vigas_laterales(
		glm::scale(
			glm::translate(m,glm::vec3(0.0,0.0,0.5)),
			glm::vec3(0.59, 0.59, 1.0)
		));

	dibujar_vigas_laterales(
		glm::scale(
			glm::translate(m,glm::vec3(0.0,0.0,0.75)),
			glm::vec3(0.5, 0.5, 1.0)
		));
}

void Brazo::suciedad(float _suciedad) {
	material.cambiar_suciedad(_suciedad);
}
