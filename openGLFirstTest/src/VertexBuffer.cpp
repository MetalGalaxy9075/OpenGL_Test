#include "VertexBuffer.h"




VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    //create the buffer
    GLCALL(glGenBuffers(1, &m_RendererID));
    //bind the buffer and sets it's type
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    //tell the buffer what type of data it holds
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() 
{
    GLCALL(glDeleteBuffers(1,&m_RendererID));
}


void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID))
}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
}