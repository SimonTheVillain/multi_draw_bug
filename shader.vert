R"(
#version 460 core
layout(std430, binding = 0) buffer VertexBuffer {
    vec2 vertices[];
};


void main(void){
    int ind =  gl_VertexID;
    gl_Position.xy = vertices[ind];
    gl_Position.zw = vec2(0,1);


}
)"