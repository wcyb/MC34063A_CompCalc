/*
 Name:		Mc34063aStepDown.h
 Author:	Wojciech Cybowski (github.com/wcyb)
 License:	GPL v2
*/
#pragma once
#include "Mc34063a.h"

class Mc34063aStepDown final : public Mc34063a
{
public:
	using Mc34063a::Mc34063a;

protected:
	/// <summary>
	/// Calculates ton/toff ratio.
	/// </summary>
	/// <returns>ton/toff ratio</returns>
	float tonToff() const;

	/// <summary>
	/// Calculates Toff time of switching cycle.
	/// </summary>
	/// <returns>Toff time</returns>
	float tOff() const;

	/// <summary>
	/// Calculates Ton time of switching cycle.
	/// </summary>
	/// <returns>Ton time</returns>
	float tOn() const;

	/// <summary>
	/// Calculates timing capacitor value.
	/// </summary>
	/// <returns>timing capacitor value</returns>
	float cT() const;

	/// <summary>
	/// Calculates peak switching current.
	/// </summary>
	/// <returns>peak switching current</returns>
	float iPk() const;

	/// <summary>
	/// Calculates current sense resistor value.
	/// </summary>
	/// <returns>sense resistor value</returns>
	float rSc() const;

	/// <summary>
	/// Calculates inductor value.
	/// </summary>
	/// <returns>inductor value</returns>
	float l() const;

	/// <summary>
	/// Calculates output filter capacitor value.
	/// </summary>
	/// <returns>output filter capacitor value</returns>
	float cO() const;
};

