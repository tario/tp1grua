#include "dibujable.h"
#include "cubo_texturado.h"
#include "olas.h"

class Agua : public Dibujable {
public:
	Agua();

	void dibujar(const glm::mat4& m);

private:
	Texture texture;
	CuboTexturado cubo;
	Olas olas;
};
