#include "stdafx.h"
#include "cubo_texturado.h"

static float textureCoordData[] = 
{
     1.0f,  0.0f,
     0.0f,  1.0f,
     0.0f,  0.0f,
     0.0f,  0.0f
};

CuboTexturado::CuboTexturado(Texture* tex) : Cubo(), texture(tex) {
	this->extra_data = new float[36*2];
	int i;

	for (i=0; i<6; i++) {
		extra_data[i*12] = 0.0;
		extra_data[i*12+1] = 0.0;

		extra_data[i*12+2] = 1.0;
		extra_data[i*12+3] = 0.0;

		extra_data[i*12+4] = 0.0;
		extra_data[i*12+5] = 1.0;

		extra_data[i*12+6] = 1.0;
		extra_data[i*12+7] = 0.0;

		extra_data[i*12+8] = 0.0;
		extra_data[i*12+9] = 1.0;

		extra_data[i*12+10] = 1.0;
		extra_data[i*12+11] = 1.0;
	}

	GLuint textureCoordBufferHandle;
	glGenBuffers(1, &textureCoordBufferHandle);
	
    glEnableVertexAttribArray(1);
	
	glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 36*2 * sizeof (float), this->extra_data, GL_STATIC_DRAW );

    // Map index 1 to the texture coord buffer
    glBindBuffer( GL_ARRAY_BUFFER, textureCoordBufferHandle);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	textureShader = new Shader("TextureFShader.frag", "TextureVShader.vert");
	textureShader->bindAttribLocation(0, "VertexPosition" );
    textureShader->bindAttribLocation(1, "VertexColor" );
	textureShader->link();
	this->texture_location = textureShader->getUniformLocation("texture1");
	this->transform_matrix_index = textureShader->getUniformLocation("TransformMatrix");
}

void CuboTexturado::dibujar(const glm::mat4& m) {
	texture->load(0);
	glUniform1i(this->texture_location, 0);
	glUniformMatrix4fv(this->transform_matrix_index, 1, 0, glm::value_ptr(m));

	glBindVertexArray( this->getVaoHandle() );

	this->textureShader->use();
	glDrawArrays( GL_TRIANGLES, 0, 36);
}
