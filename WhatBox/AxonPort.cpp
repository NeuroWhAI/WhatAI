#include "AxonPort.h"

#include "cCore.h"







































AxonPort::AxonPort()
{

}


AxonPort::~AxonPort()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

size_t AxonPort::GetCount() const
{
	return m_pAxonList.size();
}


int AxonPort::Add(Axon* pAxon, bool bCheckOverlap)
{
	const size_t axonListCount = m_pAxonList.size();

	size_t nullIdx = m_pAxonList.size();

	if (bCheckOverlap)
	{
		// �ߺ��˻�
		for (size_t i = 0; i < axonListCount; ++i)
		{
			Axon* const pCurrAxon = m_pAxonList[i];

			if (pAxon == pCurrAxon)
			{
				// �ߺ��̹Ƿ� �߰����� ����
				return -1;
			}

			if (nullIdx == axonListCount && pCurrAxon == nullptr)
			{
				nullIdx = i;
			}
		}
	}

	if (nullIdx == axonListCount) nullIdx = 0;

	// ������� ������ �ְ� �ƴϸ� �ڿ� �߰�
	for (size_t i = nullIdx; i < axonListCount; ++i)
	{
		if (m_pAxonList[i] == nullptr)
		{
			m_pAxonList[i] = pAxon;


			return 0;
		}
	}

	m_pAxonList.emplace_back(pAxon);


	return 0;
}


int AxonPort::Remove(const Axon* pAxon)
{
	for (size_t i = 0; i < m_pAxonList.size(); ++i)
	{
		Axon* const pCurrAxon = m_pAxonList[i];

		if (pAxon == pCurrAxon)
		{
			m_pAxonList[i] = nullptr;


			return 0;
		}
	}


	return -1;
}


int AxonPort::RemoveAt(int index)
{
	m_pAxonList[index] = nullptr;


	return 0;
}


Axon*& AxonPort::operator[] (size_t idx)
{
	return m_pAxonList[idx];
}


Axon *const & AxonPort::operator[] (size_t idx) const
{
	return m_pAxonList[idx];
}


Axon* AxonPort::At(size_t idx)
{
	return m_pAxonList[idx];
}


const Axon* AxonPort::At(size_t idx) const
{
	return m_pAxonList[idx];
}

