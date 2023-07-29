#include "main.h"
#include "types.h"
#include "wm.h"
#include <X11/Xlib.h>
#include <stdio.h>

struct Global GlobalData;

i32 main()
{
	XSetErrorHandler(WMErrorHandler);

	GlobalData.pCurrentDisplay = XOpenDisplay(NULL);

	if (!GlobalData.pCurrentDisplay)
	{
		fprintf(stderr, "Could not open display");
		return 1;
	}

	GlobalData.iCurrentScreenId = XDefaultScreen(GlobalData.pCurrentDisplay);
	GlobalData.pRootWindow = &RootWindow(GlobalData.pCurrentDisplay, GlobalData.iCurrentScreenId);

	WMInit();
	WMRun();
	WMDestroy();

	XCloseDisplay(GlobalData.pCurrentDisplay);
	return 0;
}
