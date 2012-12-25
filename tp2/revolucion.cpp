#include "stdafx.h"
#include "revolucion.h"
#include "circunferencia.h"

Revolucion::Revolucion(
				FuncionConjuntoPuntos* funcionConjuntoPuntos,
				float radio,
				float h,
				Material* material,
				float t_inicial, float t_final
			) :

	barrido(
			funcionConjuntoPuntos,
			&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.0,1.0),glm::vec3(radio,0.0,0.0)),
			&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,radio,0.0)),
			&Circunferencia(glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.0,1.0),glm::vec3(1.0,0.0,0.0)),
			h,
			material,
			t_inicial,
			t_final,
			(t_inicial > 0.0 || t_final < 1.0) ? true : false
		)
	{


}

void Revolucion::dibujar(const glm::mat4& m) {
	barrido.dibujar(m);
}