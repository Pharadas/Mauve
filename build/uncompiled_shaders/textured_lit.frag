#version 460

layout(binding = 1) uniform sampler2D texSampler[100];

struct LightingInfo {
    vec3 objectColor;
    vec3 lightColor;
    vec3 lightPos;
    vec3 viewPos;
};

layout(std140,set = 0, binding = 2) readonly buffer LightBuffer {
	LightingInfo light[];
} lightBuffer;

layout(location = 0) in vec3 Normal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform constants {
    int numOfTexture;
    int numOfObjectWithinMaterial;
    mat4 render_matrix;
} PushConstants;

void main() {
    LightingInfo currObjectLightingInfo = lightBuffer.light[PushConstants.numOfObjectWithinMaterial];

    // outColor = vec4(currObjectLightingInfo.objectColor, 1);

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * currObjectLightingInfo.lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(currObjectLightingInfo.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * currObjectLightingInfo.lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(currObjectLightingInfo.viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * currObjectLightingInfo.lightColor;  

    vec3 result = (ambient + diffuse + specular) * currObjectLightingInfo.objectColor;
    outColor = vec4(result, 1.0);
}
