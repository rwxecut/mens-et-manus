#version 330 core

in vec2 texCoord;

out vec4 color;

uniform float alpha;
uniform sampler2D splashTex;

void main () {
    color = texture (splashTex, texCoord) * vec4 (alpha, alpha, alpha, 1);
}
