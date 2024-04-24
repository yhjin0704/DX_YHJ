#pragma once
#include "Bullet.h"

class AAsacocoBullet : public ABullet
{
	GENERATED_BODY(ABullet)

public:
	// constrcuter destructer
	AAsacocoBullet();
	~AAsacocoBullet();

	// delete Function
	AAsacocoBullet(const AAsacocoBullet& _Other) = delete;
	AAsacocoBullet(AAsacocoBullet&& _Other) noexcept = delete;
	AAsacocoBullet& operator=(const AAsacocoBullet& _Other) = delete;
	AAsacocoBullet& operator=(AAsacocoBullet&& _Other) noexcept = delete;

protected:

private:

};

