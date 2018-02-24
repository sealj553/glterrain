#version 330 core
layout(triangles) in;

// Three lines will be generated: 6 vertices
layout(line_strip, max_vertices=6) out;

uniform mat4 viewProjection;

in vec3 vNormal[];

float normal_length = 3;

void main() {
  int i;
  for(i = 0; i < gl_in.length(); i++){
    vec3 P = gl_in[i].gl_Position.xyz;
    vec3 N = vNormal[i].xyz;
    
    gl_Position = viewProjection * vec4(P, 1.0);
    EmitVertex();
    
    gl_Position = viewProjection * vec4(P + N * normal_length, 1.0);
    EmitVertex();
    
    EndPrimitive();
  }
}
