// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAITHREAD_H
#define MOAITHREAD_H

#include <moaicore/MOAIMutex.h>

class MOAIThreadImpl;
class MOAIThreadLocalImpl;

//================================================================//
// MOAIThreadState
//================================================================//
class MOAIThreadState {
private:

	MOAIMutex		mMutex;
	u32				mState;

public:

	enum {
		NEW,
		RUNNING,
		PAUSED,
		STOPPED,
	};

	//----------------------------------------------------------------//
	u32			GetState				();
	bool		IsPaused				();
	bool		IsRunning				();
	bool		IsStopped				();
				MOAIThreadState			();
				~MOAIThreadState		();
	void		SetState				( u32 state );
};

//================================================================//
// MOAIThread
//================================================================//
class MOAIThread {
public:
	
	typedef void ( *Func )( void*, MOAIThreadState& threadState );

	static MOAIThreadLocalImpl	gThreadLocalStorage;

private:

	MOAIThreadState				mThreadState;
	MOAIThread::Func			mMain;
	void*						mParam;
	MOAIThreadImpl*				mImpl;

	USHashedString				mName;

	//----------------------------------------------------------------//
	void					Clear				();
							MOAIThread			( const MOAIThread& ) {}
	
	//----------------------------------------------------------------//
	MOAIThread& operator = ( const MOAIThread& ) {
		return *this;
	}

public:

	GET_SET ( USHashedString, Name, mName )

	//----------------------------------------------------------------//
	Func					GetMainFunc			();
	static MOAIThread*		GetCurrentThread	();
	void*					GetParam			();
	MOAIThreadState*		GetState			();
	bool					IsCurrent			() const;
	bool					IsRunning			() const;
	void					Join				();
							MOAIThread			();
							~MOAIThread			();
	static void				Sleep				();
	void					Start				( Func main, void* param, u32 stackSize );
	void					Stop				();
};

#endif
