#include "stdafx.h"
#include "torre.h"
#include "model_object.h"

static const float border = 0.2744;
static const glm::vec3 ocre = glm::vec3(0.6, 0.7, 0.0);
static CuboTexturado::Cara cara_solida(0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.1, 0.0);
	
static CuboTexturado::Cara caras_cubo_solido[] = {
	cara_solida,cara_solida,cara_solida,cara_solida,cara_solida,cara_solida
};

static CuboTexturado::Cara caras[] = {
	CuboTexturado::Cara(1.0, border/4+border*3/4, 0.0, border/4+border*3/4, 0.0, 0.0+border*3/4, 1.0, 0.0+border*3/4),
	CuboTexturado::Cara(1.0, border/4+border/2, 0.0, border/4+border/2, 0.0, 0.0+border/2, 1.0, 0.0+border/2),
	CuboTexturado::Cara(1.0, border/4+border/4, 0.0, border/4+border/4, 0.0, 0.0+border/4, 1.0, 0.0+border/4),
	CuboTexturado::Cara(1.0, border/4, 0.0, border/4, 0.0, 0.0, 1.0, 0.0),
	CuboTexturado::Cara(0.0, 0.2, 0.0, 0.0, 0.5, 0.0, 0.5, 0.2),
	CuboTexturado::Cara(0.0, 0.2, 0.0, 0.0, 0.5, 0.0, 0.5, 0.2)
};

static glm::mat4 ajuste_proporcion = glm::scale(glm::mat4(1.0), glm::vec3(1.0, 1.0, 2.0));
static float z_factor = 2.7;

Torre::Torre() : 
	// inicializar textura
	texture("textura.bmp"),
	// inicializar primitivas graficas
	cubo(&texture, caras),
	solido(&texture, caras_cubo_solido),
	// inicializar objetos del modelo
	columna11(&cubo, ModelObject::cell_matrix(-0.5,-0.4, -0.5,-0.4,-0.5,0.45) ),
	columna12(&cubo, ModelObject::cell_matrix(-0.5,-0.4, 0.4,0.5,-0.5,0.45) ),
	columna21(&cubo, ModelObject::cell_matrix(0.4,0.5, -0.5,-0.4,-0.5,0.45) ),
	columna22(&cubo, ModelObject::cell_matrix(0.4,0.5, 0.4,0.5,-0.5,0.45) ),
	base(&solido, ModelObject::cell_matrix(-0.5,0.5,-0.5,0.5,0.45,0.5)),

	viga11_1(&solido),
	viga11_2(&solido),
	viga11_3(&solido),
	viga11_4(&solido),
	viga22_1(&solido, ModelObject::cell_matrix(-0.5,-0.4, -0.5,-0.3,-0.5,0.45)),
	viga22_2(&solido, ModelObject::cell_matrix(-0.5,-0.4, -0.5,-0.3,-0.5,0.45)),
	viga22_3(&solido, ModelObject::cell_matrix(-0.5,-0.4, -0.5,-0.3,-0.5,0.45)),
	viga22_4(&solido, ModelObject::cell_matrix(-0.5,-0.4, -0.5,-0.3,-0.5,0.45))

	{

	calcular_viga_cruzada(viga11_1, glm::vec3(-0.45, -0.45, -0.4), glm::vec3(-0.45, 0.45, -0.04));
	calcular_viga_cruzada(viga11_2, glm::vec3(-0.45, -0.45, -0.04), glm::vec3(-0.45, 0.45, -0.4));
	calcular_viga_cruzada(viga11_3, glm::vec3(-0.45, -0.45, 0.04), glm::vec3(-0.45, 0.45, 0.4));
	calcular_viga_cruzada(viga11_4, glm::vec3(-0.45, -0.45, 0.4), glm::vec3(-0.45, 0.45, 0.04));

	calcular_viga_cruzada(viga22_1, glm::vec3(0.45, -0.45, -0.4), glm::vec3(0.45, 0.45, -0.04));
	calcular_viga_cruzada(viga22_2, glm::vec3(0.45, -0.45, -0.04), glm::vec3(0.45, 0.45, -0.4));
	calcular_viga_cruzada(viga22_3, glm::vec3(0.45, -0.45, 0.04), glm::vec3(0.45, 0.45, 0.4));
	calcular_viga_cruzada(viga22_4, glm::vec3(0.45, -0.45, 0.4), glm::vec3(0.45, 0.45, 0.04));
}

void Torre::calcular_viga_cruzada(ModelObject& mo, const glm::vec3& p0, const glm::vec3& p1) {
	mo.set_model_matrix(
		ModelObject::adjust_z(
		ModelObject::line(
			glm::vec3(p0[0], p0[1], p0[2]*z_factor),
			glm::vec3(p1[0], p1[1], p1[2]*z_factor),
			0.1,
			0.1, 1.0/z_factor), 
			z_factor)
	);
}

void Torre::dibujar(const glm::mat4& m) {
	this->columna11.dibujar(m);
	this->columna12.dibujar(m);
	this->columna21.dibujar(m);
	this->columna22.dibujar(m);
	this->base.dibujar(m);

	this->viga11_1.dibujar(m);
	this->viga11_2.dibujar(m);
	this->viga11_3.dibujar(m);
	this->viga11_4.dibujar(m);
	this->viga22_1.dibujar(m);
	this->viga22_2.dibujar(m);
	this->viga22_3.dibujar(m);
	this->viga22_4.dibujar(m);
}
