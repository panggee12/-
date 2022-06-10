#pragma once

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;	// ���� ������
	float	fCY;	// ���� ������
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