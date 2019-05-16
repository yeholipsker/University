#pragma once
#include <FramedSource.hh>
#include <DeviceSource.hh>
#include "Media.h"
#include <queue>
#include <GroupsockHelper.hh>

//MPEG2LiveSource Class - responsible for delivering frames from live source to live555
class MPEG2LiveSource : public FramedSource
{
public:
	//create new reference
	static MPEG2LiveSource* createNew(UsageEnvironment& env);
	//push to sample queue
	void PushToQueue(std::pair<BYTE*, DWORD> myPair);
public:
	//id for triggering event
	static EventTriggerId m_eventTriggerId;

protected:
	//constructor and destructor
	MPEG2LiveSource(UsageEnvironment& env);
	virtual ~MPEG2LiveSource();

private:

	// redefined virtual functions:
	virtual void doGetNextFrame();
	void deliverFrame();
	//virtual void doStopGettingFrames(); // optional
	static void deliverFrame0(void* clientData);

	// Members
	std::queue<std::pair<BYTE*, DWORD>> * myQueue;
	CRITICAL_SECTION CriticalSection;
	static unsigned m_referenceCount; // used to count how many instances of this class currently exist
	DeviceParameters m_fParams;
	timeval m_currentTime;
};
