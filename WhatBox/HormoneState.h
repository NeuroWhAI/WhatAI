#pragma once







































class HormoneState
{
public:
	HormoneState();


private:
	double m_pn;							// ����/������ ����


public:
	int Update();
	int Render();


public:
	const double& GetPN() const;
	void SetPN(double pn);
	void AddPN(double add);
};

