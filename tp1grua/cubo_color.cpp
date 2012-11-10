#include "stdafx.h" 
#include "cubo_color.h"
#include "model_object.h"

CuboColor::CuboColor(const glm::vec3& color) {
	initCube(color,color,color,color,color,color);
}

CuboColor::CuboColor(
		const glm::vec3& colorzp,
		const glm::vec3& colorzm,
		const glm::vec3& colorxp,
		const glm::vec3& colorxm,
		const glm::vec3& coloryp,
		const glm::vec3& colorym
		) { 
	initCube(colorzp, colorzm, colorxp, colorxm, coloryp, colorym);		
}

void CuboColor::initCube(
		const glm::vec3& colorzp,
		const glm::vec3& colorzm,
		const glm::vec3& colorxp,
		const glm::vec3& colorxm,
		const glm::vec3& coloryp,
		const glm::vec3& colorym
		) {
	
	float extra_data[36*3];
	int i, j;

	glm::vec3 color_array[6] = {colorzp, colorzm, colorxp, colorxm, coloryp, colorym };

	for (i=0; i<6; i++) {
		for (j=0; j<6; j++) {
			extra_data[i*18+j*3] = color_array[i][0];
			extra_data[i*18+j*3+1] = color_array[i][1];
			extra_data[i*18+j*3+2] = color_array[i][2];
		}
	}

	GLuint colorBufferHandle;
	glGenBuffers(1, &colorBufferHandle);
	
    glEnableVertexAttribArray(lastIndex());
	
	glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*3 * sizeof (float), extra_data, GL_STATIC_DRAW );			

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( lastIndex(), 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	
	colorShader = ColorShader::instance();
}
void CuboColor::dibujar(const glm::mat4& m) {
	this->colorShader->use();
	colorShader->setTransformMatrix(m);
	colorShader->setProjectionMatrix(Shader::projectionMatrix);

	glBindVertexArray( this->getVaoHandle() );
	glDrawArrays( GL_TRIANGLES, 0, 36);
}
