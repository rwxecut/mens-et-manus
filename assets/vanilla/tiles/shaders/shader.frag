#version 330 core

in vec2 texCoord;

out vec4 color;

uniform bool drawBorder;
uniform sampler2D tex;
uniform bool selected;

const vec3 colorUnselected  = vec3 (1.000, 1.000, 1.000);
const vec3 colorSelected    = vec3 (0.122, 0.608, 0.176);
const vec3 colorBorder      = vec3 (0.737, 0.737, 0.737);

void main () {
    if (drawBorder)
        color = vec4 (colorBorder, 1);
    else {
        if (selected)
            color = texture (tex, texCoord) * vec4 (colorSelected, 1);
        else
            color = texture (tex, texCoord) * vec4 (colorUnselected, 1);
    }
}
