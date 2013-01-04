#include "stdafx.h" 
#include "material.h" 

Material* Material::last_material = 0;

bool Material::is_last_material() {
	if (last_material != this) {
		last_material = this;
		return false;
	} else {
		return true;
	}
}
	
