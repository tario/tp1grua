#include "dibujable.h"
#include "cubo_texturado.h"
#include "material_textura.h"

class Piso : public Dibujable {
public:
	Piso();

	void dibujar(const glm::mat4& m);

private:
	MaterialTextura material;
	CuboTexturado cubo;
};
