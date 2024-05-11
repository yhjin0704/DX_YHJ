#pragma once
class AExpObject
{
public:
	// constrcuter destructer
	AExpObject();
	~AExpObject();

	// delete Function
	AExpObject(const AExpObject& _Other) = delete;
	AExpObject(AExpObject&& _Other) noexcept = delete;
	AExpObject& operator=(const AExpObject& _Other) = delete;
	AExpObject& operator=(AExpObject&& _Other) noexcept = delete;

protected:

private:

};

