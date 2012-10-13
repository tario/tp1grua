#include "dibujable.h"
#include "cubo_texturado.h"

class Piso : public Dibujable {
public:
	Piso();

	void dibujar(const glm::mat4& m);

private:
	CuboTexturado cubo;
};
