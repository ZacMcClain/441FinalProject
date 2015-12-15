/*
 *   Glow Vertex Shader
 */

#version 120

void main(void) {
    /*****************************************/
    /********* Vertex Calculations  **********/
    /*****************************************/
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    /*****************************************/
    /********* Texture Calculations  *********/
    /*****************************************/
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
}