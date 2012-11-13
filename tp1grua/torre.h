#ifndef __TORRE_H
#define __TORRE_H

#include "dibujable.h"
#include "cubo_texturado.h"
#include "texture.h"
#include "model_object.h"
#include "material.h"
#include "material_textura_suciedad_specular.h"

class Torre : public Dibujable {
	public:
		Torre();
		void dibujar(const glm::mat4& m);
		void suciedad(float _suciedad);
	private:
		Texture texture;
		Texture mapa_suciedad, mapa_specular;
		CuboTexturado cubo;
		CuboTexturado solido;

		MaterialTexturaSuciedadSpecular material;

		ModelObject columna11, columna12, columna22, columna21; // columnas de la torre
		ModelObject base; // la base encima de la torre que separa a la cabina de las vigas

		// vigas que se encuentran entre las columnas
		ModelObject viga11_1, viga11_2, viga11_3, viga11_4;
		ModelObject viga22_1, viga22_2, viga22_3, viga22_4;

		void calcular_viga_cruzada(ModelObject& mo, const glm::vec3& p0, const glm::vec3& p1);
		
};

#endif
