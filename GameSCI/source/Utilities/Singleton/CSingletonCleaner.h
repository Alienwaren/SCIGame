/*
 _______________________________________________
| CSingletonCleaner.h - class definition.       |
| SCI - July 2012.                              |
|_______________________________________________|

*/

#ifndef H_SINGLETON_CLEANER_SCI
#define H_SINGLETON_CLEANER_SCI

#include <assert.h>
#include <vector>
#include <cstdio>

#include "ICleanupable.h"

///
///Klasa reprezentuje kontener na wska�niki obiekt�w klas pochodnych interfejsu ICleanupable(Singletony)
///Jej zadaniem jest usuwanie Singleton�w
///
class CSingletonCleaner
{
public:

	///
	///Konstruktor domy�lny
	///
	CSingletonCleaner();

	///
	///Destruktor wirtualny
	///
    virtual ~CSingletonCleaner();

	///
	///Metoda rejestruje obiekty dziedzicz�ce po klasie ICleanupable (Singletony)
	///
	///@param *p_cleanupable - wska�nik na obiekty klas pochodnych interfejsu CCleanupable
	///
    void Register(ICleanupable *p_cleanupable);

	///
	///Metoda statyczna zwracaj�ca referencj� do tego obiektu
	///
	static CSingletonCleaner& GetSingleton();

private:

    std::vector<ICleanupable *>	m_cleanupables;	//kontener na wska�niki obiekt�w klas pochodnych interfejsu ICleanupable(Singletony)
    static CSingletonCleaner*	s_instance;		//wska�nik na statyczn� (jedyn�) instancj� tego obiektu - na ten obiekt

};

#endif//H_SINGLETON_CLEANER_SCI