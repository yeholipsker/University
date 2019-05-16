#include "stdafx.h"
#include "MPEG2LiveSource.h"

// Static members
EventTriggerId MPEG2LiveSource::m_eventTriggerId = 0;
unsigned MPEG2LiveSource::m_referenceCount = 0;

//return new instance
MPEG2LiveSource* MPEG2LiveSource::createNew(UsageEnvironment &env)
{
	return new MPEG2LiveSource(env);
}

//push to samples queue
void MPEG2LiveSource::PushToQueue(std::pair<BYTE*, DWORD> myPair)
{
	EnterCriticalSection(&CriticalSection);
	myQueue->push(myPair);
	LeaveCriticalSection(&CriticalSection);
}

//constructor
MPEG2LiveSource::MPEG2LiveSource(UsageEnvironment& env) : FramedSource(env)
{
	//initialize queue
	InitializeCriticalSection(&CriticalSection);
	if (m_referenceCount == 0)
	{
		EnterCriticalSection(&CriticalSection);
		myQueue = new std::queue<std::pair <BYTE*, DWORD>>();
		LeaveCriticalSection(&CriticalSection);
	}
	++m_referenceCount;
	//initialize m_eventTriggerId
	if (m_eventTriggerId == 0)
	{
		m_eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
	}
}

//destructor
MPEG2LiveSource::~MPEG2LiveSource()
{
	--m_referenceCount;
	if (m_referenceCount == 0)
	{
		envir().taskScheduler().deleteEventTrigger(m_eventTriggerId);
		m_eventTriggerId = 0;
	}
	//empty the queue and delete it
	EnterCriticalSection(&CriticalSection);
	while (!myQueue->empty())
	{
		std::pair<BYTE*, DWORD> myPair = myQueue->front();
		myQueue->pop();
		delete myPair.first;
	}
	delete myQueue;
	LeaveCriticalSection(&CriticalSection);
}

//deliver the next encoded frame
void MPEG2LiveSource::doGetNextFrame()
{
		deliverFrame();
}

//trigger deliverFrame
void MPEG2LiveSource::deliverFrame0(void* clientData)
{
	((MPEG2LiveSource*)clientData)->deliverFrame();
}

//deliver frame to rtpsink
void MPEG2LiveSource::deliverFrame()
{
	//return if wait for data
	if (!isCurrentlyAwaitingData())
	{
		return;
	}
	//pop from queue if exist
	EnterCriticalSection(&CriticalSection);
	if (!myQueue->empty())
	{
		std::pair <BYTE*, DWORD> myPair = myQueue->front();
		myQueue->pop();
		LeaveCriticalSection(&CriticalSection);
		//if sample not null, send it to rtpsink
		if (myPair.first)
		{
			gettimeofday(&fPresentationTime, NULL);
			fFrameSize = myPair.second;
			if (fFrameSize > fMaxSize) fFrameSize = fMaxSize;
			memmove(fTo, myPair.first, fFrameSize);
			delete myPair.first;
			FramedSource::afterGetting(this);
		}
	}
	else {
		LeaveCriticalSection(&CriticalSection);
	}
}