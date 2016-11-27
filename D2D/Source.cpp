#include "Game.h"

int WINAPI WinMain(HINSTANCE currentInstance,HINSTANCE,LPSTR,int)
{
	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
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
