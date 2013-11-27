/*
 _______________________________
| IMouseListener.h - interface. |
| Jack Flower june 2013.        |
|_______________________________|

*/

#ifndef H_MOUSE_LISTENER_SCI
#define H_MOUSE_LISTENER_SCI

#include <SFML/Window/Event.hpp>

namespace listener
{
	///
	///Interfejs reprezentuje zdarzenia myszy
	///
	class IMouseListener
	{
	public:
		virtual ~IMouseListener() {};
		virtual void MousePressed( const sf::Event::MouseButtonEvent &e ) {};
		virtual void MouseReleased( const sf::Event::MouseButtonEvent &e ) {};
		virtual void MouseMoved( const sf::Event::MouseMoveEvent& e ) {}; 
		virtual void MouseWheelMoved( const sf::Event::MouseWheelEvent& e ) {};
	};
}//namespace listener;
#endif//H_MOUSE_LISTENER_SCI
