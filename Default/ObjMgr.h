#pragma once
#include "Obj.h"
class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();

private:
	list<CObj*> m_ObjList[OBJ_END];
	static CObjMgr* m_pInstance;

public:
	void Add_Obj(OBJID _id, CObj* _obj);
	void Delete_Obj(OBJID _id);
	int Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	list<CObj*>*	Get_Block() { return &m_ObjList[OBJ_BLOCK]; }
	list<CObj*>*	Get_Monster() { return &m_ObjList[OBJ_MONSTER]; }
	list<CObj*>*	Get_Buttons() { return &m_ObjList[OBJ_BUTTONS]; }
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*			Get_Mouse() { return m_ObjList[OBJ_MOUSE].front(); }
	CObj*			Get_Shop() { return m_ObjList[OBJ_SHOP].front(); }
	CObj*			Get_Ui() { return m_ObjList[OBJ_UI].front(); }
public:
	static CObjMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}




};

