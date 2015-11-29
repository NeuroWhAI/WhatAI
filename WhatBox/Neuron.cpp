#include "Neuron.h"

#include "cCore.h"

#include "SynapsePort.h"
#include "AxonPort.h"
#include "Axon.h"
#include "Synapse.h"
#include "NeuronPotential.h"






































Neuron::Neuron(const NeuronPotential& signalInfo)
	: m_signalInfo(signalInfo)
	, m_signal(m_signalInfo.rest)
	
	, m_pInSypPort(new SynapsePort())
	, m_pOutSypPort(new SynapsePort())

	, CurrUpdate(nullptr)

	, m_pInAxonPort(new AxonPort())
	, m_pOutAxonPort(new AxonPort())
{

}


Neuron::~Neuron()
{
	SAFE_DELETE(m_pInSypPort);
	SAFE_DELETE(m_pOutSypPort);

	SAFE_DELETE(m_pInAxonPort);
	SAFE_DELETE(m_pOutAxonPort);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int Neuron::Update(HormoneState* pHormoneState)
{
	// 전위변화 시뮬레이션
	if (CurrUpdate != nullptr)
	{
		(this->*CurrUpdate)();
	}


	return 0;
}

int Neuron::Draw()
{
	cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Neuron]->GetTexture(0),
		m_pos);


	return 0;
}


int Neuron::DrawAxon()
{
	size_t axonCnt;

	axonCnt = m_pInAxonPort->GetCount();
	for (size_t i = 0; i < axonCnt; ++i)
	{
		D3DXVECTOR2 vec = *m_pInAxonPort->At(i)->GetPos();
		D3DXVec2Normalize(&vec, &vec);
		vec *= 8.0f;
		cCore::Sprite.SetColor(D3DCOLOR_ARGB(100, 0, 255, 0));
		cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Neuron]->GetTexture(0),
			m_pos + vec);
	}

	axonCnt = m_pOutAxonPort->GetCount();
	for (size_t i = 0; i < axonCnt; ++i)
	{
		D3DXVECTOR2 vec = *m_pOutAxonPort->At(i)->GetPos();
		D3DXVec2Normalize(&vec, &vec);
		vec *= 8.0f;
		cCore::Sprite.SetColor(D3DCOLOR_ARGB(100, 0, 0, 255));
		cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Neuron]->GetTexture(0),
			m_pos + vec);
	}


	return 0;
}


int Neuron::DrawInSynapse()
{
	size_t sypCnt = m_pInSypPort->GetCount();
	for (size_t i = 0; i < sypCnt; ++i)
	{
		m_pInSypPort->At(i)->Draw();
	}


	return 0;
}


int Neuron::DrawOutSynapse()
{
	size_t sypCnt = m_pOutSypPort->GetCount();
	for (size_t i = 0; i < sypCnt; ++i)
	{
		m_pOutSypPort->At(i)->Draw();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

SynapsePort* Neuron::GetInSypList()
{
	return m_pInSypPort;
}


SynapsePort* Neuron::GetOutSypList()
{
	return m_pOutSypPort;
}

//////////////////////////////////////////////////////////////////////////////////////////////

AxonPort* Neuron::GetInAxonList()
{
	return m_pInAxonPort;
}


AxonPort* Neuron::GetOutAxonList()
{
	return m_pOutAxonPort;
}

//////////////////////////////////////////////////////////////////////////////////////////////

double Neuron::GetSignal() const
{
	return m_signal;
}


void Neuron::SetSignal(double signal)
{
	m_signal = signal;

	if (m_signal < m_signalInfo.refractory)
		m_signal = m_signalInfo.refractory;
	else if (m_signal > m_signalInfo.action)
		m_signal = m_signalInfo.action;

	AutoRest();
}


void Neuron::AddSignal(double signal)
{
	SetSignal(m_signal + signal);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int Neuron::Activate()
{
	m_signal = m_signalInfo.threshold;
	CurrUpdate = &Neuron::Step_ToAction;


	return 0;
}


bool Neuron::IsActivated() const
{
	return (m_signal >= m_signalInfo.threshold);
}


bool Neuron::IsUpdateEnd() const
{
	return (CurrUpdate == nullptr);
}


bool Neuron::IsOnActivateUpdate() const
{
	return (CurrUpdate != nullptr && CurrUpdate != &Neuron::Step_ToRestByDown);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void Neuron::Step_ToAction()
{
	m_signal += 0.1*cCore::TimeMgr.GetFrameRate();

	if (m_signal >= m_signalInfo.action)
	{
		m_signal = m_signalInfo.action;

		CurrUpdate = &Neuron::Step_ToRefractory;
	}
}


void Neuron::Step_ToRefractory()
{
	m_signal -= 0.1*cCore::TimeMgr.GetFrameRate();

	if (m_signal <= m_signalInfo.refractory)
	{
		m_signal = m_signalInfo.refractory;

		CurrUpdate = &Neuron::Step_ToRestByUp;
	}
	else if (this->IsActivated() == false)
	{
		m_signal = m_signalInfo.refractory;
	}
}


void Neuron::Step_ToRestByUp()
{
	m_signal += 0.05*cCore::TimeMgr.GetFrameRate();

	if (m_signal >= m_signalInfo.rest)
	{
		m_signal = m_signalInfo.rest;

		CurrUpdate = nullptr;
	}
}


void Neuron::Step_ToRestByDown()
{
	m_signal -= 0.05*cCore::TimeMgr.GetFrameRate();

	if (m_signal <= m_signalInfo.rest)
	{
		m_signal = m_signalInfo.rest;

		CurrUpdate = nullptr;
	}
}


void Neuron::AutoRest()
{
	if (m_signal > m_signalInfo.rest)
	{
		CurrUpdate = &Neuron::Step_ToRestByDown;
	}
	else
	{
		CurrUpdate = &Neuron::Step_ToRestByUp;
	}
}

