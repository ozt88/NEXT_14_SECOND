#pragma once
#include "stdafx.h"

#define BOX_SIZE 47

enum ObjectType
{
	TYPE_NONE,
	TYPE_TANK,
	TYPE_BULLET,
	TYPE_ENEMY,
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	double GetPosX(){return m_PosX;}
	double GetPosY(){return m_PosY;}
	int GetType(){return m_Type;}
	int GetEndPosX(){return m_PosX + m_Width;}
	int GetEndPosY(){return m_PosY + m_Length;}
	bool IsOutOfScreen(){return( m_PosX < 0 || m_PosX > 1000 || m_PosY < 0 || m_PosY > 500 );}
	bool IsClashed( GameObject* otherObject );

	void Render( const HWND& hWnd , const HINSTANCE& hinst , HDC hdc);
	virtual bool IsDestroy() = 0;
	virtual void Update() = 0;

protected:
	int m_Hp;
	double m_PosX;
	double m_PosY;
	int m_Width;
	int m_Length;
	int m_Body;
	ObjectType m_Type;
};

