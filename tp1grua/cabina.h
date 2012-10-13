#ifndef __CABINA_H
#define __CABINA_H

#include "dibujable.h"
#include "cubo_color.h"
#include "brazo.h" 

class Cabina : public Dibujable {
	public:
		Cabina();
		void dibujar(const glm::mat4& m);

		void girar_brazo(float angulo);
		void longitud_cable(float delta);
	private:
		void actualizar_matrices_brazo();

		CuboColor cubo;
		CuboColor contra_peso;
		CuboColor cable;
		CuboColor gancho;
		Brazo brazo;

		glm::mat4 m_contra_peso;
		glm::mat4 m_brazo, m_cable, m_gancho;

		float angulo_brazo;
		float _longitud_cable;
};

#endif
