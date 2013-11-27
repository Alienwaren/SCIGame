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

//mo�e si� przyda, gdy jaki� ucze� napisze implementacj�...
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
		m_state				(L"main-menu")//potrzebna b�dzia jaka� tablica stan�w logiki gry...
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

	//Wirtualna metoda aktualizuj�ca logik� obiekt�w - implementacja
	void CLogic::FrameStarted(float secondsPassed)
	{
		UpdatePhysicals(secondsPassed);
	}

	//Wirtualna metoda aktualizuj�ca logik� gry - zdarzenia klawiatury
	void CLogic::KeyPressed(const sf::Event::KeyEvent &e)
	{
		//to do...
	}

	//Wirtualna metoda aktualizuj�ca logik� gry - zdarzenia myszy
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

	//Metoda uruchamia now� rozgrywk�
	void CLogic::StartNewGame(const std::wstring& start_file)
	{
		//to do...
	}

	//Metoda restaruje rozgrywk�
	void CLogic::CheckRestart()
	{
		if (m_state == L"death-ready-to-restart")
		{
			ExitToMainMenu();
		}
	}

	//Metoda powrotu do g��wnego menu ustawie� gry
	void CLogic::ExitToMainMenu()
	{
		//to do...
	}

	//Metoda czy�ci stan rozgrywki
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

	//Metoda aktualizuje wszystkie obiekty dziedzicz�ce po CPhysical
	void CLogic::UpdatePhysicals(float secondsPassed)
	{
		const std::vector<logic::CPhysical*> &physicals = gPhysicalManager.GetPhysicals();

		for (unsigned int i = 0; i < physicals.size(); ++i)
		physicals[i]->Update( secondsPassed );
	}
}//namespace logic
