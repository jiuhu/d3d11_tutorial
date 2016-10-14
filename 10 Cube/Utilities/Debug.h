#pragma once

#include <cstdio>

#ifdef _DEBUG

	#define WIN32_LEAN_AND_MEAN 1
	#include <windows.h>

	#include <crtdbg.h>

	#ifndef DBG_NEW
	  #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	  #define new DBG_NEW
	#endif

#endif
//--------------------------------------------------------------------

/*
	This function is called to print out message on the console.
	print "\n" explicitly.
*/
#ifdef UNICODE
    #define outputMsg outputMsgW 
#else
    #define outputMsg outputMsgA
#endif

inline void outputMsgA(const char * const format, ...) 
{ 
	va_list args; 
	va_start(args, format); 
	vprintf(format, args); 
	va_end(args);
}
//--------------------------------------------------------------------

inline void outputMsgW(const wchar_t * const format, ...) 
{ 
	va_list args; 
	va_start(args, format);
	vwprintf(format, args); 
	va_end(args);
}
//--------------------------------------------------------------------

#ifdef _DEBUG

	#ifdef UNICODE
		#define debugMsg debugMsgW 
	#else
		#define debugMsg debugMsgA
	#endif
	/*
		This function is called to print out message on DEBUG version only.
		print "\n" explicitly.
	*/
	inline void debugMsgA(const char * const format, ...) 
	{ 
		va_list args; 
		va_start(args, format); 
		vprintf(format, args); 
		va_end(args);
	}
	//--------------------------------------------------------------------

	inline void debugMsgW(const wchar_t * const format, ...) 
	{ 
		va_list args; 
		va_start(args, format);
		vwprintf(format, args); 
		va_end(args);
	}
	//--------------------------------------------------------------------

	/*
		This function is called to detect memory leaks.
		Call this function only once in a project.
	*/
	inline void detectMemoryLeak() 
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
	//--------------------------------------------------------------------

	/*
		This function is called to dump memory statistics at the moment.
	*/
	inline void dumpMemoryStatistics() 
	{
		_CrtMemState state;
		_CrtMemCheckpoint(&state);
		_CrtMemDumpStatistics(&state);
	}
	//--------------------------------------------------------------------

#else

	#define debugMsg 

	#define detectMemoryLeak()

	#define dumpMemoryStatistics()

#endif
//--------------------------------------------------------------------