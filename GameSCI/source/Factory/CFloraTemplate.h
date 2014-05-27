#ifndef H_CFloraTemplate
#define H_CFloraTemplate
class CFloraTemplate
{

#include "CActorTemplate.h"
#include "../Logic/Flora/CFlora.h"
///
///Forward declaration
///
namespace xml
{
	class CXml;
}

namespace factory
{
	///
	///Klasa reprezentuje generyczny wzorzec ro�linno�ci
	///
	class CFloraTemplate : public CActorTemplate
	{

	public:

		///
		///Konstruktor
		///
		CFloraTemplate();

		///
		///Destruktor wirtualny
		///
		virtual ~CFloraTemplate();

		///
		///Wirtualna metoda zwalniaj�ca zas�b
		///
		void Drop();

		///
		///Metoda �aduj�ca dane
		///
		///@param &name - sta�a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda �aduj�ca dane z xml �aduje cechy CFlora
		///
		///@param &xml - referencja na obiekt klasy CXml
		///
		bool Load(CXml &xml);

		///
		///Metoda tworzy obiek klasy CFlora
		///
		///@param id - nazwa identyfikatora - obiekt klasy std::wstring
		///
		CFlora* Create(std::wstring id = L"");

	private:

		///
		///Wirtualna metoda wype�niaj�ca danymi obiekt klasy CFlora
		///
		///@param *flora - wska�nik na obiekt klasy CFlora
		///
		virtual void Fill(CFlora *flora);

		//gdy w klasie CFlora byd� dodawane pola
		//to tutaj, w klasie jej fabryki,
		//nale�ay utworzy� takie same pola oraz je uwzgl�dni�
	};
}//namespace factory


#endif //#ifndef H_CFloraTemplate