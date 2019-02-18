/*
 Name:		Mc34063a.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "Mc34063a.h"

Mc34063a::Mc34063a(float Vf, float Vsat, float Vin, float VinMin, float Vout, float Iout, float fmin, float Vripple)
	:m_Vf(Vf), m_Vsat(Vsat), m_Vin(Vin), m_VinMin(VinMin), m_Vout(Vout), m_Iout(Iout), m_fmin(fmin), m_Vripple(Vripple) {}

Mc34063a::~Mc34063a() {}
