#include "PreCompile.h"
#include "TeamBundle.h"
#include "SlotButton.h"
#include "GreenArrow.h"
#include "MenuButton.h"
#include "BundleButton.h"
#include "easing.h"

TeamBundle::TeamBundle()
{

}

TeamBundle::~TeamBundle()
{

}

void TeamBundle::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.AddLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, 200.0f });

	Recruitment = GetLevel()->CreateActor<BundleButton>();
	Recruitment->SetButtonText("���� ����");
	Recruitment->Transform.AddLocalPosition(ButtonPos);
	Recruitment->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());
	ButtonPos += ButtonYInter;

	Traning = GetLevel()->CreateActor<BundleButton>();
	Traning->SetButtonText("�Ʒ�");
	Traning->Transform.AddLocalPosition(ButtonPos);
	Traning->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());
	ButtonPos += ButtonYInter;

	Squad = GetLevel()->CreateActor<BundleButton>();
	Squad->SetButtonText("������");
	Squad->Transform.AddLocalPosition(ButtonPos);
	Squad->SetParent<TeamBundle>(GetDynamic_Cast_This<TeamBundle>());
	ButtonPos += ButtonYInter;

	AllButtonColOff();

	State.CreateState(BundleState::PopDown, {
				.Start =
				[=](class GameEngineState* _Parent)
				{
					// �ݸ��� �ٲ���
					AllButtonColOff();
					PopDownDelta = 0.0f;
					//TestValue = 0.01f;
					Transform.SetLocalPosition(float4::ZERO);
				},
				.Stay =
				[=](float _Delta, class GameEngineState* _Parent)
				{
					// �ö���� ����
					// ��ġ ������ �ٿö����� true �ؼ� End ����
					if (-170.0f >= Transform.GetLocalPosition().Y)
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

					float Test = std::lerp(0.0f, -170.0f, PopDownDelta);

					Transform.SetLocalPosition({Transform.GetLocalPosition().X, Test, Transform.GetLocalPosition().Z});


				},
				.End =
				[=](class GameEngineState* _Parent)
				{
					Transform.SetLocalPosition({Transform.GetLocalPosition().X, -170.0f, Transform.GetLocalPosition().Z});
					// �ݸ��� �������� ����
					IsPopUp = false;
				},
		});

	State.CreateState(BundleState::PopUp, {
			.Start =
			[=](class GameEngineState* _Parent)
			{
				// �ݸ��� �ٲ���
				AllButtonColOff();
				PopUpDelta = 0.0f;
				//TestValue = 0.01f;
				Transform.SetLocalPosition({ Transform.GetLocalPosition().X, -170.0f, Transform.GetLocalPosition().Z });
			},
			.Stay =
			[=](float _Delta, class GameEngineState* _Parent)
			{
				// �ö���� ����
				// ��ġ ������ �ٿö����� true �ؼ� End ����
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

				float Test = std::lerp(-170.0f, 0.0f, PopUpDelta);

				Transform.SetLocalPosition({Transform.GetLocalPosition().X, Test, Transform.GetLocalPosition().Z});


			},
			.End =
			[=](class GameEngineState* _Parent)
			{
				Transform.SetLocalPosition(float4::ZERO);
				// �ݸ��� �� �Ѱ�
				AllButtonColOn();
				IsPopUp = true;

			},
			});
}


void TeamBundle::Update(float _Delta)
{
	State.Update(_Delta);

}

void TeamBundle::AllButtonColOn()
{
	Recruitment->ButtonColOn();
	Traning->ButtonColOn();
	Squad->ButtonColOn();
}

void TeamBundle::AllButtonColOff()
{
	Recruitment->ButtonColOff();
	Traning->ButtonColOff();
	Squad->ButtonColOff();
}
