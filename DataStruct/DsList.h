#ifndef INCLUDED_DS_LIST_H_
#define INCLUDED_DS_LIST_H_

#include <functional>
#include <vector>

struct DsItem 
{
	void *data;
	DsItem *next;
};

class DsList
{
public:
	DsList() : m_head(nullptr), m_tail(nullptr) {}
	~DsList();

public:
	void addData(void *data);
	void removeData(void *data);
	const std::vector<void *> &removeData(std::function<bool (void *data)> ftn);
	void visitData(std::function<void (void *data)> ftn);

private:
	DsItem *m_head;
	DsItem *m_tail;
};

#endif