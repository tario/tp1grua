#ifndef __TEXTURE_SHADER_H
#define __TEXTURE_SHADER_H

#include "shader.h"
#include "glm/glm.hpp"

class TextureShader : public Shader {
public:
	TextureShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setTextureUnit(int unitnumber);

	static TextureShader* instance();
private:
	int transform_matrix_index;
	int projection_matrix_index;
	int texture_location;
};

#endif
