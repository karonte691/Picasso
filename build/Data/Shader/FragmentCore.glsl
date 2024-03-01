#version 440

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseTexture;
    sampler2D specularTexture;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_textcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform sampler2D texture0;
uniform Material material;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

vec3 calcAmbientLight(Material material)
{
    return material.ambient;
}

vec3 calcDiffuseLight(Material material)
{
    vec3 posToLight = normalize(lightPosition - vs_position);
    float diffuseColor = max(dot(posToLight, normalize(vs_normal)), 1);
    return material.diffuse * diffuseColor;
}

vec3 calcSpecularLight(Material material)
{
    vec3 specLightPosition = normalize(lightPosition - vs_position);
    vec3 reflectDir = normalize(reflect(specLightPosition, normalize(vs_normal)));
    vec3 posToView = normalize(vs_position - cameraPosition);
    float spec = pow(max(dot(posToView, reflectDir), 0.0f), 32.0f);
    return  material.specular * spec;
}

void main()
{
    //ambient light
    vec3 ambient = calcAmbientLight(material);
    vec3 diffuseLight = calcDiffuseLight(material);
    vec3 specular = calcSpecularLight(material);

    fs_color = texture(material.diffuseTexture, vs_textcoord) * vec4(vs_color, 1.0f) 
               * (  
                    vec4(ambient, 1.0f) + vec4(diffuseLight, 1.0f) + vec4(specular, 1.0f)
                 );
}
