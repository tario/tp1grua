#include "stdafx.h" 
#include "toroide.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/type_ptr.hpp>


static void assignvec3(float* data, glm::vec4 vect) {
	data[0] = glm::vec3(vect)[0];
	data[1] = glm::vec3(vect)[1];
	data[2] = glm::vec3(vect)[2];
}

static void assignvec2(float* data, glm::vec2 vect) {
	data[0] = vect[0];
	data[1] = vect[1];
}

static glm::vec4 getvec4(float* data) {
	return glm::vec4(data[0],data[1],data[2],1.0);
}

static glm::vec4 project_xy(glm::vec4 vect) {
	return glm::vec4(vect[0], vect[1], 0.0, 1.0);
}

Toroide::Toroide(Material* material, float section_ratio, int geometric_detail) : 
	material(material) {
	GLuint vboHandles[3];
    glGenBuffers(2, vboHandles);

    GLuint positionBufferHandle = vboHandles[0];
    GLuint normalBufferHandle = vboHandles[1];

	float section_ratio_absolute = 0.25 * section_ratio;
	float ratio = 0.5 - section_ratio_absolute;

	int cantidadVerticesMeridiano = (geometric_detail-1)*6 + 6;
	this->cantidadVertices = cantidadVerticesMeridiano*geometric_detail;

	float* vertexdata = new float[cantidadVertices*3];
	float* normaldata = new float[cantidadVertices*3];
	float* normalxdata = new float[cantidadVertices*3];
	float* texcoord_data = new float[cantidadVertices*2];
	
	glm::mat4 girox = glm::rotate(glm::mat4(1.0), 360.0f / geometric_detail, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 trSectionCenter = glm::translate(glm::mat4(1.0), glm::vec3(0.0, -ratio, 0.0));
	glm::mat4 trSectionCenterContrario = glm::translate(glm::mat4(1.0), glm::vec3(0.0, ratio, 0.0));

	girox = trSectionCenter * girox * trSectionCenterContrario;

	glm::mat4 girox_contrario = glm::rotate(glm::mat4(1.0), -180.0f / geometric_detail, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 giroz = glm::rotate(glm::mat4(1.0), 360.0f / geometric_detail, glm::vec3(0.0, 0.0, 1.0));

	float* indiceMeridiano = vertexdata;
	
	glm::vec4 currentPoint = glm::vec4(0.0,-ratio,section_ratio_absolute,1.0);
	glm::vec4 sectionCenter = glm::vec4(0.0, -ratio, 0.0, 1.0);

	for (int i=0; i<geometric_detail; i++){
		glm::vec4 nextPoint = girox * currentPoint;

		assignvec3(indiceMeridiano+i*18, currentPoint);
		assignvec3(indiceMeridiano+i*18+3, nextPoint);
		assignvec3(indiceMeridiano+i*18+6, giroz * nextPoint);
		assignvec3(indiceMeridiano+i*18+9, currentPoint);
		assignvec3(indiceMeridiano+i*18+12, giroz * currentPoint);
		assignvec3(indiceMeridiano+i*18+15, giroz * nextPoint);

		assignvec2(texcoord_data+i*12, glm::vec2(0.0, i*1.0/geometric_detail));
		assignvec2(texcoord_data+i*12+2, glm::vec2(0.0, (i+1)*1.0/geometric_detail));
		assignvec2(texcoord_data+i*12+4, glm::vec2(1.0/geometric_detail, (i+1)*1.0/geometric_detail));
		assignvec2(texcoord_data+i*12+6, glm::vec2(0.0, i*1.0/geometric_detail));
		assignvec2(texcoord_data+i*12+8, glm::vec2(1.0/geometric_detail, i*1.0/geometric_detail));
		assignvec2(texcoord_data+i*12+10, glm::vec2(1.0/geometric_detail, (i+1)*1.0/geometric_detail));

			assignvec3(normaldata+(indiceMeridiano-vertexdata)+i*18, glm::normalize(
				getvec4(indiceMeridiano+i*18) - sectionCenter) 
				);
			assignvec3(normaldata+(indiceMeridiano-vertexdata)+i*18+3, glm::normalize(
				getvec4(indiceMeridiano+i*18+3) - sectionCenter) 
				);
			assignvec3(normaldata+(indiceMeridiano-vertexdata)+i*18+6, glm::normalize(
				getvec4(indiceMeridiano+i*18+6) - giroz * sectionCenter) 
				);
			assignvec3(normaldata+(indiceMeridiano-vertexdata)+i*18+9, glm::normalize(
				getvec4(indiceMeridiano+i*18+9) - sectionCenter) 
				);
			assignvec3(normaldata+(indiceMeridiano-vertexdata)+i*18+12, glm::normalize(
				getvec4(indiceMeridiano+i*18+12) - giroz * sectionCenter) 
				);
			assignvec3(normaldata+(indiceMeridiano-vertexdata)+i*18+15, glm::normalize(
				getvec4(indiceMeridiano+i*18+15) - giroz * sectionCenter) 
				);
		currentPoint = nextPoint;
	}

	for (int j=1; j<geometric_detail; j++) {
		indiceMeridiano = vertexdata + j*cantidadVerticesMeridiano*3;
		float* indiceMeridianoNormal = normaldata + j*cantidadVerticesMeridiano*3;
		glm::mat4 giroz_j = glm::rotate(glm::mat4(1.0), j * 360.0f / geometric_detail, glm::vec3(0.0, 0.0, 1.0));
		
		for (int i=0; i<cantidadVerticesMeridiano; i++){
			assignvec3(indiceMeridiano+i*3, giroz_j * getvec4(vertexdata+i*3));
		}

		for (int i=0; i<geometric_detail; i++){
			int b1 = j*cantidadVerticesMeridiano*2 + i*12;
			int b2 = (j-1)*cantidadVerticesMeridiano*2 + i*12;

			for (int k=0;k<6;k++) {
				texcoord_data[b1+k*2] = texcoord_data[b2+k*2] + 1.0/geometric_detail;
				texcoord_data[b1+k*2+1] = texcoord_data[b2+k*2+1];
			}

			assignvec3(indiceMeridianoNormal+i*18, glm::normalize(
				getvec4(indiceMeridiano+i*18) - giroz_j * sectionCenter)
				);
			assignvec3(indiceMeridianoNormal+i*18+3, glm::normalize(
				getvec4(indiceMeridiano+i*18+3) - giroz_j * sectionCenter)
				);
			assignvec3(indiceMeridianoNormal+i*18+6, glm::normalize(
				getvec4(indiceMeridiano+i*18+6) - giroz * giroz_j * sectionCenter)
				);
			assignvec3(indiceMeridianoNormal+i*18+9, glm::normalize(
				getvec4(indiceMeridiano+i*18+9) - giroz_j * sectionCenter)
				);
			assignvec3(indiceMeridianoNormal+i*18+12, glm::normalize(
				getvec4(indiceMeridiano+i*18+12) - giroz * giroz_j * sectionCenter)
				);
			assignvec3(indiceMeridianoNormal+i*18+15, glm::normalize(
				getvec4(indiceMeridiano+i*18+15) - giroz * giroz_j * sectionCenter)
				);
		}
	}

	giroz = glm::rotate(glm::mat4(1.0), 90.0f, glm::vec3(0.0, 0.0, 1.0));
	for (int i=0; i<cantidadVertices; i++) {
		glm::vec4 normal_centro = getvec4(vertexdata+i*3);
		assignvec3(normalxdata+i*3, glm::normalize(
			project_xy(giroz * normal_centro)
			));
	}
	
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), vertexdata, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle );
    glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normaldata, GL_STATIC_DRAW );

    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray( vaoHandle );

	glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glEnableVertexAttribArray(1);
	glBindBuffer( GL_ARRAY_BUFFER, normalBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	GLuint textureCoordBufferHandle;
	glGenBuffers(1, &textureCoordBufferHandle);

    glEnableVertexAttribArray(2);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, cantidadVertices*2 * sizeof (float), texcoord_data, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

 
	GLuint normalxBufferHandle;
	glGenBuffers(1, &normalxBufferHandle);
	
	glEnableVertexAttribArray(3);

	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, cantidadVertices*3 * sizeof (float), normalxdata, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	delete[] texcoord_data;
	delete[] vertexdata;
	delete[] normalxdata;
	delete[] normaldata;
}

void Toroide::dibujar(const glm::mat4& m) {
	material->use(m);

	glBindVertexArray( this->getVaoHandle() );
	glDrawArrays( GL_TRIANGLES, 0, cantidadVertices); 
}
