/*
 _______________________________________________
| CSingletonCleaner.cpp - class implementation. |
| SCI - July 2012.                              |
|_______________________________________________|

*/

#include "CSingletonCleaner.h"

//Konstruktor domy�lny
CSingletonCleaner::CSingletonCleaner()
{
	fprintf(stderr, "CSingletonCleaner::CSingletonCleaner()\n");
	s_instance = this;
}

//Destruktor wirtualny
CSingletonCleaner::~CSingletonCleaner()
{
	fprintf(stderr, "CSingletonCleaner::~CSingletonCleaner()\n");
	assert(s_instance);
	while (m_cleanupables.size() > 0)
	{
		m_cleanupables[m_cleanupables.size()-1]->Cleanup();
		m_cleanupables.pop_back();
		fprintf(stderr, "CSingletonCleaner - %d objects unregistered\n", m_cleanupables.size());
	}
	s_instance = NULL;
}

//Metoda rejestruje obiekty dziedzicz�ce po klasie ICleanupable (Singletony)
void CSingletonCleaner::Register(ICleanupable *p_cleanupable)
{
	m_cleanupables.push_back(p_cleanupable);
	fprintf(stderr, "CSingletonCleaner - %d objects registered\n", m_cleanupables.size());
}

//Metoda statyczna zwracaj�ca referencj� do tego obiektu
CSingletonCleaner& CSingletonCleaner::GetSingleton()
{
	assert(s_instance);
	return (*s_instance);
}

//Nadanie warto�ci pocz�tkowej sk�adowej statycznej
CSingletonCleaner *CSingletonCleaner::s_instance = NULL;
