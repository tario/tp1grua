#ifndef __BUMP_MAPPING_SHADER_H
#define __BUMP_MAPPING_SHADER_H

#include "shader.h"
#include "glm/glm.hpp"

class BumpMappingShader : public Shader {
public:
	BumpMappingShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setCameraDirection(const glm::vec3& v);
	void setTextureUnit(int unitnumber);
	void setNormalmapUnit(int unitnumber);

	void setLightningParameters(float ka, float kd, float ks);

	static BumpMappingShader* instance();
private:
	int transform_matrix_index;
	int projection_matrix_index;
	int texture_location;
	int camera_direction_index;
	int normal_matrix_index;
	int normal_map_index;

	int ka_index, kd_index, ks_index;
};

#endif