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
	///Wyliczenie typów kolizji
	///
	enum ECollisionShape
	{
		SHAPE_CIRCLE,	//kolizja okr¹g - okr¹g
		SHAPE_RECT		//kolizja prostok¹t - prostok¹t
	};
}
#endif //H_ECOLLISION_SHAPE_SCI