#ifndef INCLUDED_KEYBOARD_LISTENER_UTIL_H_
#define INCLUDED_KEYBOARD_LISTENER_UTIL_H_

#include <string>

struct KeyboardListenerUtil
{
	static bool isKeyDownUp(int keyCode, const std::string &str);
	static bool isKeyDown(int keyCode);
	static bool isKeyUp(int keyCode);
	static void stopListening(bool isStop);
};

#endif