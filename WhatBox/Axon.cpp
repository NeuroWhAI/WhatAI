#include "Axon.h"

#include <algorithm>

#include "cCore.h"

#include "Neuron.h"






































const int Axon::MAX_LAYER_GAP = 1;

//////////////////////////////////////////////////////////////////////////////////////////////

Axon::Axon(AxonTypes type, Neuron* pCenterNeuron)
	: m_type(type)
	, m_pCenterNeuron(pCenterNeuron)
{

}


Axon::~Axon()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

AxonTypes Axon::GetAxonType() const
{
	return m_type;
}


Neuron* Axon::GetCenterNeuron()
{
	return m_pCenterNeuron;
}


const Neuron* Axon::GetCenterNeuron() const
{
	return m_pCenterNeuron;
}


void Axon::SetCenterNeuron(Neuron* pNeuron)
{
	m_pCenterNeuron = pNeuron;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int Axon::AddNearNeuron(Neuron* pNearNeuron)
{
	if (m_pCenterNeuron == pNearNeuron) return -1;


	m_pNearNeuronList.emplace_back(pNearNeuron);

	// ��迡 ������ �ִ� ���������� ����
	std::sort(m_pNearNeuronList.begin(), m_pNearNeuronList.end(),
		[&](Neuron* pN1, Neuron* pN2)->bool {
		D3DXVECTOR2 subVec1, subVec2;
		D3DXVec2Subtract(&subVec1, pN1->GetPos(), m_pCenterNeuron->GetPos());
		D3DXVec2Normalize(&subVec1, &subVec1);
		D3DXVec2Subtract(&subVec2, pN1->GetPos(), m_pCenterNeuron->GetPos());
		D3DXVec2Normalize(&subVec2, &subVec2);

		D3DXVECTOR2 axonVec;
		D3DXVec2Normalize(&axonVec, this->GetPos());

		float dot1 = D3DXVec2Dot(&axonVec, &subVec1);
		float dot2 = D3DXVec2Dot(&axonVec, &subVec2);

		return (dot1 > dot2);
	});


	return 0;
}


int Axon::RemoveNearNeuron(const Neuron* pNearNeuron)
{
	for (size_t i = 0; i < m_pNearNeuronList.size(); ++i)
	{
		if (pNearNeuron == m_pNearNeuronList[i])
		{
			m_pNearNeuronList.erase(m_pNearNeuronList.begin() + i);
			return 0;
		}
	}


	return -1;
}


std::vector<Neuron*>& Axon::GetNearNeuronList()
{
	return m_pNearNeuronList;
}


const std::vector<Neuron*>& Axon::GetNearNeuronList() const
{
	return m_pNearNeuronList;
}


bool Axon::CheckNeuronInNear(const Neuron* pNeuron) const
{
	if (m_pCenterNeuron == nullptr) return false;
	else if (m_pCenterNeuron == pNeuron) return false;


	// �� Axon�� ���ᰡ���� �������� �ִ��� ���θ� ��ȯ

	// �ִ� ���Է��̾� ������ ����� NO
	if (abs(pNeuron->GetLayerNum() - this->GetLayerNum()) > MAX_LAYER_GAP)
	{
		return false;
	}

	// �߽ɴ������� �Ÿ��� ������ ���� ũ�� NO
	if (cCore::ShapeMath.GetDistanceSq(pNeuron->GetPos(), m_pCenterNeuron->GetPos())
		> D3DXVec2LengthSq(this->GetPos()))
	{
		return false;
	}

	// ���� ������� ������ �־�� YES
	D3DXVECTOR2 subVec;
	D3DXVec2Subtract(&subVec, pNeuron->GetPos(), m_pCenterNeuron->GetPos());
	D3DXVec2Normalize(&subVec, &subVec);

	D3DXVECTOR2 axonVec;
	D3DXVec2Normalize(&axonVec, this->GetPos());

	float dot = D3DXVec2Dot(&axonVec, &subVec);

	// dot�� �ִ��� 1.0�� �������� ������ �������� -1.0�� �������� ������ �о�����.
	if (dot > 0.5f)
	{
		return true;
	}

	// �� �ܿ��� NO
	return false;
}

