#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_texCoord;

out vec2 texCoord;

uniform mat4 MVP;
uniform vec2 tilePos;

void main () {
    gl_Position = MVP * vec4 (pos + tilePos, 0.0f, 1.0f);
    texCoord = vec2 (in_texCoord.s, 1.0f - in_texCoord.t);
}
