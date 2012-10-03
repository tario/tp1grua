/*
	Crea un prisma de una unidad de altura cuya base es un poligono regular con 0.5 de apotema en el plano xy, 
	es decir que el cuerpo esta totalmente contenido en un cubo de lado unitario centrado en el origen

	Los parametros son
		n: la cantidad de caras del poligono
		color: el color del prisma 

	Esta primitiva es util para modelar un cilindro, si se usan la suficiente cantidad de caras
*/
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/freeglut.h"
#include "dibujable.h"

class Prisma : public Dibujable {
public:
	Prisma(int n, glm::vec3 color);

	// dibuja el objeto transformando los vertices con una matriz de transformacion
	void dibujar(const glm::mat4& m);
private:
	GLuint caraSuperior; // handler para los vertices de la cara superior
	GLuint caraInferior; // handler para los vertices de la cara inferior
	GLuint carasCostado; // handler para los vertices de las caras del costado

	int caras; // cantidad de caras
};
