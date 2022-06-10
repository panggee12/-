#include "stdafx.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Block.h"
#include "AbstractFactory.h"
CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	
}

void CLineMgr::Update(void)
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		// ó�� ���콺 ��ŷ�� �� ���
		if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
		{
			m_tLinePoint[LEFT].fX = (float)pt.x;
			m_tLinePoint[LEFT].fY = (float)pt.y;
		}
		// ó�� ��ŷ�� ��찡 �ƴ� ��
		else
		{
			m_tLinePoint[RIGHT].fX = (float)pt.x;
			m_tLinePoint[RIGHT].fY = m_tLinePoint[LEFT].fY;

			m_LineList.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

			m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
			m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down('P'))
		CObjMgr::Get_Instance()->Add_Obj(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(pt.x, pt.y));

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_tLinePoint[LEFT].fX = 0;
		m_tLinePoint[LEFT].fY = 0;
		m_tLinePoint[RIGHT].fX = 0;
		m_tLinePoint[RIGHT].fY = 0;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_File();
		//Save_File_Portal();
	}

	/*if (CKeyMgr::Get_Instance()->Key_Down('L'))
		Load_File();*/
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
	/*for_each(CObjMgr::Get_Instance()->Get_Block()->begin(), CObjMgr::Get_Instance()->Get_Block()->end(), CDeleteObj());
	CObjMgr::Get_Instance()->Get_Block()->clear();*/
}

bool CLineMgr::Collision_Line(float fX, float* fY,float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;
	float fyUnder = 1500.f;
	float fyOver = 1500;
	float fOnLine = 0.f;
	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Line().LINEL.fX &&
			fX < iter->Get_Line().LINER.fX)
		{
			float	x1 = iter->Get_Line().LINEL.fX;
			float	x2 = iter->Get_Line().LINER.fX;

			float	y1 = iter->Get_Line().LINEL.fY;
			float	y2 = iter->Get_Line().LINER.fY;

			float fiterLine = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			if (!pTarget&&fiterLine >= *fY)
			{
				pTarget = iter;
				fOnLine = fiterLine;
			}
			else if (fiterLine >= *fY&&fiterLine<fOnLine)
			{
				pTarget = iter;
				fOnLine = fiterLine;
			}
		}
			
	}

	if (!pTarget)
		return false;

	// ������ ������ 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTarget->Get_Line().LINEL.fX;
	float	x2 = pTarget->Get_Line().LINER.fX;

	float	y1 = pTarget->Get_Line().LINEL.fY;
	float	y2 = pTarget->Get_Line().LINER.fY;

	*pY = fOnLine;
	
	return true;
}

void CLineMgr::Save_File(void)
{
	// 1. ���� ����
	HANDLE	hFile = CreateFile(L"../Save/Line2.dat",	// ���� ��ο� �̸��� ����ϴ� �Ű�����
		GENERIC_WRITE,		// ��� ����, GENERIC_WRITE(����), GENERIC_READ(�б�)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ���ΰ�, NULL�� ���� �� �������� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ������ ����
		CREATE_ALWAYS,		// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ���� ������ ���� CREATE_ALWAYS(���� ����) : ������ ���ٸ� ����, ������ �����,  OPEN_EXISTING(�б� ����) : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� ����, FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� �Ϲ����� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �츰 �� ���� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save File", L"Error", MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD	dwByte = 0;

	for (auto& iter :m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Line()), sizeof(LINE), &dwByte, nullptr);
	}

	// 3. ������ ���� �Ҹ��ϱ�
	CloseHandle(hFile);

#ifdef _DEBUG
	MessageBox(g_hWnd, L"Save ����", L"����", MB_OK);
