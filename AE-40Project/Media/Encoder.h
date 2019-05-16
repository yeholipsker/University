#pragma once

#include "Utilities.h"
//Class encoder - responsible for encoding video and audio samples
class Encoder
{
public:
	//constructor
	Encoder();
	//initialize encoders
	HRESULT InitializeVideoEncoder(IMFMediaType *pType);
	HRESULT InitializeAudioEncoder(IMFMediaType *pType);

	//encode video and audio samples
	HRESULT TransformVideoSample(IMFSample * pSample, BYTE ** ppRawBuffer, DWORD * pBuffLength);
	HRESULT TransformAudioSample(IMFSample * pSample, BYTE ** ppRawBuffer, DWORD * pBuffLength);
	
	//destructor
	~Encoder();
private:
	//Members
	IMFTransform * m_pVidEncoderTransform;
	IMFTransform * m_pAudEncoderTransform;
	HRESULT FindOutputMediaType(IMFMediaType *pType);
	HRESULT FindInputMediaType();
};