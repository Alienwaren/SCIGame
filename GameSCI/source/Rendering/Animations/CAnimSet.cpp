/*
 _____________________________________
| CAnimSet.cpp - implementacja klasy. |
| SCI - March 2012.                   |
|_____________________________________|

*/

#include "CAnimSet.h"
#include "CAnimationManager.h"
#include "CAnimation.h"
#include "CNameAnimPairTranslator.h"

namespace rendering
{
	namespace animation
	{
		//Rejestracja wpis�w tablicy s�ownika parsuj�cego std::string na uchwyt (enum - wyliczenie)
		std::string CAnimSet::m_anim_handle_names[] = 
		{
			//body animations names
			"default_body",
			"move_body",
			"death_body",
			//head animations names
			"default_head",
			"shot_head",
			"ammo_loading_head",
			"death_head",
		};

		//Nadanie warto�ci sta�ej sk�adowej statycznej - obliczenie ile wpis�w ma tablica m_anim_handle_names[]
		int CAnimSet::m_anim_handle_number = sizeof(CAnimSet::m_anim_handle_names) / sizeof(std::string);

		//Konstruktor domy�lny
		CAnimSet::CAnimSet()
		:
			m_animset_name			("")
		{
			m_anims.resize(m_anim_handle_number);
		}

		//Destruktor
		CAnimSet::~CAnimSet()
		{
			m_animset_name			= "";
			m_anim_handle_number	= 0;
			m_anims.clear();
		}

		//Metoda zwraca nazw� zestawu animacji
		const std::string CAnimSet::GetAnimSetName() const
		{
			return m_animset_name;
		}

		//Metoda ustawia nazw� zestawu animacji
		void CAnimSet::SetAnimSetName(const std::string &animset_name)
		{
			m_animset_name = animset_name;
		}

		//Metoda parsuje uchwyt animacji na podstawie nazwy lub int
		int CAnimSet::ParseAnimHandle(std::string &handle_input)
		{
			//sprawdzam, czy w tablicy znajduje si� podany parametr (uchwyt)
			for (int i = 0; i < m_anim_handle_number; i++)
				if (m_anim_handle_names[i] == handle_input)
				return i;
			
			//sprawdzamy, czy parametr jest liczb�
			int tmp;
			//sprawdzam, czy w tablicy znajduje si� podany parametr (jako liczba) (uchwyt)
			if (sscanf(handle_input.c_str(),"%d", &tmp) == 1)
				return m_anim_handle_number + tmp;
			//w przypadku, gdy w tablicy nie znaleziono podanego parametru (uchwytu) zwracamy kod b��du
			return -1;
		}

		//Metoda ustawia animacj�
		void CAnimSet::SetAnimation(int anim_handle, CAnimation *p_anim)
		{
			if ((anim_handle < 0) || (p_anim == NULL)) return;
			if ((unsigned int)anim_handle >= m_anims.size()) m_anims.resize(anim_handle + 1);
			m_anims[anim_handle] = CNameAnimPairTranslator(p_anim->GetAnimationName());
			m_anims[anim_handle].SetAnim(p_anim);
		}

		//Metoda ustawia animacj�
		void CAnimSet::SetAnimation(int anim_handle, std::string &anim_name)
		{
			if (anim_handle < 0) return;
			if ((unsigned int) anim_handle >= m_anims.size()) m_anims.resize(anim_handle + 1);
			m_anims[anim_handle] = CNameAnimPairTranslator(anim_name);
		}

		//Metoda zwraca nazw� animacji na podstawie uchwytu
		std::string *CAnimSet::GetAnimName(int anim_handle)
		{
			if ((anim_handle < 0) || ((unsigned int) anim_handle >= m_anims.size()))
				return NULL;
			return &m_anims[anim_handle].GetAnimationName();
		}

		//Metoda zwraca wska�nik na animacj� na podstawie parametru - uchwytu
		CAnimation *CAnimSet::GetAnim(int anim_handle)
		{
			//nieprawid�owy uchwyt zwraca NULL
			if ((anim_handle < 0) || ((unsigned int) anim_handle >= m_anims.size()))
				return NULL;
			//je�li animacja pod indeksem (uchwyt-parametr) nie jest gotowa (wgrana)
			if (!m_anims[anim_handle].GetReady())
			{
				//ustawiamy animacj� na pobran� w menad�era animacji
				m_anims[anim_handle].SetAnim(gAnimationManager.GetAnimation(m_anims[anim_handle].GetAnimationName()));
			}
			return m_anims[anim_handle].GetAnimation();//zwracamy z wzrorca ju� gotow� animacj� (wska�nik)
		}

		//Metoda sprawdza nazwy animacji i wstawia animacje do zestawu animacji
		void CAnimSet::Parse(CXml &xml, rapidxml::xml_node<> *root)
		{
			std::string tmp;//zmienna na odczytan� nazw� animacji i odczytany typ animacji z zestawu
			for (xml_node<> *node = xml.GetChild(root, "anim"); node; node=xml.GetSibling(node, "anim") )
			{
				tmp = xml.GetString(node, "type");	//odczytuj� typ animacji z zestawu
				int a_handle = ParseAnimHandle(tmp);//sprawdzam, czy odczytany typ animacji istnieje (zamiana na uchwyt)
				if (a_handle < 0) continue;			//kontynuacja, gdy nie ma typu (zostanie to i tak zapisane pod takim kluczem)
				tmp = xml.GetString(node, "name");	//odczyt nazwy animacji z zestawu
				SetAnimation(a_handle, tmp);		//ustawienie animacji (uchwyt, nazwa animacji)
													//i zapis do wektora
			}
		}
	}//namespace animation
}//namespace rendering
