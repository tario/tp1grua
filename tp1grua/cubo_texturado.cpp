#include "stdafx.h"
#include "cubo_texturado.h"

static void assign_normalx(float* normalp, const glm::vec4& normalx) {
	for (int i=0; i<6; i++) {
		normalp[i*3] = normalx[0];
		normalp[i*3+1] = normalx[1];
		normalp[i*3+2] = normalx[2];
	}
}

static glm::vec4 cara_normalx(CuboTexturado::Cara* cara) {
	glm::vec4 ret = glm::vec4(glm::normalize(glm::vec3(
		cara->coords[6] - cara->coords[0], 
		cara->coords[7] - cara->coords[1], 
		0.0)
		),1.0);

	return ret;
}


CuboTexturado::CuboTexturado(Material* material, Cara* caras, bool _carasuperior) : 
	material(material),
	Cubo(_carasuperior), 
	carasuperior(_carasuperior) {
	
	float normalx_data[36*3];	
	this->extra_data = new float[36*2];

	int i;

	for (i=0; i<6; i++) {
		extra_data[i*12] = caras[i].coords[0];
		extra_data[i*12+1] = caras[i].coords[1];

		extra_data[i*12+2] = caras[i].coords[2];
		extra_data[i*12+3] = caras[i].coords[3];

		extra_data[i*12+4] = caras[i].coords[6];
		extra_data[i*12+5] = caras[i].coords[7];

		extra_data[i*12+6] = caras[i].coords[2];
		extra_data[i*12+7] = caras[i].coords[3];

		extra_data[i*12+8] = caras[i].coords[6];
		extra_data[i*12+9] = caras[i].coords[7];

		extra_data[i*12+10] = caras[i].coords[4];
		extra_data[i*12+11] = caras[i].coords[5];
	}

	glm::mat4 zrotation = glm::rotate(glm::mat4(1.0),90.0f, glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 yrotation = glm::rotate(glm::mat4(1.0),90.0f, glm::vec3(0.0f,1.0f,0.0f));

	assign_normalx(normalx_data, cara_normalx(caras));
	assign_normalx(normalx_data+18, zrotation * cara_normalx(caras+1));
	assign_normalx(normalx_data+36, zrotation * zrotation * cara_normalx(caras+2));
	assign_normalx(normalx_data+54, zrotation * zrotation * zrotation * cara_normalx(caras+3));
	assign_normalx(normalx_data+18*4, yrotation * cara_normalx(caras+4));
	assign_normalx(normalx_data+18*5, yrotation * yrotation * yrotation * cara_normalx(caras+5));

	GLuint textureCoordBufferHandle;
	glGenBuffers(1, &textureCoordBufferHandle);
	
    glEnableVertexAttribArray(lastIndex());
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*2 * sizeof (float), this->extra_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( lastIndex(), 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	GLuint normalxBufferHandle;
	glGenBuffers(1, &normalxBufferHandle);

    glEnableVertexAttribArray(lastIndex()+1);

	glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*3 * sizeof (float), normalx_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, normalxBufferHandle );
    glVertexAttribPointer( lastIndex()+1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

void CuboTexturado::dibujar(const glm::mat4& m) {
	this->material->use(m);

	glBindVertexArray( this->getVaoHandle() );
	if (carasuperior) {
	glDrawArrays( GL_TRIANGLES, 0, 36); 
	} else {
	glDrawArrays( GL_TRIANGLES, 0, 30); 
	}
}
