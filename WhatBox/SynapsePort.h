#pragma once
#include <vector>
#include <functional>

class Synapse;
class Neuron;






































class SynapsePort
{
public:
	SynapsePort();
	virtual ~SynapsePort();


private:
	std::vector<Synapse*> m_pSypList;


public:
	size_t GetCount() const;
	int Add(Synapse* pSyp, bool bCheckOverlap/*�ߺ��˻翩��*/);
	int Remove(const Synapse* pSyp);
	int RemoveAt(int index);
	Synapse*& operator[] (size_t idx);
	Synapse *const & operator[] (size_t idx) const;
	Synapse* At(size_t idx);
	const Synapse* At(size_t idx) const;
	void Foreach(std::function<void(Synapse*)> Func); // ���ڷ� ������ Synapse*�� null�� �ƴ��� ������.
	bool CheckInputOverlap(const Neuron* pInNeuron) const;
	bool CheckOutputOverlap(const Neuron* pOutNeuron) const;
};

