#pragma once
class AAsacocoBullet
{
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

