#ifndef MAIN_H
#define MAIN_H

#include <X11/X.h>
#include <X11/Xlib.h>

typedef struct Global
{
	Display *pCurrentDisplay;
	Window *pRootWindow;
	int iCurrentScreenId;
} Global;

extern Global GlobalData;

#define CURRENT_DISPLAY		(GlobalData.pCurrentDisplay)
#define ROOT_WINDOW			(*GlobalData.pRootWindow)
#define CURRENT_SCREEN		(GlobalData.iCurrentScreenId)

#endif // !MAIN_H
