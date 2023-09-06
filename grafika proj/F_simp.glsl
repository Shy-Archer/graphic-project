#version 330

out vec4 pixelColor;    


in vec4 n;
in vec4 l1;
in vec4 l2;
in vec4 v;
uniform sampler2D textureMap0;
//uniform sampler2D textureMap1;
uniform vec4 lightDir1 = vec4(1, 1, 1, 1);   
uniform vec4 lightDir2 = vec4(-1, -1, -1, 1);
in vec2 iTexCoord0;
//in vec2 iTexCoord1;

void main(void) {
    // znormalizowane, spolaryzowane wektory
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);
    
    // wektory odbicia
    vec4 mr1 = reflect(-l1, mn);   // Reflected vector for light 1
    vec4 mr2 = reflect(-l2, mn);   // Reflected vector for light 2
    
    // parametry powierzchniowe
    
    vec4 ks = vec4(0, 0, 0, 1);
    vec4 ks1 = vec4(0, 0, 0, 1);
    

    
   
    float nl1 = clamp(dot(mn, l1), 0, 1.0f) + clamp(dot(n, lightDir1), 0, 1.0f);//intensywnoœæ œwiat³a rozproszonego 
    float nl2 = clamp(dot(mn, l2), 0, 0.5f) + clamp(dot(n, lightDir2), 0, 0.5f);
    float rv1 = pow(clamp(dot(mr1, mv), 0, 1.0f), 50); //po³ysk
    float rv2 = pow(clamp(dot(mr2, mv), 0, 0.5f), 50);
    
    vec4 texColor = texture(textureMap0, iTexCoord0);
    pixelColor = vec4(texColor.rgb * (nl1 +nl2), texColor.a) + vec4(ks.rgb * rv1, 0) + vec4(ks1.rgb * rv2, 0);
}