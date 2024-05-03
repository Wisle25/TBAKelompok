#include "InputToaster.h"
#include "Components/Button.h"
#include "Components/InputText.h"

InputToaster::InputToaster(BasePage* Page, const std::string& LabelName, const std::string& Label):
    Super(Page)
{
    bDisableDraw = bDisableEvent = bDisableTick = true;

    // Components
    MakeRoundedRect({
        .Size=CalculateByScreenPercent(60.f, 20.f),
        .Position=CalculateByScreenPercent(50.f, 50.f),
        .Color=COLOR,
        .BorderRadius=5.f
    });

    MakeText({
        .TextString=LabelName,
        .Size=CalculateTextScreenPercent(5),
        .Color=sf::Color::Black,
        .Position=CalculateByScreenPercent(50.f, 45.5f),
        .Style=sf::Text::Bold
    });

    const FMakeShape InputProps = {
        .Size=CalculateByScreenPercent(45.f, 5.f),
        .Position=CalculateByScreenPercent(50.f, 51.f),
        .Color=sf::Color::Black,
        .OutlineColor=COLOR,
        .OutlineThickness=3.f,
        .BorderRadius=5.f,
    };
    Input = std::make_shared<InputText>(Page, InputProps, Label);
    AddChildComponent(Input);

    // Btn
    const FMakeShape ButtonShapeProps = {
        .Size=CalculateByScreenPercent(20.f, 5.f),
        .Position=CalculateByScreenPercent(50.f, 56.75f),
        .Color=sf::Color::Blue,
    };
    const FMakeText ButtonTextProps = {
        .TextString="Submit"
    };
    SubmitButton = std::make_shared<Button>(Page, ButtonShapeProps, ButtonTextProps);
    SubmitButton->OnClicked.Bind(this, &InputToaster::SubmitPressed);
    AddChildComponent(SubmitButton);
}

void InputToaster::SubmitPressed()
{
    if (OnSubmit.IsBinded())
    {
        bDisableDraw = bDisableEvent = bDisableDraw = true;

        OnSubmit.Execute(Input->GetValue());
    }
}
