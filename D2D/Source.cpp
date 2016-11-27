#include "Game.h"

int WINAPI WinMain(HINSTANCE currentInstance,HINSTANCE,LPSTR,int)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			Game engine(currentInstance);

			if (SUCCEEDED(engine.Initialize()))
			{
				engine.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}
