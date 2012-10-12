#ifndef __MODEL_OBJECT
#define __MODEL_OBJECT

#include "dibujable.h"

class ModelObject : public Dibujable{
public:

	ModelObject(Dibujable* primitiva);
	ModelObject(Dibujable* primitiva, const glm::mat4& model_matrix);

	void dibujar(const glm::mat4& project_view);
	void set_model_matrix(const glm::mat4& m);

	static glm::mat4 cell_matrix(
	float xdown, float xup, float ydown, float yup, float zdown, float zup
	);

	static glm::mat4 line(const glm::vec3& p0, const glm::vec3& p1, float anchox, float anchoy);

private:
	glm::mat4 model_matrix;
	Dibujable* primitiva;
};

#endif
