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

