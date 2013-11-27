/*
 _______________________________
| IKeyListener.h - interface.   |
| Jack Flower june 2013.        |
|_______________________________|

*/

#ifndef H_KEY_LISTENER_SCI
#define H_KEY_LISTENER_SCI

#include <SFML/Window/Event.hpp>

namespace listener
{
	///
	///Interfejs reprezentuje zdarzenia klawiatury
	///
	class IKeyListener
	{
	public:
		virtual ~IKeyListener() {};
		virtual void KeyPressed( const sf::Event::KeyEvent &e ) {};
		virtual void KeyReleased( const sf::Event::KeyEvent &e ) {};
	};
}//namespace listener;
#endif//H_KEY_LISTENER_SCI
