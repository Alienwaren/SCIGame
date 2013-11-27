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
///Klasa reprezentuje kontener na wskaŸniki obiektów klas pochodnych interfejsu ICleanupable(Singletony)
///Jej zadaniem jest usuwanie Singletonów
///
class CSingletonCleaner
{
public:

	///
	///Konstruktor domyœlny
	///
	CSingletonCleaner();

	///
	///Destruktor wirtualny
	///
    virtual ~CSingletonCleaner();

	///
	///Metoda rejestruje obiekty dziedzicz¹ce po klasie ICleanupable (Singletony)
	///
	///@param *p_cleanupable - wskaŸnik na obiekty klas pochodnych interfejsu CCleanupable
	///
    void Register(ICleanupable *p_cleanupable);

	///
	///Metoda statyczna zwracaj¹ca referencjê do tego obiektu
	///
	static CSingletonCleaner& GetSingleton();

private:

    std::vector<ICleanupable *>	m_cleanupables;	//kontener na wskaŸniki obiektów klas pochodnych interfejsu ICleanupable(Singletony)
    static CSingletonCleaner*	s_instance;		//wskaŸnik na statyczn¹ (jedyn¹) instancjê tego obiektu - na ten obiekt

};

#endif//H_SINGLETON_CLEANER_SCI