#include "cubo.h" 
#include "texture.h"

class CuboTexturado : public Cubo {
public:

	CuboTexturado(Texture& texture);
	GLuint extraVertexInfo();

	void dibujar();
private:
	float* extra_data;
};
