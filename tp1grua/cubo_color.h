#include "cubo.h"
#include "color_shader.h"

class CuboColor : public Cubo {
public:
	CuboColor(const glm::vec3& color);
	CuboColor(
		const glm::vec3& colorzp,
		const glm::vec3& colorzm,
		const glm::vec3& colorxp,
		const glm::vec3& colorxm,
		const glm::vec3& coloryp,
		const glm::vec3& colorym
		);

	void dibujar(const glm::mat4& m);
private:
	ColorShader* colorShader;

	void initCube(
		const glm::vec3& colorzp,
		const glm::vec3& colorzm,
		const glm::vec3& colorxp,
		const glm::vec3& colorxm,
		const glm::vec3& coloryp,
		const glm::vec3& colorym
		);
};

