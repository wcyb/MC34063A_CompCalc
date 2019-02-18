/*
 Name:		Mc34063aInverting.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "Mc34063aInverting.h"

float Mc34063aInverting::tonToff() const
{
	return (abs(m_Vout) + m_Vf) / (m_VinMin - m_Vsat);
}

float Mc34063aInverting::tOff() const
{
	return tonPlusToff() / (tonToff() + 1.0f);
}

float Mc34063aInverting::tOn() const
{
	return tonPlusToff() - tOff();
}

float Mc34063aInverting::cT() const
{
	return 4.0f * static_cast<float>(pow(10, -5)) * tOn();
}

float Mc34063aInverting::iPk() const
{
	return 2.0f * m_Iout * (tonToff() + 1.0f);
}

float Mc34063aInverting::rSc() const
{
	return 0.3f / iPk();
}

float Mc34063aInverting::l() const
{
	return ((m_VinMin - m_Vsat) / iPk()) * tOn();
}

float Mc34063aInverting::cO() const
{
	return 9.0f * ((m_Iout * tOn()) / m_Vripple);
}
