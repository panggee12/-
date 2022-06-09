#include "stdafx.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
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
	Load_File();
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
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
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
			m_tLinePoint[RIGHT].fX = m_tLinePoint[LEFT].fX;
			m_tLinePoint[RIGHT].fY = (float)pt.y;

			m_BlockList.push_back(new CBlock(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

			m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
			m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
		}
	}


	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_tLinePoint[LEFT].fX = 0;
		m_tLinePoint[LEFT].fY = 0;
		m_tLinePoint[RIGHT].fX = 0;
		m_tLinePoint[RIGHT].fY = 0;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		Save_File();

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
		Load_File();
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
}

bool CLineMgr::Collision_Line(float fX, float fY,float* pY, float *pY1)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Line().LINEL.fX &&
			fX < iter->Get_Line().LINER.fX)
			pTarget = iter;
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

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
	*pY1 = y1;
	return true;
}
bool CLineMgr::Collision_Block(float fX, float fY, float * pY, float * pY1)
{
	if (m_BlockList.empty())
		return false;

	CBlock*		pTarget = nullptr;

	for (auto& iter : m_BlockList)
	{
		if (fX >= iter->Get_Rect().left &&
			fX < iter->Get_Rect().right)
			pTarget = iter;
	}

	if (!pTarget)
		return false;

	// ������ ������ 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTarget->Get_Rect().left;
	float	x2 = pTarget->Get_Rect().right;

	float	y1 = pTarget->Get_Rect().top;
	float	y2 = pTarget->Get_Rect().bottom;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
	*pY1 = y1;
	return true;
}
void CLineMgr::Save_File(void)
{
	// 1. ���� ����
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// ���� ��ο� �̸��� ����ϴ� �Ű�����
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

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Line()), sizeof(LINE), &dwByte, nullptr);
	}

	// 3. ������ ���� �Ҹ��ϱ�
	CloseHandle(hFile);

#ifdef _DEBUG
	MessageBox(g_hWnd, L"Save ����", L"����", MB_OK);
#endif // _DEBUG

}
void CLineMgr::Load_File(void)
{
	// 1. ���� ����
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// ���� ��ο� �̸��� ����ϴ� �Ű�����
		GENERIC_READ,		// ��� ����, GENERIC_WRITE(����), GENERIC_READ(�б�)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ���ΰ�, NULL�� ���� �� �������� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ������ ����
		OPEN_EXISTING,		// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ���� ������ ���� CREATE_ALWAYS(���� ����) : ������ ���ٸ� ����, ������ �����,  OPEN_EXISTING(�б� ����) : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ� ����, FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� �Ϲ����� ���� ����
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �츰 �� ���� NULL

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