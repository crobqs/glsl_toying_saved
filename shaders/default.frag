#version 460 core

uniform float time;
uniform vec2 resolution;
uniform vec2 mpos;
uniform float clickTime;
unfiorm vec2 clickPos;

out vec4 FragColor;

float _smoothstep(float a, float b, float x) {
    float t = clamp((x - a) / (b - a), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

float _smootherstep(float a, float b, float x) {
    float t = clamp((x - a) / (b - a), 0.0f, 1.0f);
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

float _smootheststep(float a, float b, float x) {
    float t = clamp((x - a) / (b - a), 0.0f, 1.0f);
    return t * t * t * t * (35.0f - 84.0f * t + 70.0f * t * t - 20.0f * t * t * t);
}

float _gaussian(float d, float r) {
    float x = d / r;
    return exp(-x * x * 8.0f);
}

float _powstep(float d, float r) {
    float t = clamp(1.0f - d / r, 0.0f, 1.0f);
    return pow(t, 4.0f);
}

float _blendFalloff(float d, float r) {
    return _gaussian(d, r) * _smootheststep(0.0f, r, d);
}

void main() {
    // Aspect-corrected UV and mouse
    vec2 aspect = vec2(resolution.x / resolution.y, 1.0f);
    vec2 uv = (gl_FragCoord.xy / resolution) * aspect;
    vec2 muv = (vec2(mpos.x, resolution.y - mpos.y) / resolution) * aspect;

    float d = distance(uv, muv);

    // Horizontal split for left/right screen
    float mask = 0.0f;
    if (gl_FragCoord.x < resolution.x * 0.5f)
        mask = _gaussian(d, 0.4f);
    else
        mask = _powstep(d, 0.4f);
        // mask = 1.0f - _smootheststep(0.0f, 0.4f, d);

    vec3 pulseColor = vec3(muv, abs(sin(time)));
    vec3 color = pulseColor * mask;

    FragColor = vec4(color, 1.0f);
}
