#pragma once







































class NeuronPotential
{
public:
	NeuronPotential();
	~NeuronPotential();


public:
	// 휴지전위
	double rest;
	// 역치전위
	double threshold;
	// 활동전위
	double action;
	// 불응전위
	double refractory;
};

