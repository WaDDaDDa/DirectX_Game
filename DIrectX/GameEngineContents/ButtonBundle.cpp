#include "PreCompile.h"
#include "ButtonBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

ButtonBundle::ButtonBundle()
{

}

ButtonBundle::~ButtonBundle()
{

}

void ButtonBundle::CreateButton(const std::string& _Text)
{
	std::shared_ptr<class BundleButton> NewButton = GetLevel()->CreateActor<BundleButton>();
	NewButton->SetButtonText(_Text);
	NewButton->Transform.AddLocalPosition(ButtonPos);
	NewButton->SetParent<ButtonBundle>(GetDynamic_Cast_This<ButtonBundle>());
	ButtonPos += ButtonYInter;
	Buttons.push_back(NewButton);
	CreateCount++;
	MovePos = ButtonYInter.Y * CreateCount + 10.0f;
}


void ButtonBundle::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	State.CreateState(BundleState::PopDown, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
					// 콜리젼 다끄고
					AllButtonColOff();
					PopDownDelta = 0.0f;
					Transform.SetLocalPosition(float4::ZERO);
				},
				.Stay =
				[=](float _Delta, class GameEngineState* _Parent)
				{
					// 올라오는 순간
					// 위치 끝까지 다올라갔으면 true 해서 End 진입
					if (-MovePos >= Transform.GetLocalPosition().Y)
					{
						State.ChangeState(BundleState::Idle);
						return;
					}

					//auto easingFunction = getEasingFunction(EaseOutCubic);

					//TestValue += static_cast<float>(easingFunction(TestValue));

					PopDownDelta += _Delta * 5.0f;

					if (PopDownDelta >= 1.0f)
					{
						PopDownDelta = 1.0f;
					}

					float Test = std::lerp(0.0f, -MovePos, PopDownDelta);

					Transform.SetLocalPosition({Transform.GetLocalPosition().X, Test, Transform.GetLocalPosition().Z});


				},
				.End =
				[=](class GameEngineState* _Parent)
				{
					Transform.SetLocalPosition({Transform.GetLocalPosition().X, -MovePos, Transform.GetLocalPosition().Z});
					// 콜리젼 꺼진상태 유지
					IsPopUp = false;
				},
		});

	State.CreateState(BundleState::PopUp, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
				// 콜리젼 다끄고
				AllButtonColOff();
				PopUpDelta = 0.0f;
				//TestValue = 0.01f;
				Transform.SetLocalPosition({ Transform.GetLocalPosition().X, -MovePos, Transform.GetLocalPosition().Z });
			},
			.Stay =
			[=](float _Delta, class GameEngineState* _Parent)
			{
				// 올라오는 순간
				// 위치 끝까지 다올라갔으면 true 해서 End 진입
				if (0.0f <= Transform.GetLocalPosition().Y)
				{
					State.ChangeState(BundleState::Idle);
					return;
				}

				//auto easingFunction = getEasingFunction(EaseOutCubic);

				//TestValue += static_cast<float>(easingFunction(TestValue));

				PopUpDelta += _Delta * 5.0f;

				if (PopUpDelta >= 1.0f)
				{
					PopUpDelta = 1.0f;
				}

				float Test = std::lerp(-MovePos, 0.0f, PopUpDelta);

				Transform.SetLocalPosition({Transform.GetLocalPosition().X, Test, Transform.GetLocalPosition().Z});


			},
			.End =
			[=](class GameEngineState* _Parent)
			{
				Transform.SetLocalPosition(float4::ZERO);
				// 콜리젼 다 켜고
				AllButtonColOn();
				IsPopUp = true;

			},
			});
}


void ButtonBundle::Update(float _Delta)
{
	State.Update(_Delta);

}

void ButtonBundle::AllButtonColOn()
{
	size_t Count = Buttons.size();

	for (size_t i = 0; i < Count; i++)
	{
		Buttons[i]->ButtonColOn();
	}
}

void ButtonBundle::AllButtonColOff()
{
	size_t Count = Buttons.size();

	for (size_t i = 0; i < Count; i++)
	{
		Buttons[i]->ButtonColOff();
	}
}
