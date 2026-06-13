#include "Renderer.h"
#include <iostream>



void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const 
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() 
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}