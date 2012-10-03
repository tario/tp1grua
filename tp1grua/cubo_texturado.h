#include "cubo.h" 
#include "texture.h"
#include "texture_shader.h"

class CuboTexturado : public Cubo {
public:

	CuboTexturado(Texture* texture);
	void dibujar(const glm::mat4& m);
private:
	float* extra_data;
	Texture* texture;
	TextureShader* textureShader;
};
