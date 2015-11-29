#pragma once
#include "NetObject.h"

class NeuronPotential;
class SynapsePort;
class AxonPort;
class HormoneState;






































class Neuron : public NetObject
{
public:
	explicit Neuron(const NeuronPotential& signalInfo);
	virtual ~Neuron();
	

protected:
	const NeuronPotential& m_signalInfo;
	double m_signal;


protected:
	SynapsePort* m_pInSypPort;
	SynapsePort* m_pOutSypPort;


private:
	void (Neuron::*CurrUpdate)(void);


protected:
	AxonPort* m_pInAxonPort;
	AxonPort* m_pOutAxonPort;


public:
	virtual int Update(HormoneState* pHormoneState);
	virtual int Draw();
	int DrawAxon();
	int DrawInSynapse();
	int DrawOutSynapse();


public:
	SynapsePort* GetInSypList();
	SynapsePort* GetOutSypList();


public:
	AxonPort* GetInAxonList();
	AxonPort* GetOutAxonList();


public:
	double GetSignal() const;
	void SetSignal(double signal);
	void AddSignal(double signal);


public:
	int Activate();
	bool IsActivated() const;
	bool IsUpdateEnd() const;
	bool IsOnActivateUpdate() const;


private:
	void Step_ToAction();
	void Step_ToRefractory();
	void Step_ToRestByUp();
	void Step_ToRestByDown();
	void AutoRest();
};

