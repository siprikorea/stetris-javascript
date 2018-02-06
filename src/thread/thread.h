#ifndef __THREAD_H__
#define __THREAD_H__

/************************************************************
 *	@brief		Thread Function
 ************************************************************/
typedef void (*ThreadFunc)(void *);

/************************************************************
 *	@brief		Thread Exit Signal
 ************************************************************/
class ThreadExitSignal { };

/************************************************************
 *	@brief		Thread Object
 ************************************************************/
class ThreadObject {
public:
	// Create thread
	static bool New(ThreadFunc proc, void *param, ThreadObject **thread = 0, const char *name = 0);
	// Destructor
	virtual ~ThreadObject() {};

	// Exit thread
	virtual bool Exit() = 0;
	// Join
	virtual void Join() = 0;
};

/************************************************************
 *	@brief		Thread Mutex
 ************************************************************/
class ThreadMutex {
public:
	// Create therad mutex
	static ThreadMutex *New();
	// Destructor
	virtual ~ThreadMutex() {};

	// Begin critial section
	virtual void BeginCritical(bool allow_recursive = false) = 0;
	// End critial section
	virtual void EndCritical(bool allow_recursive = false) = 0;

	// Wait for signal
	virtual void WaitForSignal() = 0;
	// Send signal
	virtual void SendSignal() = 0;
};

/************************************************************
 *	@brief		Thread Mutex Locker
 ************************************************************/
class ThreadMutexLocker {
public:
	// Constructor
	ThreadMutexLocker(ThreadMutex *mutex)
		: mutex(mutex)
	{
		mutex->BeginCritical();
	}

	// Destructor
	~ThreadMutexLocker()
	{
		this->mutex->EndCritical();
	}

private:
	// Constructor
	ThreadMutexLocker(const ThreadMutexLocker &) { } 
	// Operator =
	ThreadMutexLocker &operator=(const ThreadMutexLocker &) { return *this; } 
	// Thread mutex
	ThreadMutex *mutex;
};

#endif
