#pragma once

#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual		void	Initialize(void)    PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

public:
	STAGEID m_tStage;
	FRAME		m_tFrame;
	INFO		m_tInfo;
};

