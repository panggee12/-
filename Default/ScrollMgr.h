#pragma once
#include "Include.h"
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

	void Set_ScrollX(float _X) { m_iScrollX += _X; }
	void Set_ScrollY(float _Y) { m_iScrollY += _Y; }

	int  Get_ScrollX() { return m_iScrollX; }
	int  Get_ScrollY() { return m_iScrollY; }

	void Scroll_Lock();
public:
	static		CScrollMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CScrollMgr* m_pInstance;

	int m_iScrollX;
	int m_iScrollY;
};

