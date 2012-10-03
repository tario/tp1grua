#include "cubo.h" 
#include "texture.h"
#include "shader.h"

class CuboTexturado : public Cubo {
public:

	CuboTexturado(Texture* texture);
	void dibujar(const glm::mat4& m);
private:
	float* extra_data;
	Texture* texture;
	Shader* textureShader;
	int transform_matrix_index;
	int texture_location;
};
