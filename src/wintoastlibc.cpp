/**
 * MIT License
 *
 * Copyright (C) 2022-2025 WinToastLibC v0.6 - Peter Zhigalov <peter.zhigalov@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined (UNICODE)
#define UNICODE
#endif
#if !defined (_UNICODE)
#define _UNICODE
#endif
#if !defined (WTLC_BUILD_LIBRARY)
#define WTLC_BUILD_LIBRARY
#endif

#include "wintoastlibc.h"
#include "wintoastlib.h"

void WTLCAPI WTLC_setDebugOutputEnabled(BOOL enabled)
{
    try
    {
        WinToastLib::setDebugOutputEnabled(enabled);
    }
    catch(...)
    {}
}

struct _WTLC_Template
{
    _WTLC_Template(WinToastLib::WinToastTemplate::WinToastTemplateType type)
        : _template(type)
    {}

    inline WinToastLib::WinToastTemplate & data()
    {
        return _template;
    }

private:
    WinToastLib::WinToastTemplate _template;
};

WTLC_Template * WTLCAPI WTLC_Template_Create(_In_ WTLC_TemplateType type)
{
    try
    {
        WinToastLib::WinToastTemplate::WinToastTemplateType _type;
        switch(type)
        {
#define ADD_CASE(X) case WTLC_TemplateType_ ##X : _type = WinToastLib::WinToastTemplate:: X ; break
        ADD_CASE(ImageAndText01);
        ADD_CASE(ImageAndText02);
        ADD_CASE(ImageAndText03);
        ADD_CASE(ImageAndText04);
        ADD_CASE(Text01);
        ADD_CASE(Text02);
        ADD_CASE(Text03);
        ADD_CASE(Text04);
#undef ADD_CASE
        default:
            _type = WinToastLib::WinToastTemplate::ImageAndText02;
            break;
        }
        return new _WTLC_Template(_type);
    }
    catch(...)
    {
        return NULL;
    }
}

void WTLCAPI WTLC_Template_Destroy(_Inout_ WTLC_Template * toast)
{
    try
    {
        delete toast;
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setFirstLine(_Inout_ WTLC_Template * toast, _In_ LPCWSTR text)
{
    try
    {
        if(toast)
            toast->data().setFirstLine(text);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setSecondLine(_Inout_ WTLC_Template * toast, _In_ LPCWSTR text)
{
    try
    {
        if(toast)
            toast->data().setSecondLine(text);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setThirdLine(_Inout_ WTLC_Template * toast, _In_ LPCWSTR text)
{
    try
    {
        if(toast)
            toast->data().setThirdLine(text);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setTextField(_Inout_ WTLC_Template * toast, _In_ LPCWSTR txt, _In_ WTLC_TextField pos)
{
    try
    {
        WinToastLib::WinToastTemplate::TextField _pos;
        switch(pos)
        {
#define ADD_CASE(X) case WTLC_TextField_ ##X : _pos = WinToastLib::WinToastTemplate:: X ; break
        ADD_CASE(FirstLine);
        ADD_CASE(SecondLine);
        ADD_CASE(ThirdLine);
#undef ADD_CASE
        default:
            _pos = static_cast<WinToastLib::WinToastTemplate::TextField>(pos);
            break;
        }
        if(toast)
            toast->data().setTextField(txt, _pos);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setAttributionText(_Inout_ WTLC_Template * toast, _In_ LPCWSTR attributionText)
{
    try
    {
        if(toast)
            toast->data().setAttributionText(attributionText);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setImagePath(_Inout_ WTLC_Template * toast, _In_ LPCWSTR imgPath)
{
    try
    {
        if(toast)
            toast->data().setImagePath(imgPath);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setImagePathWithCropHint(_Inout_ WTLC_Template * toast, _In_ LPCWSTR imgPath, _In_ WTLC_CropHint cropHint)
{
    try
    {
        WinToastLib::WinToastTemplate::CropHint _cropHint;
        switch(cropHint)
        {
#define ADD_CASE(X) case WTLC_CropHint_ ##X : _cropHint = WinToastLib::WinToastTemplate:: X ; break
            ADD_CASE(Square);
            ADD_CASE(Circle);
#undef ADD_CASE
        default:
            _cropHint = WinToastLib::WinToastTemplate::Square;
            break;
        }
        if(toast)
            toast->data().setImagePath(imgPath, _cropHint);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setHeroImagePath(_Inout_ WTLC_Template * toast, _In_ LPCWSTR imgPath, _In_ BOOL inlineImage)
{
    try
    {
        if(toast)
            toast->data().setHeroImagePath(imgPath, inlineImage);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setAudioSystemFile(_Inout_ WTLC_Template * toast, _In_ WTLC_AudioSystemFile audio)
{
    try
    {
        WinToastLib::WinToastTemplate::AudioSystemFile _audio;
        switch(audio)
        {
#define ADD_CASE(X) case WTLC_AudioSystemFile_ ##X : _audio = WinToastLib::WinToastTemplate::AudioSystemFile:: X ; break
        ADD_CASE(DefaultSound);
        ADD_CASE(IM);
        ADD_CASE(Mail);
        ADD_CASE(Reminder);
        ADD_CASE(SMS);
        ADD_CASE(Alarm);
        ADD_CASE(Alarm2);
        ADD_CASE(Alarm3);
        ADD_CASE(Alarm4);
        ADD_CASE(Alarm5);
        ADD_CASE(Alarm6);
        ADD_CASE(Alarm7);
        ADD_CASE(Alarm8);
        ADD_CASE(Alarm9);
        ADD_CASE(Alarm10);
        ADD_CASE(Call);
        ADD_CASE(Call1);
        ADD_CASE(Call2);
        ADD_CASE(Call3);
        ADD_CASE(Call4);
        ADD_CASE(Call5);
        ADD_CASE(Call6);
        ADD_CASE(Call7);
        ADD_CASE(Call8);
        ADD_CASE(Call9);
        ADD_CASE(Call10);
#undef ADD_CASE
        default:
            _audio = static_cast<WinToastLib::WinToastTemplate::AudioSystemFile>(audio);
            break;
        }
        if(toast)
            toast->data().setAudioPath(_audio);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setAudioPath(_Inout_ WTLC_Template * toast, _In_ LPCWSTR audioPath)
{
    try
    {
        if(toast)
            toast->data().setAudioPath(audioPath);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setAudioOption(_Inout_ WTLC_Template * toast, _In_ WTLC_AudioOption audioOption)
{
    try
    {
        WinToastLib::WinToastTemplate::AudioOption _audioOption;
        switch(audioOption)
        {
#define ADD_CASE(X) case WTLC_AudioOption_ ##X : _audioOption = WinToastLib::WinToastTemplate:: X ; break
        ADD_CASE(Default);
        ADD_CASE(Silent);
        ADD_CASE(Loop);
#undef ADD_CASE
        default:
            _audioOption = static_cast<WinToastLib::WinToastTemplate::AudioOption>(audioOption);
            break;
        }
        if(toast)
            toast->data().setAudioOption(_audioOption);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setDuration(_Inout_ WTLC_Template * toast, _In_ WTLC_Duration duration)
{
    try
    {
        WinToastLib::WinToastTemplate::Duration _duration;
        switch(duration)
        {
#define ADD_CASE(X) case WTLC_Duration_ ##X : _duration = WinToastLib::WinToastTemplate:: X ; break
        ADD_CASE(System);
        ADD_CASE(Short);
        ADD_CASE(Long);
#undef ADD_CASE
        default:
            _duration = static_cast<WinToastLib::WinToastTemplate::Duration>(duration);
            break;
        }
        if(toast)
            toast->data().setDuration(_duration);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setExpiration(_Inout_ WTLC_Template * toast, _In_ INT64 millisecondsFromNow)
{
    try
    {
        if(toast)
            toast->data().setExpiration(millisecondsFromNow);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_setScenario(_Inout_ WTLC_Template * toast, _In_ WTLC_Scenario scenario)
{
    try
    {
        WinToastLib::WinToastTemplate::Scenario _scenario;
        switch(scenario)
        {
#define ADD_CASE(X) case WTLC_Scenario_ ##X : _scenario = WinToastLib::WinToastTemplate::Scenario:: X ; break
        ADD_CASE(Default);
        ADD_CASE(Alarm);
        ADD_CASE(IncomingCall);
        ADD_CASE(Reminder);
#undef ADD_CASE
        default:
            _scenario = static_cast<WinToastLib::WinToastTemplate::Scenario>(scenario);
            break;
        }
        if(toast)
            toast->data().setScenario(_scenario);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_addAction(_Inout_ WTLC_Template * toast, _In_ LPCWSTR label)
{
    try
    {
        if(toast)
            toast->data().addAction(label);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_Template_addInput(_Inout_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            toast->data().addInput();
    }
    catch(...)
    {}
}

size_t WTLCAPI WTLC_Template_textFieldsCount(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().textFieldsCount();
    }
    catch(...)
    {}
    return 0;
}

size_t WTLCAPI WTLC_Template_actionsCount(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().actionsCount();
    }
    catch(...)
    {}
    return 0;
}

BOOL WTLCAPI WTLC_Template_hasImage(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().hasImage();
    }
    catch(...)
    {}
    return FALSE;
}

BOOL WTLCAPI WTLC_Template_hasHeroImage(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().hasHeroImage();
    }
    catch(...)
    {}
    return FALSE;
}

LPCWSTR WTLCAPI WTLC_Template_textField(_In_ WTLC_Template * toast, _In_ WTLC_TextField pos)
{
    try
    {
        WinToastLib::WinToastTemplate::TextField _pos;
        switch(pos)
        {
#define ADD_CASE(X) case WTLC_TextField_ ##X : _pos = WinToastLib::WinToastTemplate:: X ; break
        ADD_CASE(FirstLine);
        ADD_CASE(SecondLine);
        ADD_CASE(ThirdLine);
#undef ADD_CASE
        default:
            _pos = static_cast<WinToastLib::WinToastTemplate::TextField>(pos);
            break;
        }
        if(toast)
            return toast->data().textField(_pos).c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_Template_actionLabel(_In_ WTLC_Template * toast, _In_ size_t pos)
{
    try
    {
        if(toast)
            return toast->data().actionLabel(pos).c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_Template_imagePath(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().imagePath().c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_Template_heroImagePath(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().heroImagePath().c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_Template_audioPath(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().audioPath().c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_Template_attributionText(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().attributionText().c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_Template_scenario(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().scenario().c_str();
    }
    catch(...)
    {}
    return NULL;
}

INT64 WTLCAPI WTLC_Template_expiration(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().expiration();
    }
    catch(...)
    {}
    return 0;
}

WTLC_TemplateType WTLCAPI WTLC_Template_type(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
        {
            WinToastLib::WinToastTemplate::WinToastTemplateType result = toast->data().type();
            switch(result)
            {
#define ADD_CASE(X) case WinToastLib::WinToastTemplate:: X : return WTLC_TemplateType_ ##X
            ADD_CASE(ImageAndText01);
            ADD_CASE(ImageAndText02);
            ADD_CASE(ImageAndText03);
            ADD_CASE(ImageAndText04);
            ADD_CASE(Text01);
            ADD_CASE(Text02);
            ADD_CASE(Text03);
            ADD_CASE(Text04);
#undef ADD_CASE
            default:
                break;
            }
            return static_cast<WTLC_TemplateType>(result);
        }
    }
    catch(...)
    {}
    return WTLC_TemplateType_ImageAndText02;
}

WTLC_AudioOption WTLCAPI WTLC_Template_audioOption(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
        {
            WinToastLib::WinToastTemplate::AudioOption result = toast->data().audioOption();
            switch(result)
            {
#define ADD_CASE(X) case WinToastLib::WinToastTemplate:: X : return WTLC_AudioOption_ ##X
            ADD_CASE(Default);
            ADD_CASE(Silent);
            ADD_CASE(Loop);
#undef ADD_CASE
            default:
                break;
            }
            return static_cast<WTLC_AudioOption>(result);
        }
    }
    catch(...)
    {}
    return WTLC_AudioOption_Default;
}

WTLC_Duration WTLCAPI WTLC_Template_duration(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
        {
            WinToastLib::WinToastTemplate::Duration result = toast->data().duration();
            switch(result)
            {
#define ADD_CASE(X) case WinToastLib::WinToastTemplate:: X : return WTLC_Duration_ ##X
            ADD_CASE(System);
            ADD_CASE(Short);
            ADD_CASE(Long);
#undef ADD_CASE
            default:
                break;
            }
            return static_cast<WTLC_Duration>(result);
        }
    }
    catch(...)
    {}
    return WTLC_Duration_System;
}

BOOL WTLCAPI WTLC_Template_isToastGeneric(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().isToastGeneric();
    }
    catch(...)
    {}
    return FALSE;
}

BOOL WTLCAPI WTLC_Template_isInlineHeroImage(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().isInlineHeroImage();
    }
    catch(...)
    {}
    return FALSE;
}

BOOL WTLCAPI WTLC_Template_isCropHintCircle(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().isCropHintCircle();
    }
    catch(...)
    {}
    return FALSE;
}

BOOL WTLCAPI WTLC_Template_isInput(_In_ WTLC_Template * toast)
{
    try
    {
        if(toast)
            return toast->data().isInput();
    }
    catch(...)
    {}
    return FALSE;
}

struct _WTLC_Instance
{
    _WTLC_Instance()
    {}

    inline WinToastLib::WinToast & data()
    {
        return _instance;
    }

private:
    WinToastLib::WinToast _instance;
};

WTLC_Instance * WTLCAPI WTLC_Instance_Create(void)
{
    try
    {
        return new WTLC_Instance();
    }
    catch(...)
    {
        return NULL;
    }
}

void WTLCAPI WTLC_Instance_Destroy(_Inout_ WTLC_Instance * instance)
{
    try
    {
        delete instance;
    }
    catch(...)
    {}
}

BOOL WTLCAPI WTLC_isCompatible(void)
{
    try
    {
        return WinToastLib::WinToast::isCompatible();
    }
    catch(...)
    {
        return FALSE;
    }
}

BOOL WTLCAPI WTLC_isSupportingModernFeatures(void)
{
    try
    {
        return WinToastLib::WinToast::isSupportingModernFeatures();
    }
    catch(...)
    {
        return FALSE;
    }
}

BOOL WTLCAPI WTLC_isWin10AnniversaryOrHigher(void)
{
    try
    {
        return WinToastLib::WinToast::isWin10AnniversaryOrHigher();
    }
    catch(...)
    {
        return FALSE;
    }
}

LPCWSTR WTLCAPI WTLC_strerror(_In_ WTLC_Error error)
{
    try
    {
        WinToastLib::WinToast::WinToastError _error = WinToastLib::WinToast::NoError;
        switch(error)
        {
#define ADD_CASE(X) case WTLC_Error_ ##X : _error = WinToastLib::WinToast:: X ; break
        ADD_CASE(NoError);
        ADD_CASE(NotInitialized);
        ADD_CASE(SystemNotSupported);
        ADD_CASE(ShellLinkNotCreated);
        ADD_CASE(InvalidAppUserModelID);
        ADD_CASE(InvalidParameters);
        ADD_CASE(InvalidHandler);
        ADD_CASE(NotDisplayed);
        ADD_CASE(UnknownError);
#undef ADD_CASE
        default:
            _error = static_cast<WinToastLib::WinToast::WinToastError>(error);
            break;
        }
        return WinToastLib::WinToast::strerror(_error).c_str();
    }
    catch(...)
    {
        return NULL;
    }
}

static WTLC_Error convertError(WinToastLib::WinToast::WinToastError error)
{
    switch(error)
    {
#define ADD_CASE(X) case WinToastLib::WinToast:: X : return WTLC_Error_ ##X
    ADD_CASE(NoError);
    ADD_CASE(NotInitialized);
    ADD_CASE(SystemNotSupported);
    ADD_CASE(ShellLinkNotCreated);
    ADD_CASE(InvalidAppUserModelID);
    ADD_CASE(InvalidParameters);
    ADD_CASE(InvalidHandler);
    ADD_CASE(NotDisplayed);
    ADD_CASE(UnknownError);
#undef ADD_CASE
    default:
        break;
    }
    return static_cast<WTLC_Error>(error);
}

BOOL WTLCAPI WTLC_initialize(_Inout_ WTLC_Instance * instance, _Out_opt_ WTLC_Error * error)
{
    try
    {
        if(!instance)
        {
            if(error)
                *error = WTLC_Error_InvalidParameters;
            return FALSE;
        }
        WinToastLib::WinToast::WinToastError _error = WinToastLib::WinToast::NoError;
        const BOOL result = instance->data().initialize(&_error);
        if(error)
            *error = convertError(_error);
        return result;
    }
    catch(...)
    {
        if(error)
            *error = WTLC_Error_UnknownError;
        return FALSE;
    }
}

BOOL WTLCAPI WTLC_isInitialized(_In_ WTLC_Instance * instance)
{
    try
    {
        if(instance)
            return instance->data().isInitialized();
    }
    catch(...)
    {}
    return FALSE;
}

BOOL WTLCAPI WTLC_hideToast(_Inout_ WTLC_Instance * instance, _In_ INT64 id)
{
    try
    {
        if(instance)
            return instance->data().hideToast(id);
    }
    catch(...)
    {}
    return FALSE;
}

namespace {

const UINT64 TOAST_ACTIVATED_INPUT_VERSION = WTLC_MAKE_VERSION(0, 5, 0);

class CustomHandler : public WinToastLib::IWinToastHandler
{
public:
    CustomHandler(_In_opt_ WTLC_Handler * handler)
    {
        ZeroMemory(&m_handler, sizeof(m_handler));
        if(handler)
        {
            m_handler.version = handler->version;
            m_handler.userData = handler->userData;
            m_handler.toastActivated = handler->toastActivated;
            m_handler.toastActivatedAction = handler->toastActivatedAction;
            m_handler.toastDismissed = handler->toastDismissed;
            m_handler.toastFailed = handler->toastFailed;
            if(m_handler.version >= TOAST_ACTIVATED_INPUT_VERSION)
                m_handler.toastActivatedInput = handler->toastActivatedInput;
        }
    }

    void toastActivated() const override
    {
        if(m_handler.toastActivated)
            m_handler.toastActivated(m_handler.userData);
    }

    void toastActivated(int actionIndex) const override
    {
        if(m_handler.toastActivatedAction)
            m_handler.toastActivatedAction(m_handler.userData, actionIndex);
    }

    void toastActivated(std::wstring response) const override
    {
        if(m_handler.version >= TOAST_ACTIVATED_INPUT_VERSION)
        {
            if(m_handler.toastActivatedInput)
                m_handler.toastActivatedInput(m_handler.userData, response.c_str());
        }
        else
        {
            if(m_handler.toastActivatedAction)
                m_handler.toastActivatedAction(m_handler.userData, 0);
        }
    }

    void toastDismissed(WinToastLib::IWinToastHandler::WinToastDismissalReason state) const override
    {
        WTLC_DismissalReason _state;
        switch(state)
        {
#define ADD_CASE(X) case WinToastLib::IWinToastHandler:: X : _state = WTLC_DismissalReason_ ##X ; break
        ADD_CASE(UserCanceled);
        ADD_CASE(ApplicationHidden);
        ADD_CASE(TimedOut);
#undef ADD_CASE
        default:
            _state = static_cast<WTLC_DismissalReason>(state);
            break;
        }
        if(m_handler.toastDismissed)
            m_handler.toastDismissed(m_handler.userData, _state);
    }

    void toastFailed() const override
    {
        if(m_handler.toastFailed)
            m_handler.toastFailed(m_handler.userData);
    }

private:
    WTLC_Handler m_handler;
};

}

INT64 WTLCAPI WTLC_showToast(_Inout_ WTLC_Instance * instance,
                             _In_ WTLC_Template * toast,
                             _In_opt_ void * userData,
                             _In_opt_ WTLC_CB_toastActivated toastActivated,
                             _In_opt_ WTLC_CB_toastActivatedAction toastActivatedAction,
                             _In_opt_ WTLC_CB_toastDismissed toastDismissed,
                             _In_opt_ WTLC_CB_toastFailed toastFailed,
                             _Out_opt_ WTLC_Error* error)
{
    try
    {
        WTLC_Handler handler;
        ZeroMemory(&handler, sizeof(handler));
        handler.version = TOAST_ACTIVATED_INPUT_VERSION - 1;
        handler.userData = userData;
        handler.toastActivated = toastActivated;
        handler.toastActivatedAction = toastActivatedAction;
        handler.toastDismissed = toastDismissed;
        handler.toastFailed = toastFailed;
        return WTLC_showToastEx(instance, toast, &handler, error);
    }
    catch(...)
    {}
    return -1;
}

INT64 WTLCAPI WTLC_showToastEx(_Inout_ WTLC_Instance * instance,
                               _In_ WTLC_Template * toast,
                               _In_opt_ WTLC_Handler * handler,
                               _Out_opt_ WTLC_Error * error)
{
    try
    {
        if(instance)
        {
            WinToastLib::WinToast::WinToastError _error = WinToastLib::WinToast::NoError;
            const INT64 result = instance->data().showToast(toast->data(), new CustomHandler(handler), &_error);
            if(error)
                *error = convertError(_error);
            return result;
        }
    }
    catch(...)
    {}
    return -1;
}

void WTLCAPI WTLC_clear(_Inout_ WTLC_Instance * instance)
{
    try
    {
        if(instance)
            instance->data().clear();
    }
    catch(...)
    {}
}

WTLC_ShortcutResult WTLCAPI WTLC_createShortcut(_Inout_ WTLC_Instance * instance)
{
    try
    {
        if(!instance)
            return WTLC_SHORTCUT_MISSING_PARAMETERS;
        const WinToastLib::WinToast::ShortcutResult result = instance->data().createShortcut();
        switch(result)
        {
#define ADD_CASE(X) case WinToastLib::WinToast:: X : return WTLC_ ##X
        ADD_CASE(SHORTCUT_UNCHANGED);
        ADD_CASE(SHORTCUT_WAS_CHANGED);
        ADD_CASE(SHORTCUT_WAS_CREATED);
        ADD_CASE(SHORTCUT_MISSING_PARAMETERS);
        ADD_CASE(SHORTCUT_INCOMPATIBLE_OS);
        ADD_CASE(SHORTCUT_COM_INIT_FAILURE);
        ADD_CASE(SHORTCUT_CREATE_FAILED);
#undef ADD_CASE
        default:
            return static_cast<WTLC_ShortcutResult>(result);
        }
    }
    catch(...)
    {}
    return WTLC_SHORTCUT_CREATE_FAILED;
}

LPCWSTR WTLCAPI WTLC_appName(_In_ WTLC_Instance * instance)
{
    try
    {
        if(instance)
            return instance->data().appName().c_str();
    }
    catch(...)
    {}
    return NULL;
}

LPCWSTR WTLCAPI WTLC_appUserModelId(_In_ WTLC_Instance * instance)
{
    try
    {
        if(instance)
            return instance->data().appUserModelId().c_str();
    }
    catch(...)
    {}
    return NULL;
}

void WTLCAPI WTLC_setAppUserModelId(_Inout_ WTLC_Instance * instance, _In_ LPCWSTR aumi)
{
    try
    {
        if(instance)
            return instance->data().setAppUserModelId(aumi);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_setAppName(_Inout_ WTLC_Instance * instance, _In_ LPCWSTR appName)
{
    try
    {
        if(instance)
            return instance->data().setAppName(appName);
    }
    catch(...)
    {}
}

void WTLCAPI WTLC_setShortcutPolicy(_Inout_ WTLC_Instance * instance, _In_ WTLC_ShortcutPolicy policy)
{
    try
    {
        if(!instance)
            return;
        WinToastLib::WinToast::ShortcutPolicy _policy = WinToastLib::WinToast::SHORTCUT_POLICY_REQUIRE_CREATE;
        switch(policy)
        {
#define ADD_CASE(X) case WTLC_ ##X : _policy = WinToastLib::WinToast:: X ; break
        ADD_CASE(SHORTCUT_POLICY_IGNORE);
        ADD_CASE(SHORTCUT_POLICY_REQUIRE_NO_CREATE);
        ADD_CASE(SHORTCUT_POLICY_REQUIRE_CREATE);
#undef ADD_CASE
        default:
            _policy = static_cast<WinToastLib::WinToast::ShortcutPolicy>(policy);
            break;
        }
        instance->data().setShortcutPolicy(_policy);
    }
    catch(...)
    {}
}

UINT64 WTLCAPI WTLC_runtimeVersion(void)
{
    return WTLC_VERSION;
}
