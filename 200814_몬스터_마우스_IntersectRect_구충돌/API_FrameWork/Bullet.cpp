#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;

	m_fSpeed = 10.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	m_tInfo.fX += m_tDirection.x * m_fSpeed;
	m_tInfo.fY += m_tDirection.y * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if(0>= m_tRect.left || 0 >= m_tRect.top
		|| WINCX<= m_tRect.right || WINCY<= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
