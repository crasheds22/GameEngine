#ifndef EVENT_H
#define EVENT_H

#include "ngpch.h"

#include "Engine/Core.h"

namespace Engine
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		Apptick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

	#define EVENT_CLASS_TYPE(type) static EventType StaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return StaticType(); }\
								virtual const char* Name() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int CategoryFlags() const override { return category; }

	class ENGINE_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* Name() const = 0;
		virtual int CategoryFlags() const = 0;
		virtual std::string ToString() const { return Name(); }

		bool IsInCategory(EventCategory category)
		{
			return CategoryFlags() & category;
		}

	public:
		bool Handled;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : mEvent(event)
		{ }

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (mEvent.GetEventType() == T::StaticType())
			{
				mEvent.Handled = func(*(T*)&mEvent);
				return true;
			}
			return false;
		}

	private:
		Event& mEvent;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}

#endif
