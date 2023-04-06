# version 330
in vec3 vert;
in vec3 normal;

void main(void)
{
    gl_Position = vec4(vert,1.0);
}
