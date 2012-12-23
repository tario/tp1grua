#version 330

in vec3 VertexPosition;
in vec3 VertexNormal;

uniform mat4 TransformMatrix;
uniform mat4 NormalMatrix;
uniform mat4 ProjectionMatrix;

out vec3 normal;
out vec3 position;

const float clipping1 = 0.9;
const float clipping2 = 0.99;

void main()
{		
        vec4 trVertexPosition = TransformMatrix * vec4( VertexPosition, 1.0);
		vec4 normal4 = NormalMatrix * vec4(VertexNormal,1.0);
		normal = vec3(normal4[0], normal4[1], normal4[2]);
		//normal = VertexNormal;
		gl_Position = ProjectionMatrix * TransformMatrix * vec4( VertexPosition, 1.0);
		
		if (VertexNormal[0] > 0.0) {
			if (gl_Position[0]/gl_Position[3] >= clipping1) {
			gl_Position[0]=clipping1*gl_Position[3];
			}
			if (gl_Position[0]/gl_Position[3] <= -clipping2) {
			gl_Position[0]=-clipping2*gl_Position[3];
			}
		} else { 
			if (gl_Position[0]/gl_Position[3] >= clipping2) {
			gl_Position[0]=clipping2*gl_Position[3];
			}
			if (gl_Position[0]/gl_Position[3] <= -clipping1) {
			gl_Position[0]=-clipping1*gl_Position[3];
			}
		}

		if (VertexNormal[1] > 0.0) {
			if (gl_Position[1]/gl_Position[3] >= clipping1) {
			gl_Position[1]=clipping1*gl_Position[3];
			}
			if (gl_Position[1]/gl_Position[3] <= -clipping2) {
			gl_Position[1]=-clipping2*gl_Position[3];
			}
		} else {
			if (gl_Position[1]/gl_Position[3] >= clipping2) {
			gl_Position[1]=clipping2*gl_Position[3];
			}
			if (gl_Position[1]/gl_Position[3] <= -clipping1) {
			gl_Position[1]=-clipping1*gl_Position[3];
			}
		}
		position = vec3(trVertexPosition[0], trVertexPosition[1], trVertexPosition[2]);
}