#version 460

uniform float size;
uniform sampler2D heightMap;
uniform float height;

in vec2 texCoord;
in vec3 posCoord;

out vec4 color;

void main() {
	const float offset = 0.0002;
	const float sOffset = offset * size;
	vec3 c0 = vec3(posCoord.x, texture(heightMap, vec2(texCoord.x, texCoord.y)).r * height, posCoord.z);
	vec3 c1 = vec3(posCoord.x + sOffset, texture(heightMap, vec2(texCoord.x + offset, texCoord.y)).r * height, posCoord.z);
	vec3 c2 = vec3(posCoord.x, texture(heightMap, vec2(texCoord.x, texCoord.y + offset)).r * height, posCoord.z + sOffset);
	vec3 normal = normalize(cross(c2 - c0, c1 - c0));
	color = vec4(normal, 1);

}