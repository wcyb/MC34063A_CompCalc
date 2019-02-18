/*
 Name:		Mc34063aStepUp.cpp
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#include "pch.h"
#include "Mc34063aStepUp.h"

float Mc34063aStepUp::tonToff() const
{
	return (m_Vout + m_Vf - m_VinMin) / (m_VinMin - m_Vsat);
}

float Mc34063aStepUp::tOff() const
{
	return  tonPlusToff() / (tonToff() + 1.0f);
}

float Mc34063aStepUp::tOn() const
{
	return tonPlusToff() - tOff();
}

float Mc34063aStepUp::cT() const
{
	return 4.0f * static_cast<float>(pow(10, -5)) * tOn();
}

float Mc34063aStepUp::iPk() const
{
	return 2.0f * m_Iout * (tonToff() + 1.0f);
}

float Mc34063aStepUp::rSc() const
{
	return 0.3f / iPk();
}

float Mc34063aStepUp::l() const
{
	return ((m_VinMin - m_Vsat) / iPk()) * tOn();
}

float Mc34063aStepUp::cO() const
{
	return 9.0f * ((m_Iout * tOn()) / m_Vripple);
}
