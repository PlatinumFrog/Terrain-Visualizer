#version 460

in vec3 texCoord;
in vec3 normal;

out vec4 color;

void main() {
	color = vec4(0.5 * normalize(normal) + 0.5, 1);
}