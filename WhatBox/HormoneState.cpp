#include "HormoneState.h"

#include "cCore.h"







































HormoneState::HormoneState()
	: m_pn(0.0)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int HormoneState::Update()
{
	// PN수치 안정화
	if (abs(m_pn) < 0.000001)
	{
		m_pn = 0.0;
	}
	else
	{
		m_pn -= m_pn*0.01*cCore::TimeMgr.GetFrameRate();
	}


	return 0;
}


int HormoneState::Render()
{
	Util::ShowText("PN: %f", 8.f, 128.f + 18.f*2.f, 0xffffffff, &cCore::Resource.Font0,
		m_pn);


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

const double& HormoneState::GetPN() const
{
	return m_pn;
}


void HormoneState::SetPN(double pn)
{
	m_pn = pn;
}


void HormoneState::AddPN(double add)
{
	m_pn += add;
}

