// IFT3100H20 ~ gouraud_330_fs.glsl

#version 330

uniform sampler2D tex0;

// attribut interpolé à partir des valeurs en sortie du shader de sommet
in vec3 surface_color;
in vec2 texCoordVarying;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // calculer la couleur du fragment
  fragment_color = texture(tex0, texCoordVarying) + vec4(surface_color, 1.0) * 0.5;
}
