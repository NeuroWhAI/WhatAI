#pragma once







































class NeuronPotential
{
public:
	NeuronPotential();
	~NeuronPotential();


public:
	// ��������
	double rest;
	// ��ġ����
	double threshold;
	// Ȱ������
	double action;
	// ��������
	double refractory;
};

