#pragma once
#include "Include.h"
#include "Logo.h"
#include "Lobby.h"
#include "Stage.h"

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

private:
	static CSceneMgr* m_pInstance;

public:
	static CSceneMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Scene_Change(STAGEID _ID);
private:
	STAGEID m_preScene;
	STAGEID m_cureScene;

	CScene* m_pScene;
};

