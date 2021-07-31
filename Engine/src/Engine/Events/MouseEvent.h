#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Event.h"

#include <sstream>

namespace Engine {

	class ENGINE_API MouseMovedEvent
		: public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: mMouseX(x), mMouseY(y)
		{ }

		float Y() const { return mMouseY; }
		float X() const { return mMouseX; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << mMouseX << "," << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		float mMouseX;
		float mMouseY;
	};

	class ENGINE_API MouseScrolledEvent
		: public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: mXOffset(xOffset), mYOffset(yOffset)
		{ }

		float XOffset() const { return mXOffset; }
		float YOffset() const { return mYOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << XOffset() << ", " << YOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float mXOffset;
		float mYOffset;
	};

	class ENGINE_API MouseButtonEvent
		: public Event
	{
	public:
		int GetMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	protected:
		MouseButtonEvent(int button)
			: mButton(button)
		{ }

		int mButton;
	};

	class ENGINE_API MouseButtonPressedEvent
		: public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MosueButtonPressedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class ENGINE_API MouseButtonReleasedEvent
		: public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

#endif
