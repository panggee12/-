#pragma once

struct Status
{
	int			m_iLv;
	int			m_iHp;
	int			m_iMaxHp;
	int			m_iMp;
	int			m_iMaxMp;
	int			m_iExp;
	int			m_iMaxExp;
	int			m_iDamage;
	int			m_iAbPoint;
	int			m_iSTR;
	int			m_iDEX;
	int			m_iINT;
	int			m_iLUK;
};

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;	// 가로 사이즈
	float	fCY;	// 세로 사이즈
}INFO;

typedef struct LINEPOINT
{
	float fX;
	float fY;

	LINEPOINT() { ZeroMemory(this, sizeof(LINEPOINT)); }
	LINEPOINT(float X, float Y) { fX = X; fY = Y; }
};

typedef struct LINE
{
	LINEPOINT LINEL;
	LINEPOINT LINER;

	LINE() { ZeroMemory(this, sizeof(LINE)); }
	LINE(LINEPOINT& L, LINEPOINT& R) { LINEL = L; LINER = R; }
};

typedef struct FRAME
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;

};