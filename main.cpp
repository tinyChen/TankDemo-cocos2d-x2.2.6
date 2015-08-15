#include "main.h"
#include "Classes/AppDelegate.h"
#include "CCEGLView.h"
#include "LogUtil.h"
#include "DsList.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	LogUtil::openConsole();
    // create the application instance


    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("BlockEditor");
    eglView->setFrameSize(1024, 768);
    return CCApplication::sharedApplication()->run();
}
