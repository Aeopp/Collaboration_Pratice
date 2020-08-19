#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;

	m_fSpeed = 1.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fDirection = CalculateRadian(m_tInfo.fX, m_tInfo.fY, *m_fTargetX, *m_fTargetY);

	if (!isnan(m_fDirection))
	{
		m_tInfo.fX += cosf(m_fDirection) * m_fSpeed;
		m_tInfo.fY += sinf(m_fDirection) * m_fSpeed;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (WINCX - 100 <= m_tRect.right
		|| 100 >= m_tRect.left)
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC _DC)
{
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}

float CMonster::CalculateRadian(float _fStartX, float _fStartY, float _fEndX, float _fEndY)
{
	float fHypotenuse, fBase, fAltitude;

	fBase = _fEndX - _fStartX;
	fAltitude = _fEndY - _fStartY;

	fHypotenuse = sqrtf(powf(fBase, 2) + powf(fAltitude, 2));

	float radian = acosf(fBase / fHypotenuse);
	
	return (fAltitude < 0 ? 2 * PI - radian : radian);
}
