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
	typedef unsigned long long	ResourceHandle;			//uchwyt zasobu - bardzo du�a liczba
	#define						InvalidResourceHandle 0	//definicja - makro (zamiast pisa� 0)

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
		///Wirtualna metoda �aduj�ca zas�b - implementacje w klasach pochodnych
		///
		///@param &file_name - sta�a referencja na nazw� pliku
		///
		virtual bool Load(const std::string &file_name) = 0;

		///
		///Wirtualna metoda zwalniaj�ca zas�b - implementacje w klasach pochodnych
		///
		virtual void Drop() = 0;

	};
}//namespace resource
#endif //H_IRESOURCE_SCI
