#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"


CPlayer::CPlayer()
	: m_pBullet(nullptr)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_fSpeed = 5.f;

	m_iDegree = 90;
	Update_Direction();
}

int CPlayer::Update()
{

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_tDirection.x * m_fSpeed;
		m_tInfo.fY -= m_tDirection.y* m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX -= m_tDirection.x * m_fSpeed;
		m_tInfo.fY += m_tDirection.y * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_iDegree += 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_iDegree -= 1;
	}
	Update_Direction();

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBullet->emplace_back(Create_Bullet(m_tDirection));
	}
	else if (GetAsyncKeyState('S'))
	{
		m_pBullet->emplace_back(Create_Bullet(m_tDirection, TRUE));
	}

	if (GetAsyncKeyState('A'))
	{
		m_pShield->emplace_back(CreateShield());
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
	MoveToEx(_DC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(_DC, m_tInfo.fX + m_tDirection.x * 100, m_tInfo.fY - m_tDirection.y * 100);
}

void CPlayer::Release()
{
}

CObj* CPlayer::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);

	return pObj;
}

CObj* CPlayer::Create_Bullet(BULLET::DIR _eDir)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_eDir);

	return pObj;
}

CObj * CPlayer::Create_Bullet(VECTOR _tDirection, BOOL _bIsScrewed)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX + m_tDirection.x * 100, m_tInfo.fY - m_tDirection.y * 100);
	dynamic_cast<CBullet*>(pObj)->Set_Dir(_tDirection);
	if (_bIsScrewed)
	{
		dynamic_cast<CBullet*>(pObj)->SetPivot(m_tInfo.fX + m_tDirection.x * 100, m_tInfo.fY - m_tDirection.y * 100);
	}
	return pObj;
}

CObj * CPlayer::CreateShield()
{
	CObj* pObj = CAbstractFactory<CShield>::Create();
	dynamic_cast<CShield*>(pObj)->SetTarget(&m_tInfo.fX, &m_tInfo.fY);
	return pObj;
}
