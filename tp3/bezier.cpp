#include "stdafx.h"
#include "bezier.h"

static int factorial(int x){
	if (x <= 1) {
		return 1;
	} else {
		return x * factorial(x-1);
	}
}

glm::vec3 bezier_eval(const std::vector<glm::vec3>& v, float t) {
	glm::vec3 ret(0.0,0.0,0.0);
	int n=v.size();
	for (int i=0; i<n; i++) {
		float factor = float(factorial(n-1))/float(factorial(i))/float(factorial(n-i-1));
		glm::vec3 punto = v[i];
		if (i==0) {
			ret = ret + punto * factor * float(pow(1.0-t,n-i-1));
		} else if (n-i-1==0) {
			ret = ret + punto * factor * float(pow(t,i));
		} else {
			ret = ret + punto * factor * float(pow(1.0-t,n-i-1) * pow(t,i));
		}
	}

	return ret;
}

std::vector<glm::vec3> puntos_bezier(const std::vector<glm::vec3>& v, int n) {
	std::vector<glm::vec3> ret;

	for (int i=0; i<n; i++) {
		float t = float(i)/float(n);
		ret.push_back(bezier_eval(v,t));
	}
	return ret;
}
	