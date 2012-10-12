#include "dibujable.h"
#include "cubo_color.h"

class Piso : public Dibujable {
public:
	Piso();

	void dibujar(const glm::mat4& m);

private:
	CuboColor cubo;
};
