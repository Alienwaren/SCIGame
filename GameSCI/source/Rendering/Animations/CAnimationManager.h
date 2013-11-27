/*
 ______________________________________________
| CAnimationManager.h - definicja klasy.       |
| SCI - March 2012.                            |
|______________________________________________|

*/

#ifndef H_ANIMATION_MANAGER_SCI
#define H_ANIMATION_MANAGER_SCI

#include "../../Game/Listener/IFrameListener.h"
#include "../../Utilities/Singleton/CSingleton.h"

#include <string>
#include <vector>
#include <map>
#include <set>


///
///Forward declaration
///
namespace rendering
{
	namespace animation
	{
		///
		///Forward declaration
		///
		class CAnimation;
		class CAnimationState;
	}
}

using namespace listener;

#define gAnimationManager CAnimationManager::GetSingleton()

namespace rendering
{
	namespace animation
	{
		///
		///Klasa reprezentuje menad�era animacji - Singleton
		///
		class CAnimationManager: public CSingleton<CAnimationManager> , IFrameListener
		{
		public:

			///
			///Konstruktor domy�lny
			///
			CAnimationManager();
			
			///
			///Destruktor
			///
			~CAnimationManager();

			///
			///Wirtualna metoda aktualizuj�ca logik� obiekt�w - implementacja
			///
			virtual void FrameStarted(float secondsPassed);

			///
			///Metoda zwraca animacj� z kontenera na podstawie nazwy
			///
			///@param &animation_name - nazwa animacji
			///
			CAnimation* GetAnimation(const std::string& animation_name);

			///
			///Metoda tworzy funkcjonalny obiekt animowany
			///
			///@param &animation_name - nazwa animacji
			///
			CAnimationState* CreateAnimationState(const std::string& animation_name);

			///
			///Metoda tworzy funkcjonalny obiekt animowany
			///
			///@param *p_animation - wska�nik na animacj�
			///
			CAnimationState* CreateAnimationState(CAnimation *p_animation);

			///
			///Metoda usuwa funkcjonalny obiekt animowany
			///
			///@param *p_animation_state - wska�nik na funkcjonalny obiekt animowany
			///
			void DestroyAnimationState(CAnimationState* p_animation_state);
		
		private:

			//metoda �aduje dane (wszystkie animacje) z pliku xml (wywo�ywana w konstruktorze)
			//
			//@param &file_name - nazwa pliku - sta�a referencja na obiekt klasy std::string
			//
			//@param &node_name - nazwa w�z�a xml - sta�a referencja na obiekt klasy std::string
			//
			void LoadAnimations(const std::string &file_name, const std::string &node_name);

		private:

			typedef std::map<std::string, CAnimation*>	AnimationsMap;		//definicja typu - kontener (mapa) na animacje
			typedef std::set<CAnimationState*>			AnimationStatesSet;	//definicja typu - kontener (set) na funkcjonalne obiekty animowane
			AnimationsMap								m_animations;		//kontener (mapa) na animacje
			AnimationStatesSet							m_animation_states;	//kontener (set) na funkcjonalne obiekty animowane
		};
	}//namespace animation
}//namespace rendering
#endif //H_ANIMATION_MANAGER_SCI
