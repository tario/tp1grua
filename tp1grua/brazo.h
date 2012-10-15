#ifndef __BRAZO_H
#define __BRAZO_H

#include "dibujable.h"
#include "cubo_texturado.h"
#include "texture.h"
#include "model_object.h"

class Brazo: public Dibujable {
public:
	Brazo();
	void dibujar(const glm::mat4& m);
private:
	CuboTexturado cubo;

	ModelObject columna11, columna12, columna21, columna22;
	ModelObject viga_lateral_1, viga_lateral_2, viga_lateral_3, viga_lateral_4;
	Texture texture;

	void dibujar_vigas_laterales(const glm::mat4& m);
};


#endif
