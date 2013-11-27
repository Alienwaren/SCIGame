/*
 ______________________________________________
| CAnimationManager.cpp - implementacja klasy. |
| SCI - March 2012.                            |
|______________________________________________|

*/

#include "CAnimationManager.h"
#include "CAnimationState.h"
#include "CAnimation.h"
#include "../../Game/CGame.h"
#include "../../XML/CXml.h"

using namespace rendering::animation;
using namespace game;

template<> CAnimationManager* CSingleton<CAnimationManager>::m_singleton = 0;

namespace rendering
{
	namespace animation
	{
		//Konstruktor domyœlny
		CAnimationManager::CAnimationManager()
		{
			fprintf(stderr, "CAnimationManager::CAnimationsManager()\n");
			gGame.AddFrameListener(this);

			//£adowanie pliku xml - wszystkie animacje
			LoadAnimations("data/xml_data/animations/all_animations.xml", "root");
			fprintf(stderr, "CAnimationManager::CAnimationsManager() all animations loaded...\n");
		}

		//Destruktor
		CAnimationManager::~CAnimationManager()
		{
			for (AnimationStatesSet::iterator it = m_animation_states.begin(); it != m_animation_states.end(); it++)
			{
				delete (*it);
			}
			m_animation_states.clear();

			for (AnimationsMap::iterator it = m_animations.begin(); it != m_animations.end(); it++)
			{
				delete (it->second);
			}
			m_animations.clear();
		}

		//Wirtualna metoda aktualizuj¹ca logikê obiektów - implementacja
		void CAnimationManager::FrameStarted(float secondsPassed)
		{
			for (AnimationStatesSet::iterator it = m_animation_states.begin(); it != m_animation_states.end(); it++)
			{
				CAnimationState* state = (*it);
				if (!state->GetPaused())
					state->AddTime(secondsPassed);
			}
		}

		//Metoda zwraca animacjê z kontenera na podstawie nazwy
		CAnimation* CAnimationManager::GetAnimation(const std::string& animation_name)
		{
			CAnimation* animationPtr = NULL;
			if (m_animations.find(animation_name) != m_animations.end())
				animationPtr = m_animations[animation_name];

			if (animationPtr == NULL)
			{
				if (animation_name != "")
					fprintf(stderr, "warning: CAnimationManager::CreateAnimationState - unable to find `%s' animation in m_animations map\n", animation_name.c_str());
				return NULL;
			}
			return animationPtr;
		}

		//Metoda tworzy funkcjonalny obiekt animowany
		CAnimationState* CAnimationManager::CreateAnimationState(const std::string& animation_name)
		{
			CAnimation* animationPtr = GetAnimation(animation_name);
			return CreateAnimationState(animationPtr);
		}

		//Metoda tworzy funkcjonalny obiekt animowany
		CAnimationState* CAnimationManager::CreateAnimationState(CAnimation *p_animation)
		{
			if (p_animation == NULL)
				return NULL;
			CAnimationState* p_animation_state = new CAnimationState(p_animation);
			m_animation_states.insert(p_animation_state);
			return p_animation_state;
		}

		//Metoda usuwa funkcjonalny obiekt animowany
		void CAnimationManager::DestroyAnimationState(CAnimationState* p_animation_state)
		{
			if (!p_animation_state)
			{
				fprintf(stderr, "warning: CAnimationManager::DestroyAnimationState - p_animation_state was NULL\n");
				return;
			}

			if (m_animation_states.find(p_animation_state) != m_animation_states.end())
			{
				m_animation_states.erase(m_animation_states.find(p_animation_state));
				delete p_animation_state;
				return;
			}
			else
			{
				fprintf(stderr, "error: CAnimationManager::DestroyAnimationState - p_animation_state was not found in set\n");
				return;
			}
		}

		//metoda ³aduje dane z pliku xml
		void CAnimationManager::LoadAnimations(const std::string &file_name, const std::string &node_name)
		{
			//zmienne pomocnicze, poza pêtl¹, aby nie obci¹¿aæ stosu
			std::string		m_animation_name = "";
			float			m_frame_time = 0.0f;
			float			m_total_frame_time = 0.0f;
			std::string		m_texture_name = "";
			sf::IntRect		rectangle = sf::IntRect(0,0,0,0);

			CXml xml(file_name, node_name);
			
			for(xml_node<> *node = xml.GetChild(xml.GetRootNode(),"animation_name"); node; node = xml.GetSibling(node,"animation_name"))
			{
				m_animation_name = xml.GetString(node, "name");	//odczutujê nazwê
				CAnimation* animation = new CAnimation();		//tworzê animacjê
				animation->SetAnimationName(m_animation_name);	//nadajê nazwê animacji
				m_total_frame_time = 0;							//resetujemy kumulacjê czasu trwania animacji

				for(xml_node<> *second_node = xml.GetChild(node,"animation_frame"); second_node; second_node = xml.GetSibling(second_node,"animation_frame"))
				{
					m_frame_time = xml.GetFloat(second_node,"frame_time");		//odczyt czasu ekspozycji klatki animacji
					m_texture_name = xml.GetString(second_node,"texture_name");	//odczyt nazwy tekstury, z której pobierany jest obraz klatki
					rectangle = sf::IntRect										//odczyt koordynatów poszczególnych klatek animacji
						(
							xml.GetInt(second_node,"rect_left"),
							xml.GetInt(second_node,"rect_top"),
							xml.GetInt(second_node,"rect_width"),
							xml.GetInt(second_node,"rect_height")
						);
					//kumulacja czasów ekspozycji poszczególnych klatek animacji
					//zatem, pobieraj¹c z wektora ostatni element kontenera
					//pobieramy tym samym ³¹czny czas trwania animacji
					//float CAnimation::TotalLength()
					m_total_frame_time += m_frame_time;
					m_animations[animation->GetAnimationName()] = animation;
					animation->m_frames.push_back(CTimedAnimationFrame(m_total_frame_time, CAnimationFrame(m_texture_name, rectangle)));
				}
			}
		}
	}//namespace animation
}//namespace rendering