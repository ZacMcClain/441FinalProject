/*
 *   Glow Fragment Shader (kinda Working)
 */

#version 120

uniform sampler2D tex; // our frame buffer tex

uniform float fbSize;  // the size of the frame buffer

void main() {
    float glowSize = 5; // the side of pixel window we will glow over
    // this will be set to the final pixel color after the blur is applied
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
	
	vec2 texel = (gl_TexCoord[0].st);
	vec4 original = texture2D( tex, texel);
    // centered around some s, go glowSize steps left and right (pixel rows)
    for( float i = -glowSize; i <= glowSize; i += 1.0 ) {
        // centered around t, go glowSize steps up and down (pixel columns)
        for( float j = -glowSize; j <= glowSize; j += 1.0 ) {
            // take a texel offset from the fragment tex and add it to our running total
            // this will normalize the blur window position
            finalColor += texture2D( tex, gl_TexCoord[0].st + (vec2(i, j) / fbSize) ); 
        }
    }

    // calc the blur dimension
    float blurDim = (glowSize * 2.0) + 1.0;
    // average the colors by the number of samples we took
    finalColor *= (1.0 / (blurDim*blurDim));

    // glow
    finalColor = (finalColor * 1.0) + original;

    // we need to make certain that all our values are between 0 and 1
    gl_FragColor = clamp( finalColor, 0.0, 1.0 ); 
}
