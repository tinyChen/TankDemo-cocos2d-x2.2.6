#ifndef INCLUDED_KEYBOARD_LISTENER_H_
#define INCLUDED_KEYBOARD_LISTENER_H_

#include <unordered_map>
#include <string>

class KeyboardListener
{
public:	
	static KeyboardListener *sharedListener();

private:
	KeyboardListener();
	~KeyboardListener();

public:
	bool isKeyDownUp(int keyCode, const std::string &str);
	bool isKeyDown(int keyCode);
	bool isKeyUp(int keyCode);
	void stopListening(bool isStop) { m_stopListening = isStop; }

private:
	std::unordered_map<std::string, std::unordered_map<int, bool> > m_keyState;

private:
	bool m_stopListening;

};

#endif