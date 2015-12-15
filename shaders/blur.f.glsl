/*
 *   Blur Fragment Shader
 */

#version 120

uniform sampler2D tex; // our frame buffer tex

uniform float fbSize;  // the size of the frame buffer
uniform float blurSize;         // the side of our blur window

void main() {
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0); // this will be set to the final pixel color after the blur is applied

    // centered around some s, go blurSize steps left and right (its a box)
    for( float i = -blurSize; i <= blurSize; i += 1.0 ) {
        // centered around t, go blurSize steps up and down
        for( float j = -blurSize; j <= blurSize; j += 1.0 ) {
            // take a texel offset from our fragment tex and add it to our running total
            finalColor += texture2D( tex, gl_TexCoord[0].st + (vec2(i, j) / fbSize) ); // we need to normalize our blur window position
        }
    }

    float blurDim = (blurSize * 2.0) + 1.0;
    finalColor *= (1.0 / (blurDim*blurDim));    // average the colors by the number of samples we took

    gl_FragColor = clamp( finalColor, 0.0, 1.0 ); // make sure all our values are between 0 and 1
}
