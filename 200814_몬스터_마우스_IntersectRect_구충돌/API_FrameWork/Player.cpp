#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"


CPlayer::CPlayer()
	: m_pBullet(nullptr),m_bFire(false)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;

	m_fSpeed = 5.f;
}

int CPlayer::Update()
{
	if (m_dwTime + 50 < GetTickCount())
	{
		m_dwTime = GetTickCount();
		m_bFire = true;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState(VK_SPACE) && m_bFire)
	{
		m_pBullet->emplace_back(Create_Bullet(VECTOR{ 1, 0 }));
		m_bFire = false;
	}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}



CObj * CPlayer::Create_Bullet(VECTOR _tDirection)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX + m_tDirection.x * 100, m_tInfo.fY - m_tDirection.y * 100);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_tDirection);

	return pObj;
}


