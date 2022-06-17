#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance=nullptr;

CSceneMgr::CSceneMgr():m_preScene(STAGE_END), m_cureScene(STAGE_LOGO), m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(STAGEID _ID)
{
	m_cureScene = _ID;
	
	if (m_preScene != m_cureScene)
	{
		Safe_Delete(m_pScene);

		switch (m_cureScene)
		{
		case STAGE_LOGO:
			m_pScene = new CLogo;
			break;

		case STAGE_LOBBY:
			m_pScene = new CLobby;
	
			break;

		case STAGE_1:
			m_pScene = new CStage;
			
			break;
		case STAGE_2:
			m_pScene = new CStage2;

			break;
		case STAGE_3:
			m_pScene = new CStage3;

			break;
		case STAGE_4:
			m_pScene = new CStage4;

			break;
		}

		m_pScene->Initialize();

		m_preScene = m_cureScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{	
	Safe_Delete<CScene*>(m_pScene);
}


