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
		///Klasa bazowa reprezentuje publiczny inreface dla obieków renderowalnych
		///
		class IDrawable
		{

		public:
			
			///
			///Konstruktor domyœlny
			///
			IDrawable();

			///
			///Konstruktor kopiuj¹cy
			///
			///@param IDrawableCopy - obiekt klasy IDrawable
			///
			IDrawable(const IDrawable& IDrawableCopy);

			///
			///Wirtualny destruktor
			///
			virtual ~IDrawable();

			///
			///Metoda zwraca flagê, czy obiekt jest widoczny
			///
			const bool GetVisible() const;

			///
			///Metoda ustawia flagê, czy obiekt jest widoczny
			///
			///@param visible - flaga, czy obiekt ma byæ widoczny
			///
			const void SetVisible(bool visible);

			///
			///Metoda zwraca indeks warstwy, na której ma byæ renderowany obiekt
			///
			const int GetLayerIndex() const;

			///
			///Metoda ustawia indeks warstwy, na której ma byæ renderowany obiekt
			///
			///@param layer_index - indeks warstwy, na której ma byæ renderowany obiekt
			///
			const void SetLayerIndex(int layer_index);

			///
			///Witrualna abstrakcyjna metoda renderuj¹ca - interfejs
			///
			///@param *renderWindow - wskaŸnik na okno renderingu
			///
			virtual void Draw(sf::RenderWindow* renderWindow) = 0;

		private:

			///
			///Deklaracja przyjaŸni (klasa CDrawableManager jest przyjacielem tej klasy)
			///
			friend class CDrawableManager;

			bool	m_visible;				//flaga okreœlajaca, czy obiekt jest widoczny
			int		m_layer_index;			//indeks warstwy, na której ma byæ renderowany obiekt
			int		m_layer_vector_index;	//indeks w kontenerze, okreœlaj¹cy, czy obiekt znajduje siê na prawid³owej warstwie
		    
		};

	}//using  namespace drawable;
}//namespace rendering
#endif //H_IDRAWABLE_SCI
