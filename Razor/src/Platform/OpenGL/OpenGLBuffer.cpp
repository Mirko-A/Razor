#include "rzr_pch.h"

#include "OpenGLBuffer.h"

#include "Razor/Log.h"

namespace Razor
{
    /********* Vertex buffer implementation *************************/
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_BufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
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

    void OpenGLVertexBuffer::SetLayout(BufferLayout Layout)
    {
        RZR_CORE_ASSERT(Layout.GetElements().size(), "Empty layout is not allowed!");
     
        m_Layout = Layout;

        uint8_t LayoutIndex = 0;
        for (const BufferElement& Element : Layout)
        {
            glEnableVertexAttribArray(LayoutIndex);
            glVertexAttribPointer(LayoutIndex,
                                  Element.Count,
                                  ShaderDataTypeToGLenum(Element.Type), 
                                  Element.Normalized ? GL_TRUE : GL_FALSE,
                                  Layout.GetStride(),
                                  (const void*) Element.Offset);

            LayoutIndex++;
        }
    }

    const BufferLayout& OpenGLVertexBuffer::GetLayout() const
    {
        return m_Layout;
    }

    void OpenGLVertexBuffer::SetData(float* Vertices, uint32_t size)
    {
        glBufferData(GL_ARRAY_BUFFER, size, Vertices, GL_STATIC_DRAW);
    }

    GLenum OpenGLVertexBuffer::ShaderDataTypeToGLenum(ShaderDataType Type)
    {
        GLenum OpenGLType;

        switch (Type)
        {
        case Razor::Float:
            OpenGLType = GL_FLOAT;
            break;
        case Razor::Float2:
            OpenGLType = GL_FLOAT;
            break;
        case Razor::Float3:
            OpenGLType = GL_FLOAT;
            break;
        case Razor::Float4:
            OpenGLType = GL_FLOAT;
            break;
        case Razor::Int:
            OpenGLType = GL_INT;
            break;
        case Razor::Int2:
            OpenGLType = GL_INT;
            break;
        case Razor::Int3:
            OpenGLType = GL_INT;
            break;
        case Razor::Int4:
            OpenGLType = GL_INT;
            break;
        case Razor::Mat3:
            OpenGLType = GL_FLOAT;
            break;
        case Razor::Mat4:
            OpenGLType = GL_FLOAT;
            break;
        case Razor::Bool:
            OpenGLType = GL_BOOL;
            break;
        default:
            RZR_CORE_ASSERT(false, "Invalid enum conversion!");
            break;
        }

        return OpenGLType;
    }

    /********* Index buffer implementation *************************/
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t size)
    {
        glCreateBuffers(1, &m_BufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, Indices, GL_STATIC_DRAW);

        m_Count = size / sizeof(uint32_t);
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