#pragma once

#include "GeneralUtil.hpp"
#include "IPackageHandler.hpp"
#include "MsixRequest.hpp"

namespace MsixCoreLib
{
    enum AutoPlayType
    {
        InvalidAutoPlayType = 0,
        DesktopAppxContent,
        DesktopAppxDevice
    };

    /// the autoplay structure
    struct AutoPlayObject
    {
        std::wstring id;
        std::wstring action;
        std::wstring handleEvent;
        std::wstring provider;
        std::wstring defaultIcon;
        std::wstring appUserModelId;
        std::wstring generatedProgId;
        std::wstring generatedhandlerName;
        std::wstring dropTargetHandler;
        std::wstring parameters;
        std::wstring hwEventHandler;
        std::wstring initCmdLine;
        AutoPlayType autoPlayType;
    };

    class AutoPlay : IPackageHandler
    {
    public:
        HRESULT ExecuteForAddRequest();

        HRESULT ExecuteForRemoveRequest();

        static const PCWSTR HandlerName;
        static HRESULT CreateHandler(_In_ MsixRequest* msixRequest, _Out_ IPackageHandler** instance);
    private:
        MsixRequest * m_msixRequest = nullptr;
        std::vector<AutoPlayObject> m_autoPlay;

        AutoPlay() {}
        AutoPlay(_In_ MsixRequest* msixRequest) : m_msixRequest(msixRequest) {}

        HRESULT ParseManifest();

        HRESULT ProcessAutoPlayForAdd(AutoPlayObject& autoPlayObject);

        HRESULT ProcessAutoPlayForRemove(AutoPlayObject& autoPlayObject);

        HRESULT GenerateProgId(_In_ std::wstring categoryName, _In_opt_ std::wstring subCategory, _Out_ std::wstring & generatedProgId);

        HRESULT GenerateHandlerName(_In_ LPWSTR type, _In_ const std::wstring handlerNameSeed, _Out_ std::wstring & generatedHandlerName);

        HRESULT BuildVerbKey(_In_ std::wstring generatedProgId, _In_ std::wstring id, _Out_ RegistryKey & verbRootKey);

    };
}