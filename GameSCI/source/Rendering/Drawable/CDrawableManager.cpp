/*
 _____________________________________________
| CDrawableManager.cpp - class implementation |
| SCI - August 2012.                          |
|_____________________________________________|

*/

#include "CDrawableManager.h"
#include "IDrawable.h"
#include "../Displayable/CDisplayable.h"
#include "../../Game/CGame.h"

template<> CDrawableManager* CSingleton<CDrawableManager>::m_singleton = 0;

using namespace game;

namespace rendering
{
	namespace drawable
	{
		//Konstruktor domyœlny
		CDrawableManager::CDrawableManager()
		{
			fprintf(stderr,"CDrawableManager::CDrawableManager()\n");
			m_layers.resize(Z_MAX + 1);
			gGame.AddFrameListener(this);
		}

		//Destruktor
		CDrawableManager::~CDrawableManager()
		{
			fprintf(stderr,"CDrawableManager::~CDrawbleManager()\n");
		    
			for (DrawableLists::iterator it1 = m_layers.begin(); it1 != m_layers.end(); it1++)
			{
				DrawableList& list = (*it1);
				for (DrawableList::iterator it2 = list.begin(); it2 != list.end(); it2++)
				{
					delete ( *it2 );
				}
				(*it1).clear();
			}
			m_layers.clear();
		}

		//Metoda tworzy obiekt klasy CDisplayable i zwraca wskaŸnik na ten obiekt
		CDisplayable* CDrawableManager::CreateDisplayable(int z_index)
		{
			if (!IsCorrectZIndex(z_index)) return NULL;

			CDisplayable* displayable = new CDisplayable();
			RegisterDrawable(displayable, z_index);

			return displayable;
		}

		//Metoda rejestruje obiekt
		void CDrawableManager::RegisterDrawable(IDrawable* drawable, int z_index)
		{
			if (!IsCorrectZIndex(z_index)) return;
			if (drawable == NULL) return;

			if (drawable->m_layer_index >= 0)
				UnregisterDrawable(drawable);
			m_layers[z_index].push_back(drawable);
			drawable->m_layer_index = z_index;
			drawable->m_layer_vector_index = (int)(m_layers[z_index].size()-1);
		}

		//Metoda wyrejstrowuje obiekt - bez usuwania
		void CDrawableManager::UnregisterDrawable(IDrawable *drawable)
		{
			if ((drawable == NULL) || (drawable->m_layer_index < 0) || (drawable->m_layer_vector_index < 0))
				return;
			int zi = drawable->m_layer_index, vi = drawable->m_layer_vector_index;
			m_layers[zi][vi] = m_layers[zi][m_layers[zi].size()-1];
			m_layers[zi][vi]->m_layer_vector_index = vi;
			m_layers[zi].pop_back();
			drawable->m_layer_index = -1;
			drawable->m_layer_vector_index = -1;
		}

		//Metoda usuwa obiekt z kontenera
		void CDrawableManager::DestroyDrawable(IDrawable* drawable)
		{
			if (drawable != NULL)
			{
				UnregisterDrawable(drawable);
				delete drawable;
			}
			else
				fprintf(stderr, "warning: CDrawableManager::DestroyDrawable: tried to destroy null drawable\n");
		}

		//Metoda renderuj¹ca obiekt klasy CDisplayable
		void CDrawableManager::DrawFrame(sf::RenderWindow* render)
		{
			if (render == NULL)
				render = gGame.GetRenderWindow();

			for (DrawableLists::reverse_iterator it1 = m_layers.rbegin(); it1 != m_layers.rend(); it1++ )
			{
				const DrawableList& list = (*it1);
				for (DrawableList::const_iterator it2 = list.begin() ; it2 != list.end() ; it2++)
				{
					IDrawable* drawable = (*it2);
					if (drawable->GetVisible())
						drawable->Draw(render);
				} 
			}
		}

		//Funkcja pomocnicza - sprawdza, czy indeks warstwy jest poprawny
		bool IsCorrectZIndex(int z_index)
		{
			if (z_index > Z_MAX)
			{
				fprintf(stderr, "warning, z_index > Z_MAX; returning null\n");
				return false;
			}
			if (z_index < 0)
			{
				fprintf(stderr, "warning, z_index > Z_MAX; returning null\n");
				return false;
			}
			return true;
		}
	}//namespace drawable
}//namespace rendering
