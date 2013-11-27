/*
 ____________________________________________________________________________________________________
| IFrameListener.h - interfejs abstrakcyjnej klasy bazowej z metodami aktulizuj�cymi logik� obiektu. |
| SCI - February 2012.                                                                               |
|____________________________________________________________________________________________________|

*/

#ifndef H_FRAME_LISTENER_SCI
#define H_FRAME_LISTENER_SCI

namespace listener
{
	///
	///Klasa bazowa reprezentuje publiczny interface dla obiek�w aktulizuj�cych logik� w czasie rzeczywistym
	///
	class IFrameListener
	{
	public:

		///
		///Wirtualny destruktor
		///
		virtual ~IFrameListener() {};

		///
		///Wirtulana abstrakcyjna metoda aktualizuj�ca logik� obiektu
		///
		///@param elapsed_time - up�ywaj�cy czas
		///
		virtual void FrameStarted(float elapsed_time) = 0;
	};
}//namespace listener
#endif//H_FRAME_LISTENER_SCI
