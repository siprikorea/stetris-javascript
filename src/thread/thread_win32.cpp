#include "thread.h"
#include <stdlib.h>
#include <windows.h>
#include <process.h>

/************************************************************
 *	@brief		Thread name information
 *				Code from MSDN: https://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
 *	@retval		Nothing
 ************************************************************/
const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)
typedef struct {
	DWORD dwType;     ///< Must be 0x1000.
	LPCSTR szName;    ///< Pointer to name (in user addr space).
	DWORD dwThreadID; ///< Thread ID (-1=caller thread).
	DWORD dwFlags;    ///< Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

/************************************************************
 *	@brief		Signal thread name to any attached debuggers.
 *	@param[in]	dwThreadID		Thread ID
 *	@param[in]	szThreadName	Thread Name
 *	@retval		Nothing
 ************************************************************/
void SetThreadName(DWORD dwThreadID, const char* szThreadName)
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = szThreadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

#pragma warning(push)
#pragma warning(disable: 6320 6322)
	__try {
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}
#pragma warning(pop)
}

/************************************************************
 *	@brief		Thread Object
 ************************************************************/
class ThreadObject_Win32 : public ThreadObject {
private:
	HANDLE thread;       ///< System thread identifier.
	unsigned int id;     ///< Thread identifier.
	ThreadFunc proc; ///< External thread procedure.
	void *param;         ///< Parameter for the external thread procedure.
	bool self_destruct;  ///< Free ourselves when done?
	const char *name;    ///< Thread name.

public:
	/************************************************************
	 *	@brief		Get type
	 *	@retval		Nothing
	 ************************************************************/
	ThreadObject_Win32(ThreadFunc proc, void *param, bool self_destruct, const char *name)
		: thread(NULL),
		id(0),
		proc(proc),
		param(param),
		self_destruct(self_destruct),
		name(name)
	{
		thread = (HANDLE)_beginthreadex(NULL, 0, &stThreadProc, this, CREATE_SUSPENDED, &id);
		if (thread == NULL)
			return;

		ResumeThread(thread);
	}

	/************************************************************
	 *	@brief		Desturctor
	 *	@retval		Nothing
	 ************************************************************/
	~ThreadObject_Win32()
	{
		if (thread != NULL) {
			CloseHandle(thread);
			thread = NULL;
		}
	}

	/************************************************************
	 *	@brief		Exit
	 *	@retval		Nothing
	 ************************************************************/
	bool Exit()
	{
		throw ThreadExitSignal();
	}

	/************************************************************
	 *	@brief		Join
	 *	@retval		Nothing
	 ************************************************************/
	void Join()
	{
		WaitForSingleObject(thread, INFINITE);
	}

private:
	/************************************************************
	 *	@brief		Thread function
	 *	@retval		Nothing
	 ************************************************************/
	static UINT CALLBACK stThreadProc(void *thr)
	{
		((ThreadObject_Win32 *)thr)->ThreadProc();
		return 0;
	}

	/************************************************************
	 *	@brief		Thread function
	 *	@retval		Nothing
	 ************************************************************/
	void ThreadProc()
	{
		SetThreadName(-1, this->name);

		try {
			this->proc(this->param);
		} catch (ThreadExitSignal) {
		} catch (...) {
		}

		if (self_destruct)
			delete this;
	}
};

/************************************************************
 *	@brief		Create thread
 *	@retval		Nothing
 ************************************************************/
bool ThreadObject::New(ThreadFunc proc, void *param, ThreadObject **thread, const char *name)
{
	ThreadObject *to = new ThreadObject_Win32(proc, param, thread == NULL, name);
	if (thread != NULL)
		*thread = to;
	return true;
}

/************************************************************
 *	@brief		Thead mutex
 *	@retval		Nothing
 ************************************************************/
class ThreadMutex_Win32 : public ThreadMutex {
private:
	CRITICAL_SECTION critical_section; ///< The critical section we would enter.
	HANDLE event;                      ///< Event for signalling.
	UINT recursive_count;              ///< Recursive lock count.

public:
	ThreadMutex_Win32()
		: recursive_count(0)
	{
		InitializeCriticalSection(&this->critical_section);
		this->event = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	~ThreadMutex_Win32()
	{
		DeleteCriticalSection(&this->critical_section);
		CloseHandle(this->event);
	}

	void BeginCritical(bool allow_recursive = false)
	{
		/* windows mutex is recursive by itself */
		EnterCriticalSection(&this->critical_section);
		this->recursive_count++;
	}

	void EndCritical(bool allow_recursive = false)
	{
		this->recursive_count--;
		LeaveCriticalSection(&this->critical_section);
	}

	void WaitForSignal()
	{
		this->EndCritical();
		WaitForSingleObject(this->event, INFINITE);
		this->BeginCritical();
	}

	void SendSignal()
	{
		SetEvent(this->event);
	}
};

/************************************************************
 *	@brief		Create thread mutex
 *	@retval		Nothing
 ************************************************************/
ThreadMutex *ThreadMutex::New()
{
	return new ThreadMutex_Win32();
}
