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
		// 처음 마우스 피킹을 한 경우
		if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
		{
			m_tLinePoint[LEFT].fX = (float)pt.x;
			m_tLinePoint[LEFT].fY = (float)pt.y;
		}
		// 처음 피킹한 경우가 아닐 때
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
		// 처음 마우스 피킹을 한 경우
		if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
		{
			m_tLinePoint[LEFT].fX = (float)pt.x;
			m_tLinePoint[LEFT].fY = (float)pt.y;
		}
		// 처음 피킹한 경우가 아닐 때
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

	// 직선의 방정식 
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

	// 직선의 방정식 
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
	// 1. 파일 개방
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일 경로와 이름을 명시하는 매개변수
		GENERIC_WRITE,		// 모드 지정, GENERIC_WRITE(쓰기), GENERIC_READ(읽기)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용을 할 것인가, NULL로 지정 시 공유하지 않음
		NULL,				// 보안 속성, NULL인 경우 기본 값으로 설정
		CREATE_ALWAYS,		// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들 것인지 설정 CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있으면 덮어쓰기,  OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL, // 파일 속성 지정, FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓰니 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save File", L"Error", MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD	dwByte = 0;

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Line()), sizeof(LINE), &dwByte, nullptr);
	}

	// 3. 개방한 파일 소멸하기
	CloseHandle(hFile);

#ifdef _DEBUG
	MessageBox(g_hWnd, L"Save 성공", L"성공", MB_OK);
#endif // _DEBUG

}
void CLineMgr::Load_File(void)
{
	// 1. 파일 개방
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일 경로와 이름을 명시하는 매개변수
		GENERIC_READ,		// 모드 지정, GENERIC_WRITE(쓰기), GENERIC_READ(읽기)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용을 할 것인가, NULL로 지정 시 공유하지 않음
		NULL,				// 보안 속성, NULL인 경우 기본 값으로 설정
		OPEN_EXISTING,		// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들 것인지 설정 CREATE_ALWAYS(쓰기 전용) : 파일이 없다면 생성, 있으면 덮어쓰기,  OPEN_EXISTING(읽기 전용) : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL, // 파일 속성 지정, FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓰니 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load File", L"Error", MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD	dwByte = 0;

	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. 개방한 파일 소멸하기
	CloseHandle(hFile);


#ifdef _DEBUG
	MessageBox(g_hWnd, L"Load 성공", L"성공", MB_OK);
#endif // _DEBUG

}