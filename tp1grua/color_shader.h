#ifndef __COLOR_SHADER_H
#define __COLOR_SHADER_H

#include "shader.h"
#include "glm/glm.hpp"

class ColorShader : public Shader {
public:
	ColorShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setCameraDirection(const glm::vec3& v);

	static ColorShader* instance();

private:
	int transform_matrix_index;
	int projection_matrix_index;
	int camera_direction_index;

};

#endif
