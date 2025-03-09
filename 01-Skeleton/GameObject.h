#pragma once

#include <Windows.h>
#include <d3dx10.h>

#include "Texture.h"

class CGameObject
{
protected: 
	float x; 
	float y;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture
	LPTEXTURE texture;			
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return x; }
	float GetY() { return y; }

	CGameObject(float x = 0.0f, float y=0.0f, LPTEXTURE texture = NULL);

	virtual void Update(DWORD dt) = 0;
	virtual void Render();

	~CGameObject();
};
typedef CGameObject * LPGAMEOBJECT;

class CBrick : public CGameObject
{
public:
	CBrick(float x, float y, LPTEXTURE texture): CGameObject(x,y,texture) {}
	void Update(DWORD dt) {}; 
};

class CMario : public CGameObject
{
	float vx;
	float vy;
public: 
	CMario(float x, float y, float vx, float vy, LPTEXTURE texture) :CGameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
};LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A': // Di chuyển sang trái
		brick_x -= STEP_DISTANCE;
		if (brick_x < 0) brick_x = 0;
		break;
	case 'D': // Di chuyển sang phải
		brick_x += STEP_DISTANCE;
		if (brick_x > BackBufferWidth - BRICK_WIDTH) 
			brick_x = BackBufferWidth - BRICK_WIDTH;
		break;
	case 'W': // Di chuyển lên
		brick_y -= STEP_DISTANCE;
		if (brick_y < 0) brick_y = 0;
		break;
	case 'S': // Di chuyển xuống
		brick_y += STEP_DISTANCE;
		if (brick_y > BackBufferHeight - BRICK_HEIGHT) 
			brick_y = BackBufferHeight - BRICK_HEIGHT;
		break;
	case VK_SPACE :
	{
		Bullet newBullet;
		newBullet.x = brick_x + BRICK_WIDTH / 2; 
		newBullet.y = brick_y; 
		newBullet.active = true; 
		bullets.push_back(newBullet);
	}
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}