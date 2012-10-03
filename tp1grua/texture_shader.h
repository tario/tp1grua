#include "shader.h"
#include "glm/glm.hpp"

class TextureShader : public Shader {
public:
	TextureShader();

	void setTransformMatrix(const glm::mat4& m);
	void setTextureUnit(int unitnumber);

	static TextureShader* instance();
private:
	int transform_matrix_index;
	int texture_location;
};
