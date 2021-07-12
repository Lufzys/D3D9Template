#include <Windows.h>
#include <d3d9.h>
#include <cstdint>

#if defined(_M_X64)
typedef uint64_t uint150_t;
#else
typedef uint32_t uint150_t;
#endif

#ifdef _UNICODE
# define TEXT_(text) L##text
#else
# define TEXT_(text) text
#endif

static uint150_t* MethodsTable = NULL;
namespace DX
{
	bool Hook();
	void Shutdown();

	bool Bind(uint16_t index, void** original, void* function);
	void Unbind(uint16_t index);
}