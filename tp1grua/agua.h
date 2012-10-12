#include "dibujable.h"
#include "cubo_color.h"

class Agua : public Dibujable {
public:
	Agua();

	void dibujar(const glm::mat4& m);

private:
	CuboColor cubo;
};
