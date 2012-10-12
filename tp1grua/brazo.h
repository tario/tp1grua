#ifndef __BRAZO_H
#define __BRAZO_H

#include "dibujable.h"
#include "cubo_color.h"

class Brazo: public Dibujable {
public:
	Brazo();
	void dibujar(const glm::mat4& m);
private:
	CuboColor cubo;
};


#endif
