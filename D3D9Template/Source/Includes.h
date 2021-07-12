#include <Windows.h>
#include <d3d9.h>
#include <cstdint>
#pragma once
#include <cassert>
#include "Hook/Minhook/include/MinHook.h"
#include "Libraries/xorstr/include/xorstr.h"
#include "Hook/DX.h"
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_dx9.h"
#include "Libraries/imgui/imgui_impl_win32.h"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
