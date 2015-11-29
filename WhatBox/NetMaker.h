#pragma once
#include <d3dx9.h>
#include <vector>

class NetGene;
class NeuralNet;
class Neuron;







































class NetMaker
{
public:
	NetMaker();
	virtual ~NetMaker();


private:
	class DirNeuron
	{
	public:
		DirNeuron() : pNeuron(nullptr), dir(0.f, 0.f)
		{ }
		DirNeuron(Neuron* pNeuron) : pNeuron(pNeuron), dir(0.f, 0.f)
		{ }


	public:
		Neuron* pNeuron;
		D3DXVECTOR2 dir;
	};


private:
	NetGene* m_pNetGene;


public:
	int Setup(const NetGene& netGene);
	int Create(NeuralNet* pNet);
};

