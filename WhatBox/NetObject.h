#pragma once
#include <d3dx9.h>






































class NetObject
{
public:
	NetObject();
	NetObject(float x, float y, int layerNum);
	virtual ~NetObject();


protected:
	D3DXVECTOR2 m_pos;
	int m_layerNum;


public:
	virtual const D3DXVECTOR2* GetPos() const;
	virtual void GetPos(D3DXVECTOR2* pGet);
	virtual float GetXPos() const;
	virtual float GetYPos() const;
	virtual int GetLayerNum() const;
	virtual void SetPos(const D3DXVECTOR2& pos);
	virtual void SetPos(const D3DXVECTOR2* pPos);
	virtual void SetPos(float x, float y);
	virtual void SetLayerNum(int layerNum);
	virtual void AddPos(const D3DXVECTOR2& addPos);
	virtual void AddPos(const D3DXVECTOR2* pAddPos);
	virtual void AddPos(float x, float y);
	virtual void AddLayerNum(int addNum);
	virtual void SetXPos(float x);
	virtual void SetYPos(float y);
	virtual void AddXPos(float x);
	virtual void AddYPos(float y);
};

