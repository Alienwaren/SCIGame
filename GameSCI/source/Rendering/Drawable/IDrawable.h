/*
 ___________________________________________
| IDrawable.h - definicja interfejsu        |
| SCI - August 2012.                        |
|___________________________________________|

*/

#ifndef H_IDRAWABLE_SCI
#define H_IDRAWABLE_SCI

namespace sf
{
	///
	///Forward declaration
	///
    class RenderWindow;
}
namespace rendering
{
	namespace drawable
	{
		///
		///Klasa bazowa reprezentuje publiczny inreface dla obiek�w renderowalnych
		///
		class IDrawable
		{

		public:
			
			///
			///Konstruktor domy�lny
			///
			IDrawable();

			///
			///Konstruktor kopiuj�cy
			///
			///@param IDrawableCopy - obiekt klasy IDrawable
			///
			IDrawable(const IDrawable& IDrawableCopy);

			///
			///Wirtualny destruktor
			///
			virtual ~IDrawable();

			///
			///Metoda zwraca flag�, czy obiekt jest widoczny
			///
			const bool GetVisible() const;

			///
			///Metoda ustawia flag�, czy obiekt jest widoczny
			///
			///@param visible - flaga, czy obiekt ma by� widoczny
			///
			const void SetVisible(bool visible);

			///
			///Metoda zwraca indeks warstwy, na kt�rej ma by� renderowany obiekt
			///
			const int GetLayerIndex() const;

			///
			///Metoda ustawia indeks warstwy, na kt�rej ma by� renderowany obiekt
			///
			///@param layer_index - indeks warstwy, na kt�rej ma by� renderowany obiekt
			///
			const void SetLayerIndex(int layer_index);

			///
			///Witrualna abstrakcyjna metoda renderuj�ca - interfejs
			///
			///@param *renderWindow - wska�nik na okno renderingu
			///
			virtual void Draw(sf::RenderWindow* renderWindow) = 0;

		private:

			///
			///Deklaracja przyja�ni (klasa CDrawableManager jest przyjacielem tej klasy)
			///
			friend class CDrawableManager;

			bool	m_visible;				//flaga okre�lajaca, czy obiekt jest widoczny
			int		m_layer_index;			//indeks warstwy, na kt�rej ma by� renderowany obiekt
			int		m_layer_vector_index;	//indeks w kontenerze, okre�laj�cy, czy obiekt znajduje si� na prawid�owej warstwie
		    
		};

	}//using  namespace drawable;
}//namespace rendering
#endif //H_IDRAWABLE_SCI
