/*
 __________________________________________________________
| IResource.h - definicja abstrakcyjnego interfejsu.       |
| SCI - September 2012.                                    |
|__________________________________________________________|

*/

#ifndef H_IRESOURCE_SCI
#define H_IRESOURCE_SCI

#include <string>
#include <map>

namespace resource
{
	typedef unsigned long long	ResourceHandle;			//uchwyt zasobu - bardzo du¿a liczba
	#define						InvalidResourceHandle 0	//definicja - makro (zamiast pisaæ 0)

	///
	///Klasa reprezentuje abstrakcyjny interfejs
	///
	class IResource
	{

	public:

		///
		///Konstruktor
		///
		IResource();

		///
		///Destruktor wirtualny
		///
		virtual ~IResource();

		///
		///Wirtualna metoda ³aduj¹ca zasób - implementacje w klasach pochodnych
		///
		///@param &file_name - sta³a referencja na nazwê pliku
		///
		virtual bool Load(const std::string &file_name) = 0;

		///
		///Wirtualna metoda zwalniaj¹ca zasób - implementacje w klasach pochodnych
		///
		virtual void Drop() = 0;

	};
}//namespace resource
#endif //H_IRESOURCE_SCI
