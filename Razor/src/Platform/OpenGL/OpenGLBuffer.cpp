#include "rzr_pch.h"

#include "OpenGLBuffer.h"

#include "Razor/Log.h"

#include "glad/glad.h"

namespace Razor
{
    /********* Vertex buffer implementation *************************/
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_BufferID);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, Vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(float* Vertices, uint32_t size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, Vertices, GL_STATIC_DRAW);
    }

    /********* Index buffer implementation *************************/
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t size)
    {
        glCreateBuffers(1, &m_BufferID);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, Indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_BufferID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::SetData(uint32_t* Indices, uint32_t size)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, Indices, GL_STATIC_DRAW);
    }
}