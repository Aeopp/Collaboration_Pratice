#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 800
#define WINCY 600

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define PI 3.14159f
#define DegreeToRadian(p) (p * PI/180)

#endif // !__DEFINE_H__
