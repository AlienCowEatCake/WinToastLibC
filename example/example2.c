/**
 * This example is licensed under a Creative Commons Zero v1.0 Universal License
 * https://creativecommons.org/publicdomain/zero/1.0/legalcode
 */

#include <stdio.h>
#include <string.h>

#include <Windows.h>
#include <Shlwapi.h>
#include <strsafe.h>

#include "wintoastlibc.h"

#define RETURN_GREATER_OR_EQUAL(osvi, major, minor, build) \
    do { \
        if((osvi).dwMajorVersion > (major)) \
            return TRUE; \
        if((osvi).dwMajorVersion < (major)) \
            return FALSE; \
        if((osvi).dwMinorVersion > (minor)) \
            return TRUE; \
        if((osvi).dwMinorVersion < (minor)) \
            return FALSE; \
        if((osvi).dwBuildNumber > (build)) \
            return TRUE; \
        if((osvi).dwBuildNumber < (build)) \
            return FALSE; \
        return TRUE; \
    } while(0)

static BOOL GreaterOrEqualRTL(DWORD major, DWORD minor, DWORD build)
{
    typedef LONG(WINAPI * RtlGetVersion_t)(PRTL_OSVERSIONINFOW);
    HMODULE hNtdll = GetModuleHandle(TEXT("ntdll.dll"));
    if(hNtdll)
    {
        RtlGetVersion_t RtlGetVersion_f = (RtlGetVersion_t)GetProcAddress(hNtdll, "RtlGetVersion");
        if(RtlGetVersion_f)
        {
            RTL_OSVERSIONINFOW rosvi;
            ZeroMemory(&rosvi, sizeof(rosvi));
            rosvi.dwOSVersionInfoSize = sizeof(rosvi);
            if(RtlGetVersion_f(&rosvi) == 0)
                RETURN_GREATER_OR_EQUAL(rosvi, major, minor, build);
            return FALSE;
        }
        return FALSE;
    }
    return FALSE;
}

static BOOL GreaterOrEqualK32(DWORD major, DWORD minor, DWORD build)
{
    OSVERSIONINFOW osvi;
    ZeroMemory(&osvi, sizeof(osvi));
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    if(GetVersionExW(&osvi))
        RETURN_GREATER_OR_EQUAL(osvi, major, minor, build);
    return FALSE;
}

static BOOL GreaterOrEqual(DWORD major, DWORD minor, DWORD build)
{
    return GreaterOrEqualRTL(major, minor, build) || GreaterOrEqualK32(major, minor, build);
}

static BOOL ValidAUMIDRequired(void)
{
    /* Show notifications without registered AUMID is available since Windows 10 build 1909 */
    return !GreaterOrEqual(10, 0, 18363);
}

static BOOL ShortcutAUMIDRequired(void)
{
    /* Show notifications without shortcut with AUMID is available since Windows 10 */
    return !GreaterOrEqual(10, 0, 0);
}

