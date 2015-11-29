#pragma once
#include <vector>

class Axon;






































class AxonPort
{
public:
	AxonPort();
	virtual ~AxonPort();


private:
	std::vector<Axon*> m_pAxonList;


public:
	size_t GetCount() const;
	int Add(Axon* pAxon, bool bCheckOverlap/*중복검사여부*/);
	int Remove(const Axon* pAxon);
	int RemoveAt(int index);
	Axon*& operator[] (size_t idx);
	Axon *const & operator[] (size_t idx) const;
	Axon* At(size_t idx);
	const Axon* At(size_t idx) const;
};

