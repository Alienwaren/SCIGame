/*
 _____________________________________________________________
| ICleanupable.h - definicja klasy abstrakcyjnej - interface. |
| SCI - April 2012.                                           |
|_____________________________________________________________|

*/

#ifndef H_ICLEANUPABLE_SCI
#define H_ICLEANUPABLE_SCI

///
///Klasa abstrakcyjna reprezentuje interfejs zarz¹dzaj¹cy obiektami klas typu Singleton
///
class ICleanupable
{
	///
	///Friendship declaration
	///
	friend class CSingletonCleaner;

protected:

	///
	///Wirtualny interfejs
	///
	virtual void Cleanup() {};

	///
	///Destruktor Wirtualny
	///
	virtual ~ICleanupable(){};
};
#endif //H_ICLEANUPABLE_SCI