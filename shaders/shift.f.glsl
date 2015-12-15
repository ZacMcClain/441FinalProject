uniform sampler2D tex;
uniform float time;

void main() {
    // Adjust the texture
    float angle = atan(gl_TexCoord[0].t - 0.5, gl_TexCoord[0].s - 0.5);
    vec2 coord = vec2(0.0, 0.0);
    coord.x = gl_TexCoord[0].s - 0.5 - 0.01 * time * cos(angle);
    coord.y = gl_TexCoord[0].t - 0.5 - 0.01 * time * sin(angle);
    // Apply texture
    gl_FragColor = texture2D(tex, coord.xy);
}
