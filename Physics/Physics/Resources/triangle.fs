#version 450 core

in vec3 fragColor;

out vec4 color;

uniform float currentTime;

void main(void){
    color = texture(tex, fragTexCoord);
}