static BOOL RegisterBasicAUMID(LPCWSTR aumid, LPCWSTR displayName, LPCWSTR iconUri)
{
    /*
     * If you need more complex example, see https://hg.mozilla.org/mozilla-central/file/d9c24252e2b25e4b3eaecfbf6110c27539e47dcd/widget/windows/ToastNotification.cpp#l245
     *
     * HKEY_CURRENT_USER\Software\Classes\AppID\{GUID}                                                      DllSurrogate    : REG_SZ        = ""
     *                                   \AppUserModelId\{MOZ_TOAST_APP_NAME}PortableToast-{install hash}   CustomActivator : REG_SZ        = {GUID}
     *                                                                                                      DisplayName     : REG_EXPAND_SZ = {display name}
     *                                                                                                      IconUri         : REG_EXPAND_SZ = {icon path}
     *                                   \CLSID\{GUID}                                                      AppID           : REG_SZ        = {GUID}
     *                                                \InprocServer32                                       (Default)       : REG_SZ        = {notificationserver.dll path}
     */

    LONG ret;
    DWORD type;
    HKEY aumidRoot, aumidKey;

    aumidRoot = NULL;
    ret = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Classes\\AppUserModelId", 0, KEY_QUERY_VALUE, &aumidRoot);
    if(ret == ERROR_FILE_NOT_FOUND)
    {
        aumidRoot = NULL;
        ret = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Classes\\AppUserModelId", 0, NULL, 0, KEY_WRITE, NULL, &aumidRoot, NULL);
        if(ret != ERROR_SUCCESS)
        {
            RegCloseKey(aumidRoot);
            return FALSE;
        }
    }
    else if(ret != ERROR_SUCCESS)
    {
        return FALSE;
    }

    aumidKey = NULL;
    ret = RegOpenKeyExW(aumidRoot, aumid, 0, KEY_QUERY_VALUE, &aumidKey);
    if(ret == ERROR_FILE_NOT_FOUND)
    {
        aumidKey = NULL;
        ret = RegCreateKeyExW(aumidRoot, aumid, 0, NULL, 0, KEY_WRITE, NULL, &aumidKey, NULL);
        if(ret != ERROR_SUCCESS)
        {
            RegCloseKey(aumidKey);
            RegCloseKey(aumidRoot);
            return FALSE;
        }
    }
    else if(ret != ERROR_SUCCESS)
    {
        RegCloseKey(aumidRoot);
        return FALSE;
    }

    if(RegQueryValueExW(aumidKey, L"DisplayName", 0, &type, NULL, NULL) != ERROR_SUCCESS || type != REG_SZ)
        RegSetValueExW(aumidKey, L"DisplayName", 0, REG_SZ, (LPBYTE)displayName, (DWORD)((wcslen(displayName) + 1) * sizeof(wchar_t)));
    if(RegQueryValueExW(aumidKey, L"IconUri", 0, &type, NULL, NULL) != ERROR_SUCCESS || type != REG_SZ)
        RegSetValueExW(aumidKey, L"IconUri", 0, REG_SZ, (LPBYTE)iconUri, (DWORD)((wcslen(iconUri) + 1) * sizeof(wchar_t)));

    RegCloseKey(aumidKey);
    RegCloseKey(aumidRoot);
    return TRUE;
}

typedef struct _ToastHandlerContext
{
    HANDLE event;
    WCHAR message[128];
} ToastHandlerContext;

static void WTLCAPI OnToastActivated(void * userData)
{
    ToastHandlerContext * ctx = (ToastHandlerContext *)(userData);
    StringCbCopyW(ctx->message, sizeof(ctx->message), L"Toast Activated");
    SetEvent(ctx->event);
}

static void WTLCAPI OnToastActivatedAction(void * userData, int actionIndex)
{
    ToastHandlerContext * ctx = (ToastHandlerContext *)(userData);
    StringCbPrintfW(ctx->message, sizeof(ctx->message), L"Toast Activated with Action #%d", actionIndex);
    SetEvent(ctx->event);
}

static void WTLCAPI OnToastActivatedInput(void * userData, LPCWSTR response)
{
    ToastHandlerContext * ctx = (ToastHandlerContext *)(userData);
    if(response)
    {
        StringCbCopyW(ctx->message, sizeof(ctx->message), L"Toast Activated with Input: ");
        StringCbCatW(ctx->message, sizeof(ctx->message), response);
    }
    else
    {
        StringCbCatW(ctx->message, sizeof(ctx->message), L"Toast Activated with NULL Input");
    }
    SetEvent(ctx->event);
}

