#ifndef __TEXTURE_WAVES_SHADER
#define __TEXTURE_WAVES_SHADER

#include "shader.h"
#include "glm/glm.hpp"

class TextureWavesShader : public Shader {
public:
	TextureWavesShader();

	void setTransformMatrix(const glm::mat4& m);
	void setProjectionMatrix(const glm::mat4& m);
	void setCameraDirection(const glm::vec3& v);
	void setLightningParameters(float ka, float kd, float ks);

	void setTextureUnit(int unitnumber);
	void setFase(float fase);
	void setFase2(float fase2);
	static TextureWavesShader* instance();
private:
	int transform_matrix_index;
	int projection_matrix_index;
	int texture_location;
	int camera_direction_index;
	int normal_matrix_index;
	int fase_location;
	int fase2_location;

	int ka_index, kd_index, ks_index;
};

#endif