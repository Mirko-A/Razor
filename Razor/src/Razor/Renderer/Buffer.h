#pragma once

#include "Razor/Core.h"

#include <cstdint>

namespace Razor
{
    enum ShaderDataType
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool,
        ShaderDataTypeCount,
    };

    static const uint32_t SHADER_TYPE_SIZE_TABLE[ShaderDataType::ShaderDataTypeCount] =
    {
        0,                        // None
        4, 4 * 2, 4 * 3, 4 * 4,   // Float
        4, 4 * 2, 4 * 3, 4 * 4,   // Int
        4 * 3 * 3, 4 * 4 * 4,     // Mat
        1,                        // Bool
    };

    static const uint32_t SHADER_TYPE_COUNT_TABLE[ShaderDataType::ShaderDataTypeCount] =
    {
        0,              // None
        1, 2, 3, 4,     // Float
        1, 2, 3, 4,     // Int
        3 * 3, 4 * 4,   // Mat
        1,              // Bool
    };

    struct BufferElement
    {
        ShaderDataType Type;
        std::string Name;
        uint32_t Size;
        uint32_t Count;
        uint32_t Offset;
        bool Normalized;

        BufferElement(ShaderDataType ElementType, const std::string& ElementName, bool IsNormalized = false)
            : Type(ElementType),
              Name(ElementName), 
              Size(SHADER_TYPE_SIZE_TABLE[ElementType]),
              Count(SHADER_TYPE_COUNT_TABLE[ElementType]),
              Offset(0),
              Normalized(IsNormalized)
        {

        }
    };

    class BufferLayout
    {
    public:
        BufferLayout()
        {

        }

        BufferLayout(const std::initializer_list<BufferElement>& Elements)
            : m_Elements(Elements)
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetElements()
        {
            return m_Elements;
        }

        inline uint32_t GetStride() const
        {
            return m_Stride;
        }

        std::vector<BufferElement>::iterator begin()
        {
            return m_Elements.begin();
        }

        std::vector<BufferElement>::iterator end()
        {
            return m_Elements.end();
        }

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t Offset = 0;

            for (BufferElement& Element : m_Elements)
            {
                Element.Offset = Offset;
                Offset += Element.Size;
                m_Stride += Element.Size;
            }
        }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(BufferLayout Layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        virtual void SetData(float* Vertices, uint32_t size) = 0;

        inline uint32_t GetID() const
        {
            return m_BufferID;
        }

    protected:
        uint32_t m_BufferID;
        BufferLayout m_Layout;
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(uint32_t* Indices, uint32_t size) = 0;

        inline uint32_t GetID() const
        {
            return m_BufferID;
        }

    protected:
        uint32_t m_BufferID;
    };
}