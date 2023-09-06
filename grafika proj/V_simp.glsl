#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Attributes
in vec4 vertex; 
in vec2 texCoord0;

in vec4 normal; 
out vec2 iTexCoord0;

out vec4 ic;
out vec4 l1;
out vec4 l2;
out vec4 n;
out vec4 v;

void main(void) {
    vec4 lp1 = vec4(0, -10, 30, 1); //pozycja œwiat³a
    vec4 lp2 = vec4(100,-10,-20,1); 
    l1 = normalize(V * lp1 - V * M * vertex);
    l2 = normalize(V * lp2 - V * M * vertex); //wektory w kierunku œwiat³a w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektory w kierunku kamery w przestrzeni oka
    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
    iTexCoord0=texCoord0;
    //ic = color;

    gl_Position = P * V * M * vertex;
}
