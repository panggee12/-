#include "stdafx.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fX = 0.f;
			float fY = 0.f;
			if (Collision_Check(Dest, Sour, fX, fY))
			{
				Sour->Set_Attacked();
				Sour->Set_Attacked(true);
				Sour->Set_MinusHp(Dest->Get_Damage());
				Dest->Set_Dead();
				if (Sour->Get_Status().m_iHp <= 0)
				{
					CObjMgr::Get_Instance()->Get_Player()->Set_ExpUp(Sour->Get_Status().m_iExp);
					if (CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iExp >= CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMaxExp)
						CObjMgr::Get_Instance()->Get_Player()->Set_LvUp();
				}
				if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
				{
					if (CSceneMgr::Get_Instance()->Get_SceneID() == STAGE_1)
					{
						CSceneMgr::Get_Instance()->Scene_Change(STAGE_2);
						return true;
					}
				}
				if (fX > fY) //»óÇÏ Ãæµ¹
				{
					if (Dest->Get_Info().fY < Sour->Get_Info().fY)// Dest°¡ ¶³¾îÁö´Â ±âÁØ Sour À§·Î ¶³¾îÁü
					{
						//Dest->Set_PosY(-fY);
						return true;
					}
					else //Dest°¡ ¾Æ·¡¿¡¼­ À§·Î
					{
						//Dest->Set_PosY(fY);
						return true;
					}
				}
				else if (fX < fY)
				{
					if (Dest->Get_Info().fX < Sour->Get_Info().fX) //Dest°¡ Sour¿ÞÂÊÀ¸·Î ºÎµúÈû
					{
						//Dest->Set_PosX(-fX);
						return true;
					}
					else
					{
						//Dest->Set_PosX(fX);
						return true;
					}

				}
			}
		}
	}
	return false;

}




bool CCollisionMgr::Collision_Check(CObj* _Dest, CObj* _Sour, float & fx, float & fy)
{
	float fXdis = fabs(_Dest->Get_Info().fX - _Sour->Get_Info().fX);
	float fYdis = fabs(_Dest->Get_Info().fY - _Sour->Get_Info().fY);

	float fXrau = (_Dest->Get_Info().fCX + _Sour->Get_Info().fCX)*0.5f;
	float fYrau= (_Dest->Get_Info().fCY + _Sour->Get_Info().fCY)*0.5f;

	if (fXdis < fXrau&&fYdis < fYrau)
	{
		fx = fXdis;
		fy = fYdis;
		return true;
	}
	return false;
}
