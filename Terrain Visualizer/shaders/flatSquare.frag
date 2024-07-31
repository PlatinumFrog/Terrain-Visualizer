#version 460

in vec3 texCoord;
in vec3 normal;

out vec4 color;

void main() {
	color = vec4(normalize(normal), 1);
}