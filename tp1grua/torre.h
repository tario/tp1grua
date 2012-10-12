#ifndef __TORRE_H
#define __TORRE_H

#include "dibujable.h"
#include "cubo_color.h"

class Torre : public Dibujable {
	public:
		Torre();
		void dibujar(const glm::mat4& m);

	private:

		CuboColor cubo;
};

#endif
