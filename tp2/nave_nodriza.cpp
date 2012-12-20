#include "stdafx.h"
#include "nave_nodriza.h"
#include "null_texture.h"

NaveNodriza::NaveNodriza() : 
	textura_nave("nave.bmp"),
	material1(&textura_nave, NullTexture::instance(), NullTexture::instance()),
	material2(&textura_nave, NullTexture::instance(), NullTexture::instance()),
	material3(&textura_nave, NullTexture::instance(), NullTexture::instance())
{
	material1.kaSetter->set(0.05);
	material1.kdSetter->set(1.5);
	material1.ksSetter->set(0.0);
	material1.intensidadDifusoSetter->set(1.0);	

	material3.kaSetter->set(0.05);
	material3.kdSetter->set(1.5);
	material3.ksSetter->set(0.0);
	material3.intensidadReflexionSetter->set(0.8);
	material3.intensidadDifusoSetter->set(0.4);

	motor = Motor::instance(&material1, &material3);
}

void NaveNodriza::dibujar(const glm::mat4& m) {
	motor->dibujar(m);
}