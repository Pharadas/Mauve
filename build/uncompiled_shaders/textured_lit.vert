#version 460

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 Normal;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 FragPos;

struct ObjectData{
    mat4 model;
    mat4 view;
    mat4 proj;
};

//all object matrices
layout(std140,set = 0, binding = 0) readonly buffer ObjectBuffer {
	ObjectData objects[];
} objectBuffer;

layout(push_constant) uniform constants {
    int numOfTexture;
    int numOfObjectWithinMaterial;
    mat4 render_matrix;
} PushConstants;

void main() {
    ObjectData currObject = objectBuffer.objects[gl_BaseInstance];
    // FragPos = vec3(objectBuffer.objects[gl_BaseInstance].model * vec4(inPosition, 1.0));
    // // Normal = mat3(transpose(inverse(objectBuffer.objects[gl_BaseInstance].model))) * inNormal;  
    // gl_Position = objectBuffer.objects[gl_BaseInstance].proj * objectBuffer.objects[gl_BaseInstance].view * vec4(FragPos, 1.0);

    // fragTexCoord = inTexCoord;

    FragPos = vec3(currObject.model * vec4(inPosition, 1.0));
    Normal = mat3(transpose(inverse(currObject.model))) * inNormal;  

    gl_Position = currObject.proj * currObject.view * vec4(FragPos, 1.0);
}
