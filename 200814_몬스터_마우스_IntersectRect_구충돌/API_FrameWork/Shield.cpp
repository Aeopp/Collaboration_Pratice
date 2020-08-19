#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
	m_fRadian = 0.f;
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;

	m_fSpeed = 5.f;
}

int CShield::Update()
{
	m_fRadian += DegreeToRadian(m_fSpeed);
	m_tInfo.fX = *m_fTargetX + cosf(m_fRadian) * 100;
	m_tInfo.fY = *m_fTargetY + sinf(m_fRadian) * 100;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{
}

void CShield::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release()
{
}
