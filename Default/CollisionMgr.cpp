#include "stdafx.h"
#include "CollisionMgr.h"


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
				if (fX > fY) //���� �浹
				{
					if (Dest->Get_Info().fY < Sour->Get_Info().fY)// Dest�� �������� ���� Sour ���� ������
					{
						return true;
					}
					else //Dest�� �Ʒ����� ����
					{
						return true;
					}
				}
				else if (fX < fY)
				{
					if (Dest->Get_Info().fX < Sour->Get_Info().fX) //Dest�� Sour�������� �ε���
					{
						return true;
					}
					else
					{
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
