#include "shader.h"
#include "glm/glm.hpp"

class ColorShader : public Shader {
public:
	ColorShader();

	void setTransformMatrix(const glm::mat4& m);

	static ColorShader* instance();

private:
	int transform_matrix_index;
};
