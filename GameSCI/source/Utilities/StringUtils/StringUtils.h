/*
 ____________________________________________________________________
| StringUtils.h - modu³ zawierajacy funkcje operuj¹ce na ³añcuchach. |
| Jack Flower October 2011.                                          |
|____________________________________________________________________|

*/

#ifndef H_STRING_UTILS_SCI
#define H_STRING_UTILS_SCI

#include <sstream>
#include <string>

namespace stringutils
{

	#if !defined (get16bits)
	#define get16bits(d) ((((unsigned int)(((const unsigned char *)(d))[1])) << 8)+(unsigned int)(((const unsigned char *)(d))[0]))
	#endif

	//http://www.azillionmonkeys.com/qed/hash.html
	//Dla zaawansowanych - zainteresowaæ siê funkcjami tablicami/funkcjami haszuj¹cymi
	///
	///Funkcja hash - generuje unikalne wartoœci typu unsigned long long 
	///
	///param &str - sta³a referencja na obiekt std::string
	///
	unsigned long long GetStringHash( const std::string &str );

	///
	///Funkcja szablonowa sprawdzaj¹ca, czy mo¿na dokonaæ konwersji typu szablonowego
	///
	template< class T>
	inline bool FromString(const std::string& str, T& value)
	{
		std::istringstream streamIn(str);
		return !(streamIn >> value).fail();
	}

	///
	///Funkcja szablonowa konwertuj¹ca typ szablonowy na std::wstring
	///
	template< class type>
	inline std::wstring ToWString(const type & value)
	{
		std::wostringstream streamOut;
		streamOut << value;
		return streamOut.str();
	}

	///
	///Funkcja konwertuje std::string na std::wstring
	///
	inline std::wstring ConvertToWString(std::string string_param)
	{
		return std::wstring( string_param.begin(), string_param.end() );
	}

	///
	///Funkcja szablonowa konwertuj¹ca typ szablonowy na std::string
	///
	template <class T>
	inline std::string ToString(const T i)
	{
		std::stringstream ss;
		std::string temp;
		ss << i;
		ss >> temp;
		return temp;
	}

}//namespace stringutils
#endif //H_STRING_UTILS_SCI
