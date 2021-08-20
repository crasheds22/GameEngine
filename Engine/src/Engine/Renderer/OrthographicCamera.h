#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include <../Vendor/glm/glm/glm.hpp>

namespace Engine {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& Position() const { return mPosition; }
		void Position(const glm::vec3 position) { mPosition = position; RecalculateMatrix(); }

		float Rotation() const { return mRotation; }
		void Rotation(float rotation) { mRotation = rotation; RecalculateMatrix(); }

		const glm::mat4& Projection() const { return mProjection; }
		const glm::mat4& View() const { return mView; }
		const glm::mat4& ViewProjection() const { return mViewProjection; }

	private:
		void RecalculateMatrix();

		glm::mat4 mProjection;
		glm::mat4 mView;
		glm::mat4 mViewProjection;

		glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
		float mRotation = 0.0f;
	};
}

#endif
