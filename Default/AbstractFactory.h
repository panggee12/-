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
	/*static CObj* Create(int left, int top, int right, int bottom)
	{
		CObj* m_pInstance = new T;
		m_pInstance->Initialize();
		m_pInstance->Set_Rect(left, top, right, bottom);
		return m_pInstance;
	}*/
	static CObj* Create(float _x, float _y, SKILLID skillid=PSKILL_END, ITEMID itemid=ITEM_END)
	{
		CObj* m_pInstance = new T;
		if (skillid != PSKILL_END)
			m_pInstance->Set_Skill(skillid);
		else if(skillid == PSKILL_END)
			m_pInstance->Set_Skill(PSKILL_END);
		if (itemid != ITEM_END)
			m_pInstance->Set_Item(itemid);
		else if(itemid==ITEM_END)
			m_pInstance->Set_Item(ITEM_END);
		m_pInstance->Set_Pos(_x, _y);
		m_pInstance->Initialize();
		

		return m_pInstance;
	}
	static CObj* Create(float _x, float _y, PORTALID pId=PORTAL_END,ITEMID item=ITEM_END, BUTTONID _BUTTONID=BUTTON_END)
	{
		CObj* m_pInstance = new T;
		if (pId != PORTAL_END)
			m_pInstance->Set_Portal(pId);
		if (item != ITEM_END)
			m_pInstance->Set_Item(item);
		if (_BUTTONID != BUTTON_END)
			m_pInstance->Set_ButtonId(_BUTTONID);

		m_pInstance->Set_Pos(_x, _y);
		m_pInstance->Initialize();
		
		
		return m_pInstance;
	}
	static CObj* Create(float _x, float _y, const TCHAR* FrameKey, int AttackDamage=0, SKILLID sId = PSKILL_END)
	{
		CObj* m_pInstance = new T;
	
		if (sId != PSKILL_END)
			m_pInstance->Set_Skill(sId);
		if(AttackDamage!=0)
			m_pInstance->Set_Damage(AttackDamage);
		m_pInstance->Initialize();
		m_pInstance->Set_key(FrameKey);
		m_pInstance->Set_Pos(_x, _y);

		return m_pInstance;
	}

};

