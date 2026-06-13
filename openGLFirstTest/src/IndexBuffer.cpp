#include "IndexBuffer.h"




IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    //create the buffer
    GLCALL(glGenBuffers(1, &m_RendererID));
    //bind the buffer and sets it's type
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    //tell the buffer what type of data it holds
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() 
{
    GLCALL(glDeleteBuffers(1,&m_RendererID));
}


void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID))
}

void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}