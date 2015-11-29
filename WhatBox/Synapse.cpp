#include "Synapse.h"

#include <assert.h>

#include "cCore.h"

#include "Neuron.h"








































Synapse::Synapse()
	: m_dot1(0.f, 0.f)
	, m_dot2(0.f, 0.f)

	, m_pInNeuron(nullptr)
	, m_pOutNeuron(nullptr)

	, m_weight(CAST(rand(), double)/RAND_MAX)
{
	if (rand() % 2)
	{
		m_weight *= -1.0;
	}
}


Synapse::~Synapse()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int Synapse::Update()
{
#ifdef _DEBUG
	// 한측의 연결이라도 존재하지 않는 시냅스는 없다는 사실을 확립.
	assert(m_pInNeuron != nullptr && m_pOutNeuron != nullptr);
#endif


	return 0;
}


int Synapse::Draw() const
{
	if (m_pInNeuron->IsActivated())
	{
		int alpha = 50 + static_cast<int>(200.0 * abs(m_weight));
		if (alpha > 255) alpha = 255;

		cCore::Resource.Line.Draw(&m_dot1, &m_dot2,
			(m_weight < 0.0)
			? D3DCOLOR_ARGB(alpha, 237, 28, 36) : D3DCOLOR_ARGB(alpha, 63, 72, 204));
	}
	else
	{
		int alpha = 50 + static_cast<int>(128.0 * abs(m_weight));
		if (alpha > 255) alpha = 255;

		cCore::Resource.Line.Draw(&m_dot1, &m_dot2,
			(m_weight < 0.0)
			? D3DCOLOR_ARGB(alpha, 255, 127, 39) : D3DCOLOR_ARGB(alpha, 153, 217, 234));
	}


	return 0;
}


int Synapse::RenderWeight() const
{
	auto camPos = cCore::Camera2D.Pos();

	Util::ShowText("%.4f",
		(m_dot1.x + m_dot2.x) / 2.f - camPos->x,
		(m_dot1.y + m_dot2.y) / 2.f - camPos->y - 8.f,
		0xff888888, &cCore::Resource.Font0,
		m_weight);


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

Neuron* Synapse::GetInNeuron()
{
	return m_pInNeuron;
}


Neuron* Synapse::GetOutNeuron()
{
	return m_pOutNeuron;
}


void Synapse::SetInNeuron(Neuron* pNeuron)
{
	m_pInNeuron = pNeuron;

	if (pNeuron != nullptr)
	{
		pNeuron->GetPos(&m_dot1);
	}
}


void Synapse::SetOutNeuron(Neuron* pNeuron)
{
	m_pOutNeuron = pNeuron;

	if (pNeuron != nullptr)
	{
		pNeuron->GetPos(&m_dot2);
	}
}


bool Synapse::HaveConnection() const
{
	return (m_pInNeuron != nullptr && m_pOutNeuron != nullptr);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void Synapse::SetWeight(double w)
{
	m_weight = w;
}


const double& Synapse::GetWeight() const
{
	return m_weight;
}

