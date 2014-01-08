#ifndef _CROBOT
#define _CROBOT

#include "../GameSCI/source/Logic/Actor/CActor.h"

namespace logic
{

class CRobot : public CActor
{
protected:
	CRobot(const std::wstring& uniqueId);

	virtual ~CRobot(void);

};

}

#endif _CROBOT

