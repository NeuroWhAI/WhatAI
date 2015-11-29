#pragma once






































class TimeManager
{
public:
	TimeManager();
	virtual ~TimeManager();


private:
	double m_speed;
	double m_framerate;
	float m_fFramerate;


public:
	int Update();


public:
	void SetSpeed(double speed);
	double GetSpeed() const;
	const double& GetFrameRate() const;
	const float& GetFrameRateF() const;

};

