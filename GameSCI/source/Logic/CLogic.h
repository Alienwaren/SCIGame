/*
 ____________________________________
| CLogic.h - definicja klasy.        |
| SCI - January 2013.                |
|____________________________________|

*/

#ifndef H_LOGIC_SCI
#define H_LOGIC_SCI

#include "../Utilities/Singleton/CSingleton.h"
#include "../Game/Listener/IFrameListener.h"
#include "../Game/Listener/IKeyListener.h"
#include "../Game/Listener/IMouseListener.h"
#include <string>
#include <map>

using namespace listener;

#define gLogic CLogic::GetSingleton()

namespace logic
{
	///
	///Klasa reprezentuje machanizm logiki rozgrywki
	///
	class CLogic : public CSingleton<CLogic>, IFrameListener, IKeyListener, IMouseListener
	{
	public:

		///
		///Konstruktor
		///
		CLogic();

		///
		///Destruktor wirtualny
		///
		virtual ~CLogic();

		///
		///Wirtualna metoda aktualizuj¹ca logikê obiektów
		///
		virtual void FrameStarted(float secondsPassed);

		///
		///Wirtualna metoda aktualizuj¹ca logikê gry - zdarzenia klawiatury
		///
		///@param &e - sta³a referencja na obiekt klasy sf::Event::KeyEvent
		///
		virtual void KeyPressed(const sf::Event::KeyEvent &e);
	    
		///
		///Wirtualna metoda aktualizuj¹ca logikê gry - zdarzenia myszy
		///
		///@param &e - sta³a referencja na obiekt klasy sf::Event::MouseButtonEvent
		///
		virtual void MousePressed(const sf::Event::MouseButtonEvent &e);

		///
		///Metoda zwraca stan logiki gry
		///
		const std::wstring& GetState();

		///
		///Metoda ustawia stan logiki gry
		///
		///@param &state - sta³a referencja na obiekt klasy std::wstring
		///
		void SetState(const std::wstring& state);

		///
		///Metoda uruchamia now¹ rozgrywkê
		///
		///@param &start_file - sta³a referncja na obiekt klasy std::wstring
		///
		void StartNewGame(const std::wstring& start_file = L"new-game");
		
		///
		///Metoda restaruje rozgrywkê
		///
		void CheckRestart();
		
		///
		///Metoda powrotu do g³ównego menu ustawieñ gry
		///
		void ExitToMainMenu();
		
		///
		///Metoda czyœci stan rozgrywki
		///
		void Clear();

		///
		///Metoda zapisuje stan gry
		///
		///@param name - sta³a referencja na obiekt klasy std::string
		///
		void SaveGame(const std::string &name);

		///
		///Metoda odczytuje stan zapisanej gry
		///
		///@param name - sta³a referencja na obiekt klasy std::string
		///
		void LoadGame(const std::string& name);

		///
		///Metoda aktualizuje wszystkie obiekty dziedzicz¹ce po CPhysical
		///
		///@param secondsPassed - up³ywaj¹cy czas gry
		///
		void UpdatePhysicals(float secondsPassed);

	private:
		
		std::wstring m_state;				//stan logiki gry
	};
}//namespace logic
#endif//_H_LOGIC_JACK
