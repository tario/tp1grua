#ifndef __BRAZO_H
#define __BRAZO_H

#include "dibujable.h"
#include "texture.h"
#include "model_object.h"
#include "material_textura_suciedad.h"
#include "cubo_texturado.h"

class Brazo: public Dibujable {
public:
	Brazo();
	void dibujar(const glm::mat4& m);
	void suciedad(float _suciedad);
private:
	CuboTexturado cubo;
	MaterialTexturaSuciedad material;

	ModelObject columna11, columna12, columna21, columna22;
	ModelObject viga_lateral_1, viga_lateral_2, viga_lateral_3, viga_lateral_4;
	Texture texture;
	Texture mapa_suciedad;

	void dibujar_vigas_laterales(const glm::mat4& m);
};


#endif
