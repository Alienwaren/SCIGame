/*
 _____________________________________________
| CResourceManager.h - definicja klasy.       |
| SCI - September 2012.                       |
|_____________________________________________|

*/

#ifndef H_RESOURCE_MANAGER_SCI
#define H_RESOURCE_MANAGER_SCI

#include "../Utilities/Singleton/CSingleton.h"
#include "IResource.h"
#include <map>
#include <string>

///
///Forward declarations
///
namespace xml
{
	class CXml;
}

///
///Forward declarations
///
namespace factory
{
	class CPhysicalTemplate;
	class CActorTemplate;
	class CEnemyTemplate;
	class CPlayerTemplate;
};

///
///Forward declarations
///
namespace resource
{
	class CTexture;	//opakowanie sf::Texture 
	class CMusic;	//opakowanie sf::Music
	class CSound;	//opakowanie sf::SoundBuffer
	class CFont;	//opakowanie sf::Font
}

using namespace factory;

#define gResourceManager CResourceManager::GetSingleton()

namespace resource
{

	///
	///Klasa reprezentuje menagera zasobów
	///
	class CResourceManager : public CSingleton<CResourceManager>
	{
	public:

		///
		///Konstruktor domyślny
		///
		CResourceManager();

		///
		///Destruktor wirtualny
		///
		virtual ~CResourceManager();



		//Metody  ł a d u j ą c e  zasoby

		///
		///Metoda ładuje zasób CTexture
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		ResourceHandle LoadTexture(const std::string& name);

		///
		///Metoda ładuje zasób CMusic
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		ResourceHandle LoadMusic(const std::string& name);

		///
		///Metoda ładuje zasób CSound
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		ResourceHandle LoadSound(const std::string& name);

		///
		///Metoda ładuje zasób CFont
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		ResourceHandle LoadFont(const std::string& name);

		///
		///Metoda ładuje zasób CPhysicalTemplate
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		ResourceHandle LoadPhysicalTemplate(const std::string& name);




		//Metody  z w r a c a j ą c e  zasoby

		///
		///Metoda zwraca wskaźnik na zasób - obiekt klasy CTexture
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		CTexture* GetTexture(const std::string& name);

		///
		///Metoda zwraca wskaźnik na zasób - obiekt klasy CMusic
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		CMusic* GetMusic(const std::string& name);

		///
		///Metoda zwraca wskaźnik na zasób - obiekt klasy CSound
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		CSound* GetSound(const std::string& name);

		///
		///Metoda zwraca wskaźnik na zasób - obiekt klasy CFont
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		CFont* GetFont(const std::string& name);

		///
		///Metoda zwraca wskaźnik na zasób - obiekt klasy CPhysicalTemplate
		///
		///@param &name - stała referencja na nazwę zasobu
		///
		CPhysicalTemplate* GetPhysicalTemplate(const std::string& name);

		///
		///Metoda usuwa zasób na podstawie nazwy std::string
		///
		///@param &name - stała referencja na nazwę zasoby std::string
		///
		void DropResource(const std::string& name);
		
		///
		///Metoda usuwa wszystkie zasoby z kontenera
		///
		void Clear();

		///
		///Wirtualny interfejs - implementacja
		///
		virtual void Cleanup();
		
	private:

		std::map<ResourceHandle, IResource*> m_resources;	//kontener <map> przechowujący wskaźniki na zasoby
															//key - ResourceHandle (wygenrowana liczba - uchwyt)
															//value - wskaźnik na zasób
		
		///
		///Szablon prywatnej metody zwracającej wskaźnik na zasób na podstawie nazwy std::string
		///
		///@param &name - stała referencja na nazwę zasobu std::string
		///
		template <typename T> T* GetResource(const std::string& name);

		///
		///Szablon prywatnej metody ładującej zasób
		///
		///@param &name - stała referencja na zasób std::string
		///
		template <typename T> ResourceHandle LoadResource(const std::string& name);

		///
		///Szablon prywatnej metody ładujące zasoby (wzorce danych dla obiektów gry)
		///
		///@param &name - stała referencja na zasób std::string
		///
		template <> ResourceHandle LoadResource<CPhysicalTemplate>(const std::string& name);

	};
}//namespace resource
#endif //H_RESOURCE_MANAGER_SCI
