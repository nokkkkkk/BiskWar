// IFT3100H20 ~ phong_330_fs.glsl

#version 330


uniform sampler2D textureBase;
uniform sampler2D normalMapTex;

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;
in vec2 texCoordVarying;

//Normal Mappping
in vec3 texSpaceLight;
in vec3 texSpaceEye;


// couleurs de réflexion du matériau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;



// attribut en sortie
out vec4 fragment_color;


// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3 light_position;
uniform vec4 lightDirections;


void main()
{


  // re-normaliser la normale après interpolation
  vec3 n = normalize(surface_normal);

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




    //Normal Mapping
    vec4 textureColor =  texture(textureBase, texCoordVarying);
	  vec4 color = 0.9 * textureColor;
    // Convert the color information to a normal.
    vec3 normalDX = normalize( texture(normalMapTex, texCoordVarying).xyz * 2.0 - 1.0 );
    vec3 normal;
    normal.x = dot(vec3(1.0, 0.0, 0.0), normalDX);
    normal.y = dot(vec3(0.0, -1.0, 0.0), normalDX);
    normal.z = dot(vec3(0.0, 0.0, 1.0), normalDX);

  vec3 light = normalize(texSpaceLight);
  
  float nDotL = max(dot(light, normal), 0.0);
  if (nDotL > 0.0)
        {
            vec3 eye = normalize(texSpaceEye);
            
            // Incident vector is opposite light direction vector.
            vec3 reflection = reflect(-light, normal);
            
            float eDotR = max(dot(eye, reflection), 0.0);
            
            color +=  nDotL;
            
            // Fixed 0.1 specular color factor and fixed 20.0 specular exponent.
            color += vec4(0.5, 0.5, 0.5, 0.5) * pow(eDotR, 20.0);
        }



        
    color.w = 1.0;///Alpha always 1
    
	  fragment_color = color;	


  

  // calculer la couleur du fragment
  // fragment_color = texture(textureBase, texCoordVarying) + vec4(
  //   color_ambient +
  //   color_diffuse * reflection_diffuse +
  //   color_specular * reflection_specular, 1.0);
}


