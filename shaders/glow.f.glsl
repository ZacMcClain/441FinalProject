/*
 *   Glow Fragment Shader (Not Working yet)
 */

#version 120

uniform sampler2D tex; // our frame buffer tex

uniform float fbSize;  // the size of the frame buffer
uniform float blurSize; // the side of pixel window we will blur over

void main() {
    // this will be set to the final pixel color after the blur is applied
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);

    // centered around some s, go blurSize steps left and right (pixel rows)
    for( float i = -blurSize; i <= blurSize; i += 1.0 ) {
        // centered around t, go blurSize steps up and down (pixel columns)
        for( float j = -blurSize; j <= blurSize; j += 1.0 ) {
            // take a texel offset from the fragment tex and add it to our running total
            // this will normalize the blur window position
            finalColor += texture2D( tex, gl_TexCoord[0].st + (vec2(i, j) / fbSize) ); 
        }
    }

    // calc the blur dimension
    float blurDim = (blurSize * 2.0) + 1.0;
    // average the colors by the number of samples we took
    finalColor *= (1.0 / (blurDim*blurDim));

    // glow
    finalColor = (finalColor * 0.5) + 0.5;

    // we need to make certain that all our values are between 0 and 1
    gl_FragColor = clamp( finalColor, 0.0, 1.0 ); 
}
