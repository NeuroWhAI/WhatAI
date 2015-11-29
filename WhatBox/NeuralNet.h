#pragma once
#include <d3dx9.h>
#include <vector>

class Neuron;
class Synapse;
class NeuronLayer;
class NetOperator;
class Axon;
class NetGene;
class NeuronPotential;
class HormoneState;






































class NeuralNet
{
public:
	NeuralNet();
	virtual ~NeuralNet();


private:
	NetGene* m_pNetGene;
	NeuronPotential* m_pSignalInfo;
	HormoneState* m_pHormoneState;


private:
	std::vector<Neuron*> m_pNeuronList;
	std::vector<Synapse*> m_pSypList;
	std::vector<Axon*> m_pAxonList;


private:
	std::vector<NeuronLayer*> m_pLayerList;


private:
	NetOperator* m_pNetOperator;


public:
	int Init(const NetGene& netGene);
	int Update();
	int Render();


public:
	int AddNeuron(Neuron* pNeuron);
	int AddSynapse(Synapse* pSyp);
	int AddAxon(Axon* pAxon);


public:
	const NeuronPotential& GetSignalInfo() const;
	HormoneState* GetHormoneState();


public:
	int ActivatePNHormone(double hormoneValue);
};

