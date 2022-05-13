#version 460

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 Normal;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 FragPos;

layout(binding = 0) uniform VP {
    mat4 view;
    mat4 projection;
} vp;

//all object matrices
layout(std140,set = 0, binding = 1) readonly buffer ObjectBuffer{
	mat4 modelMatrices[];
} objectBuffer;

void main() {
    FragPos = vec3(objectBuffer.modelMatrices[gl_BaseInstance] * vec4(inPosition, 1.));
    // FragPos = vec3(PushConstants.modelMatrix * vec4(inPosition, 1.0));
    // Normal = mat3(transpose(inverse(objectBuffer.objects[gl_BaseInstance].model))) * inNormal;  
    gl_Position = vp.projection * vp.view * vec4(FragPos, 1.0);

    fragTexCoord = inTexCoord;
}