#version 460

layout(location = 0) in vec3 Normal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;
layout(location = 3) flat in int materialNumber;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform VP {
    mat4 view;
    mat4 projection;
} vp;

layout(std140,set = 0, binding = 1) readonly buffer ObjectBuffer{
	mat4 modelMatrices[];
} objectBuffer;

layout(std140,set = 0, binding = 2) readonly buffer materialNumBuffer{
	int materialNum[];
} materialNums;

layout(std140,set = 0, binding = 3) readonly buffer objectTextureNumberBuffer{
	int objectTextureNumber[];
} objectTextureNumberList;

layout(set = 0, binding = 4) uniform sampler2D texSampler[100];

void main() {
	// outColor = texture(texSampler[objectTextureNumberList.objectTextureNumber[materialNums.materialNum[materialNumber]]], fragTexCoord);
	// outColor = texture(texSampler[objectTextureNumberList.objectTextureNumber[materialNumber]], fragTexCoord);
	outColor = texture(texSampler[objectTextureNumberList.objectTextureNumber[materialNums.materialNum[materialNumber]]], fragTexCoord);
	// outColor = texture(texSampler[1], fragTexCoord);
	// outColor = vec4(1/materialNumber, 1/materialNumber, 1/materialNumber, 1);
}
