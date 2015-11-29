#include "NetGeneEditor.h"

#include <algorithm>
#include <string>
#include <iostream>

#include "cCore.h"

#include "NetGene.h"
#include "cEditBox.h"
#include "cTransformButton.h"

#undef max







































NetGeneEditor::NetGeneEditor()
	: m_pGene(nullptr)

	, m_oldCursorPos(0.f, 0.f)
	, m_layerNum(0)
	, m_neuronType(NeuronTypes::Normal)

	, m_pEdit_neuronNum(new cEditBox())
	, m_pEdit_inAxonNum(new cEditBox())
	, m_pEdit_outAxonNum(new cEditBox())
	, m_pEdit_inAxonDistance(new cEditBox())
	, m_pEdit_outAxonDistance(new cEditBox())
	, m_pEdit_maxBeginSypNum(new cEditBox())
	, m_pEdit_synapseRate(new cEditBox())
	, m_pEdit_hebbRate(new cEditBox())
	, m_pEdit_minSynapseWeight(new cEditBox())
	, m_pEdit_maxSynapseWeight(new cEditBox())
	, m_pButton_confirmEdit(new cTransformButton(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(3)))
{
	float yPos = 64.f+22.f;
	m_pEdit_neuronNum->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_inAxonNum->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_outAxonNum->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_inAxonDistance->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_outAxonDistance->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_maxBeginSypNum->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_synapseRate->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_hebbRate->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_minSynapseWeight->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pEdit_maxSynapseWeight->Init(8.f, (yPos += 22.f), 64.f, 20.f);
	m_pButton_confirmEdit->SetPos(8.f, yPos + 28.f);


	Reset();
}


