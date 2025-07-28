#version 330 core

in vec2 vUV;
in vec4 vColor;

uniform sampler2D u_Texture;

out vec4 FragColor;

void main() {
    vec4 texColor = texture(u_Texture, vUV);
    FragColor = texColor * vColor;
}
