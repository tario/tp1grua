#ifndef __SOLID_COLOR_SHADER_H
#define __SOLID_COLOR_SHADER_H

#include "shader.h"
#include "shader_program.h"
#include "glm/glm.hpp"

class SolidColorShader {
public:
	SolidColorShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setCameraDirection(const glm::vec3& v);
	void setCameraPosition(const glm::vec3& v);
	void setColor(const glm::vec3& color);

	static SolidColorShader* instance();

private:
	ShaderProgram* shader;

	int transform_matrix_index;
	int projection_matrix_index;
	int camera_direction_index;
	int normal_matrix_index;
	int camera_position_index;
	int color_index;
};

#endif
