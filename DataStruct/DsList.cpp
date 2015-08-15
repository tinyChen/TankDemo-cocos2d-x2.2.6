#include "DsList.h"

DsList::~DsList()
{

}

void DsList::addData(void *data)
{
	if (m_head == nullptr)
	{
		m_head = new DsItem;
		m_head->data = data;
		m_head->next = nullptr;
		m_tail = m_head;

	}else
	{
		DsItem *item = new DsItem;
		item->data = data;
		item->next = nullptr;
		m_tail->next = item;
		m_tail = item;
	}
}

void DsList::removeData(void *data)
{
	DsItem *item = m_head;
	DsItem *preItem = nullptr;
	while (item)
	{
		if (item->data == data)
		{
			DsItem *temp = item;
			item = item->next;
			if (temp->data) delete temp->data;			
			if (preItem) preItem->next = item;
			else
				m_head = item;
			delete temp;
			continue;
		}
		preItem = item;
		item = item->next;
	}
}

void DsList::visitData(std::function<void (void *data)> ftn)
{
	DsItem *item = m_head;
	while (item)
	{
		DsItem *temp = item->next; //避免ftn里面执行removeData删除item导致找不到下个item
		ftn(item->data);
		item = temp;
	}
}

const std::vector<void *> &DsList::removeData(std::function<bool (void *data)> ftn)
{
	static std::vector<void *> s_datas;
	s_datas.clear();

	DsItem *item = m_head;
	DsItem *preItem = nullptr;
	while (item)
	{
		if (ftn(item->data))
		{
			s_datas.push_back(item->data);

			DsItem *temp = item;
			item = item->next;	
			if (preItem) preItem->next = item;
			else
				m_head = item;
			delete temp;
			continue;
		}
		preItem = item;
		item = item->next;
	}
	m_tail = preItem;
	return s_datas;
}