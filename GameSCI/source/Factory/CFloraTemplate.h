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
	///Klasa reprezentuje generyczny wzorzec roœlinnoœci
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
		///Wirtualna metoda zwalniaj¹ca zasób
		///
		void Drop();

		///
		///Metoda ³aduj¹ca dane
		///
		///@param &name - sta³a referencja na std::string
		///
		bool Load(const std::string &name);

		///
		///Wirtualna metoda ³aduj¹ca dane z xml ³aduje cechy CFlora
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
		///Wirtualna metoda wype³niaj¹ca danymi obiekt klasy CFlora
		///
		///@param *flora - wskaŸnik na obiekt klasy CFlora
		///
		virtual void Fill(CFlora *flora);

		//gdy w klasie CFlora byd¹ dodawane pola
		//to tutaj, w klasie jej fabryki,
		//nale¿ay utworzyæ takie same pola oraz je uwzglêdniæ
	};
}//namespace factory


#endif //#ifndef H_CFloraTemplate