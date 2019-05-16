#include "stdafx.h"
#include "H264LiveSource.h"

// Static members
EventTriggerId H264LiveSource::m_eventTriggerId = 0;
unsigned H264LiveSource::m_referenceCount = 0;

//return new instance
H264LiveSource* H264LiveSource::createNew(UsageEnvironment &env)
{
	return new H264LiveSource(env);
}

//push to samples queue
void H264LiveSource::PushToQueue(std::pair<BYTE*, DWORD> myPair)
{
	EnterCriticalSection(&CriticalSection);
	myQueue->push(myPair);
	LeaveCriticalSection(&CriticalSection);
}

//constructor
H264LiveSource::H264LiveSource(UsageEnvironment& env) : FramedSource(env)
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
H264LiveSource::~H264LiveSource()
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
void H264LiveSource::doGetNextFrame()
{
	deliverFrame();
}

//trigger deliverFrame
void H264LiveSource::deliverFrame0(void* clientData)
{
	((H264LiveSource*)clientData)->deliverFrame();
}

//indicate it's video stream framer
bool H264LiveSource::isH264VideoStreamFramer() const
{
	return true;
}

//deliver frame to rtpsink
void H264LiveSource::deliverFrame()
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
