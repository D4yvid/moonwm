#include "wm.h"
#include "main.h"
#include "types.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <stdio.h>
#include <stdlib.h>

struct WM WindowManager;

i32 WMErrorHandler(Display *pDisplay, XErrorEvent *pEvent)
{
	if (!pEvent) return 1;

	LOGE("An X error occurred, type: 0x%02x", pEvent->type);

	return 0;
}

void WMInit(void)
{
	XSelectInput(CURRENT_DISPLAY, ROOT_WINDOW, SubstructureRedirectMask);
	XDefineCursor(CURRENT_DISPLAY, ROOT_WINDOW, XCreateFontCursor(CURRENT_DISPLAY, XC_left_ptr));
}

void WMRun(void)
{
	XEvent pEvent;

	while (true && !XNextEvent(CURRENT_DISPLAY, &pEvent))
	{
		if (WMHandleEvent(&pEvent)) continue;

		LOGW("Event of type %02x not handled", pEvent.type);
	}
}

void WMDestroy(void)
{
	LOGI("Destroying window manager...");

	ClientWindow *pClient;

	while (WindowManager.sWindows.uSize > 0)
	{
		StackPop(&WindowManager.sWindows, pClient);

		WMDestroyClientWindow(pClient);
	}
}

i32 WMDestroyClientWindow(ClientWindow *hWindow)
{
	hWindow->pClient = 0;

	free(hWindow);
	return 0;
}

i32 WMCreateClientWindowForHandle(Window hClient)
{
	LOGI("Creating a ClientWindow for handle %02lx", hClient);

	ClientWindow *pWindow;

	if (!(pWindow = malloc(sizeof(*pWindow))))
	{
		LOGE("[CRITICAL] Could not allocate client window");
		return -1;
	}

	pWindow->pClient = hClient;
	pWindow->bFullscreen = false;

	XGetGeometry(
		CURRENT_DISPLAY,
		hClient,
		NULL,
		&pWindow->x,
		&pWindow->y,
		(unsigned int *) &pWindow->iWidth,
		(unsigned int *) &pWindow->iHeight,
		NULL,
		NULL
	);

	StackPush(&WindowManager.sWindows, pWindow);

	return 0;
}

i32 WMHandleEvent(XEvent *event)
{
	LOGI("Event %d received", event->type);
	switch (event->type)
	{
	case ConfigureRequest: return WMConfigureRequestEventHandler(&event->xconfigurerequest);
	case MapRequest: return WMMapRequestEventHandler(&event->xmaprequest);
	}

	return 0;
}

i32 WMConfigureRequestEventHandler(XConfigureRequestEvent *pEvent)
{
	LOGI("Configuring client %04lx", pEvent->window);

	XConfigureWindow(CURRENT_DISPLAY, pEvent->window, pEvent->value_mask, &(XWindowChanges) {
		.x = pEvent->x,
		.y = pEvent->y,
		.width = pEvent->width,
		.height = pEvent->height,

		.sibling = pEvent->above,
		.stack_mode = pEvent->detail,
	});

	return 1;
}

i32 WMMapRequestEventHandler(XMapRequestEvent *pEvent)
{
	XSelectInput(CURRENT_DISPLAY, pEvent->window, StructureNotifyMask | EnterWindowMask);

	WMCreateClientWindowForHandle(pEvent->window);

	XMapWindow(CURRENT_DISPLAY, pEvent->window);
	return 1;
}
