#include "Game/CGame.h"

using namespace game;

int main()
{
	//k o n i e c z n e !
	CSingletonCleaner cleaner;

	gGame.Run();
	return 0;
}
