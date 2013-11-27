/*
 ____________________________________________________________________________________________________
| IFrameListener.h - interfejs abstrakcyjnej klasy bazowej z metodami aktulizuj¹cymi logikê obiektu. |
| SCI - February 2012.                                                                               |
|____________________________________________________________________________________________________|

*/

#ifndef H_FRAME_LISTENER_SCI
#define H_FRAME_LISTENER_SCI

namespace listener
{
	///
	///Klasa bazowa reprezentuje publiczny interface dla obieków aktulizuj¹cych logikê w czasie rzeczywistym
	///
	class IFrameListener
	{
	public:

		///
		///Wirtualny destruktor
		///
		virtual ~IFrameListener() {};

		///
		///Wirtulana abstrakcyjna metoda aktualizuj¹ca logikê obiektu
		///
		///@param elapsed_time - up³ywaj¹cy czas
		///
		virtual void FrameStarted(float elapsed_time) = 0;
	};
}//namespace listener
#endif//H_FRAME_LISTENER_SCI
