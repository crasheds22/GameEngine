#pragma once

#include "Engine/Renderer/VertexArray.h"

namespace Engine {
	
	class OpenGLVertexArray
		: public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) override;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) override;

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return mIndexBuffers; }
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return mVertexBuffers; }

	private:
		uint32_t mRendererID;

		std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffers;
	};
}
