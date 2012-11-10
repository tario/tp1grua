#ifndef __DIRTNESS_SHADER_H
#define __DIRTNESS_SHADER_H

#include "shader.h"
#include "glm/glm.hpp"

class DirtnessShader : public Shader {
public:
	DirtnessShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setTextureUnit(int unitnumber);
	void setDirtmapUnit(int unitnumber);
	void setDirtlevel(float level); // 0.0-0.1

	static DirtnessShader* instance();

private:
	int transform_matrix_index;
	int projection_matrix_index;
	int texture_location;
	int dirtmap_location;
	int dirtlevel_location;
};

#endif
