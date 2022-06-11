#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"
#include "Mouse.h"
class CMainGame
{
public:					// ������, �Ҹ���
	CMainGame();
	~CMainGame();

// public, protected, private �Լ�
 public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

// public, protected, private ����
private:
	HDC			m_hDC;
	DWORD		m_dwTime;
	TCHAR		m_szFPS[32];

	int			m_iFPS;
	
};