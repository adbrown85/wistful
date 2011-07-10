#version 140

/* Uniforms */
uniform mat4 MVPMatrix = mat4(1.0);

/* Inputs */
in vec4 MCVertex;
in vec4 TexCoord0;

/* Outputs */
out vec2 Coord0;


/** Transforms the incoming vertex. */
void main() {
    Coord0 = TexCoord0.st;
    gl_Position = MCVertex; 
}
