#ifndef __SPECULAR_DIRTNESS_SHADER_H
#define __SPECULAR_DIRTNESS_SHADER_H

#include "dirtness_shader.h"

class SpecularDirtnessShader : public DirtnessShader {
	public:
		SpecularDirtnessShader();
		void setSpecularmapUnit(int unitnumber);

		static SpecularDirtnessShader* instance();
	private:
		int specularmap_location;
};

#endif
