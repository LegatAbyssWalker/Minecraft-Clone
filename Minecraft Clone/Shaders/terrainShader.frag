#version 460

out vec4 fragColor;
in vec2 texCoord;

out vec4 color;	

uniform sampler2D theTexture;

void main() {
	color = texture(theTexture, texCoord);

	if (color.a < 0.1) {
		discard;
	}
};