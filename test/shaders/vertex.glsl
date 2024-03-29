#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 fragmentUV;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    fragmentUV = vec2(vertexUV.x,1.0f-vertexUV.y);
}
