#version 330 core

in vec2 pixelPos;
out vec4 fragColor;

uniform vec2 iResolution;
uniform float iTime;

#define PI 3.1415926
#define TWO_PI (2.0 * PI)

vec3 getColor(float t) {
    return vec3(0.5) + vec3(0.9, 0.4, 0.3) * cos(TWO_PI * (vec3(t) + vec3(0.3, 0.2, 0.5)));
}

void main() {
    vec2 c = (2.0 * pixelPos - iResolution) / iResolution.y;
    vec3 outColor = vec3(0.0);

    float d = length(c);
    float a = atan(c.y, c.x) / PI + 1.0;

    for (float i = 0.0; i < 5.0; i++) {
        float k = fract(a * i) * 4.0;
        vec3 color = getColor(d * i + iTime * 0.5 + k) * exp(-d);
        d = d * 1.5;
        outColor += color * 0.25;
    }

    fragColor = vec4(outColor, 1.0);
}
