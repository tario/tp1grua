#include "stdafx.h" 
#include "funcion_conjunto_puntos.h" 

static glm::vec2 local_bspline(
	glm::vec2 p0, 
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	float t) {

	return 	(p0 * (-t*t*t + 3*t*t - 3*t + 1.0f) + 
			p1 * (3.0f*t*t*t - 6.0f*t*t + 4.0f) + 
			p2 * (-3.0f*t*t*t + 3.0f*t*t + 3.0f*t + 1) +
			p3 * (t*t*t) ) / 6.0f;
}


std::vector<FuncionConjuntoPuntos::Punto> 
FuncionConjuntoPuntos::cubic_bspline(const std::vector<FuncionConjuntoPuntos::Punto>& puntos, int n) {
	std::vector<Punto> ret;
	for (int i=0; i<n;i++) {
		float t_global = float(i)*(puntos.size() - 3)/n;

		for (int j=1; j<puntos.size()-2;j++) {
			if (t_global >= j*1.0f - 1.0f && t_global <= j*1.0f) {
				float t = t_global - j*1.0f + 1.0f;
				glm::vec2 p0 = puntos.at(j-1).punto;
				glm::vec2 p1 = puntos.at(j).punto;
				glm::vec2 p2 = puntos.at(j+1).punto;
				glm::vec2 p3 = puntos.at(j+2).punto;

				glm::vec2 p = local_bspline(p0,p1,p2,p3,t);
				ret.push_back(Punto(p[0],p[1],Punto::SMOOTH));

				break;
			}
		}
	}

	return ret;
}


std::vector<FuncionConjuntoPuntos::Punto> 
FuncionConjuntoPuntos::closed_cubic_bspline(const std::vector<FuncionConjuntoPuntos::Punto>& v, int n) {
	std::vector<Punto> puntos = v;
	// repetir los primeros tres puntos para hacer la bspline cerrada
	puntos.push_back(v.at(0));
	puntos.push_back(v.at(1));
	puntos.push_back(v.at(2));

	return cubic_bspline(puntos,n);
}

static int factorial(int x){
	if (x <= 1) {
		return 1;
	} else {
		return x * factorial(x-1);
	}
}

std::vector<FuncionConjuntoPuntos::Punto>
FuncionConjuntoPuntos::bezier(const std::vector<Punto>& v, int cant_puntos) {
	float x, y;
	int n = v.size();
	std::vector<FuncionConjuntoPuntos::Punto> ret;
	for (int j=0; j<cant_puntos; j++) {
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
		ret.push_back(FuncionConjuntoPuntos::Punto(x,y,FuncionConjuntoPuntos::Punto::SMOOTH));
	}
	return ret;
}

