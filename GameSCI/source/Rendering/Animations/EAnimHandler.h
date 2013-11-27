/*
 ______________________________________________________
| EAnimHandler.h - wyliczenie typ�w zestaw�w animacji. |
| SCI - March 2012.                                    |
|______________________________________________________|

*/

#ifndef H_E_ANIM_HANDLER_SCI
#define H_E_ANIM_HANDLER_SCI

namespace animation
{
	///
	///Wyliczenie uchwyt�w animacji
	///
	enum EAnimHandler
	{
		//body animations handlers
		anim_handle_body_Default		= 0,
		anim_handle_body_Move			= 1,
		anim_handle_body_Death			= 2,
		//head animations handlers
		anim_handle_head_Default		= 3,
		anim_handle_head_Shot			= 4,
		anim_handle_head_Ammo_Loading	= 5,
		anim_handle_head_Death			= 6,
	};
}//namespace animation
#endif //H_E_ANIM_HANDLER_SCI