NetGeneEditor::~NetGeneEditor()
{
	SAFE_DELETE(m_pGene);

	SAFE_DELETE(m_pEdit_neuronNum);
	SAFE_DELETE(m_pEdit_inAxonNum);
	SAFE_DELETE(m_pEdit_outAxonNum);
	SAFE_DELETE(m_pEdit_inAxonDistance);
	SAFE_DELETE(m_pEdit_outAxonDistance);
	SAFE_DELETE(m_pEdit_maxBeginSypNum);
	SAFE_DELETE(m_pEdit_synapseRate);
	SAFE_DELETE(m_pEdit_minSynapseWeight);
	SAFE_DELETE(m_pEdit_maxSynapseWeight);
	SAFE_DELETE(m_pButton_confirmEdit);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetGeneEditor::Update()
{
	m_pEdit_neuronNum->Update();
	m_pEdit_inAxonNum->Update();
	m_pEdit_outAxonNum->Update();
	m_pEdit_inAxonDistance->Update();
	m_pEdit_outAxonDistance->Update();
	m_pEdit_maxBeginSypNum->Update();
	m_pEdit_synapseRate->Update();
	m_pEdit_hebbRate->Update();
	m_pEdit_minSynapseWeight->Update();
	m_pEdit_maxSynapseWeight->Update();
	m_pButton_confirmEdit->Update();


	if (m_pButton_confirmEdit->ButtonUp())
	{
		m_pGene->neuronNumPerGuide = GetIntFromEditbox(m_pEdit_neuronNum);
		m_pGene->inAxonNumPerNeuron = GetIntFromEditbox(m_pEdit_inAxonNum);
		m_pGene->outAxonNumPerNeuron = GetIntFromEditbox(m_pEdit_outAxonNum);
		m_pGene->inAxonDistance = GetFloatFromEditbox(m_pEdit_inAxonDistance);
		m_pGene->outAxonDistance = GetFloatFromEditbox(m_pEdit_outAxonDistance);
		m_pGene->maxBeginSynapseNumPerAxon = GetIntFromEditbox(m_pEdit_maxBeginSypNum);
		m_pGene->inhibitorySynapseRate = GetFloatFromEditbox(m_pEdit_synapseRate);
		m_pGene->hebbRate = static_cast<double>(GetFloatFromEditbox(m_pEdit_hebbRate));
		m_pGene->minSynapseWeight = static_cast<double>(GetFloatFromEditbox(m_pEdit_minSynapseWeight));
		m_pGene->maxSynapseWeight = static_cast<double>(GetFloatFromEditbox(m_pEdit_maxSynapseWeight));
	}


	// 초기화
	if (cCore::Input.KeyDown(VK_DELETE))
	{
		Reset();
	}


	// 가이드 배치 기능
	if (cCore::Input.MouseDown(VK_LBUTTON))
	{
		m_oldCursorPos = cCore::Input.fCursorPos();
	}
	else if (cCore::Input.MouseUp(VK_LBUTTON))
	{
		if (cCore::ShapeMath.GetDistanceSq(&m_oldCursorPos, &cCore::Input.fCursorPos())
			> 16.f*16.f)
		{
			D3DXVECTOR2 dir;
			D3DXVec2Subtract(&dir, &cCore::Input.fCursorPos(), &m_oldCursorPos);

			m_pGene->guideList.emplace_back(m_oldCursorPos/*평면 위치*/,
				m_layerNum/*레이어상 위치*/,
				dir/*방향*/,
				m_neuronType/*뉴런 종류*/);
		}
	}


	// 가이드 지우기 기능
	if (cCore::Input.MouseDown(VK_RBUTTON))
	{
		m_oldCursorPos = cCore::Input.fCursorPos();
	}
	else if (cCore::Input.MouseUp(VK_RBUTTON))
	{
		D3DXVECTOR2 cursor = cCore::Input.fCursorPos();


		auto it = std::remove_if(m_pGene->guideList.begin(), m_pGene->guideList.end(),
			[&](const NetGuideline& guide) {

			D3DXVECTOR2 endPos;
			D3DXVec2Add(&endPos, guide.GetPos(), guide.GetDir());


			return (cCore::ShapeMath.isCollided(&m_oldCursorPos, &cursor,
				guide.GetPos(), &endPos));
		});

		m_pGene->guideList.erase(it, m_pGene->guideList.end());
	}


	// 가이드 레이어번호 설정
	if (cCore::Input.GetMouseEps().z < 0)
	{
		if (m_layerNum > 0)
			--m_layerNum;
	}
	else if (cCore::Input.GetMouseEps().z > 0)
	{
		++m_layerNum;
	}


	// 뉴런 종류 선택
	for (char key = '1'; key <= '3'; ++key)
	{
		if (cCore::Input.KeyDown(key))
		{
			// 0번째 요소인 None은 사용하지 않으므로 +1을 해줌
			m_neuronType = static_cast<NeuronTypes>(key - '1' + 1);

			break;
		}
	}


	return 0;
}


int NetGeneEditor::Render()
{
	// 가이드 표시
	cCore::Resource.Line.SetWidth(4.f);
	cCore::Resource.Line.Begin();

	DWORD guideColors[] = {
		0x00000000,
		D3DCOLOR_ARGB(0, 34, 177, 76),
		D3DCOLOR_ARGB(0, 181, 230, 29),
		D3DCOLOR_ARGB(0, 255, 101, 14),
	};

	const size_t guideCnt = m_pGene->guideList.size();
	for (size_t g = 0; g < guideCnt; ++g)
	{
		NetGuideline& guideline = m_pGene->guideList[g];

		// 색 계산
		DWORD color = guideColors[(int)guideline.GetNeuronType()];
		int alpha = 255 - 80 * abs(m_layerNum - guideline.GetLayerNum());
		if (alpha < 30) alpha = 30;
		color |= (static_cast<DWORD>(alpha) << 24);


		// 화살표의 몸통 그리기
		D3DXVECTOR2 endPos;
		D3DXVec2Add(&endPos, guideline.GetPos(), guideline.GetDir());

		cCore::Resource.Line.Draw(guideline.GetPos(), &endPos,
			color);

		// 화살표의 촉 그리기
		D3DXVECTOR2 exp;
		D3DXVec2Normalize(&exp, guideline.GetDir());
		exp *= -16.f;

		D3DXVECTOR2 verticalVec;
		cCore::ShapeMath.GetNormalVec(&verticalVec, guideline.GetDir());
		verticalVec *= 8.f;

		D3DXVECTOR2 arrowEar;
		D3DXVec2Add(&arrowEar, &exp, &verticalVec);
		D3DXVec2Add(&arrowEar, &arrowEar, &endPos);

		cCore::Resource.Line.Draw(&endPos, &arrowEar,
			color);

		verticalVec *= -1.f;
		D3DXVec2Add(&arrowEar, &exp, &verticalVec);
		D3DXVec2Add(&arrowEar, &arrowEar, &endPos);

		cCore::Resource.Line.Draw(&endPos, &arrowEar,
			color);
	}

	cCore::Resource.Line.End();


	// 전체 정보 표시
	float yPos = 64.f;

	Util::ShowText("guideNum: %u", 8.f, (yPos += 22.f), 0xffffffff,
		m_pGene->guideList.size());

	Util::ShowText("neuronNumPerGuide: %d", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->neuronNumPerGuide);

	Util::ShowText("inAxonNumPerNeuron: %d", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->inAxonNumPerNeuron);

	Util::ShowText("outAxonNumPerNeuron: %d", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->outAxonNumPerNeuron);

	Util::ShowText("inAxonDistance: %.1f", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->inAxonDistance);

	Util::ShowText("outAxonDistance: %.1f", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->outAxonDistance);

	Util::ShowText("maxBeginSynapseNumPerAxon: %d", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->maxBeginSynapseNumPerAxon);

	Util::ShowText("inhibitorySynapseRate: %f", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->inhibitorySynapseRate);

	Util::ShowText("hebbRate: %f", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->hebbRate);

	Util::ShowText("minSynapseWeight: %f", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->minSynapseWeight);

	Util::ShowText("maxSynapseWeight: %f", 80.f, (yPos += 22.f), 0xffffffff,
		m_pGene->maxSynapseWeight);


	m_pEdit_neuronNum->Render();
	m_pEdit_inAxonNum->Render();
	m_pEdit_outAxonNum->Render();
	m_pEdit_inAxonDistance->Render();
	m_pEdit_outAxonDistance->Render();
	m_pEdit_maxBeginSypNum->Render();
	m_pEdit_synapseRate->Render();
	m_pEdit_hebbRate->Render();
	m_pEdit_minSynapseWeight->Render();
	m_pEdit_maxSynapseWeight->Render();
	m_pButton_confirmEdit->Render();


	// 현재 선택된 뉴런 종류 표시
	yPos += 64.f;
	const char* neuronTypeNames[] = {
		"None", "Normal", "Positive", "Negative"
	};
	Util::ShowText("NeuronType: %s", 8.f, (yPos += 22.f), 0xffffffff,
		neuronTypeNames[(int)m_neuronType], strlen(neuronTypeNames[(int)m_neuronType])+1);


	// 현재 설정된 레이어번호 표시
	Util::ShowText("LayerNum: %d", 8.f, (yPos += 22.f), 0xffffffff,
		m_layerNum);


	// 가이드 배치 미리보기
	if (cCore::Input.MousePress(VK_LBUTTON))
	{
		D3DXVECTOR2 cursor = cCore::Input.fCursorPos();

		cCore::Resource.Line.Render(&m_oldCursorPos, &cursor,
			D3DCOLOR_ARGB(255, 34, 177, 76), 2.f);

		Util::ShowText("layer: %d",
			cursor.x - cCore::Camera2D.Pos()->x + 8,
			cursor.y - cCore::Camera2D.Pos()->y - 8,
			0xffffffff,
			m_layerNum);
	}
	

	// 가이드 삭제선 표시
	if (cCore::Input.MousePress(VK_RBUTTON))
	{
		D3DXVECTOR2 cursor = cCore::Input.fCursorPos();

		cCore::Resource.Line.Render(&m_oldCursorPos, &cursor,
			D3DCOLOR_ARGB(255, 237, 28, 36), 2.f);
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetGeneEditor::Reset()
{
	SAFE_DELETE(m_pGene);

	m_pGene = new NetGene(rand());
	m_pGene->guideList.clear();
	m_pGene->neuronNumPerGuide = 8;
	m_pGene->inAxonNumPerNeuron = 2;
	m_pGene->outAxonNumPerNeuron = 1;
	m_pGene->inAxonDistance = 100.f;
	m_pGene->outAxonDistance = 100.f;
	m_pGene->maxBeginSynapseNumPerAxon = 10;
	m_pGene->inhibitorySynapseRate = 10.f;
	m_pGene->hebbRate = 0.00001;
	m_pGene->minSynapseWeight = -2.0;
	m_pGene->maxSynapseWeight = 2.0;


	SetNumTo(m_pEdit_neuronNum, m_pGene->neuronNumPerGuide);
	SetNumTo(m_pEdit_inAxonNum, m_pGene->inAxonNumPerNeuron);
	SetNumTo(m_pEdit_outAxonNum, m_pGene->outAxonNumPerNeuron);
	SetNumTo(m_pEdit_inAxonDistance, m_pGene->inAxonDistance);
	SetNumTo(m_pEdit_outAxonDistance, m_pGene->outAxonDistance);
	SetNumTo(m_pEdit_maxBeginSypNum, m_pGene->maxBeginSynapseNumPerAxon);
	SetNumTo(m_pEdit_synapseRate, m_pGene->inhibitorySynapseRate);
	SetNumTo(m_pEdit_hebbRate, m_pGene->hebbRate);
	SetNumTo(m_pEdit_minSynapseWeight, m_pGene->minSynapseWeight);
	SetNumTo(m_pEdit_maxSynapseWeight, m_pGene->maxSynapseWeight);


	return 0;
}


void NetGeneEditor::GetGene(NetGene* pGet)
{
	*pGet = *m_pGene;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int NetGeneEditor::GetIntFromEditbox(cEditBox* pEditBox)
{
	std::wstring wStr;
	pEditBox->GetStr(&wStr);


	try
	{
		return std::stoi(wStr);
	}
	catch (std::out_of_range)
	{
		return std::numeric_limits<int>::max();
	}
	catch (std::invalid_argument)
	{
		return 0;
	}
	

	return 0;
}


float NetGeneEditor::GetFloatFromEditbox(cEditBox* pEditBox)
{
	std::wstring wStr;
	pEditBox->GetStr(&wStr);


	try
	{
		return std::stof(wStr);
	}
	catch (std::out_of_range)
	{
		return std::numeric_limits<float>::max();
	}
	catch (std::invalid_argument)
	{
		return 0;
	}


	return 0;
}

