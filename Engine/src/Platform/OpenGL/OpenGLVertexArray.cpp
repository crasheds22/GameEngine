#include "ngpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Engine {

	static GLenum Convert(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		NG_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &mRendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(mRendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		NG_CORE_ASSERT(vertexbuffer->Layout().Elements().size(), "Vertex buffer has no layout");

		glBindVertexArray(mRendererID);
		vertexbuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexbuffer->Layout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.ComponentCount(),
				Convert(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.Stride(),
				(const void*)element.Offset);
			index++;
		}

		mVertexBuffers.push_back(vertexbuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(mRendererID);
		indexBuffer->Bind();

		mIndexBuffers = indexBuffer;
	}
}
