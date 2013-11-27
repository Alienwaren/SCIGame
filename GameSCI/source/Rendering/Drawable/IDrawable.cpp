/*
 ___________________________________________
| IDrawable.cpp - implementacja interfejsu. |
| SCI - August 2012.                        |
|___________________________________________|

*/

#include "IDrawable.h"
#include "../Drawable/CDrawableManager.h"

namespace rendering
{
	namespace drawable
	{
		//Konstruktor domy�lny
		IDrawable::IDrawable()
		:
			m_visible				(true),
			m_layer_vector_index	(-1),	//na wszelki wypadek wstawiamy -1, aby warstwa nie by�a ustawiona
			m_layer_index			(-1)	//na wszelki wypadek wstawiamy -1, aby warstwa nie by�a ustawiona
		{
		}

		//Konstruktor kopiuj�cy
		IDrawable::IDrawable(const IDrawable& IDrawableCopy)
		:
			m_visible				(IDrawableCopy.m_visible),
			m_layer_vector_index	(IDrawableCopy.m_layer_vector_index),
			m_layer_index			(IDrawableCopy.m_layer_index)
		{
		}

		//Wirtualny destruktor
		IDrawable::~IDrawable()
		{
			if (m_layer_vector_index >= 0)					//je�li w kontenerze, n awarstwach s� jakie� obiekty
				gDrawableManager.UnregisterDrawable(this);	//wyrejestrowujemy je
		}

		//Metoda zwraca flag�, czy obiekt jest widoczny
		const bool IDrawable::GetVisible() const
		{
			return m_visible;
		}

		//Metoda ustawia flage, czy obiekt jest widoczny
		const void IDrawable::SetVisible(bool visible)
		{
			m_visible = visible;
		}

		//Metoda zwraca indeks warstwy, na kt�rej ma by� renderowany obiekt
		const int IDrawable::GetLayerIndex() const
		{
			return m_layer_index;
		}

		//Metoda ustawia indeks warstwy, na kt�rej ma by� renderowany obiekt
		const void IDrawable::SetLayerIndex(int layer_index)
		{
			m_layer_index = layer_index;
		}
	}//namespace drawable
}//namespace rendering