static void WTLCAPI OnToastDismissed(void * userData, WTLC_DismissalReason state)
{
    ToastHandlerContext * ctx = (ToastHandlerContext *)(userData);
    WCHAR reason[32];
    switch(state)
    {
    case WTLC_DismissalReason_UserCanceled:
        StringCbCopyW(reason, sizeof(reason), L"UserCanceled");
        break;
    case WTLC_DismissalReason_ApplicationHidden:
        StringCbCopyW(reason, sizeof(reason), L"ApplicationHidden");
        break;
    case WTLC_DismissalReason_TimedOut:
        StringCbCopyW(reason, sizeof(reason), L"TimedOut");
        break;
    default:
        StringCbPrintfW(reason, sizeof(reason), L"Invalid (%d)", state);
        break;
    }
    StringCbCopyW(ctx->message, sizeof(ctx->message), L"Toast Dismissed with DismissalReason = ");
    StringCbCatW(ctx->message, sizeof(ctx->message), reason);
    SetEvent(ctx->event);
}

static void WTLCAPI OnToastFailed(void * userData)
{
    ToastHandlerContext * ctx = (ToastHandlerContext *)(userData);
    StringCbCopyW(ctx->message, sizeof(ctx->message), L"Toast Failed");
    SetEvent(ctx->event);
}

