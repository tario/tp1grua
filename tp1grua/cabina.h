#ifndef __CABINA_H
#define __CABINA_H

#include "dibujable.h"
#include "cubo_color.h"
#include "cubo_texturado_suciedad.h"
#include "texture.h"
#include "brazo.h" 
#include "model_object.h"
#include "prisma.h"

class Cabina : public Dibujable {
	public:
		Cabina();
		void dibujar(const glm::mat4& m);

		void girar_brazo(float angulo);
		void longitud_cable(float delta);
		void suciedad(float _suciedad);
	private:
		void actualizar_matrices_brazo();

		ModelObject mo_cubo;
		ModelObject mo_contra_peso;
		ModelObject mo_cable;
		ModelObject mo_gancho;
		ModelObject mo_brazo;

		CuboTexturadoSuciedad cubo;
		CuboColor contra_peso;
		CuboColor cable;
		Prisma gancho;
		Brazo brazo;

		float angulo_brazo;
		float _longitud_cable;

		Texture textura_cabina;
		Texture mapa_suciedad;
};

#endif
