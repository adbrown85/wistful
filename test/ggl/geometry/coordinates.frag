#version 140

/* Inputs */
in vec3 Coord0;

/* Outputs */
out vec4 FragColor;


/** Colors the fragment. */
void main() {
    FragColor.rgb = Coord0;
    FragColor.a = 1.0;
}
