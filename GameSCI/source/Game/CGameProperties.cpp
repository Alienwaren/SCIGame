/*
 ______________________________________________
| CGameProperties.cpp - implementatacja klasy. |
| SCI -  July 2012.                            |
|______________________________________________|

*/

#include "CGameProperties.h"
#include "CGame.h"

using namespace game;

template<> CGameProperties* CSingleton<CGameProperties>::m_singleton = 0;

namespace game
{
	//Konstruktor
	CGameProperties::CGameProperties(void)
	:
		m_width					(0),
		m_height				(0),
		m_bits_per_pixel_depth	(0),
		m_fullscreen			(false),
		m_vsync					(false),
		m_sound_volume			(0.0f),
		m_music_volume			(0.0f),
		m_windows_name			()
	{
		fprintf(stderr, "CGameProperties::CGameProperties()\n");
	}

	//Konstruktor kopiuj�cy
	CGameProperties::CGameProperties(const CGameProperties& CGamePropertiesCopy)
	:
		m_width					(CGamePropertiesCopy.m_width),
		m_height				(CGamePropertiesCopy.m_height),
		m_bits_per_pixel_depth	(CGamePropertiesCopy.m_bits_per_pixel_depth),
		m_fullscreen			(CGamePropertiesCopy.m_fullscreen),
		m_vsync					(CGamePropertiesCopy.m_vsync),
		m_sound_volume			(CGamePropertiesCopy.m_sound_volume),
		m_music_volume			(CGamePropertiesCopy.m_music_volume),
		m_windows_name			(CGamePropertiesCopy.m_windows_name)
	{
	}

	//Destruktor
	CGameProperties::~CGameProperties(void)
	{
		m_width					= 0;
		m_height				= 0;
		m_bits_per_pixel_depth	= 0;
		m_fullscreen			= false;
		m_vsync					= false;
		m_sound_volume			= 0;
		m_music_volume			= 0;
		m_windows_name			= "";
	}

	//Metoda zwraca szeroko�� okna
	unsigned int CGameProperties::GetWidth()
	{
		return m_width;
	}

	//Metoda ustawia szeroko�� okna
	void CGameProperties::SetWidth(unsigned int width)
	{
		m_width = width;
	}

	//Metoda zwraca wysoko�� okna
	unsigned int CGameProperties::GetHeight()
	{
		return m_height;
	}

	//Metoda ustawia wysoko�� okna
	void CGameProperties::SetHeight(unsigned int height)
	{
		m_height = height;
	}

	//Metoda zwraca g�ebi� kolor�w
	unsigned int CGameProperties::GetBitsPerPixel()
	{
		return m_bits_per_pixel_depth;
	}

	//Metoda ustawia g��bi� kolor�w
	void CGameProperties::SetBitsPerPixel(unsigned int bits_per_pixel_depth)
	{
		m_bits_per_pixel_depth = bits_per_pixel_depth;
	}

	//Metoda zwraca tryb pe�noekranowy
	bool CGameProperties::IsFullscreen()
	{
		return m_fullscreen;
	}

	//Metoda ustawia tryb pe�noekranowy
	void CGameProperties::SetFullscreen(bool fullscreen)
	{
		m_fullscreen = fullscreen;
	}

	//Metora zwraca tryb synchronizacji pionowej
	bool CGameProperties::IsVSync()
	{
		return m_vsync;
	}

	//Metoda ustawia tryb synchronizacji pionowej
	void CGameProperties::SetVSync(bool vsync)
	{
		m_vsync = vsync;
	}

	//Metoda zwraca g�o�no�� d�wi�ku
	float CGameProperties::GetSoundVolume()
	{
		return m_sound_volume;
	}

	//Metoda ustawia g�o�no�� d�wi�ku
	void CGameProperties::SetSoundVolume(float sound_volume)
	{
		m_sound_volume = sound_volume;
	}

	//Metoda zwraca g�o�no�� muzyki
	float CGameProperties::GetMusicVolume()
	{
		return m_music_volume;
	}

	//Metoda ustawia g�o�no�� muzyki
	void CGameProperties::SetMusicVolume(float music_volume)
	{
		m_music_volume = music_volume;
	}

	//Metoda zwraca nazw� okna
	const std::string CGameProperties::GetWindowName() const
	{
		return m_windows_name;
	}

	//Metoda ustawia nazw� okna
	const void CGameProperties::SetWindowName(std::string &windows_name)
	{
		m_windows_name = windows_name;
	}

	//Metoda �aduj�ca dane
	bool CGameProperties::Load(const std::string &name)
	{
		printf("CGameProperties::Load ...game properties loading...\n");
		CXml xml(name, "root" );
		return Load(xml);
	}

	//Metoda �aduj�ca dane z xml
	bool CGameProperties::Load(CXml &xml)
	{
		if (xml_node<> *node = xml.GetChild(xml.GetRootNode(), "game_config"))
		{
			m_width = xml.GetInt(node, "width");
			m_height = xml.GetInt(node, "height");
			m_bits_per_pixel_depth = xml.GetInt(node, "bits_per_pixel_depth");
			m_fullscreen = xml.GetBool(node, "fullscreen");
			m_vsync	= xml.GetBool(node, "vsync");
			m_sound_volume = xml.GetFloat(node, "sound_volume");
			m_music_volume = xml.GetFloat(node, "music_volume");
			m_windows_name = xml.GetString(node, "windows_name");
		}
		printf("CGameProperties::Load ...game properties loaded...\n");
		return true;
	}

	//Metoda tworzy okno
	void CGameProperties::UpdateWindow()
	{
		fprintf(stderr, "UpdateWindow()\n");
		//Na wszelki wypadek usuwamy
		if(gGame.GetRenderWindow())
		{
			gGame.GetRenderWindow()->close();
			delete gGame.GetRenderWindow();
		}
		//Tworzymy okno
		fprintf(stderr ,"SetRenderWindow\n");
		gGame.SetRenderWindow(new sf::RenderWindow(sf::VideoMode(m_width, m_height, m_bits_per_pixel_depth), m_windows_name,sf::Style::Close)); 

		gGame.GetRenderWindow()->setKeyRepeatEnabled(false);//blokujemy powtarzalno�� generatora klawiatury
															//gdy mamy wci�ni�ty jaki� klawisz
															//(czyli przy wci�ni�tym klawiszu
															//co� si� "zrobi" jeden raz)
		fprintf(stderr, "gGame.GetRenderWindow()->setKeyRepeatEnabled(false)\n");
	}

	//Wirtualna metoda czyszcz�ca singleton
	void CGameProperties::Cleanup()
	{
		fprintf(stderr, "CGameProperties::Cleanup()\n");
		fprintf(stderr, "CGameProperties::Cleanup() done...\n");
	}
}//namespace game