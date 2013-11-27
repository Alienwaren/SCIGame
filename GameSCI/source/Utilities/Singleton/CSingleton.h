/*
 ___________________________________________
| CSingleton.h - template class definition. |
| SCI - July 2012.                          |
|___________________________________________|

*/

#ifndef H_SINGLETONE_SCI
#define H_SINGLETONE_SCI

#include <assert.h>
#include "CSingletonCleaner.h"

///
///Szablon reprezentuje wzorzec Singleton
///
template <typename T> class CSingleton : public ICleanupable
{

protected:
    
    ///
	///Konstruktor chroniony
	///
    CSingleton()
    {
		assert(!m_singleton);
		m_singleton = static_cast<T*>(this);
		CSingletonCleaner::GetSingleton().Register(this);
    }

    ///
	///Destruktor chroniony
	///
	virtual ~CSingleton()
	{
		assert(m_singleton);
		m_singleton = 0;
	}
	
	static T* m_singleton;	//statyczna sk�adowa - wska�nik na instancj� obiektu

public:

	///
	///Wirtualna metoda czyszcz�ca singleton - implementacja w klasach pochodnych
	///
	virtual void Cleanup() {};

    ///
	///Metoda statyczna zwracaj�ca dereferencj� wska�nika obiektu
	///
	static T& GetSingleton()
	{
		if (m_singleton == 0)
			new T();
		return (*m_singleton);
	}
    
	///
	///Metoda statyczna zwracaj�ca wska�nik obiektu
	///
	static T* GetSingletonPtr()
	{
		return m_singleton;
	}
};

template <typename T> T* CSingleton<T>::m_singleton = 0;

#endif//H_SINGLETONE_SCI
