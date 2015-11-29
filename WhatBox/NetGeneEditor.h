#pragma once
#include <d3dx9.h>

#include "Types.h"

class NetGene;
class cEditBox;
class cTransformButton;






































class NetGeneEditor
{
public:
	NetGeneEditor();
	virtual ~NetGeneEditor();


private:
	NetGene* m_pGene;


private:
	D3DXVECTOR2 m_oldCursorPos;
	int m_layerNum;
	NeuronTypes m_neuronType;


private:
	cEditBox* m_pEdit_neuronNum;
	cEditBox* m_pEdit_inAxonNum;
	cEditBox* m_pEdit_outAxonNum;
	cEditBox* m_pEdit_inAxonDistance;
	cEditBox* m_pEdit_outAxonDistance;
	cEditBox* m_pEdit_maxBeginSypNum;
	cEditBox* m_pEdit_synapseRate;
	cEditBox* m_pEdit_hebbRate;
	cEditBox* m_pEdit_minSynapseWeight;
	cEditBox* m_pEdit_maxSynapseWeight;
	cTransformButton* m_pButton_confirmEdit;


public:
	int Update();
	int Render();


public:
	int Reset();
	void GetGene(NetGene* pGet);


private:
	int GetIntFromEditbox(cEditBox* pEditBox);
	float GetFloatFromEditbox(cEditBox* pEditBox);
	template <typename T>
	void SetNumTo(cEditBox* pEditBox, T num)
	{
		pEditBox->SetStr(std::to_wstring(num));
	}
};

