#ifndef _AUDIOENGINE_H_
#define _AUDIOENGINE_H_


#define WIN32_LEAN_AND_MEAN
#define NUM_BUFFERS 64
#define NUM_SOURCES 32

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <map>

class AudioEngine
{

public:
	AudioEngine();
	AudioEngine(const AudioEngine&);
	~AudioEngine();
	bool Initialize();
	void PlaySound(const std::string name, ALboolean loop, ALfloat sourcePos[], ALfloat sourceVel[]);
	void UpdateSourcePos(const std::string name, ALfloat sourcePos[]);
	void StopSound(const std::string name);
	void AudioEngine::UpdateSourcePosFloats(const std::string name, ALfloat x, ALfloat y, ALfloat z);
	void AudioEngine::PauseSound(const std::string name);
	void AudioEngine::UpdateListenerValues(ALfloat lisPos[], ALfloat lisVel[], ALfloat lisOri[]);

};


#endif