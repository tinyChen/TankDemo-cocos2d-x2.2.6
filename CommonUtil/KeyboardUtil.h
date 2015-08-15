#ifndef INCLUDED_DD_KEYBOARD_UTIL_H_
#define INCLUDED_DD_KEYBOARD_UTIL_H_

#include <windows.h>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif
