#pragma once
#include <vector>

class Neuron;






































class NeuronLayer
{
public:
	NeuronLayer();
	virtual ~NeuronLayer();


private:
	std::vector<Neuron*> m_pNeuronList;


public:
	int Draw();


public:
	int AddNeuron(Neuron* pNeuron, bool bCheckOverlap);
};

