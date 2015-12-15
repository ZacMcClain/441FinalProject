uniform sampler2D tex;
uniform int hit;

void main() {
    // Apply texture
    gl_FragColor = texture2D(tex, gl_TexCoord[0].st);

    // shade red if hit
    if (hit > 0) {
        gl_FragColor.r += 0.3;
    }
}
