#include "Application.h"

int main()
{	
	Application* theApp = new Application();
	if (theApp->Startup() == true)
	{
		while (theApp->update() == true)
			theApp->draw();
		theApp->shutdown();

	}

	delete theApp;

	return 0;
}