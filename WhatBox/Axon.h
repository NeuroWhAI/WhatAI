#pragma once
#include "NetObject.h"

#include <vector>

#include "Types.h"

class Neuron;







































class Axon : public NetObject
{
private:
	static const int MAX_LAYER_GAP; // TODO: NetGene∑Œ ∆Ì¿‘


public:
	explicit Axon(AxonTypes type = AxonTypes::None, Neuron* pCenterNeuron = nullptr);
	virtual ~Axon();


private:
	AxonTypes m_type;
	Neuron* m_pCenterNeuron;


private:
	std::vector<Neuron*> m_pNearNeuronList;


public:
	AxonTypes GetAxonType() const;
	Neuron* GetCenterNeuron();
	const Neuron* GetCenterNeuron() const;
	void SetCenterNeuron(Neuron* pNeuron);


public:
	int AddNearNeuron(Neuron* pNearNeuron);
	int RemoveNearNeuron(const Neuron* pNearNeuron);
	std::vector<Neuron*>& GetNearNeuronList();
	const std::vector<Neuron*>& GetNearNeuronList() const;
	bool CheckNeuronInNear(const Neuron* pNeuron) const;
};

