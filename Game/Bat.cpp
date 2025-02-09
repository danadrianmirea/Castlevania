#include "Bat.h"
#include "Simon.h"
#include "Black_Knight.h"

CBat::CBat(float x, float y) : CGameObject()
{
	start_x = x;
	start_y = y;
	vx = vy = 0;
	this->healthPoint = 2;
	SetState(BAT_STATE_IDLE);
}

void CBat::Render()
{
	int ani = -1;
	if (vx == 0 && state == BAT_STATE_IDLE)
		ani = 0;
	else ani = 1;

	if (stop)
	{
		int currentFrame = animation_set->at(ani)->GetCurrentFrame();
		animation_set->at(ani)->SetCurrentFrame(currentFrame);
		animation_set->at(ani)->RenderByFrame(currentFrame, nx, x, y);
	}
	else		
		animation_set->at(ani)->Render(x, y, nx);	
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);	
	switch (state)
	{
	case BAT_STATE_IDLE:
	{
		vx = vy = 0;
		break;
	}
	case BAT_STATE_FLYING_DOWN:
	{
		vx = 0.08f;
		vy = 0.08f;
		break;
	}
	case BAT_STATE_FLYING_HORIZONTAL:
	{
		vx = 0.1f;
		vy = 0.0f;
		break;
	}
	}
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, bool stopMoving)
{

	if (stopMoving)
	{
		stop = true;
		return;
	}
	else
	{
		stop = false;
	}

	// Activating Bat logic
	float xS, yS;
	CSimon::GetInstance()->GetPosition(xS, yS);

	float xB, yB;
	this->GetPosition(xB, yB);

	if (xS - xB <= POINT_ACTIVE_BAT_X && yS - yB <= POINT_ACTIVE_BAT_Y) // Active Point 
	{
		vx = 0.08f;
		vy = 0.08f;
	}
		// SetState(BAT_STATE_FLYING_DOWN);
	
	if (y - start_y >= BAT_FLYING_DOWN_DY)	// Redirecting point
	{
		vx = 0.1f;
		vy = 0.0f;
	}
		//SetState(BAT_STATE_FLYING_HORIZONTAL);	

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;		
	}
	else
	{
		float min_tx, min_ty, nx , ny;
		float rdx, rdy;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx;
		y += min_ty * dy;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT  e = coEventsResult[i];

			if (dynamic_cast<CBlack_Knight*>(e->obj))
			{
				// Process normally	
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
		}

	}

	
	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}
