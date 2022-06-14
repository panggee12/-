#include "stdafx.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Effect.h"
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
				
				if (!Sour->Get_God())
				{
					Sour->Set_Attacked();
					Sour->Set_Attacked(true);
					Sour->Set_MinusHp(Dest->Get_Damage());
				}
				if(Dest->Get_Skill()==NORMAL)
					Dest->Set_Dead();
				else
				{
					CObj* Effect = CAbstractFactory<CEffect>::Create(Sour->Get_Info().fX, Sour->Get_Info().fY, Dest->Get_Skill());
					Effect->Set_Target(Sour);
					
					CObjMgr::Get_Instance()->Add_Obj(OBJ_EFFECT, Effect);
					static_cast<CMonster*>(Sour)->Set_Effect_Delay();
				}
				if (Sour->Get_Status().m_iHp <= 0)
				{
					static_cast<CMonster*>(Sour)->Set_State(static_cast<CMonster*>(Sour)->DIE);
				}
				if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
				{
					if (CSceneMgr::Get_Instance()->Get_SceneID() == STAGE_1)
					{
						CSceneMgr::Get_Instance()->Scene_Change(STAGE_2);
						return true;
					}
					else if (CSceneMgr::Get_Instance()->Get_SceneID() == STAGE_2)
					{
						CSceneMgr::Get_Instance()->Scene_Change(STAGE_3);
						return true;
					}
				}
				if (fX > fY) //���� �浹
				{
					if (Dest->Get_Info().fY < Sour->Get_Info().fY)// Dest�� �������� ���� Sour ���� ������
					{
						//Dest->Set_PosY(-fY);
						return true;
					}
					else //Dest�� �Ʒ����� ����
					{
						//Dest->Set_PosY(fY);
						return true;
					}
				}
				else if (fX < fY)
				{
					if (Dest->Get_Info().fX < Sour->Get_Info().fX) //Dest�� Sour�������� �ε���
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

bool CCollisionMgr::Collision_Item(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fX = 0.f;
			float fY = 0.f;
			if (Collision_Check(Dest, Sour, fX, fY))
			{
				if (Sour->Get_Item() == MONEY&&CKeyMgr::Get_Instance()->Key_Down('Z'))
				{
					Dest->Set_MoneyUp(Sour->Get_Money());
					Sour->Set_Dead();
					return true;
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
