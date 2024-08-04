#version 460

layout(location = 0) in vec4 vert;
layout(location = 1) uniform mat4 camera;
layout(location = 5) uniform mat4 projection;
layout(location = 9) uniform float size;
layout(location = 10) uniform float height;

void main() {
	gl_Position = vert;
}