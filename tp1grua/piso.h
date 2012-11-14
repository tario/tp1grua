#include "dibujable.h"
#include "cubo_texturado.h"
#include "bump_mapping_material.h"

class Piso : public Dibujable {
public:
	Piso();

	void dibujar(const glm::mat4& m);

private:
	MaterialBumpMapping material;
	CuboTexturado cubo;
};
