/*
 _____________________________________
| CAnimSet.h - definicja klasy.       |
| SCI - March 2012.                   |
|_____________________________________|

*/

#ifndef H_ANIM_SET_SCI
#define H_ANIM_SET_SCI

#include <vector>
#include "EAnimHandler.h"
#include "../../XML/CXml.h"

using namespace animation;
using namespace xml;

namespace rendering
{
	namespace animation
	{
		///
		///Forward declaration
		///
		class CAnimation;

		///
		///Forward declaration
		///
		class CNameAnimPairTranslator;

		///
		///Klasa reprezentuje zestaw animacji obiektu
		///
		class CAnimSet
		{

		public:
	    
			///
			///Konstruktor domyœlny
			///
			CAnimSet();

			///
			///Destruktor
			///
			~CAnimSet();

			///
			///Metoda zwraca nazwê zestawu animacji
			///
			const std::string GetAnimSetName() const;

			///
			///Metoda ustawia nazwê zestawu animacji
			///
			///@param &animset_name - sta³a referencja na std::string
			///
			void SetAnimSetName(const std::string &animset_name);

			///
			///Metoda parsuje uchwyt animacji na podstawie nazwy lub int
			///
			///@param &handle_input - nazwa - referencja na obiekt klasy std::string
			///
			static int ParseAnimHandle(std::string &handle_input);

			///
			///Metoda ustawia animacjê
			///
			///@param anim_handle - uchwyt animacji
			///
			///@param *p_anim - wskaŸnik na animacjê
			///
			void SetAnimation(int anim_handle, CAnimation *p_anim);

			///
			///Metoda ustawia animacjê
			///
			///@param anim_handle - uchwyt animacji
			///
			///@param &anim_name - nazwa animacji referencja na obiekt std::string
			///
			void SetAnimation(int anim_handle, std::string &anim_name);
	    
			///
			///Metoda zwraca nazwê animacji na podstawie uchwytu
			///
			///@param anim_handle - uchwyt animacji
			///
			std::string *GetAnimName(int anim_handle);

			///
			///Metoda zwraca wskaŸnik na animacjê na podstawie parametru - uchwytu
			///
			///@param anim_handle - uchwyt animacji
			///
			CAnimation *GetAnim(int anim_handle);
	    
			//metody pomocnicze
			
			//body animations
			inline CAnimation *GetDefaultAnimBody		()	{ return GetAnim(anim_handle_body_Default);			}
			inline CAnimation *GetMoveAnimBody			()	{ return GetAnim(anim_handle_body_Move);			}
			inline CAnimation *GetDeathAnimBody			()	{ return GetAnim(anim_handle_body_Death);			}
			//head animations
			inline CAnimation *GetDefaultAnimHead		()	{ return GetAnim(anim_handle_head_Default);			}
			inline CAnimation *GetShotAnimHead			()	{ return GetAnim(anim_handle_head_Shot);			}
			inline CAnimation *GetAmmoLoadingAnimHead	()	{ return GetAnim(anim_handle_head_Ammo_Loading);	}
			inline CAnimation *GetDeathAnimHead			()	{ return GetAnim(anim_handle_head_Death);			}

			///
			///Metoda sprawdza nazwy animacji i wstawia animacje do zestawu animacji
			///
			///@param &xml - referencja na obiekt klasy CXml
			///
			///@param *root - wskaŸnik na wêze³ dokumentu xml
			///
			void Parse(CXml &xml, rapidxml::xml_node<> *root = 0);

			///
			///Metoda zwraca sta³a referencjê na wektor przechowuj¹cy zestawy animacji
			///
			inline const std::vector<CNameAnimPairTranslator> &GetAnims() const { return m_anims; }

		private:

			std::string								m_animset_name;			//nazwa zestawu
			static int								m_anim_handle_number;	//uchwyt animacji
			static std::string						m_anim_handle_names[];	//tablica stringów przechowuj¹ca nazwy animacji
			std::vector<CNameAnimPairTranslator>	m_anims;				//kontener przechowuj¹cy animacje
		};

	}//namespace animation
}//namespace rendering
#endif//H_ANIM_SET_SCI
