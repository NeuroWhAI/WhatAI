#include "NeuronPotential.h"







































NeuronPotential::NeuronPotential()
	: rest(0.0)
	, threshold(0.166)
	, action(1.0)
	, refractory(-0.415)
{

}


NeuronPotential::~NeuronPotential()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////

