/*
 Name:		Mc34063aStepDown.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "Mc34063aStepDown.h"

float Mc34063aStepDown::tonToff() const
{
	return (m_Vout + m_Vf) / (m_VinMin - m_Vsat - m_Vout);
}

float Mc34063aStepDown::tOff() const
{
	return tonPlusToff() / (tonToff() + 1.0f);
}

float Mc34063aStepDown::tOn() const
{
	return tonPlusToff() - tOff();
}

float Mc34063aStepDown::cT() const
{
	return 4.0f * static_cast<float>(pow(10, -5)) * tOn();
}

float Mc34063aStepDown::iPk() const
{
	return 2.0f * m_Iout;
}

float Mc34063aStepDown::rSc() const
{
	return 0.3f / iPk();
}

float Mc34063aStepDown::l() const
{
	return ((m_VinMin - m_Vsat - m_Vout) / iPk()) * tOn();
}

float Mc34063aStepDown::cO() const
{
	return (iPk() * tonPlusToff()) / (8.0f * m_Vripple);
}
