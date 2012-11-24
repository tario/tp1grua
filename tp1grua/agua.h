#include "dibujable.h"
#include "cubo_texturado.h"
#include "olas.h"
#include "material_textura.h"
#include "bitmap_texture.h"

class Agua : public Dibujable {
public:
	Agua();

	void dibujar(const glm::mat4& m);

private:
	BitmapTexture texture;
	MaterialTextura material;
	CuboTexturado cubo;
	Olas olas;
};
