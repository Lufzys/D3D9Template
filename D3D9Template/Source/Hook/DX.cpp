#include "../Includes.h"

bool DX::Hook()
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = TEXT_("LF1337");
	windowClass.hIconSm = NULL;

	::RegisterClassEx(&windowClass);
	HWND window = ::CreateWindow(windowClass.lpszClassName, TEXT_("1337"), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

	HMODULE libD3D9;
	if ((libD3D9 = ::GetModuleHandle(TEXT_("d3d9.dll"))) == NULL)
	{
		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return false;
	}

	void* Direct3DCreate9;
	if ((Direct3DCreate9 = ::GetProcAddress(libD3D9, "Direct3DCreate9")) == NULL)
	{
		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return false;
	}

	LPDIRECT3D9 direct3D9;
	if ((direct3D9 = ((LPDIRECT3D9(__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION)) == NULL)
	{
		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return false;
	}

	D3DPRESENT_PARAMETERS params;
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	LPDIRECT3DDEVICE9 device;
	if (direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device) < 0)
	{
		direct3D9->Release();
		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return false;
	}

	MethodsTable = (uint150_t*)::calloc(119, sizeof(uint150_t));
	::memcpy(MethodsTable, *(uint150_t**)device, 119 * sizeof(uint150_t));

	MH_Initialize();

	device->Release();
	device = NULL;
	direct3D9->Release();
	direct3D9 = NULL;

	::DestroyWindow(window);
	::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

	return true;
}

void DX::Shutdown()
{
	MH_DisableHook(MH_ALL_HOOKS);
	::free(MethodsTable);
	MethodsTable = NULL;
}

bool DX::Bind(uint16_t index, void** original, void* function) 
{
	assert(index >= 0 && original != NULL && function != NULL);

	void* target = (void*)MethodsTable[index];
	if (MH_CreateHook(target, function, original) != MH_OK || MH_EnableHook(target) != MH_OK)
	{
		return false;
	}
	return true;
}

void DX::Unbind(uint16_t index)
{
	assert(index >= 0);
	MH_DisableHook((void*)MethodsTable[index]);
}