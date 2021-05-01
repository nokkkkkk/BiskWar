// IFT3100H20 ~ color_fill_330_fs.glsl

#version 330

// couleur de remplissage du matériau
uniform vec3 color;
uniform sampler2D tex0;


in vec2 texCoordVarying;

out vec4 fragment_color;

void main()
{
  // déterminer la couleur du fragment
  fragment_color = texture(tex0, texCoordVarying) + vec4(color, 1.0);
}
