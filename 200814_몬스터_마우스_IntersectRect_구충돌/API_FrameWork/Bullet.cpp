#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDir(BULLET::END)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_fPivotX = NAN;
	m_fPivotY = NAN;
	m_fRadian = 0.f;

	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	if (isnan(m_fPivotX))
	{
		m_tInfo.fX += m_tDirection.x* m_fSpeed;
		m_tInfo.fY -= m_tDirection.y* m_fSpeed;
	}
	else
	{
		m_fPivotX += m_tDirection.x* m_fSpeed;
		m_fPivotY -= m_tDirection.y* m_fSpeed;

		m_fRadian += DegreeToRadian(90*m_fSpeed/15);
		m_tInfo.fX = m_fPivotX + cosf(m_fRadian) * 15;
		m_tInfo.fY = m_fPivotY + sinf(m_fRadian) * 15;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if(100 >= m_tRect.left || 100 >= m_tRect.top
		|| WINCX - 100 <= m_tRect.right || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
