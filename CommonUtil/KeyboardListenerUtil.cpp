#include "KeyboardListenerUtil.h"
#include "KeyboardListener.h"

bool KeyboardListenerUtil::isKeyDownUp(int keyCode, const std::string &uniqueStr)
{
	return KeyboardListener::sharedListener()->isKeyDownUp(keyCode, uniqueStr);
}

bool KeyboardListenerUtil::isKeyDown(int keyCode)
{
	return KeyboardListener::sharedListener()->isKeyDown(keyCode);
}

bool KeyboardListenerUtil::isKeyUp(int keyCode)
{
	return KeyboardListener::sharedListener()->isKeyUp(keyCode);
}

void KeyboardListenerUtil::stopListening(bool isStop)
{
	KeyboardListener::sharedListener()->stopListening(isStop);
}
