/*
 ____________________________________
| CLogic.cpp - implementacja klasy.  |
| SCI - January 2013.                |
|____________________________________|

*/


#include "CLogic.h"
#include "../Game/CGame.h"
#include "../Logic/CPhysicalManager.h"
#include "../Logic/Physical/CPhysical.h"

//mo¿e siê przyda, gdy jakiœ uczeñ napisze implementacjê...
#include <cstdio>
#include <fstream>
#include <sstream>

template<> logic::CLogic* CSingleton<logic::CLogic>::m_singleton = 0;

using namespace game;

namespace logic
{
	//Konstruktor
	CLogic::CLogic()
	:
		m_state				(L"main-menu")//potrzebna bêdzia jakaœ tablica stanów logiki gry...
	{
		fprintf(stderr, "CLogic::CLogic()\n");
		gGame.AddFrameListener(this);
		gGame.AddKeyListener(this);
		gGame.AddMouseListener(this);
	}

	//Destruktor wirtualny
	CLogic::~CLogic()
	{
		fprintf(stderr, "CLogic::~CLogic()\n");
		delete CPhysicalManager::GetSingletonPtr();
	}

	//Wirtualna metoda aktualizuj¹ca logikê obiektów - implementacja
	void CLogic::FrameStarted(float secondsPassed)
	{
		UpdatePhysicals(secondsPassed);
	}

	//Wirtualna metoda aktualizuj¹ca logikê gry - zdarzenia klawiatury
	void CLogic::KeyPressed(const sf::Event::KeyEvent &e)
	{
		//to do...
	}

	//Wirtualna metoda aktualizuj¹ca logikê gry - zdarzenia myszy
	void CLogic::MousePressed(const sf::Event::MouseButtonEvent &e)
	{
		CheckRestart();
		//to do...
	}

	//Metoda zwraca stan logiki gry
	const std::wstring& CLogic::GetState()
	{
		return m_state;
	}

	//Metoda ustaiwia stan logiki gry
	void CLogic::SetState( const std::wstring& state )
	{
		m_state = state;
	}

	//Metoda uruchamia now¹ rozgrywkê
	void CLogic::StartNewGame(const std::wstring& start_file)
	{
		//to do...
	}

	//Metoda restaruje rozgrywkê
	void CLogic::CheckRestart()
	{
		if (m_state == L"death-ready-to-restart")
		{
			ExitToMainMenu();
		}
	}

	//Metoda powrotu do g³ównego menu ustawieñ gry
	void CLogic::ExitToMainMenu()
	{
		//to do...
	}

	//Metoda czyœci stan rozgrywki
	void CLogic::Clear()
	{
		gPhysicalManager.Clear(true);
	}


	//Metoda zapisuje stan gry
	void CLogic::SaveGame(const std::string& name)
	{
		//to do...
	}

	//Metoda odczytuje stan zapisanej gry
	void CLogic::LoadGame(const std::string & name)
	{
		//to do...
	}

	//Metoda aktualizuje wszystkie obiekty dziedzicz¹ce po CPhysical
	void CLogic::UpdatePhysicals(float secondsPassed)
	{
		const std::vector<logic::CPhysical*> &physicals = gPhysicalManager.GetPhysicals();

		for (unsigned int i = 0; i < physicals.size(); ++i)
		physicals[i]->Update( secondsPassed );
	}
}//namespace logic
