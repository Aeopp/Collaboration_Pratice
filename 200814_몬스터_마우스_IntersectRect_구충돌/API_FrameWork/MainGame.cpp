#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_dwTime(GetTickCount()), m_iFPS(0)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_DC);

	m_MemBMP = CreateCompatibleBitmap(m_DC, WINCX, WINCY);
	SelectObject(m_MemDC, m_MemBMP);


	if (!m_pPlayer)
	{
		m_listObj[OBJID::PLAYER].emplace_back(CAbstractFactory<CPlayer>::Create());
		dynamic_cast<CPlayer*>(m_listObj[OBJID::PLAYER].front())->Set_Bullet(&m_listObj[OBJID::BULLET]);
		dynamic_cast<CPlayer*>(m_listObj[OBJID::PLAYER].front())->SetShield(&m_listObj[OBJID::SHIELD]);
	}

	m_listObj[OBJID::MONSTER].emplace_back(CAbstractFactory<CMonster>::Create(400.f, 200.f));

	for (auto& monster : m_listObj[OBJID::MONSTER])
	{
		dynamic_cast<CMonster*>(monster)->SetTarget(&m_listObj[OBJID::PLAYER].front()->Get_Info().fX, &m_listObj[OBJID::PLAYER].front()->Get_Info().fY);
	}
	//m_listObj[OBJID::MOUSE].emplace_back(CAbstractFactory<CMouse>::Create());
}

void CMainGame::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter = m_listObj[i].begin(); iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}

	//CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::MOUSE]);
	//CCollisionMgr::Collision_Sphere(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BULLET]);
	//CCollisionMgr::Collision_Rect(m_listObj[OBJID::BULLET], m_listObj[OBJID::MONSTER]);
}

void CMainGame::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Late_Update();
	}
}

void CMainGame::Render()
{
	Rectangle(m_MemDC, 0, 0, WINCX, WINCY);
	Rectangle(m_MemDC, 100, 100, WINCX - 100, WINCY - 100);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(m_MemDC);
	}


	TCHAR		szBuff[64] = L"";
	swprintf_s(szBuff, L"Bullet: %d", m_listObj[OBJID::BULLET].size());
	TextOut(m_MemDC, 50, 50, szBuff, lstrlen(szBuff));

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_dwTime = GetTickCount();
		m_iFPS = 0;
	}

	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_MemDC, 0, 0, SRCCOPY);
	/*Rectangle(m_DC, 0, 0, WINCX, WINCY);
	Rectangle(m_DC, 100, 100, WINCX - 100, WINCY - 100);

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(m_DC);
	}


	TCHAR		szBuff[64] = L"";
	swprintf_s(szBuff, L"Bullet: %d", m_listObj[OBJID::BULLET].size());
	TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);
		
		m_dwTime = GetTickCount();
		m_iFPS = 0;
	}*/
}

void CMainGame::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}

	ReleaseDC(g_hWnd, m_DC);
	DeleteDC(m_MemDC);
}
