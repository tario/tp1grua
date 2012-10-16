#ifndef __OLAS_H
#define __OLAS_H

#include "dibujable.h"
#include "texture.h"
#include "texture_waves_shader.h"

class Olas : public Dibujable {
	public:
		Olas::Olas(Texture* texture);
		void dibujar(const glm::mat4& m);

	private:
		Texture* texture;
		TextureWavesShader* textureWavesShader;
		GLuint vaoHandle;
};

#endif