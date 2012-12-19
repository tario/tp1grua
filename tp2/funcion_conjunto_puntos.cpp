#include "stdafx.h" 
#include "funcion_conjunto_puntos.h" 

static int factorial(int x){
	if (x <= 1) {
		return 1;
	} else {
		return x * factorial(x-1);
	}
}

std::vector<FuncionConjuntoPuntos::Punto> FuncionConjuntoPuntos::bezier(const std::vector<Punto>& v, int cant_puntos) {
	float x, y;
	int n = v.size();
	std::vector<FuncionConjuntoPuntos::Punto> ret;
	for (int j=0; j<cant_puntos+1; j++) {
		x = 0; y = 0;
		float t = float(j)/cant_puntos;
		for (int i=0; i<n; i++) {
			float factor = float(factorial(n-1))/float(factorial(i))/float(factorial(n-i-1));
			glm::vec2 punto = v[i].punto;
			if (i==0) {
				x = x + punto.x * factor * pow(1.0-t,n-i-1);
				y = y + punto.y * factor * pow(1.0-t,n-i-1);
			} else if (n-i-1==0) {
				x = x + punto.x * factor * pow(t,i);
				y = y + punto.y * factor * pow(t,i);
			} else {
				x = x + punto.x * factor * pow(1.0-t,n-i-1) * pow(t,i);
				y = y + punto.y * factor * pow(1.0-t,n-i-1) * pow(t,i);
			}
		}
		if (t!=1.0) {
		ret.push_back(FuncionConjuntoPuntos::Punto(x,y,FuncionConjuntoPuntos::Punto::SMOOTH));
		}
	}
	return ret;
}

