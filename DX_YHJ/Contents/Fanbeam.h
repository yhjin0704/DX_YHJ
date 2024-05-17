#pragma once
class AFanbeam
{
public:
	// constrcuter destructer
	AFanbeam();
	~AFanbeam();

	// delete Function
	AFanbeam(const AFanbeam& _Other) = delete;
	AFanbeam(AFanbeam&& _Other) noexcept = delete;
	AFanbeam& operator=(const AFanbeam& _Other) = delete;
	AFanbeam& operator=(AFanbeam&& _Other) noexcept = delete;

protected:

private:

};

