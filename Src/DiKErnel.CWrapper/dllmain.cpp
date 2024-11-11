// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <cmath>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) double Pow(double x, double y)
{
    return pow(x, y);
}

extern "C" __declspec(dllexport) double Log10(double x)
{
    return log10(x);
}

extern "C" __declspec(dllexport) double Sin(double x)
{
    return sin(x);
}

extern "C" __declspec(dllexport) double Cos(double x)
{
    return cos(x);
}

extern "C" __declspec(dllexport) double Exp(double x)
{
    return exp(x);
}