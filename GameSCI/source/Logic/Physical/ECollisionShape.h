/*
 ________________________________
| ECollisionShape.h - wyliczenie |
| SCI - 2012.                    |
|________________________________|

 */

#ifndef H_ECOLLISION_SHAPE_SCI
#define H_ECOLLISION_SHAPE_SCI

namespace logic
{
	///
	///Wyliczenie typ�w kolizji
	///
	enum ECollisionShape
	{
		SHAPE_CIRCLE,	//kolizja okr�g - okr�g
		SHAPE_RECT		//kolizja prostok�t - prostok�t
	};
}
#endif //H_ECOLLISION_SHAPE_SCI