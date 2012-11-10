#ifndef __TEXTURE_WAVES_SHADER
#define __TEXTURE_WAVES_SHADER

#include "shader.h"
#include "glm/glm.hpp"

class TextureWavesShader : public Shader {
public:
	TextureWavesShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setTextureUnit(int unitnumber);
	void setFase(float fase);
	void setFase2(float fase2);
	static TextureWavesShader* instance();
private:
	int transform_matrix_index;
	int projection_matrix_index;
	int texture_location;
	int fase_location;
	int fase2_location;
};

#endif
