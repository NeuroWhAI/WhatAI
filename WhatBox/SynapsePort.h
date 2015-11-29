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
	int Add(Synapse* pSyp, bool bCheckOverlap/*중복검사여부*/);
	int Remove(const Synapse* pSyp);
	int RemoveAt(int index);
	Synapse*& operator[] (size_t idx);
	Synapse *const & operator[] (size_t idx) const;
	Synapse* At(size_t idx);
	const Synapse* At(size_t idx) const;
	void Foreach(std::function<void(Synapse*)> Func); // 인자로 들어오는 Synapse*는 null이 아님을 보장함.
	bool CheckInputOverlap(const Neuron* pInNeuron) const;
	bool CheckOutputOverlap(const Neuron* pOutNeuron) const;
};