int main(int argc, char ** argv)
{
    WTLC_Instance * instance = NULL;
    WTLC_Template * templ = NULL;
    WTLC_Handler handler;
    WTLC_Error error = WTLC_Error_NoError;
    LPCWSTR imagePath = L"C:\\ProgramData\\Microsoft\\User Account Pictures\\guest.png";
    BOOL withImage = PathFileExistsW(imagePath);
    ToastHandlerContext handlerContext;
    const ULONGLONG loopTimeout = 31000; /* 31 seconds */
    ULONGLONG loopStartTime;

    if(!WTLC_isCompatible())
    {
        MessageBoxW(NULL, L"Your system is not compatible!", L"Error", MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }

    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        MessageBoxW(NULL, L"COM library initialization failed!", L"Error", MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }

    instance = WTLC_Instance_Create();
    if(!instance)
    {
        MessageBoxW(NULL, L"WinToast instance creation failed!", L"Error", MB_OK | MB_ICONERROR);
        CoUninitialize();
        return EXIT_FAILURE;
    }

    WTLC_setAppName(instance, L"Example");
    if(ShortcutAUMIDRequired())
        WTLC_setAppUserModelId(instance, L"Microsoft.Windows.Explorer");
    else if(RegisterBasicAUMID(L"ExampleToast", L"Example", imagePath))
        WTLC_setAppUserModelId(instance, L"ExampleToast");
    else if(ValidAUMIDRequired())
        WTLC_setAppUserModelId(instance, L"Microsoft.Windows.Explorer");
    else
        WTLC_setAppUserModelId(instance, L"Example");
    WTLC_setShortcutPolicy(instance, WTLC_SHORTCUT_POLICY_IGNORE);

    if(!WTLC_initialize(instance, &error))
    {
        MessageBoxW(NULL, WTLC_strerror(error), L"Error", MB_OK | MB_ICONERROR);
        WTLC_Instance_Destroy(instance);
        CoUninitialize();
        return EXIT_FAILURE;
    }

    templ = WTLC_Template_Create(withImage ? WTLC_TemplateType_ImageAndText02 : WTLC_TemplateType_Text02);
    WTLC_Template_setTextField(templ, L"HELLO, WORLD!", WTLC_TextField_FirstLine);
    WTLC_Template_setSecondLine(templ, L"This is a test notification");
    WTLC_Template_setAudioOption(templ, WTLC_AudioOption_Default);
    WTLC_Template_setExpiration(templ, 30000);
    if(withImage)
        WTLC_Template_setImagePath(templ, imagePath);
    /* Actions and Input are mutually exclusive */
    /* WTLC_Template_addInput(templ); */
    WTLC_Template_addAction(templ, L"Action #0");
    WTLC_Template_addAction(templ, L"Action #1");

    ZeroMemory(&handlerContext, sizeof(handlerContext));
    handlerContext.event = CreateEventW(NULL, TRUE, FALSE, NULL);
    if(!handlerContext.event)
    {
        const DWORD lastError = GetLastError();
        LPWSTR lastErrorMsgBuf = NULL;
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lastErrorMsgBuf, 0, NULL);
        MessageBoxW(NULL, lastErrorMsgBuf, L"Error", MB_OK | MB_ICONERROR);
        LocalFree(lastErrorMsgBuf);
        WTLC_Template_Destroy(templ);
        WTLC_Instance_Destroy(instance);
        CoUninitialize();
        return EXIT_FAILURE;
    }

    ZeroMemory(&handler, sizeof(handler));
    handler.version = WTLC_VERSION;
    handler.userData = &handlerContext;
    handler.toastActivated = &OnToastActivated;
    handler.toastActivatedAction = &OnToastActivatedAction;
    handler.toastActivatedInput = &OnToastActivatedInput;
    handler.toastDismissed = &OnToastDismissed;
    handler.toastFailed = &OnToastFailed;
    if(WTLC_showToastEx(instance, templ, &handler, &error) < 0)
    {
        MessageBoxW(NULL, WTLC_strerror(error), L"Error", MB_OK | MB_ICONERROR);
        CloseHandle(handlerContext.event);
        WTLC_Template_Destroy(templ);
        WTLC_Instance_Destroy(instance);
        CoUninitialize();
        return EXIT_FAILURE;
    }

    loopStartTime = GetTickCount64();
    while(TRUE)
    {
        const ULONGLONG loopElapsedTime = GetTickCount64() - loopStartTime;
        DWORD waitTime = 0;
        DWORD waitResult = 0;

        if(loopElapsedTime >= loopTimeout)
        {
            MessageBoxW(NULL, L"Timeout was reached without callback", L"Error", MB_OK | MB_ICONERROR);
            break;
        }

        waitTime = (DWORD)(loopTimeout - loopElapsedTime);

        /* Use MsgWaitForMultipleObjects to wait for messages or event */
        waitResult = MsgWaitForMultipleObjects(1, &handlerContext.event, FALSE, waitTime, QS_ALLINPUT);

        if(waitResult == WAIT_OBJECT_0)
        {
            /* Event object is signaled */
            WCHAR message[192];
            StringCbCopyW(message, sizeof(message), L"Callback was called with message:\n\n");
            StringCbCatW(message, sizeof(message), handlerContext.message);
            MessageBoxW(NULL, message, L"Handler", MB_OK | MB_ICONASTERISK);
            break;
        }
        else if(waitResult == WAIT_OBJECT_0 + 1)
        {
            /* There are messages in queue */
            BOOL loopIsDone = FALSE;
            MSG msg;
            while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if(msg.message == WM_QUIT)
                {
                    loopIsDone = TRUE;
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            if(loopIsDone)
                break;
        }
        else if(waitResult == WAIT_TIMEOUT)
        {
            MessageBoxW(NULL, L"Timeout was reached without callback", L"Error", MB_OK | MB_ICONERROR);
            break;
        }
        else if(waitResult == WAIT_FAILED)
        {
            const DWORD lastError = GetLastError();
            LPWSTR lastErrorMsgBuf = NULL;
            FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lastErrorMsgBuf, 0, NULL);
            MessageBoxW(NULL, lastErrorMsgBuf, L"Error", MB_OK | MB_ICONERROR);
            LocalFree(lastErrorMsgBuf);
            break;
        }
        else
        {
            WCHAR message[64];
            StringCbPrintfW(message, sizeof(message), L"Unexpected waitResult = 0x%08lX", waitResult);
            MessageBoxW(NULL, message, L"Error", MB_OK | MB_ICONERROR);
            break;
        }
    }

    CloseHandle(handlerContext.event);
    WTLC_Template_Destroy(templ);
    WTLC_Instance_Destroy(instance);
    CoUninitialize();
    return EXIT_SUCCESS;
}

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, INT nCmdShow)
{
    return main(0, NULL);
}