#endif // _DEBUG

}
void CLineMgr::Load_File(STAGEID _STAGEID)
{
	HANDLE	hFile=nullptr;
	// 1. ���� ����
	switch (_STAGEID)
	{
	case STAGE_1:
			hFile = CreateFile(L"../Save/Line.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		break;
	case STAGE_2:
			hFile = CreateFile(L"../Save/Line2.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		break;
	case STAGE_3:
			hFile = CreateFile(L"../Save/Line3.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		break;

	}
					

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load File", L"Error", MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD	dwByte = 0;

	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. ������ ���� �Ҹ��ϱ�
	CloseHandle(hFile);


#ifdef _DEBUG
	MessageBox(g_hWnd, L"Load ����", L"����", MB_OK);
#endif // _DEBUG

}

//void CLineMgr::Save_File_Portal(void)
//{
//	// 1. ���� ����
//	HANDLE	hFile = CreateFile(L"../Save/Portal2.dat",	// ���� ��ο� �̸��� ����ϴ� �Ű�����
//		GENERIC_WRITE,		// ��� ����, GENERIC_WRITE(����), GENERIC_READ(�б�)
//		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ���ΰ�, NULL�� ���� �� �������� ����
//		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ������ ����
//		CREATE_ALWAYS,		// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ���� ������ ���� CREATE_ALWAYS(���� ����) : ������ ���ٸ� ����, ������ �����,  OPEN_EXISTING(�б� ����) : ������ ���� ��쿡�� ����
//		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� ����, FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� �Ϲ����� ���� ����
//		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �츰 �� ���� NULL
//
//	if (INVALID_HANDLE_VALUE == hFile)
//	{
//		MessageBox(g_hWnd, L"Save File", L"Error", MB_OK);
//		return;
//	}
//
//	// 2. ���� ����
//
//	DWORD	dwByte = 0;
//
//	for (auto& iter =CObjMgr::Get_Instance()->Get_Block()->begin();iter!= CObjMgr::Get_Instance()->Get_Block()->end();++iter)
//	{
//		WriteFile(hFile, &((*iter)->Get_Info()), sizeof(INFO), &dwByte, nullptr);
//	}
//
//	// 3. ������ ���� �Ҹ��ϱ�
//	CloseHandle(hFile);
//
//#ifdef _DEBUG
//	MessageBox(g_hWnd, L"Save ����", L"����", MB_OK);
//#endif // _DEBUG
//
//}
//void CLineMgr::Load_File_Portal(STAGEID _STAGEID)
//{
//	HANDLE	hFile = nullptr;
//	// 1. ���� ����
//	switch (_STAGEID)
//	{
//	case STAGE_1:
//		hFile = CreateFile(L"../Save/Portal.dat",
//			GENERIC_READ,
//			NULL,
//			NULL,
//			OPEN_EXISTING,
//			FILE_ATTRIBUTE_NORMAL,
//			NULL);
//		break;
//	case STAGE_2:
//		hFile = CreateFile(L"../Save/Portal2.dat",
//			GENERIC_READ,
//			NULL,
//			NULL,
//			OPEN_EXISTING,
//			FILE_ATTRIBUTE_NORMAL,
//			NULL);
//		break;
//	case STAGE_3:
//		hFile = CreateFile(L"../Save/Portal3.dat",
//			GENERIC_READ,
//			NULL,
//			NULL,
//			OPEN_EXISTING,
//			FILE_ATTRIBUTE_NORMAL,
//			NULL);
//		break;
//
//	}
//
//
//	if (INVALID_HANDLE_VALUE == hFile)
//	{
//		MessageBox(g_hWnd, L"Load File", L"Error", MB_OK);
//		return;
//	}
//
//	// 2. ���� ����
//
//	DWORD	dwByte = 0;
//
//	INFO		tInfo{};
//
//	while (true)
//	{
//		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
//
//		if (0 == dwByte)
//			break;
//
//		CObjMgr::Get_Instance()->Add_Obj(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(tInfo.fX, tInfo.fY));
//	}
//
//
//	// 3. ������ ���� �Ҹ��ϱ�
//	CloseHandle(hFile);
//
//
//#ifdef _DEBUG
//	MessageBox(g_hWnd, L"Load ����", L"����", MB_OK);
//#endif // _DEBUG
//
//}