#include "cubo.h" 
#include "texture.h"
#include "texture_shader.h"

class CuboTexturado : public Cubo {
public:
	struct Cara {
		float coords[8];
		Cara(float* _coords) {
			memcpy(coords, _coords, sizeof(coords));
		}
	};

	CuboTexturado(Texture* texture, Cara* caras);
	void dibujar(const glm::mat4& m);
private:
	float* extra_data;
	Texture* texture;
	TextureShader* textureShader;
};
