#pragma once
#include "Obj.h"
template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory()
	{
	}

	~CAbstractFactory()
	{
	}
	static CObj* Create()
	{
		CObj* m_pInstance = new T;
		m_pInstance->Initialize();

		return m_pInstance;
	}
	static CObj* Create(float _x, float _y, PORTALID pId=PORTAL_END)
	{
		CObj* m_pInstance = new T;
		m_pInstance->Initialize();
		m_pInstance->Set_Pos(_x, _y);
		if (pId != PORTAL_END)
			m_pInstance->Set_Portal(pId);
		return m_pInstance;
	}

};

