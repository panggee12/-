#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"

class CMainGame
{
public:					// ������, �Ҹ���
	CMainGame();
	~CMainGame();

// public, protected, private �Լ�
 public:
	void		Initialize(void);
	void		Update(void);
	void		Render(void);
	void		Release(void);

// public, protected, private ����
private:
	HDC			m_hDC;

};