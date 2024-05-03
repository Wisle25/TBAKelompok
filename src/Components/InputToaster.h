#pragma once

#include "Core.h"
#include "Components/BaseComponent.h"

class InputText;
class Button;

class InputToaster : public BaseComponent
{
public:
    InputToaster(BasePage* Page, const std::string& LabelName, const std::string& Label);

    Delegate<void(const std::string&)> OnSubmit;

    __forceinline void ShowToaster()
    {
        bDisableDraw = bDisableEvent = bDisableTick = false;
    }

private:
    bool bShowToaster = true;

    void SubmitPressed();

    // ***===== Components =====*** //

    std::shared_ptr<InputText> Input;
    std::shared_ptr<Button> SubmitButton;
};