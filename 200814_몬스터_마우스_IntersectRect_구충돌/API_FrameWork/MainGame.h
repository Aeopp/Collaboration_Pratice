#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC				m_DC;
	CObj*			m_pPlayer;
	list<CObj*>		m_listBullet;

	list<CObj*>		m_listObj[OBJID::END];


	int				m_iFPS;
	DWORD			m_dwTime;
	TCHAR			m_szFPS[16];


	HDC				m_MemDC;
	HBITMAP			m_MemBMP;
};


#endif // !__MAINGAME_H__
