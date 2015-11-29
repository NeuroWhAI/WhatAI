#include "TimeManager.h"

#include "cCore.h"







































TimeManager::TimeManager()
	: m_speed(1.0)
	, m_framerate(CAST(cCore::FrameRate, double))
	, m_fFramerate(cCore::FrameRate)
{

}


TimeManager::~TimeManager()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

int TimeManager::Update()
{
	m_framerate = CAST(cCore::FrameRate, double) * m_speed;
	m_fFramerate = CAST(m_framerate, float);


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void TimeManager::SetSpeed(double speed)
{
	if (speed < 0) speed = 0;

	m_speed = speed;
}


double TimeManager::GetSpeed() const
{
	return m_speed;
}


const double& TimeManager::GetFrameRate() const
{
	return m_framerate;
}


const float& TimeManager::GetFrameRateF() const
{
	return m_fFramerate;
}

