#version 460

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 Normal;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 FragPos;
layout(location = 3) flat out int materialNumber;

layout(binding = 0) uniform VP {
    mat4 view;
    mat4 projection;
} vp;

//all object matrices
layout(std140,set = 0, binding = 1) readonly buffer ObjectBuffer{
	mat4 modelMatrices[];
} objectBuffer;

//all object matrices
layout(std140,set = 0, binding = 2) readonly buffer materialNumBuffer{
	int materialNum[];
} materialNums;

void main() {
    FragPos = vec3(objectBuffer.modelMatrices[gl_BaseInstance] * vec4(inPosition, 1.));
    gl_Position = vp.projection * vp.view * vec4(FragPos, 1.0);

    fragTexCoord = inTexCoord;
    // materialNumber = materialNums.materialNum[gl_BaseInstance];
    materialNumber = gl_BaseInstance;
}
