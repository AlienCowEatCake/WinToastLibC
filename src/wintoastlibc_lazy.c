/**
 * Copyright (c) 2022 Peter Zhigalov <peter.zhigalov@gmail.com>
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

#if !defined (WTLC_DLLNAME)
#define WTLC_DLLNAME "wintoastlibc.dll"
#endif

static HMODULE s_module = NULL;

#define LOAD(X) \
    HMODULE X = s_module; \
    if(!X) \
    { \
        X = LoadLibraryA(WTLC_DLLNAME); \
        if(!X) \
        { \
            MessageBoxA(NULL, "FAILED TO LOAD " WTLC_DLLNAME, "Error", MB_OK | MB_ICONERROR); \
            abort(); \
        } \
        s_module = X; \
    }

#define SYMCHECK(NAME, SYM) \
    if(!SYM) \
    { \
        MessageBoxA(NULL, "FAILED TO FIND PROC " NAME " IN " WTLC_DLLNAME, "Error", MB_OK | MB_ICONERROR); \
        abort(); \
    }

#define FORWARD0(NAME, RTYPE) \
    RTYPE WTLCAPI NAME (void) { \
        typedef RTYPE (WTLCAPI * t)(void); \
        t f; \
        LOAD(h) \
        f = (t)GetProcAddress(h, #NAME); \
        SYMCHECK(#NAME, f) \
        return f(); \
    }
#define FORWARD1(NAME, RTYPE, A1TYPE) \
    RTYPE WTLCAPI NAME (A1TYPE a1) { \
        typedef RTYPE (WTLCAPI * t)(A1TYPE); \
        t f; \
        LOAD(h) \
        f = (t)GetProcAddress(h, #NAME); \
        SYMCHECK(#NAME, f) \
        return f(a1); \
    }
#define FORWARD2(NAME, RTYPE, A1TYPE, A2TYPE) \
    RTYPE WTLCAPI NAME (A1TYPE a1, A2TYPE a2) { \
        typedef RTYPE (WTLCAPI * t)(A1TYPE, A2TYPE); \
        t f; \
        LOAD(h) \
        f = (t)GetProcAddress(h, #NAME); \
        SYMCHECK(#NAME, f) \
        return f(a1, a2); \
    }
#define FORWARD3(NAME, RTYPE, A1TYPE, A2TYPE, A3TYPE) \
    RTYPE WTLCAPI NAME (A1TYPE a1, A2TYPE a2, A3TYPE a3) { \
        typedef RTYPE (WTLCAPI * t)(A1TYPE, A2TYPE, A3TYPE); \
        t f; \
        LOAD(h) \
        f = (t)GetProcAddress(h, #NAME); \
        SYMCHECK(#NAME, f) \
        return f(a1, a2, a3); \
    }
#define FORWARD8(NAME, RTYPE, A1TYPE, A2TYPE, A3TYPE, A4TYPE, A5TYPE, A6TYPE, A7TYPE, A8TYPE) \
    RTYPE WTLCAPI NAME (A1TYPE a1, A2TYPE a2, A3TYPE a3, A4TYPE a4, A5TYPE a5, A6TYPE a6, A7TYPE a7, A8TYPE a8) { \
        typedef RTYPE (WTLCAPI * t)(A1TYPE, A2TYPE, A3TYPE, A4TYPE, A5TYPE, A6TYPE, A7TYPE, A8TYPE); \
        t f; \
        LOAD(h) \
        f = (t)GetProcAddress(h, #NAME); \
        SYMCHECK(#NAME, f) \
        return f(a1, a2, a3, a4, a5, a6, a7, a8); \
    }

FORWARD1(WTLC_Template_Create, WTLC_Template *, WTLC_TemplateType)
FORWARD1(WTLC_Template_Destroy, void, WTLC_Template *)
FORWARD2(WTLC_Template_setFirstLine, void, WTLC_Template *, LPCWSTR)
FORWARD2(WTLC_Template_setSecondLine, void, WTLC_Template *, LPCWSTR)
FORWARD2(WTLC_Template_setThirdLine, void, WTLC_Template *, LPCWSTR)
FORWARD3(WTLC_Template_setTextField, void, WTLC_Template *, LPCWSTR, WTLC_TextField)
FORWARD2(WTLC_Template_setAttributionText, void, WTLC_Template *, LPCWSTR)
FORWARD2(WTLC_Template_setImagePath, void, WTLC_Template *, LPCWSTR)
FORWARD2(WTLC_Template_setAudioSystemFile, void, WTLC_Template *, WTLC_AudioSystemFile)
FORWARD2(WTLC_Template_setAudioPath, void, WTLC_Template *, LPCWSTR)
FORWARD2(WTLC_Template_setAudioOption, void, WTLC_Template *, WTLC_AudioOption)
FORWARD2(WTLC_Template_setDuration, void, WTLC_Template *, WTLC_Duration)
FORWARD2(WTLC_Template_setExpiration, void, WTLC_Template *, INT64)
FORWARD2(WTLC_Template_setScenario, void, WTLC_Template *, WTLC_Scenario)
FORWARD2(WTLC_Template_addAction, void, WTLC_Template *, LPCWSTR)
FORWARD1(WTLC_Template_textFieldsCount, size_t, WTLC_Template *)
FORWARD1(WTLC_Template_actionsCount, size_t, WTLC_Template *)
FORWARD1(WTLC_Template_hasImage, BOOL, WTLC_Template *)
FORWARD2(WTLC_Template_textField, LPCWSTR, WTLC_Template *, WTLC_TextField)
FORWARD2(WTLC_Template_actionLabel, LPCWSTR, WTLC_Template *, size_t);
FORWARD1(WTLC_Template_imagePath, LPCWSTR, WTLC_Template *);
FORWARD1(WTLC_Template_audioPath, LPCWSTR, WTLC_Template *);
FORWARD1(WTLC_Template_attributionText, LPCWSTR, WTLC_Template *);
FORWARD1(WTLC_Template_scenario, LPCWSTR, WTLC_Template *);
FORWARD1(WTLC_Template_expiration, INT64, WTLC_Template *);
FORWARD1(WTLC_Template_type, WTLC_TemplateType, WTLC_Template *);
FORWARD1(WTLC_Template_audioOption, WTLC_AudioOption, WTLC_Template *);
FORWARD1(WTLC_Template_duration, WTLC_Duration, WTLC_Template *);
FORWARD0(WTLC_Instance_Create, WTLC_Instance *);
FORWARD1(WTLC_Instance_Destroy, void, WTLC_Instance *);
FORWARD0(WTLC_isCompatible, BOOL);
FORWARD0(WTLC_isSupportingModernFeatures, BOOL);
FORWARD1(WTLC_strerror, LPCWSTR, WTLC_Error);
FORWARD2(WTLC_initialize, BOOL, WTLC_Instance *, WTLC_Error *);
FORWARD1(WTLC_isInitialized, BOOL, WTLC_Instance *);
FORWARD2(WTLC_hideToast, BOOL, WTLC_Instance *, INT64);
FORWARD8(WTLC_showToast, INT64, WTLC_Instance *, WTLC_Template *, void *, WTLC_CB_toastActivated, WTLC_CB_toastActivatedAction, WTLC_CB_toastDismissed, WTLC_CB_toastFailed, WTLC_Error *);
FORWARD1(WTLC_clear, void, WTLC_Instance *);
FORWARD1(WTLC_createShortcut, WTLC_ShortcutResult, WTLC_Instance *);
FORWARD1(WTLC_appName, LPCWSTR, WTLC_Instance *);
FORWARD1(WTLC_appUserModelId, LPCWSTR, WTLC_Instance *);
FORWARD2(WTLC_setAppUserModelId, void, WTLC_Instance *, LPCWSTR);
FORWARD2(WTLC_setAppName, void, WTLC_Instance *, LPCWSTR);
FORWARD2(WTLC_setShortcutPolicy, void, WTLC_Instance *, WTLC_ShortcutPolicy);
