/*
 Name:		Mc34063a.h
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#pragma once
#include "pch.h"

class Mc34063a
{
public:
	/// <summary>
	/// Initializes class with given values.
	/// </summary>
	/// <param name="Vf">Forward voltage drop of the output rectifier</param>
	/// <param name="Vsat">Saturation voltage of switching transistor</param>
	/// <param name="Vin">Nominal input voltage</param>
	/// <param name="VinMin">Minimum input voltage</param>
	/// <param name="Vout">Desired output voltage</param>
	/// <param name="Iout">Desired output current</param>
	/// <param name="fmin">Minimum desired output switching frequency at the selected values of Vin and Io</param>
	/// <param name="Vripple">Desired peak-to-peak output ripple voltage</param>
	Mc34063a(float Vf, float Vsat, float Vin, float VinMin, float Vout, float Iout, float fmin, float Vripple);
	virtual ~Mc34063a();

	Mc34063a(const Mc34063a&) = delete;
	Mc34063a& operator=(const Mc34063a&) = delete;

protected:
	/// <summary>
	/// Forward voltage drop of the output rectifier.
	/// </summary>
	float m_Vf;

	/// <summary>
	/// Saturation voltage of switching transistor.
	/// </summary>
	float m_Vsat;

	/// <summary>
	/// Nominal input voltage.
	/// </summary>
	float m_Vin;

	/// <summary>
	/// Minimum input voltage.
	/// </summary>
	float m_VinMin;

	/// <summary>
	/// Desired output voltage.
	/// </summary>
	float m_Vout;

	/// <summary>
	/// Desired output current.
	/// </summary>
	float m_Iout;

	/// <summary>
	/// Minimum desired output switching frequency at the selected values of Vin and Io.
	/// </summary>
	float m_fmin;

	/// <summary>
	/// Desired peak-to-peak output ripple voltage.
	/// </summary>
	float m_Vripple;

protected:
	/// <summary>
	/// Calculates ton/toff ratio.
	/// </summary>
	/// <returns>ton/toff ratio</returns>
	virtual float tonToff(void) const = 0;

	/// <summary>
	/// Calculates time depending on switching frequency.
	/// </summary>
	/// <returns>time period depending on switching frequency</returns>
	float tonPlusToff(void) const { return 1.0f / this->m_fmin; };

	/// <summary>
	/// Calculates Toff time of switching cycle.
	/// </summary>
	/// <returns>Toff time</returns>
	virtual float tOff(void) const = 0;

	/// <summary>
	/// Calculates Ton time of switching cycle.
	/// </summary>
	/// <returns>Ton time</returns>
	virtual float tOn(void) const = 0;

	/// <summary>
	/// Calculates timing capacitor value.
	/// </summary>
	/// <returns>timing capacitor value</returns>
	virtual float cT(void) const = 0;

	/// <summary>
	/// Calculates peak switching current.
	/// </summary>
	/// <returns>peak switching current</returns>
	virtual float iPk(void) const = 0;

	/// <summary>
	/// Calculates current sense resistor value.
	/// </summary>
	/// <returns>sense resistor value</returns>
	virtual float rSc(void) const = 0;

	/// <summary>
	/// Calculates inductor value.
	/// </summary>
	/// <returns>inductor value</returns>
	virtual float l(void) const = 0;

	/// <summary>
	/// Calculates output filter capacitor value.
	/// </summary>
	/// <returns>output filter capacitor value</returns>
	virtual float cO(void) const = 0;

public:
	/// <summary>
	/// Calculates all needed components values for apropriate configuration.
	/// </summary>
	/// <returns>Ct, Rsc, L, Co, Ipk</returns>
	std::vector<float> calculateComponentsValues(void) const { return std::vector<float> {cT(), rSc(), l(), cO(), iPk()}; };
};
