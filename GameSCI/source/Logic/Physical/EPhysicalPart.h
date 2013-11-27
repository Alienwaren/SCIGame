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
	///Wyliczenie reprezentuje elementy sk³adowe klasy CPhysical
	///
	enum EPhysicalPart
	{
		BODY,	//czêœæ podstawa (np. w przypadku czo³gu - podwozie)
		HEAD	//czêœæ dodatkowa (np. w przypadku czo³gu - wie¿a)
	};
}
#endif //H_PHYSICAL_PART_SCI