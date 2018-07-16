#version 330

out vec4 outputColor;
smooth in vec4 fragmentColor;
smooth in vec3 normal_worldSpace;
smooth in vec3 tangent_worldSpace;
smooth in vec3 binormal_worldSpace;
smooth in vec3 vertexPosition_worldSpace;
smooth in vec3 lightVector1_worldSpace;
smooth in vec3 viewVector_worldSpace;
smooth in vec2 textureCoordinate;

vec4 textureColorAt(vec2 textureCoordinate, vec4 fragmentColor);
float kSpecular(vec2 textureCoordinate);
vec3 fragmentNormal(vec2 textureCoordinate, vec3 tangent_worldSpace, vec3 binormal_worldSpace);

void main()
{
    vec3 t = normalize(tangent_worldSpace);
    vec3 b = normalize(binormal_worldSpace);
    vec3 n = normalize(fragmentNormal(textureCoordinate, t, b));
    vec3 l = normalize(lightVector1_worldSpace);
    vec3 v = normalize(viewVector_worldSpace);
    vec3 r = normalize(reflect(-l, n));

    vec4 finalFragmentColor = textureColorAt(textureCoordinate, fragmentColor);

    vec4 ambientLightComponent = 0.1 * finalFragmentColor;
    vec4 diffuseComponent = finalFragmentColor * clamp( dot( n,l ), 0,1 );

    float shininessFactor = 100;
    float phongTerm = clamp(dot(-v,r), 0, 1);
    phongTerm = pow(phongTerm, shininessFactor);
    phongTerm = phongTerm * 1.0f;
    vec4 speculatComponent = vec4(1.0,1.0,1.0,1.0) * phongTerm * kSpecular(textureCoordinate);

    outputColor = ambientLightComponent + diffuseComponent + speculatComponent;
    //outputColor = speculatComponent;
    //outputColor = vec4(textureCoordinate, 0, 1);
    //outputColor = vec4(n, 1);
}

vec3 fragmentNormal(vec2 textureCoordinate, vec3 t, vec3 b)
{
    vec3 normal_tangentSpace;
    if (
        textureCoordinate.x > 0.1 &&
        textureCoordinate.x < 0.9 &&
        textureCoordinate.y > 0.1 &&
        textureCoordinate.y < 0.9
       )
    {
        normal_tangentSpace = vec3(0,0,1);
    }
    else
    {
       normal_tangentSpace = vec3(0,1,1);
    }
    vec3 n = normalize(cross(t,b));
    normal_tangentSpace = normalize(normal_tangentSpace);
    vec3 normal_worldSpace = normal_tangentSpace.x * t + normal_tangentSpace.y * b + normal_tangentSpace.z * n;
    return normal_worldSpace;

    //return normalize(cross(tangent_worldSpace, binormal_worldSpace));
}

vec4 textureColorAt(vec2 textureCoordinate, vec4 fragmentColor)
{
    if (
        textureCoordinate.x > 0.1 &&
        textureCoordinate.x < 0.9 &&
        textureCoordinate.y > 0.1 &&
        textureCoordinate.y < 0.9
       )
    {
        //fragmentColor unverändert übernehmen.
        return fragmentColor;
    }
    else
    {
        return vec4(0.1,0.1,0.1,1.0);
        //return vec4(0,0,0,1);
    }
}

float kSpecular(vec2 textureCoordinate)
{
    if (
        textureCoordinate.x > 0.1 &&
        textureCoordinate.x < 0.9 &&
        textureCoordinate.y > 0.1 &&
        textureCoordinate.y < 0.9
       )
    {
        return 1.0f;
    }
    else
    {
        return 0.2f;
    }
}
