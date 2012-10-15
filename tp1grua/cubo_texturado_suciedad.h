#ifndef __CUBO_TEXTURADO_SUCIEDAD_H
#define __CUBO_TEXTURADO_SUCIEDAD_H

#include "cubo.h" 
#include "texture.h"
#include "cubo_texturado.h"
#include "dirtness_shader.h"

class CuboTexturadoSuciedad : public Cubo {
public:
	CuboTexturadoSuciedad(
		Texture* texture,
		Texture* mapa_suciedad,
		CuboTexturado::Cara* caras,
		float suciedad = 0.5);
	void dibujar(const glm::mat4& m);

	void cambiar_suciedad(float suciedad);
private:
	float* extra_data;
	Texture* texture;
	Texture* mapa_suciedad;
	DirtnessShader* dirtnessShader;
	float suciedad;
};

#endif
