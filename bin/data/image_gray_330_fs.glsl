// IFT3100H21 ~ image_invert_330_fs.glsl

#version 330

// attribut uniforme
uniform sampler2D image;

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // échantillonner la texture
  vec4 texture_sample = texture(image, surface_texcoord);

  float gray = (texture_sample.r + texture_sample.g + texture_sample.b) / 3;

  vec3 grayscale = vec3(gray);


  // couleur finale du fragment
  fragment_color = vec4(grayscale, 1.0);
}
