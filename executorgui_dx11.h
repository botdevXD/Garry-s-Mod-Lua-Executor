#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

typedef HRESULT(APIENTRY* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
IDXGISwapChainPresent oIDXGISwapChainPresent;

typedef void(APIENTRY* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
ID3D11DrawIndexed oID3D11DrawIndexed;

//D3D11 Methods Table:
//[0] QueryInterface
//[1] AddRef
//[2] Release
//[3] SetPrivateData
//[4] SetPrivateDataInterface
//[5] GetPrivateData
//[6] GetParent
//[7] GetDevice
//[8] Present
//[9] GetBuffer
//[10] SetFullscreenState
//[11] GetFullscreenState
//[12] GetDesc
//[13] ResizeBuffers
//[14] ResizeTarget
//[15] GetContainingOutput
//[16] GetFrameStatistics
//[17] GetLastPresentCount
//[18] QueryInterface
//[19] AddRef
//[20] Release
//[21] CreateBuffer
//[22] CreateTexture1D
//[23] CreateTexture2D
//[24] CreateTexture3D
//[25] CreateShaderResourceView
//[26] CreateUnorderedAccessView
//[27] CreateRenderTargetView
//[28] CreateDepthStencilView
//[29] CreateInputLayout
//[30] CreateVertexShader
//[31] CreateGeometryShader
//[32] CreateGeometryShaderWithStreamOutput
//[33] CreatePixelShader
//[34] CreateHullShader
//[35] CreateDomainShader
//[36] CreateComputeShader
//[37] CreateClassLinkage
//[38] CreateBlendState
//[39] CreateDepthStencilState
//[40] CreateRasterizerState
//[41] CreateSamplerState
//[42] CreateQuery
//[43] CreatePredicate
//[44] CreateCounter
//[45] CreateDeferredContext
//[46] OpenSharedResource
//[47] CheckFormatSupport
//[48] CheckMultisampleQualityLevels
//[49] CheckCounterInfo
//[50] CheckCounter
//[51] CheckFeatureSupport
//[52] GetPrivateData
//[53] SetPrivateData
//[54] SetPrivateDataInterface
//[55] GetFeatureLevel
//[56] GetCreationFlags
//[57] GetDeviceRemovedReason
//[58] GetImmediateContext
//[59] SetExceptionMode
//[60] GetExceptionMode
//[61] QueryInterface
//[62] AddRef
//[63] Release
//[64] GetDevice
//[65] GetPrivateData
//[66] SetPrivateData
//[67] SetPrivateDataInterface
//[68] SetConstantBuffers
//[69] SetShaderResources
//[70] SetShader
//[71] SetSamplers
//[72] SetShader
//[73] DrawIndexed
//[74] Draw
//[75] Map
//[76] Unmap
//[77] SetConstantBuffers
//[78] IASetInputLayout
//[79] IASetVertexBuffers
//[80] IASetIndexBuffer
//[81] DrawIndexedInstanced
//[82] DrawInstanced
//[83] SetConstantBuffers
//[84] SetShader
//[85] IASetPrimitiveTopology
//[86] SetShaderResources
//[87] SetSamplers
//[88] Begin
//[89] End
//[90] GetData
//[91] SetPredication
//[92] SetShaderResources
//[93] SetSamplers
//[94] OMSetRenderTargets
//[95] OMSetRenderTargetsAndUnorderedAccessViews
//[96] OMSetBlendState
//[97] OMSetDepthStencilState
//[98] SOSetTargets
//[99] DrawAuto
//[100] DrawIndexedInstancedIndirect
//[101] DrawInstancedIndirect
//[102] Dispatch
//[103] DispatchIndirect
//[104] RSSetState
//[105] RSSetViewports
//[106] RSSetScissorRects
//[107] CopySubresourceRegion
//[108] CopyResource
//[109] UpdateSubresource
//[110] CopyStructureCount
//[111] ClearRenderTargetView
//[112] ClearUnorderedAccessViewUint
//[113] ClearUnorderedAccessViewFloat
//[114] ClearDepthStencilView
//[115] GenerateMips
//[116] SetResourceMinLOD
//[117] GetResourceMinLOD
//[118] ResolveSubresource
//[119] ExecuteCommandList
//[120] SetShaderResources
//[121] SetShader
//[122] SetSamplers
//[123] SetConstantBuffers
//[124] SetShaderResources
//[125] SetShader
//[126] SetSamplers
//[127] SetConstantBuffers
//[128] SetShaderResources
//[129] CSSetUnorderedAccessViews
//[130] SetShader
//[131] SetSamplers
//[132] SetConstantBuffers
//[133] VSGetConstantBuffers
//[134] PSGetShaderResources
//[135] PSGetShader
//[136] PSGetSamplers
//[137] VSGetShader
//[138] PSGetConstantBuffers
//[139] IAGetInputLayout
//[140] IAGetVertexBuffers
//[141] IAGetIndexBuffer
//[142] GSGetConstantBuffers
//[143] GSGetShader
//[144] IAGetPrimitiveTopology
//[145] VSGetShaderResources
//[146] VSGetSamplers
//[147] GetPredication
//[148] GSGetShaderResources
//[149] GSGetSamplers
//[150] OMGetRenderTargets
//[151] OMGetRenderTargetsAndUnorderedAccessViews
//[152] OMGetBlendState
//[153] OMGetDepthStencilState
//[154] SOGetTargets
//[155] RSGetState
//[156] RSGetViewports
//[157] RSGetScissorRects
//[158] HSGetShaderResources
//[159] HSGetShader
//[160] HSGetSamplers
//[161] HSGetConstantBuffers
//[162] DSGetShaderResources
//[163] DSGetShader
//[164] DSGetSamplers
//[165] DSGetConstantBuffers
//[166] CSGetShaderResources
//[167] CSGetUnorderedAccessViews
//[168] CSGetShader
//[169] CSGetSamplers
//[170] CSGetConstantBuffers
//[171] ClearState
//[172] Flush
//[173] GetType
//[174] GetContextFlags
//[175] FinishCommandList
//[176] CopySubresourceRegion1
//[177] UpdateSubresource1
//[178] DiscardResource
//[179] DiscardView
//[180] SetConstantBuffers1
//[181] SetConstantBuffers1
//[182] SetConstantBuffers1
//[183] SetConstantBuffers1
//[184] SetConstantBuffers1
//[185] SetConstantBuffers1
//[186] VSGetConstantBuffers1
//[187] HSGetConstantBuffers1
//[188] DSGetConstantBuffers1
//[189] GSGetConstantBuffers1
//[190] PSGetConstantBuffers1
//[191] CSGetConstantBuffers1
//[192] SwapDeviceContextState
//[193] ClearView
//[194] DiscardView1
//[195] UpdateTileMappings
//[196] CopyTileMappings
//[197] CopyTiles
//[198] UpdateTiles
//[199] ResizeTilePool
//[200] TiledResourceBarrier
//[201] IsAnnotationEnabled
//[202] SetMarkerInt
//[203] BeginEventInt
//[204] EndEvent

#include "DirectX11.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"
#include "dllmain.hpp"

bool ShowMenu = false;
bool ImGui_Initialised = false;

namespace Process {
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	HMODULE Module;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}

namespace DirectX11Interface {
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(Process::WndProc, hwnd, uMsg, wParam, lParam);
}

HRESULT APIENTRY MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!ImGui_Initialised) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DirectX11Interface::Device))) {
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

			DirectX11Interface::Device->GetImmediateContext(&DirectX11Interface::DeviceContext);

			DXGI_SWAP_CHAIN_DESC Desc;
			pSwapChain->GetDesc(&Desc);
			WindowHwnd = Desc.OutputWindow;

			ID3D11Texture2D* BackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			DirectX11Interface::Device->CreateRenderTargetView(BackBuffer, NULL, &DirectX11Interface::RenderTargetView);
			BackBuffer->Release();

			ImGui_ImplWin32_Init(WindowHwnd);
			ImGui_ImplDX11_Init(DirectX11Interface::Device, DirectX11Interface::DeviceContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			ImGui::GetIO().ImeWindowHandle = Process::Hwnd;
			Process::WndProc = (WNDPROC)SetWindowLongPtr(Process::Hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			ImGui_Initialised = true;
		}
	}
	if (GetAsyncKeyState(VK_INSERT) & 1) ShowMenu = !ShowMenu;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = ShowMenu;
	if (ShowMenu == true) {
		
		ImGui::Begin("Menu", &ShowMenu);

		static char buf[258] = "Enter text here";
		ImGui::SetNextItemWidth(300);

		ImGui::InputText("Input", buf, IM_ARRAYSIZE(buf));

		if (ImGui::Button("Execute")) {
			executor::executeLua(buf);
		}

		ImGui::SetWindowSize(ImVec2(400, 400));

		ImGui::End();

	}
	ImGui::EndFrame();
	ImGui::Render();
	DirectX11Interface::DeviceContext->OMSetRenderTargets(1, &DirectX11Interface::RenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
}

void APIENTRY MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {

}

DWORD WINAPI MainThread(LPVOID lpParameter) {
	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetCurrentProcessId() == ForegroundWindowProcessID) {

			Process::ID = GetCurrentProcessId();
			Process::Handle = GetCurrentProcess();
			Process::Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Process::Hwnd, &TempRect);
			Process::WindowWidth = TempRect.right - TempRect.left;
			Process::WindowHeight = TempRect.bottom - TempRect.top;

			char TempTitle[MAX_PATH];
			GetWindowText(Process::Hwnd, (LPWSTR)TempTitle, sizeof(TempTitle));
			Process::Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Process::Hwnd, (LPWSTR)TempClassName, sizeof(TempClassName));
			Process::ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Process::Handle, NULL, (LPWSTR)TempPath, sizeof(TempPath));
			Process::Path = TempPath;

			WindowFocus = true;
		}
	}
	bool InitHook = false;
	while (InitHook == false) {
		if (DirectX11::Init() == true) {
			CreateHook(8, (void**)&oIDXGISwapChainPresent, MJPresent);
			CreateHook(12, (void**)&oID3D11DrawIndexed, MJDrawIndexed);
			InitHook = true;
		}
	}
	return 0;
}

namespace execution_gui {
	void Init() {
		CreateThread(0, 0, MainThread, 0, 0, 0);
	}
}