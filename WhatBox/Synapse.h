#pragma once
#include <d3dx9.h>

class Neuron;






































class Synapse
{
public:
	Synapse();
	virtual ~Synapse();


private:
	D3DXVECTOR2 m_dot1, m_dot2;


private:
	Neuron* m_pInNeuron;
	Neuron* m_pOutNeuron;


private:
	double m_weight;


public:
	int Update();
	int Draw() const;
	int RenderWeight() const;


public:
	Neuron* GetInNeuron();
	Neuron* GetOutNeuron();
	void SetInNeuron(Neuron* pNeuron);
	void SetOutNeuron(Neuron* pNeuron);
	bool HaveConnection() const;


public:
	void SetWeight(double w);
	const double& GetWeight() const;
};

