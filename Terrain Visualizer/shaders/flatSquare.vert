#version 460

layout(location = 0) in vec4 vert;

layout(location = 1) uniform mat4 camera;
layout(location = 5) uniform mat4 projection;
layout(location = 9) uniform float size;

void main() {
	//gl_Position = projection * camera * vec4(vert.x, 0.0, vert.y, 1.0);
	gl_Position = vert;
}