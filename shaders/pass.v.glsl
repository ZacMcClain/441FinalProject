// Shakes the ships left/right if hit

uniform float time;
uniform int hit;

void main(void) {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // Shake if hit
    if (hit > 0) {
        gl_Position.x += 2.0 * sin(50.0 * time);
    }

    gl_TexCoord[0] = gl_MultiTexCoord0;
}
