#version 140

/* Inputs */
in vec3 MCVertex;
in vec3 TexCoord0;

/* Outputs */
out vec3 Coord0;


/** Transforms the incoming vertex. */
void main() {
    Coord0 = TexCoord0;
    gl_Position = vec4(MCVertex, 1.0); 
}
