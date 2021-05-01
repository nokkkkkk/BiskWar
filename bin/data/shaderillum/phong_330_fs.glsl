// IFT3100H20 ~ phong_330_fs.glsl

#version 330


uniform sampler2D tex0;
uniform sampler2D normalMapTex;

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;
in vec2 texCoordVarying;


// couleurs de réflexion du matériau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;


// attribut en sortie
out vec4 fragment_color;

// //Ajout Normal Map
// in vec4 v_vertex;
// in vec3 v_normal;



// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3 light_position;
uniform int nb_light;





void main()
{

  // re-normaliser la normale après interpolation
  vec3 n = normalize(surface_normal);
  fragment_color = texture(tex0, texCoordVarying);

  for (int i=0; i<nb_light; i++)
  {

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(light_position - surface_position);

  // calculer le niveau de réflexion diffuse (n • l)
  float reflection_diffuse = max(dot(n, l), 0.0);


  // réflexion spéculaire par défaut
  float reflection_specular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflection_diffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (v)
    vec3 v = normalize(-surface_position);

    // calculer la direction de la réflection (r) du rayon incident (-l) en fonction de la normale (n)
    vec3 r = reflect(-l, n);

    // calculer le niveau de réflexion spéculaire (r • v)
    reflection_specular = pow(max(dot(v, r), 0.0), brightness);
  }
  

  // calculer la couleur du fragment
  fragment_color += vec4(
    color_ambient +
    color_diffuse * reflection_diffuse  * 0.3 +
    color_specular * reflection_specular  * 0.4, 1.0);

  }



  // // calculer la couleur du fragment
  // fragment_color = texture(tex0, texCoordVarying) + vec4(
  //   color_ambient +
  //   color_diffuse * reflection_diffuse  * 0.3 +
  //   color_specular * reflection_specular  * 0.4, 1.0);
}


