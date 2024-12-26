#version 430

layout (local_size_x = 256) in;

layout (std430, binding = 0) buffer Data {
    vec3 values[];
};

void main() {
    uint idx = gl_GlobalInvocationID.x;
    values[idx + 0]  += values[idx + 1];
}
