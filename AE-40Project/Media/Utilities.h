#pragma once

#include <Windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <iostream>
#include <Mfreadwrite.h>
#include <strsafe.h>
#include <Mferror.h>
#include <wmcodecdsp.h>
#include <wmsdkidl.h>

#ifndef IF_EQUAL_RETURN
#define IF_EQUAL_RETURN(param, val) if(val == param) return L#val
#endif

#define CHECK_HR(hr, msg) if (hr != S_OK) std::cout << "FAILED!!\t" << msg << std::endl;

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

template <class T> inline void SafeRelease(T*& pT)
{
	if (pT != NULL)
	{
		pT->Release();
		pT = NULL;
	}
}

class Utilities
{
public:
	Utilities();
	LPCWSTR GetGUIDNameConst(const GUID& guid);
	HRESULT GetGUIDName(const GUID& guid, WCHAR **ppwsz);
	HRESULT LogAttributeValueByIndex(IMFAttributes *pAttr, DWORD index);
	HRESULT SpecialCaseAttributeValue(GUID guid, const PROPVARIANT& var);
	void DBGMSG(PCWSTR format, ...);
	HRESULT LogMediaType(IMFMediaType *pType);
	void LogUINT32AsUINT64(const PROPVARIANT& var);
	float OffsetToFloat(const MFOffset& offset);
	HRESULT LogVideoArea(const PROPVARIANT& var);
	~Utilities();
};

