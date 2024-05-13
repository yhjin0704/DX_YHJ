#include "PreCompile.h"
#include "PlayLevelUI.h"
#include "PlayGameMode.h"

int APlayLevelUI::KillCount = 0;

APlayLevelUI::APlayLevelUI()
{
	
}

APlayLevelUI::~APlayLevelUI()
{
}

void APlayLevelUI::BeginPlay()
{
	Super::BeginPlay();

	//Character Image
	CharacterImage = CreateWidget<UImage>(GetWorld(), "CharacterImage");
	CharacterImage->AddToViewPort(EUIOrder::PlayInfo);
	CharacterImage->SetAutoSize(ContentsValue::MultipleSize, true);
	CharacterImage->SetPosition(FVector(-590.f, 288.f));

	CharacterFrame = CreateWidget<UImage>(GetWorld(), "CharacterFrame");
	CharacterFrame->AddToViewPort(EUIOrder::Frame);
	CharacterFrame->SetSprite("HUDCharacterFrame.png");
	CharacterFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	CharacterFrame->SetPosition(FVector(-587.f, 293.f));

	//Exp
	ExpBarFrame = CreateWidget<UImage>(GetWorld(), "ExpBarBack");
	ExpBarFrame->AddToViewPort(EUIOrder::Frame);
	ExpBarFrame->SetSprite("hud_expbar_bg_0.png");
	ExpBarFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	ExpBarFrame->SetPosition(FVector(5.0f * ContentsValue::MultipleSize, 170.0f * ContentsValue::MultipleSize));

	//Hp
	HpHUD = CreateWidget<UImage>(GetWorld(), "HpHUD");
	HpHUD->AddToViewPort(EUIOrder::Frame);
	HpHUD->SetSprite("hud_new_HUDHP_0.png");
	HpHUD->SetAutoSize(ContentsValue::MultipleSize, true);
	HpHUD->SetPosition(FVector(-450.f, 269.f));

	HpBarFrame = CreateWidget<UImage>(GetWorld(), "HpBarBack");
	HpBarFrame->AddToViewPort(EUIOrder::Frame);
	HpBarFrame->SetSprite("hud_HUD_HP_green_1.png");
	HpBarFrame->SetAutoSize(ContentsValue::MultipleSize, true);
	HpBarFrame->SetPosition(FVector(-382.f, 320.f));

	HpBar = CreateWidget<UImage>(GetWorld(), "HpBar");
	HpBar->AddToViewPort(EUIOrder::PlayInfo);
	HpBar->SetSprite("hud_HUD_HP_green_0.png");
	HpBar->SetAutoSize(ContentsValue::MultipleSize, true);
	HpBar->SetPosition(FVector(-382.f, 320.f));

	HpText = CreateWidget<UTextWidget>(GetWorld(), "HpText");
	HpText->AddToViewPort(EUIOrder::PlayInfo);
	HpText->SetScale(7.5f * ContentsValue::MultipleSize);
	HpText->SetFont("Galmuri9");
	HpText->SetColor(Color8Bit::White);
	HpText->SetPosition(FVector(-225.f, 320.f));

	//Money
	MoneyIcon = CreateWidget<UImage>(GetWorld(), "Money");
	MoneyIcon->AddToViewPort(EUIOrder::PlayInfo);
	MoneyIcon->SetSprite("spr_holoCoin_0.png");
	MoneyIcon->SetAutoSize(ContentsValue::MultipleSize, true);
	MoneyIcon->SetPosition(FVector(180.f * ContentsValue::MultipleSize, 155.0f * ContentsValue::MultipleSize));

	MoneyText = CreateWidget<UTextWidget>(GetWorld(), "MoneyText");
	MoneyText->AddToViewPort(EUIOrder::PlayInfo);
	MoneyText->SetScale(ContentsValue::MultipleSize * 10);
	MoneyText->SetFont("Galmuri9");
	MoneyText->SetColor(Color8Bit::White);
	MoneyText->SetPosition(FVector(192.5f * ContentsValue::MultipleSize, 155.0f * ContentsValue::MultipleSize));
	MoneyText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT | FW1_TEXT_FLAG::FW1_VCENTER));

	//Kill Count
	KillCountIcon = CreateWidget<UImage>(GetWorld(), "KillCount");
	KillCountIcon->AddToViewPort(EUIOrder::PlayInfo);
	KillCountIcon->SetSprite("ui_defeatedEnemies_0.png");
	KillCountIcon->SetAutoSize(ContentsValue::MultipleSize, true);
	KillCountIcon->SetPosition(FVector(180.f * ContentsValue::MultipleSize, 137.5f * ContentsValue::MultipleSize));

	KillCountText = CreateWidget<UTextWidget>(GetWorld(), "KillCountText");
	KillCountText->AddToViewPort(EUIOrder::PlayInfo);
	KillCountText->SetScale(ContentsValue::MultipleSize * 10);
	KillCountText->SetFont("Galmuri9");
	KillCountText->SetColor(Color8Bit::White);
	KillCountText->SetPosition(FVector(192.5f * ContentsValue::MultipleSize, 137.5f * ContentsValue::MultipleSize));
	KillCountText->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_LEFT | FW1_TEXT_FLAG::FW1_VCENTER));

	//Time
	StageText = CreateWidget<UImage>(GetWorld(), "StageText");
	StageText->AddToViewPort(EUIOrder::PlayInfo);
	StageText->SetSprite("STAGE.png");
	StageText->SetAutoSize(0.3f * ContentsValue::MultipleSize, true);
	StageText->SetPosition(FVector(0.0f, 152.5f * ContentsValue::MultipleSize));

	PlayTimeUI = CreateWidget<UTextWidget>(GetWorld(), "PlayTime");
	PlayTimeUI->AddToViewPort(EUIOrder::PlayInfo);
	PlayTimeUI->SetScale(ContentsValue::MultipleSize * 10);
	PlayTimeUI->SetFont("Galmuri9");
	PlayTimeUI->SetColor(Color8Bit::White);
	PlayTimeUI->SetPosition(FVector(0.f, 285.f));
	PlayTimeUI->SetFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER));
}

void APlayLevelUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	HpUpdate();
	MoneyUpdate();
	KillCountUpdate();
	TimeUpdate();
}

void APlayLevelUI::StartSetting()
{
	PlayerName = APlayGameMode::MainPlayer->GetName();
	CharacterImage->SetSprite("spr_" + PlayerName + "Portrait_0.png");
	Money = 0;
	KillCount = 0;
}

void APlayLevelUI::HpUpdate()
{
	HpText->SetText(std::to_string(APlayGameMode::MainPlayer->GetHp()));

	HpBar->SetScale({129.0f * ContentsValue::MultipleSize , 9.0f * ContentsValue::MultipleSize });
}

void APlayLevelUI::MoneyUpdate()
{
	MoneyText->SetText(std::to_string(Money));
}

void APlayLevelUI::KillCountUpdate()
{
	KillCountText->SetText(std::to_string(KillCount));
}

void APlayLevelUI::TimeUpdate()
{
	int Second = PlayTime % 60;
	int Minute = PlayTime / 60;

	std::string SecZeroPadding = "00" + std::to_string(Second);
	std::string MinZeroPadding = "00" + std::to_string(Minute);

	std::string SecText = SecZeroPadding.substr(SecZeroPadding.size() - 2, 2);
	std::string MinText = MinZeroPadding.substr(MinZeroPadding.size() - 2, 2);

	PlayTimeUI->SetText(MinText + " : " + SecText);
}