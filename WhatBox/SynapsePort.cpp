#include "SynapsePort.h"

#include "cCore.h"

#include "Synapse.h"







































SynapsePort::SynapsePort()
{
	m_pSypList.reserve(32/*여유공간*/);
}


SynapsePort::~SynapsePort()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

size_t SynapsePort::GetCount() const
{
	return m_pSypList.size();
}


int SynapsePort::Add(Synapse* pSyp, bool bCheckOverlap)
{
	const size_t sypListCount = m_pSypList.size();

	size_t nullIdx = m_pSypList.size();

	if (bCheckOverlap)
	{
		// 중복검사
		for (size_t i = 0; i < sypListCount; ++i)
		{
			Synapse* const pSynapse = m_pSypList[i];

			if (pSyp == pSynapse)
			{
				// 중복이므로 추가하지 않음
				return -1;
			}

			if (nullIdx == sypListCount && pSynapse == nullptr)
			{
				nullIdx = i;
			}
		}
	}

	if (nullIdx == sypListCount) nullIdx = 0;

	// 빈공간이 있으면 넣고 아니면 뒤에 추가
	for (size_t i = nullIdx; i < sypListCount; ++i)
	{
		if (m_pSypList[i] == nullptr)
		{
			m_pSypList[i] = pSyp;


			return 0;
		}
	}

	m_pSypList.emplace_back(pSyp);


	return 0;
}


int SynapsePort::Remove(const Synapse* pSyp)
{
	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		Synapse* const pSynapse = m_pSypList[i];

		if (pSyp == pSynapse)
		{
			m_pSypList[i] = nullptr;


			return 0;
		}
	}


	return -1;
}


int SynapsePort::RemoveAt(int index)
{
	m_pSypList[index] = nullptr;


	return 0;
}


Synapse*& SynapsePort::operator[] (size_t idx)
{
	return m_pSypList[idx];
}


Synapse *const & SynapsePort::operator[] (size_t idx) const
{
	return m_pSypList[idx];
}


Synapse* SynapsePort::At(size_t idx)
{
	return m_pSypList[idx];
}


const Synapse* SynapsePort::At(size_t idx) const
{
	return m_pSypList[idx];
}


void SynapsePort::Foreach(std::function<void(Synapse*)> Func)
{
	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		if (m_pSypList[i] == nullptr) continue;


		Func(m_pSypList[i]);
	}
}


bool SynapsePort::CheckInputOverlap(const Neuron* pInNeuron) const
{
	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		if (m_pSypList[i] == nullptr) continue;


		if (m_pSypList[i]->GetInNeuron() == pInNeuron)
		{
			return true;
		}
	}


	return false;
}


bool SynapsePort::CheckOutputOverlap(const Neuron* pOutNeuron) const
{
	for (size_t i = 0; i < m_pSypList.size(); ++i)
	{
		if (m_pSypList[i] == nullptr) continue;


		if (m_pSypList[i]->GetOutNeuron() == pOutNeuron)
		{
			return true;
		}
	}


	return false;
}

