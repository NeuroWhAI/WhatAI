#pragma once
#include "Neuron.h"






































class HormoneNeuron : public Neuron
{
public:
	HormoneNeuron(const NeuronPotential& signalInfo, double hormoneValue);
	virtual ~HormoneNeuron();


private:
	double m_hormoneValue;


public:
	int Update(HormoneState* pHormoneState) override;
	int Draw() override;
};

