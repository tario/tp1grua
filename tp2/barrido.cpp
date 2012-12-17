#include "stdafx.h" 
#include "barrido.h"

static void insert_vertex(float* p, glm::vec3 p0) {
	p[0] = p0[0];
	p[1] = p0[1];
	p[2] = p0[2];
}
static void insert_triangle(float* p, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) {
	insert_vertex(p,p0);
	insert_vertex(p+3,p1);
	insert_vertex(p+6,p2);
}

Barrido::Barrido(
		FuncionConjuntoPuntos* funcionConjuntoPuntos,
		Curva* trayectoria,
		Curva* torcion,
		float h,
		Material* material
) : material(material) {

	glm::vec3 punto_central0, punto_central1;
	std::vector<FuncionConjuntoPuntos::Punto> puntos0, puntos1;

	this->cantidadVertices = funcionConjuntoPuntos->conjunto(0).size() * 6 * (1.0/h + 1);
	float* vertex_data = (float*)malloc(sizeof(float)*(this->cantidadVertices * 3));
	float* normal_data = (float*)malloc(sizeof(float)*(this->cantidadVertices * 3));
	float* current_position_pointer = vertex_data;
	float* current_normal_pointer = normal_data;

	float t, t0, t1;
	for (t=0.0; t<1.0; t+=h) {
		t0 = t;
		t1 = t + h;
		if (t1 > 1.0) t1 = 1.0;

		puntos0 = funcionConjuntoPuntos->conjunto(t0);
		puntos1 = funcionConjuntoPuntos->conjunto(t1);

		punto_central0 = trayectoria->punto(t0);
		punto_central1 = trayectoria->punto(t1);

		for (int i=0; i<puntos0.size(); i++){
			int nextindex = i + 1;
			if (nextindex > puntos0.size()-1) nextindex = 0;

			glm::vec3 p00, p01, p10, p11;

			p00 = glm::vec3(puntos0.at(i).punto,0.0)  + punto_central0;
			p01 = glm::vec3(puntos0.at(nextindex).punto,0.0)  + punto_central0;
			p10 = glm::vec3(puntos1.at(i).punto,0.0) + punto_central1;
			p11 = glm::vec3(puntos1.at(nextindex).punto,0.0) + punto_central1;

			glm::vec3 dummy_normal(1.0,0.0,0.0);

			insert_triangle(current_position_pointer, p00, p01, p11);
			insert_triangle(current_position_pointer+9, p10, p11, p00);
			current_position_pointer = current_position_pointer + 18;

			insert_triangle(current_normal_pointer, dummy_normal, dummy_normal, dummy_normal);
			insert_triangle(current_normal_pointer+9, dummy_normal, dummy_normal, dummy_normal);
			current_normal_pointer = current_normal_pointer + 18;
		}

	}

	this->cantidadVertices = (current_position_pointer - vertex_data) / 3;

	GLuint vboHandles[3];
    glGenBuffers(2, vboHandles);

    GLuint positionBufferHandle = vboHandles[0];
    GLuint normalBufferHandle = vboHandles[1];

    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertex_data, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normal_data, GL_STATIC_DRAW );

    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

	glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(1);
	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	free(vertex_data);
	free(normal_data);
}

void Barrido::dibujar(const glm::mat4& m) {
	material->use(m);

	glBindVertexArray( this->getVaoHandle() );
	glDrawArrays( GL_TRIANGLES, 0, cantidadVertices); 
}
