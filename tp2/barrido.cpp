#include "stdafx.h" 
#include "barrido.h"
#include <list>
#include <map>

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

class VertexRegister {
	public:
		VertexRegister(int levels, int points) : v(levels) {
		}

		void addNormal(int level, int index, float* normal){
			v[level][index].push_back(normal);
		}


		std::vector<std::list<float*>> normal_groups() {
			std::vector<std::list<float*>> ret;
			for (
				std::vector<std::map<int,std::list<float*>>>::iterator it1 = v.begin();
				it1 != v.end();
				it1++){

				for (std::map<int,std::list<float*>>::iterator it2 = it1->begin();
					it2 != it1->end();
					it2++) {

						ret.push_back(it2->second);
				}
			}

			return ret;
		}

	private:
		std::vector<std::map<int,std::list<float*>>> v;
};

Barrido::Barrido(
		FuncionConjuntoPuntos* funcionConjuntoPuntos,
		Curva* trayectoria,
		Curva* derivada,
		Curva* torcion,
		float h,
		Material* material,
		float t_inicial,
		float t_final
) : material(material) {

	glm::vec3 punto_central0, punto_central1;
	std::vector<FuncionConjuntoPuntos::Punto> puntos0, puntos1;

	int cantPuntos = funcionConjuntoPuntos->conjunto(0).size();
	this->cantidadVertices = cantPuntos * 6 * (1.0/h + 1);
	float* vertex_data = (float*)malloc(sizeof(float)*(this->cantidadVertices * 3));
	float* normal_data = (float*)malloc(sizeof(float)*(this->cantidadVertices * 3));
	float* normalx_data = (float*)malloc(sizeof(float)*(this->cantidadVertices * 3));
	float* texcoord_data = (float*)malloc(sizeof(float)*(this->cantidadVertices * 2));

	float* current_position_pointer = vertex_data;
	float* current_normal_pointer = normal_data;
	float* current_normalx_pointer = normalx_data;
	float* current_texcoord_pointer = texcoord_data;

	VertexRegister vertexRegister(1.0/h + 2, cantPuntos);

	int level=0;
	float t, t0, t1;
	for (t=t_inicial; t<t_final; t+=h) {
		t0 = t;
		t1 = t + h;
		if (t1 > t_final) t1 = t_final;

		puntos0 = funcionConjuntoPuntos->conjunto(t0);
		puntos1 = funcionConjuntoPuntos->conjunto(t1);

		punto_central0 = trayectoria->punto(t0);
		punto_central1 = trayectoria->punto(t1);

		for (int i=0; i<puntos0.size(); i++){
			int nextindex = i + 1;
			if (nextindex > puntos0.size()-1) nextindex = 0;

			glm::vec3 p00, p01, p10, p11;

			glm::vec3 vector_derivado = glm::normalize(derivada->punto(t));
			glm::vec3 vector_torcion = glm::normalize(torcion->punto(t));
			glm::vec3 vector_cross = glm::cross(vector_derivado, vector_torcion);
			glm::mat3 giro(vector_torcion[0], vector_torcion[1], vector_torcion[2],
				vector_cross[0], vector_cross[1], vector_cross[2],
				vector_derivado[0], vector_derivado[1], vector_derivado[2]);

			p00 = giro * glm::vec3(puntos0.at(i).punto,0.0)  + punto_central0;
			p01 = giro * glm::vec3(puntos0.at(nextindex).punto,0.0)  + punto_central0;
			p10 = giro * glm::vec3(puntos1.at(i).punto,0.0) + punto_central1;
			p11 = giro * glm::vec3(puntos1.at(nextindex).punto,0.0) + punto_central1;

			insert_triangle(current_position_pointer, p00, p01, p11);
			insert_triangle(current_position_pointer+9, p10, p11, p00);
			current_position_pointer = current_position_pointer + 18;

			glm::vec3 normal, normalx;

			normal = glm::normalize(glm::cross(p01-p00,p11-p00));
			normalx = glm::normalize(glm::cross(normal, vector_derivado));
			insert_triangle(current_normal_pointer, normal, normal, normal);
			insert_triangle(current_normalx_pointer, normalx, normalx, normalx);

			vertexRegister.addNormal(level, i + i*cantPuntos, current_normal_pointer);
			vertexRegister.addNormal(level, nextindex + i*cantPuntos, current_normal_pointer+3);
			vertexRegister.addNormal(level+1, nextindex + i*cantPuntos, current_normal_pointer+6);

			normal = glm::normalize(glm::cross(p00-p10,p11-p10));
			normalx = glm::normalize(glm::cross(normal, vector_derivado));
			insert_triangle(current_normal_pointer+9, normal, normal, normal);
			insert_triangle(current_normalx_pointer+9, normalx, normalx, normalx);

			vertexRegister.addNormal(level+1, i + i*cantPuntos, current_normal_pointer+9);
			vertexRegister.addNormal(level+1, nextindex + i*cantPuntos, current_normal_pointer+12);
			vertexRegister.addNormal(level, i + i*cantPuntos, current_normal_pointer+15);

			current_normal_pointer = current_normal_pointer + 18;
			current_normalx_pointer = current_normalx_pointer + 18;

			current_texcoord_pointer[0] = float(i)/float(cantPuntos);
			current_texcoord_pointer[1] = t;
			current_texcoord_pointer[2] = float(nextindex)/float(cantPuntos);
			current_texcoord_pointer[3] = t;
			current_texcoord_pointer[4] = float(nextindex)/float(cantPuntos);
			current_texcoord_pointer[5] = t1;
			current_texcoord_pointer[6] = float(i)/float(cantPuntos);
			current_texcoord_pointer[7] = t1;
			current_texcoord_pointer[8] = float(nextindex)/float(cantPuntos);
			current_texcoord_pointer[9] = t1;
			current_texcoord_pointer[10] = float(i)/float(cantPuntos);
			current_texcoord_pointer[11] = t;
			current_texcoord_pointer = current_texcoord_pointer + 12;
		}

		level++;
	}

	// suavizar normales

	std::vector<std::list<float*>> groups = vertexRegister.normal_groups();
	for (std::vector<std::list<float*>>::iterator it = groups.begin();
		it != groups.end();
		it++) {

		std::list<float*> normals = *it;
			if (normals.size() > 1 ) {
				glm::vec3 suma_normal;

				for (std::list<float*>::iterator it = normals.begin();
					it != normals.end();
					it++){

					suma_normal = suma_normal + glm::vec3((*it)[0],(*it)[1],(*it)[2]);
				}

				suma_normal = glm::normalize(suma_normal);
				for (std::list<float*>::iterator it = normals.begin();
					it != normals.end();
					it++){

					(*it)[0] = suma_normal[0];
					(*it)[1] = suma_normal[1];
					(*it)[2] = suma_normal[2];
				}
			}
	}

	this->cantidadVertices = (current_position_pointer - vertex_data) / 3;

	GLuint vboHandles[5];
    glGenBuffers(4, vboHandles);

    GLuint positionBufferHandle = vboHandles[0];
    GLuint normalBufferHandle = vboHandles[1];
    GLuint textureCoordBufferHandle = vboHandles[2];
    GLuint normalxBufferHandle = vboHandles[3];

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

    glEnableVertexAttribArray(2);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, cantidadVertices*2 * sizeof (float), texcoord_data, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(3);

	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normalx_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	free(vertex_data);
	free(normal_data);
	free(normalx_data);
	free(texcoord_data);
}

void Barrido::dibujar(const glm::mat4& m) {
	material->use(m);

	glBindVertexArray( this->getVaoHandle() );
	glDrawArrays( GL_TRIANGLES, 0, cantidadVertices); 
}
