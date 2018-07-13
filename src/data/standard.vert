#version 330

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec3 normal_modelSpace;
layout(location = 3) in vec2 uv;
layout(location = 4) in vec3 tangent_modelSpace;
layout(location = 5) in vec3 binormal_modelSpace;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightPosition_worldSpace;

smooth out vec4 fragmentColor;
smooth out vec3 normal_worldSpace;
smooth out vec3 tangent_worldSpace;
smooth out vec3 binormal_worldSpace;
smooth out vec3 vertexPosition_worldSpace;
smooth out vec3 lightVector1_worldSpace;
smooth out vec3 viewVector_worldSpace;
smooth out vec2 textureCoordinate;

void main()
{
    fragmentColor = vertexColor;
    textureCoordinate = uv;

    gl_Position = MVP * vec4(vertexPosition_modelSpace,1.f);

    vertexPosition_worldSpace = (M * vec4(vertexPosition_modelSpace,1)).xyz;
    normal_worldSpace = (M * vec4(normal_modelSpace, 1.f)).xyz;
    tangent_worldSpace = (M * vec4(tangent_modelSpace, 1.f)).xyz;
    binormal_worldSpace = (M * vec4(binormal_modelSpace, 1.f)).xyz;

    lightVector1_worldSpace = normalize(lightPosition_worldSpace - vertexPosition_worldSpace);

    vec3 cameraPosition_worldSpace = V[3].xyz; //TODO: Verstehen warum. Lürig könnte fragen.

    viewVector_worldSpace = normalize(cameraPosition_worldSpace - vertexPosition_worldSpace);
}
