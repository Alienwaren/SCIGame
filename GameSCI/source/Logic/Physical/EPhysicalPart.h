/*
 ______________________________
| EPhysicalPart.h - wyliczenie |
| SCI - October 2012.          |
|______________________________|

 */

#ifndef H_PHYSICAL_PART_SCI
#define H_PHYSICAL_PART_SCI

namespace logic
{
	///
	///Wyliczenie reprezentuje elementy sk�adowe klasy CPhysical
	///
	enum EPhysicalPart
	{
		BODY,	//cz�� podstawa (np. w przypadku czo�gu - podwozie)
		HEAD	//cz�� dodatkowa (np. w przypadku czo�gu - wie�a)
	};
}
#endif //H_PHYSICAL_PART_SCI