// // IFT3100H20 ~ blinn_phong_330_vs.glsl

// #version 330
#version 150

// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

in vec4 position;
in vec4 normal;
in vec2 texcoord;

// this is something we're creating for this shader
out vec2 texCoordVarying;
out vec3 surface_position;
out vec3 surface_normal;


void main()
{
    // here we move the texture coordinates
    texCoordVarying = vec2(texcoord.x, texcoord.y);

  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  surface_normal = vec3(normalMatrix * normal);

  // transformation de la position du sommet dans l'espace de vue
  surface_position = vec3(modelViewMatrix * position);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projectionMatrix * modelViewMatrix * position;
}










