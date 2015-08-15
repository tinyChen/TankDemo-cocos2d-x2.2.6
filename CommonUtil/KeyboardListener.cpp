#include "KeyboardListener.h"
#include "KeyboardUtil.h"

using namespace std;

KeyboardListener::KeyboardListener()
	: m_stopListening(false)
{

}

KeyboardListener::~KeyboardListener()
{
	m_keyState.clear();
}

static bool isWindowActivated()
{
// 	HWND hwnd = CCEGLView::sharedOpenGLView()->getHWnd();
// 	return GetActiveWindow() == hwnd;
	return true;
}
	

bool KeyboardListener::isKeyDownUp(int keyCode, const string &str)
{
	if (m_stopListening || !isWindowActivated())
	{
		return false;
	}
	unordered_map<string, unordered_map<int, bool> >::iterator iter = m_keyState.find(str);
	if (iter == m_keyState.end())
	{
		unordered_map<int, bool> temp;
		temp.insert(make_pair(keyCode, false));
		m_keyState.insert(make_pair(str, temp));
	}else
	{
		unordered_map<int, bool> &temp = iter->second;
		if (temp.find(keyCode) == temp.end())
		{
			temp.insert(make_pair(keyCode, false));
		}
	}
	iter = m_keyState.find(str);
	if (KEY_DOWN(keyCode))
	{
		iter->second[keyCode] = true;
	}else if (KEY_UP(keyCode) && iter->second[keyCode])
	{
		iter->second[keyCode] = false;
		return true;
	}
	return false;
}

bool KeyboardListener::isKeyDown(int keyCode)
{
	if (m_stopListening || !isWindowActivated())
	{
		return false;
	}
	return KEY_DOWN(keyCode);
}

bool KeyboardListener::isKeyUp(int keyCode)
{
	if (m_stopListening || !isWindowActivated())
	{
		return false;
	}
	return KEY_UP(keyCode);
}

KeyboardListener *KeyboardListener::sharedListener()
{
	static KeyboardListener listener;
	return &listener;
}
