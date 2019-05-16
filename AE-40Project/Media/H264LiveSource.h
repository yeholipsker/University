#pragma once
#include <FramedSource.hh>
#include <DeviceSource.hh>
#include "Media.h"
#include <queue>
#include <GroupsockHelper.hh>

//H264LiveSource Class - responsible for delivering frames from live source to live555
class H264LiveSource : public FramedSource
{
public:
	//create new reference
	static H264LiveSource* createNew(UsageEnvironment& env);
	//push to sample queue
	void PushToQueue(std::pair<BYTE*, DWORD> myPair);

public:
	//id for triggering event
	static EventTriggerId m_eventTriggerId;
	
protected:
	//constructor and destructor
	H264LiveSource(UsageEnvironment& env);
	virtual ~H264LiveSource();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();
	void deliverFrame();
	static void deliverFrame0(void* clientData);
	bool isH264VideoStreamFramer() const;

	// Members
	std::queue<std::pair<BYTE*, DWORD>> * myQueue;
	CRITICAL_SECTION CriticalSection;
	static unsigned m_referenceCount; // used to count how many instances of this class currently exist
	DeviceParameters m_fParams;
	timeval m_currentTime;

};

