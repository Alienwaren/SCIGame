/*
 ____________________________________________
| CBulletTemplate.cpp - implementacja klasy. |
| SCI - November 2012.                       |
|____________________________________________|

*/

#include "CBulletTemplate.h"
#include "../XML/CXml.h"
#include "../Rendering/Displayable/CDisplayable.h"
#include "../Rendering/Animations/CAnimationManager.h"
#include "../Rendering/Animations/CAnimationState.h"
#include <iostream>

using namespace rapidxml;

namespace factory
{
	//Konstruktor
	CBulletTemplate::CBulletTemplate()
	{
	}

	//Destruktor
	CBulletTemplate::~CBulletTemplate()
	{
	}

	//Wirtualna metoda zwalniaj¹ca zasób
	void CBulletTemplate::Drop()
	{
		delete this;
	}

	//Metoda ³aduj¹ca dane
	bool CBulletTemplate::Load(const std::string &name)
	{
		CXml xml(name, "root");
		return Load(xml);
	}

	//Metoda ³aduj¹ca dane
	bool CBulletTemplate::Load(CXml &xml)
	{
		if (!CPhysicalTemplate::Load(xml)) return false;

		//sprawdzamy, czy xml zawiera informacjê, ¿e jest to bullet
		if (xml.GetString(xml.GetRootNode(), "type") != "bullet")
			return false;

		//plik xml pocisku przypomina plik physical'a
		//ewentualne ³adowanie danych generycznych pocisku...


		//if (xml_node<>*	node = xml.GetChild(xml.GetRootNode(), "zabawa z pociskiem..."))

		//mMinDamage = xml.GetFloat( "damage", "min" );
		//mMaxDamage = xml.GetFloat( "damage", "max" );

		//node = xml.GetChild(0, "anim");
		//if (node)
		  //  mAnimation = gAnimationManager.GetAnimation(xml.GetString(node,"name"));

		//for (node=xml.GetChild(0,"image"); node; node=xml.GetSibl(node,"image") )
		//	mImages.push_back( xml.GetString(node,"filename") );

		//for (node=xml.GetChild(0,"effect"); node; node=xml.GetSibl(node,"effect") )
		//	mEffects.push_back( xml.GetString(node,"name") );

		//for (node=xml.GetChild(0,"destroyEffect"); node; node=xml.GetSibl(node,"destroyEffect") )
		//	mDestroyEffects.push_back( xml.GetString(node,"name") );

		return true;
	}

	//Wirtualna metoda tworzenie obiektów pochodnych klasy CPhysical
	CBullet* CBulletTemplate::Create(std::wstring id)
	{
		CBullet* bullet = gPhysicalManager.CreateBullet();

		Fill(bullet);
		
		//gdyby by³y jakieœ pola do przekazania, nale¿y to uczyniæ...
		//ale w Fill(...)


		//this->Fill(

		//float random =	gRand.Rndf( 0.0f, 1.0f );
		//float scale =	Lerp( mMinScale,	mMaxScale,	random );
		//float radius =	Lerp( mMinRadius,	mMaxRadius,	random );

		//bullet->SetCategory(PHYSICAL_BULLET);
		//bullet->SetBoundingCircle(radius);// atrapa, coœ muszê mieæ.../
		//this->m_templ_circle_radius
		//m_templ_animation_name_body
		//this->m_templ_animation_name_body...

		//if ( mImages.size() > 0 ) 
		//{
		//	int imageNo = gRand.Rnd( 0, static_cast<unsigned>(mImages.size()) );
		//	bullet->SetImage( mImages[imageNo] );
		//} else {
		//	bullet->SetUseDisplayable(false);
		//}

		//if (mAnimation)
		//	bullet->SetAnimation(mAnimation);

		//if ( bullet->GetDisplayable() )
		//	bullet->GetDisplayable()->SetScale( scale, scale );

		/* TODO:
		*  przypisywanie efektów cz¹steczkowych do pocisku
		*  ( czekam na system cz¹steczek z predefiniowanymi efektami identyfikowanymi po nazwie - stringu )
		*/

		return bullet;
	}

	//implementacja metod  p r o t e c e t e d:

	//Wirtualna metoda wype³niaj¹ca danymi obiekt klasy CBullet
	void CBulletTemplate::Fill(CBullet *bullet)
	{
		bullet->SetTemplate(this);
		//to do...
	}


}//namespace factory