#ifndef WM_H
#define WM_H

#include "types.h"
#include <X11/Xlib.h>

#define MAX_XORG_CLIENTS 256

typedef struct ClientWindow
{
	Window pClient;

	i32 iWidth, iHeight;
	i32 x, y;
	bool bFullscreen;
} ClientWindow;

typedef struct WM
{
	Stack(ClientWindow *) sWindows;
	ClientWindow *pCurrentWindow;
} WM;

extern struct WM WindowManager;

i32 WMErrorHandler(Display *pDisplay, XErrorEvent *pEvent);

i32 WMHandleEvent(XEvent *pEvent);
i32 WMConfigureRequestEventHandler(XConfigureRequestEvent *pEvent);
i32 WMMapRequestEventHandler(XMapRequestEvent *pEvent);

i32 WMCreateClientWindowForHandle(Window hWindow);
i32 WMDestroyClientWindow(ClientWindow *hWindow);

void WMInit(void);
void WMRun(void);
void WMDestroy(void);

#endif // !WM_H
