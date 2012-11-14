#ifndef __CUBO_COLOR_H
#define __CUBO_COLOR_H

#include "cubo.h"
#include "material.h"

class CuboColor : public Cubo {
public:
	CuboColor(Material* material, const glm::vec3& color);
	CuboColor(
		Material* material,
		const glm::vec3& colorzp,
		const glm::vec3& colorzm,
		const glm::vec3& colorxp,
		const glm::vec3& colorxm,
		const glm::vec3& coloryp,
		const glm::vec3& colorym
		);

	void dibujar(const glm::mat4& m);
private:
	Material* material;

	void initCube(
		const glm::vec3& colorzp,
		const glm::vec3& colorzm,
		const glm::vec3& colorxp,
		const glm::vec3& colorxm,
		const glm::vec3& coloryp,
		const glm::vec3& colorym
		);
};

#endif
