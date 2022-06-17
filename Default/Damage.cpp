#include "stdafx.h"
#include "Damage.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDamage::CDamage():m_iDamageCount(0), m_bAlreadyPrint(false)
{
	m_dwDeleteEffect = GetTickCount();
}


CDamage::~CDamage()
{
}

void CDamage::Initialize(void)
{
	m_tInfo.fCX = 37.f;
	m_tInfo.fCY = 47.f;



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Maple/Effect/DamageSkin3.bmp", L"Damage");
}

int CDamage::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_pTarget->Get_Info().fCY*0.7f;
	m_iDamageCount = 1;
	if (!m_bAlreadyPrint)
	{
		while (true)
		{
			m_DamageList.push_front(m_tStatus.m_iDamage % 10);//데미지가 30이라 했을때 처음 0이 들어간다

			m_tStatus.m_iDamage /= 10;  //데미지를 10으로 나누면 남은 값이 10보다 작아지고
			++m_iDamageCount;
			if (m_tStatus.m_iDamage < 10)
			{
				m_DamageList.push_front(m_tStatus.m_iDamage);  //10보다 작으면 바로 프론트로 다시 넣어줘서 브레이크로 while문을 끝낸다 한다
				++m_iDamageCount;  //
				m_bAlreadyPrint = true;
				break;
			}
		}
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CDamage::Late_Update(void)
{
	if (!m_pTarget)
		m_bDead = true;
	if (m_dwDeleteEffect +1500<= GetTickCount())
		m_bDead = true;
}

void CDamage::Render(HDC hDC)
{
	HDC DAMAGEHDC = CBmpMgr::Get_Instance()->Find_Image(L"Damage");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	for (auto& iter : m_DamageList)
	{
		GdiTransparentBlt(hDC,
			m_tInfo.fX - m_iDamageCount*int(m_tInfo.fCX) + iScrollX,
			int(m_tRect.top) - 30 + iScrollY,
			int(m_tInfo.fCX),
			int(m_tInfo.fCY),
			DAMAGEHDC,
			iter*(int)m_tInfo.fCX,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(227, 227, 227));
		--m_iDamageCount;
	}
}

void CDamage::Release(void)
{
}
