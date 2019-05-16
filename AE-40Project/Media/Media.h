#pragma once
#include "Encoder.h"
//Media class - responsible for capturing audio and video
class Media
{
public:
	Media();
	// Initialize source reader
	bool			InitializeSource();
	// Getters
	IMFSourceReader* getSourceReader() { return m_pReader; }
	IMFMediaType * getOutputMediaTypeAudio();
	IMFMediaType * getOutputMediaTypeVideo();
	~Media();

private:
	// Members
	IMFMediaSource*		m_pVIDSource;
	IMFMediaSource*		m_pAUDSource;
	IMFMediaSource*		m_pAggSource;
	IMFSourceReader*	m_pReader;
	IMFSinkWriter*		m_pSinkWriter;
	bool				m_stopRecording;

	// Methods
	HRESULT	EnumerateDevicesAndActivateSource(GUID deviceType);
	HRESULT CreateAggregatedSourceReader();
	HRESULT SetSourceReaderMediaTypes();
};

