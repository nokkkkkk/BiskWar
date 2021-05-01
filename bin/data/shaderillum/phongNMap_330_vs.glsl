// IFT3100H20 ~ phong_330_vs.glsl

#version 330

// attributs de sommet
in vec4 position;
in vec2 texcoord;
in vec3 normal;

// attributs en sortie
out vec3 surface_position;
out vec3 surface_normal;
out vec2 texCoordVarying;

//Normal Mapping
out vec2 varyingtexcoord;
out vec3 texSpaceLight;
out vec3 texSpaceEye;
uniform vec4 light_position_vertex_shader;

// attributs uniformes
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;
uniform mat4 normalMatrix;


void main()
{
  texCoordVarying = texcoord;


    vec3 n_normal = vec3(normalMatrix) * normal;
    
    vec3 tangent;
    vec3 bitangent;
    vec3 c1 = cross(n_normal, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(n_normal, vec3(0.0, 1.0, 0.0));
    if (length(c1) > length(c2))
        tangent = c1;
    else
        tangent = c2;
    tangent     = normalize(tangent);
    bitangent   = normalize(cross(n_normal, tangent));
    

  //Normal Mapping
  vec4 spaceVertex = modelViewMatrix * position;
   vec3 lightDirection = vec3(light_position_vertex_shader - spaceVertex);
        
        texSpaceLight.x = dot(tangent,   lightDirection);
        texSpaceLight.y = dot(bitangent, lightDirection);
        texSpaceLight.z = dot(n_normal,  lightDirection);
  
	// Calculate eye vector, which is in camera space.
	vec3 v_vertex = vec3(-spaceVertex) ;

	// Like the light, this brings the eye vector to texture space.
	texSpaceEye.x = dot(v_vertex, tangent);
	texSpaceEye.y = dot(v_vertex, bitangent);
	texSpaceEye.z = dot(v_vertex, n_normal);



  // calculer la matrice normale
  mat4x4 normalMatrixPhong = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  surface_normal = vec3(normalMatrixPhong) * normal;

  // transformation de la position du sommet dans l'espace de vue
  surface_position = vec3(modelViewMatrix * position);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projectionMatrix * modelViewMatrix * position;
}
