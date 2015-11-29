#pragma once
#include <vector>

class Neuron;
class NetGene;
class NeuralNet;
class HormoneState;






































class NetOperator
{
public:
	NetOperator();
	virtual ~NetOperator();


private:
	const NetGene* m_pNetGene;
	NeuralNet* m_pNeuralNet;
	HormoneState* m_pHormoneState;


private:
	std::vector<Neuron*> m_pCurrNeuronList;
	std::vector<Neuron*> m_pUpdateNeuronList;
	std::vector<Neuron*> m_pNextNeuronList;


public:
	int Setup(const NetGene* pNetGene, NeuralNet* pNeuralNet);
	int Update();
	int Render();


public:
	int AddNeuron(Neuron* pNeuron, bool bCheckOverlap);
	int RemoveNeuron(const Neuron* pNeuron);
	int RemoveNeuronAt(int index);
	int RemoveNeuronAt(size_t index);
	std::vector<Neuron*>& GetCurrNeuronList();


private:
	int AddUpdateNeuron(Neuron* pNeuron, bool bCheckOverlap);
	int RemoveUpdateNeuron(const Neuron* pNeuron);
	int RemoveUpdateNeuronAt(int index);
	int RemoveUpdateNeuronAt(size_t index);
	std::vector<Neuron*>& GetUpdateNeuronList();


private:
	// * 뉴런이 활성화된 그 순간에 적용되는 규칙들
	int WhenNeuronActivated(Neuron* pNeuron, const NetGene* pNetGene);
	int AutoSynapseCreation(Neuron* pNeuron, const NetGene* pNetGene);


private:
	// * 뉴런이 활동중일때 적용되는 규칙들
	int OnNeuronActivated(Neuron* pNeuron, const NetGene* pNetGene);
	int HebbLearningRule(Neuron* pNeuron, const NetGene* pNetGene);
	int HormoneEffect(Neuron* pNeuron, const NetGene* pNetGene);
};

