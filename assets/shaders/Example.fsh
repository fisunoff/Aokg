#version 330 core

uniform vec4 color1;
uniform vec4 color2;

in vec2 pos;
out vec4 fragColor;

void main()
{

	fragColor = int(pos.y<pos.x)*color2 + int(pos.y>pos.x)*color1;

}