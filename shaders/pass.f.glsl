uniform sampler2D tex;

void main() {
    // Apply texture
    gl_FragColor = texture2D(tex, gl_TexCoord[0].st);
}
