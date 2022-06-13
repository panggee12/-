#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Obj(OBJID _id, CObj * _obj)
{
	if (_id >= OBJ_END || _obj == nullptr)
		return;

	m_ObjList[_id].push_back(_obj);
}

void CObjMgr::Delete_Obj(OBJID _id)
{
	for (auto& iter : m_ObjList[_id])
		Safe_Delete(iter);

	m_ObjList[_id].clear();
}

int CObjMgr::Update()
{
	int iCheck = 0;
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();iter!=m_ObjList[i].end();)
		{
			iCheck=(*iter)->Update();

			if (iCheck == OBJ_DEAD)
			{
				Safe_Delete((*iter));
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	
	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;
		}
	}
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BLOCK]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PATTACK], m_ObjList[OBJ_MONSTER]);
	
	
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render(hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			Safe_Delete(iter);
		}
		m_ObjList[i].clear();
	}
}

