#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

typedef HRESULT(APIENTRY* EndScene) (IDirect3DDevice9*);
EndScene oEndScene = NULL;

typedef HRESULT(APIENTRY* Present) (IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
Present oPresent = NULL;

typedef HRESULT(APIENTRY* DrawIndexedPrimitive)(IDirect3DDevice9*, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
DrawIndexedPrimitive oDrawIndexedPrimitive = NULL;

typedef HRESULT(APIENTRY* DrawPrimitive)(IDirect3DDevice9*, D3DPRIMITIVETYPE, UINT, UINT);
DrawPrimitive oDrawPrimitive = NULL;

typedef HRESULT(APIENTRY* SetTexture)(IDirect3DDevice9*, DWORD, IDirect3DBaseTexture9*);
SetTexture oSetTexture = NULL;

typedef HRESULT(APIENTRY* Reset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
Reset oReset = NULL;

typedef HRESULT(APIENTRY* SetStreamSource)(IDirect3DDevice9*, UINT, IDirect3DVertexBuffer9*, UINT, UINT);
SetStreamSource oSetStreamSource = NULL;

typedef HRESULT(APIENTRY* SetVertexDeclaration)(IDirect3DDevice9*, IDirect3DVertexDeclaration9*);
SetVertexDeclaration oSetVertexDeclaration = NULL;

typedef HRESULT(APIENTRY* SetVertexShaderConstantF)(IDirect3DDevice9*, UINT, const float*, UINT);
SetVertexShaderConstantF oSetVertexShaderConstantF = NULL;

typedef HRESULT(APIENTRY* SetVertexShader)(IDirect3DDevice9*, IDirect3DVertexShader9*);
SetVertexShader oSetVertexShader = NULL;

typedef HRESULT(APIENTRY* SetPixelShader)(IDirect3DDevice9*, IDirect3DPixelShader9*);
SetPixelShader oSetPixelShader = NULL;

//D3D9 Methods Table :
//[0] QueryInterface
//[1] AddRef
//[2] Release
//[3] TestCooperativeLevel
//[4] GetAvailableTextureMem
//[5] EvictManagedResources
//[6] GetDirect3D
//[7] GetDeviceCaps
//[8] GetDisplayMode
//[9] GetCreationParameters
//[10] SetCursorProperties
//[11] SetCursorPosition
//[12] ShowCursor
//[13] CreateAdditionalSwapChain
//[14] GetSwapChain
//[15] GetNumberOfSwapChains
//[16] Reset
//[17] Present
//[18] GetBackBuffer
//[19] GetRasterStatus
//[20] SetDialogBoxMode
//[21] SetGammaRamp
//[22] GetGammaRamp
//[23] CreateTexture
//[24] CreateVolumeTexture
//[25] CreateCubeTexture
//[26] CreateVertexBuffer
//[27] CreateIndexBuffer
//[28] CreateRenderTarget
//[29] CreateDepthStencilSurface
//[30] UpdateSurface
//[31] UpdateTexture
//[32] GetRenderTargetData
//[33] GetFrontBufferData
//[34] StretchRect
//[35] ColorFill
//[36] CreateOffscreenPlainSurface
//[37] SetRenderTarget
//[38] GetRenderTarget
//[39] SetDepthStencilSurface
//[40] GetDepthStencilSurface
//[41] BeginScene
//[42] EndScene
//[43] Clear
//[44] SetTransform
//[45] GetTransform
//[46] MultiplyTransform
//[47] SetViewport
//[48] GetViewport
//[49] SetMaterial
//[50] GetMaterial
//[51] SetLight
//[52] GetLight
//[53] LightEnable
//[54] GetLightEnable
//[55] SetClipPlane
//[56] GetClipPlane
//[57] SetRenderState
//[58] GetRenderState
//[59] CreateStateBlock
//[60] BeginStateBlock
//[61] EndStateBlock
//[62] SetClipStatus
//[63] GetClipStatus
//[64] GetTexture
//[65] SetTexture
//[66] GetTextureStageState
//[67] SetTextureStageState
//[68] GetSamplerState
//[69] SetSamplerState
//[70] ValidateDevice
//[71] SetPaletteEntries
//[72] GetPaletteEntries
//[73] SetCurrentTexturePalette
//[74] GetCurrentTexturePalette
//[75] SetScissorRect
//[76] GetScissorRect
//[77] SetSoftwareVertexProcessing
//[78] GetSoftwareVertexProcessing
//[79] SetNPatchMode
//[80] GetNPatchMode
//[81] DrawPrimitive
//[82] DrawIndexedPrimitive
//[83] DrawPrimitiveUP
//[84] DrawIndexedPrimitiveUP
//[85] ProcessVertices
//[86] CreateVertexDeclaration
//[87] SetVertexDeclaration
//[88] GetVertexDeclaration
//[89] SetFVF
//[90] GetFVF
//[91] CreateVertexShader
//[92] SetVertexShader
//[93] GetVertexShader
//[94] SetVertexShaderConstantF
//[95] GetVertexShaderConstantF
//[96] SetVertexShaderConstantI
//[97] GetVertexShaderConstantI
//[98] SetVertexShaderConstantB
//[99] GetVertexShaderConstantB
//[100] SetStreamSource
//[101] GetStreamSource
//[102] SetStreamSourceFreq
//[103] GetStreamSourceFreq
//[104] SetIndices
//[105] GetIndices
//[106] CreatePixelShader
//[107] SetPixelShader
//[108] GetPixelShader
//[109] SetPixelShaderConstantF
//[110] GetPixelShaderConstantF
//[111] SetPixelShaderConstantI
//[112] GetPixelShaderConstantI
//[113] SetPixelShaderConstantB
//[114] GetPixelShaderConstantB
//[115] DrawRectPatch
//[116] DrawTriPatch
//[117] DeletePatch
//[118] CreateQuery

#include "DirectX9.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"
#include "TextEditor.h"
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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(Process::WndProc, hwnd, uMsg, wParam, lParam);
}

HRESULT APIENTRY MJEndScene(IDirect3DDevice9* pDevice) {
	if (!ImGui_Initialised) {
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui_ImplWin32_Init(Process::Hwnd);
		ImGui_ImplDX9_Init(pDevice);
		ImGui_ImplDX9_CreateDeviceObjects();
		ImGui::GetIO().ImeWindowHandle = Process::Hwnd;
		Process::WndProc = (WNDPROC)SetWindowLongPtr(Process::Hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
		ImGui_Initialised = true;
	}
	if (GetAsyncKeyState(VK_INSERT) & 1) ShowMenu = !ShowMenu;
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = ShowMenu;
	if (ShowMenu == true) {
		ImGui::Begin("Menu", &ShowMenu);

		static TextEditor editor;
		auto lang = TextEditor::LanguageDefinition::Lua();
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
		editor.SetShowWhitespaces(false);
		editor.Render("Script executor", ImVec2(800, 750));
		editor.SetReadOnly(false);

		editor.SetLanguageDefinition(lang);

		ImGui::CaptureKeyboardFromApp(true);
		ImGui::CaptureMouseFromApp(true);

		if (ImGui::Button("Execute")){
			executor::executeLua(editor.GetText());
		}

		ImGui::SetWindowSize(ImVec2(800, 800));

		ImGui::End();
	}
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	return oEndScene(pDevice);
}

HRESULT APIENTRY MJPresent(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion) {
	return oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT APIENTRY MJDrawIndexedPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
	return oDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT APIENTRY MJDrawPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) {
	return oDrawPrimitive(pDevice, PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT APIENTRY MJSetTexture(LPDIRECT3DDEVICE9 pDevice, DWORD Sampler, IDirect3DBaseTexture9* pTexture) {
	return oSetTexture(pDevice, Sampler, pTexture);
}

HRESULT APIENTRY MJReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) {
	return oReset(pDevice, pPresentationParameters);;
}

HRESULT APIENTRY MJSetStreamSource(LPDIRECT3DDEVICE9 pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT sStride) {
	return oSetStreamSource(pDevice, StreamNumber, pStreamData, OffsetInBytes, sStride);
}

HRESULT APIENTRY MJSetVertexDeclaration(LPDIRECT3DDEVICE9 pDevice, IDirect3DVertexDeclaration9* pdecl) {
	return oSetVertexDeclaration(pDevice, pdecl);
}

HRESULT APIENTRY MJSetVertexShaderConstantF(LPDIRECT3DDEVICE9 pDevice, UINT StartRegister, const float* pConstantData, UINT Vector4fCount) {
	return oSetVertexShaderConstantF(pDevice, StartRegister, pConstantData, Vector4fCount);
}

HRESULT APIENTRY MJSetVertexShader(LPDIRECT3DDEVICE9 pDevice, IDirect3DVertexShader9* veShader) {
	return oSetVertexShader(pDevice, veShader);
}

HRESULT APIENTRY MJSetPixelShader(LPDIRECT3DDEVICE9 pDevice, IDirect3DPixelShader9* piShader) {
	return oSetPixelShader(pDevice, piShader);
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
		if (DirectX9::Init() == true) {
			CreateHook(42, (void**)&oEndScene, MJEndScene);
			CreateHook(17, (void**)&oPresent, MJPresent);
			CreateHook(82, (void**)&oDrawIndexedPrimitive, MJDrawIndexedPrimitive);
			CreateHook(81, (void**)&oDrawPrimitive, MJDrawPrimitive);
			CreateHook(65, (void**)&oSetTexture, MJSetTexture);
			CreateHook(16, (void**)&oReset, MJReset);
			CreateHook(100, (void**)&oSetStreamSource, MJSetStreamSource);
			CreateHook(87, (void**)&oSetVertexDeclaration, MJSetVertexDeclaration);
			CreateHook(94, (void**)&oSetVertexShaderConstantF, MJSetVertexShaderConstantF);
			CreateHook(92, (void**)&oSetVertexShader, MJSetVertexShader);
			CreateHook(107, (void**)&oSetPixelShader, MJSetPixelShader);
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