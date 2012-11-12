#ifndef __CUBO_TEXTURADO_H
#define __CUBO_TEXTURADO_H

#include "cubo.h" 
#include "texture.h"
#include "texture_shader.h"
#include "material.h"

class CuboTexturado : public Cubo {
public:
	struct Cara {
		float coords[8];
		Cara(float* _coords) {
			memcpy(coords, _coords, sizeof(coords));
		}
		Cara(float x0, float y0, 
			float x1, float y1,
			float x2, float y2,
			float x3, float y3) {
			coords[0] = x0;	coords[1] = y0;
			coords[2] = x1; coords[3] = y1;
			coords[4] = x2; coords[5] = y2;
			coords[6] = x3; coords[7] = y3;
		}
	};

	CuboTexturado(Material* material, Cara* caras, bool carasuperior=true);
	void dibujar(const glm::mat4& m);
private:
	float* extra_data;
	Material* material;
	bool carasuperior;
};

#endif
