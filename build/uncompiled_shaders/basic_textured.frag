#version 460

layout(binding = 1) uniform sampler2D texSampler[100];

layout(location = 0) in vec3 Normal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform constants {
    int numOfTexture;
    mat4 render_matrix;
} PushConstants;

void main() {
    outColor = texture(texSampler[PushConstants.numOfTexture], fragTexCoord);
}
