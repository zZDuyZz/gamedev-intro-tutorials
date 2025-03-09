#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

/*
	Initialize game object 
*/
CGameObject::CGameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		case VK_SPACE:
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
void CMario::Update(DWORD dt)
{
	x += vx*dt;
	y += vy * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {
		
		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}
