#include "stdafx.h"
#include "nave_nodriza.h"
#include "null_texture.h"

NaveNodriza::NaveNodriza() : 
	textura_nave("nave.bmp"),
	material1(&textura_nave, NullTexture::instance(), NullTexture::instance()),
	material2(&textura_nave, NullTexture::instance(), NullTexture::instance()),
	material3(glm::vec3(0.25,0.25,0.25),true)
{
	material1.kaSetter->set(0.05);
	material1.kdSetter->set(1.5);
	material1.ksSetter->set(0.0);
	material1.intensidadDifusoSetter->set(1.0);	

	motor = Motor::instance(&material1, &material3);
}

void NaveNodriza::dibujar(const glm::mat4& m) {
	motor->dibujar(m);
}