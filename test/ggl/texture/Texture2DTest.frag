#version 140

/* Uniforms */
uniform vec4 Color = vec4(1.0);
uniform sampler2D Texture;

/* Inputs */
in vec2 Coord0;

/* Outputs */
out vec4 FragColor;


/** Colors the fragment. */
void main() {
    FragColor = texture(Texture, Coord0.st);
    FragColor.a = 1.0;
}
