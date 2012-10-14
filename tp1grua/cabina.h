#ifndef __CABINA_H
#define __CABINA_H

#include "dibujable.h"
#include "cubo_color.h"
#include "cubo_texturado.h"
#include "texture.h"
#include "brazo.h" 
#include "model_object.h"

class Cabina : public Dibujable {
	public:
		Cabina();
		void dibujar(const glm::mat4& m);

		void girar_brazo(float angulo);
		void longitud_cable(float delta);
	private:
		void actualizar_matrices_brazo();

		ModelObject mo_cubo;
		ModelObject mo_contra_peso;
		ModelObject mo_cable;
		ModelObject mo_gancho;
		ModelObject mo_brazo;

		CuboTexturado cubo;
		CuboColor contra_peso;
		CuboColor cable;
		CuboColor gancho;
		Brazo brazo;

		float angulo_brazo;
		float _longitud_cable;

		Texture textura_cabina;
};

#endif
