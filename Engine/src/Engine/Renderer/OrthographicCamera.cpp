#include "ngpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: mProjection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), mView(1.0f)
	{
		mViewProjection = mProjection * mView;
	}

	void OrthographicCamera::RecalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1));
	}
}
