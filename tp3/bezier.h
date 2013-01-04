#ifndef __BEZIER_H
#define __BEZIER_H

#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>

// evalua la curva de bezier para un vector de puntos de control y 
// un valor de t
glm::vec3 bezier_eval(const std::vector<glm::vec3>& v, float t);

// dado un vector de puntos de control y un N la cantidad de puntos
// devuelve N puntos de la curva de bezier correspondiente a esos puntos 
// de control
std::vector<glm::vec3> puntos_bezier(const std::vector<glm::vec3>& v, int n);

#endif
