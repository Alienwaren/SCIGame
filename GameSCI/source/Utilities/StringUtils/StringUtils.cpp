/*
 ______________________________________________________________________
| StringUtils.cpp - modu³ zawierajacy funkcje operuj¹ce na ³añcuchach. |
| Jack Flower October 2011.                                            |
|______________________________________________________________________|

*/

#include "StringUtils.h"

namespace stringutils
{
	//Funkcja hash - generuje unikalne wartoœci typu unsigned long long
	unsigned long long GetStringHash( const std::string & str )
	{
		const char * data = str.c_str();
		unsigned int len = (unsigned int)str.length();

		unsigned long long hash = len, tmp;
		int rem;

		if (len <= 0 || data == NULL) return 0;

		rem = len & 3;
		len >>= 2;

		for (;len > 0; len--)
		{
			hash  += get16bits (data);
			tmp    = (get16bits (data+2) << 11) ^ hash;
			hash   = (hash << 16) ^ tmp;
			data  += 2*sizeof (unsigned short);
			hash  += hash >> 11;
		}

		switch (rem) 
		{
		case 3: hash += get16bits (data);
			hash ^= hash << 16;
			hash ^= data[sizeof (unsigned short)] << 18;
			hash += hash >> 11;
			break;
		case 2: hash += get16bits (data);
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1: hash += *data;
			hash ^= hash << 10;
			hash += hash >> 1;
		}

		//mieszanie poprzez przesuwanie bitowe (prawdopodobnie daje unikalnoœæ)
		hash ^= hash << 3;
		hash += hash >> 5;
		hash ^= hash << 4;
		hash += hash >> 17;
		hash ^= hash << 25;
		hash += hash >> 6;

		return hash + 0x10000000;
	}
}//namespace stringutils
