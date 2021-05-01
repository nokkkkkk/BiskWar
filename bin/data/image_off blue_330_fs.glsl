// IFT3100H21 ~ image_invert_330_fs.glsl

#version 330

// attribut uniforme
uniform sampler2D image;

// attribut en entrée
in vec2 surface_texcoord;
in float rdm_float;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // échantillonner la texture
  vec4 texture_sample = texture(image, surface_texcoord);

  // inverser la valeur de chaque composante de couleur
  vec4 rdm_color;
  rdm_color.r = 1.0 - texture_sample.r;
  rdm_color.g = 1.0 - texture_sample.g;
  rdm_color.b = 0.0;
  rdm_color.a = texture_sample.a;

  // couleur finale du fragment
  fragment_color = rdm_color;
}
