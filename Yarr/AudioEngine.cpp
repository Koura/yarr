#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator.hpp>
#include "AudioEngine.h"

using namespace std;
namespace fs = boost::filesystem;

ALuint Buffers[NUM_BUFFERS];

ALuint Sources[NUM_SOURCES];


ALfloat SourcesPos[NUM_SOURCES][3];

ALfloat SourcesVel[NUM_SOURCES][3];


ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

map<const string, int> bufferNumeration;
map<const string, int> sourceNumeration;

int numberOfSources = 0;

AudioEngine::AudioEngine()
{
}

AudioEngine::AudioEngine(const AudioEngine& other)
{
}

AudioEngine::~AudioEngine()
{
}

// Requires Boost. Iterates through a folder and creates buffers from
// all of the .wav files. A buffer for default background music is
// created separately. Maximum number of buffers is 64.
ALboolean CreateBuffersFromFiles()
{
	int i = 1;
	string tiedostonNimi;

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	alGenBuffers(NUM_BUFFERS, Buffers);

	if(alGetError() != AL_NO_ERROR)
	{
		printf("Buffers could not be created");
		return AL_FALSE;
	}

	fs::path targetDir("./wavdata");
	fs::directory_iterator it(targetDir), eod;

	alutLoadWAVFile("wavdata/bgmusic.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[0], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
	bufferNumeration.insert(make_pair("bgmusic.wav", 0));

	if(alGetError() != AL_NO_ERROR)
	{
		printf("bgmusic.wav not found");
		return AL_FALSE;
	}

	BOOST_FOREACH(fs::path const &p, make_pair(it, eod))
	{
		if (!p.filename().string().compare("bgmusic.wav")) 
		{
			continue;
		}

		if (i == 64) 
		{
			break;
		}

		if(is_regular_file(p))
		{

			tiedostonNimi = "wavdata/" + p.filename().string();
			
			alutLoadWAVFile((ALbyte*)tiedostonNimi.c_str(), &format, &data, &size, &freq, &loop);
			alBufferData(Buffers[i], format, data, size, freq);
			alutUnloadWAV(format, data, size, freq);
			bufferNumeration.insert(make_pair(p.filename().string(), i));
		}

		i++;
	}
	
	return AL_TRUE;
}

// Adds a source for the default background music and places it at listener position.
ALboolean LoadALData()
{
	if (!CreateBuffersFromFiles())
	{
		return AL_FALSE;
	}

	alGenSources(NUM_SOURCES, Sources);

	alSourcei (Sources[numberOfSources], AL_BUFFER,   Buffers[0] );
	alSourcef (Sources[numberOfSources], AL_PITCH,    1.0f       );
	alSourcef (Sources[numberOfSources], AL_GAIN,     1.0f       );
	alSourcefv(Sources[numberOfSources], AL_POSITION, ListenerPos);
	alSourcefv(Sources[numberOfSources], AL_VELOCITY, ListenerVel);
	alSourcei (Sources[numberOfSources], AL_LOOPING,  AL_TRUE    );

	if(alGetError() != AL_NO_ERROR)
	{
		printf("Could not create a source for default background music");
		return AL_FALSE;
	}

	sourceNumeration.insert(make_pair("bgmusic.wav",numberOfSources));
	numberOfSources++;

	return AL_TRUE;
}

void SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void KillALData()
{
	alDeleteBuffers(NUM_BUFFERS, Buffers);
	alDeleteSources(NUM_SOURCES, Sources);
	alutExit();
}


bool AudioEngine::Initialize()
{
	alutInit(NULL, 0);
	alGetError();
	
	ALboolean al = LoadALData();

	if(al == AL_FALSE)
	{
		return false;
	}

	SetListenerValues();

	atexit(KillALData);

	printf("AudioEngine ready");
	return true;
}

// This plays a ******.wav named sound if it exists in the buffers. If there isn't a source,
// it will be created, otherwise it will just play the sound.
// Maximum number of sources simultaneously is 32.
void AudioEngine::PlaySound(const std::string name, ALboolean loop, ALfloat sourcePos[], ALfloat sourceVel[])
{
	if (sourceNumeration.find(name) == sourceNumeration.end()) 
	{
		if (bufferNumeration.find(name) != bufferNumeration.end())
		{

			alSourceStop(Sources[numberOfSources]);

			SourcesPos[numberOfSources][0] = sourcePos[0];
			SourcesPos[numberOfSources][1] = sourcePos[1];
			SourcesPos[numberOfSources][2] = sourcePos[2];

			SourcesVel[numberOfSources][0] = sourceVel[0];
			SourcesVel[numberOfSources][1] = sourceVel[1];
			SourcesVel[numberOfSources][2] = sourceVel[2];

			alSourcei (Sources[numberOfSources], AL_BUFFER,   Buffers[bufferNumeration.at(name)] );
			alSourcef (Sources[numberOfSources], AL_PITCH,    1.0f       );
			alSourcef (Sources[numberOfSources], AL_GAIN,     1.0f       );
			alSourcefv(Sources[numberOfSources], AL_POSITION, SourcesPos[numberOfSources]);
			alSourcefv(Sources[numberOfSources], AL_VELOCITY, SourcesVel[numberOfSources]);
			alSourcei (Sources[numberOfSources], AL_LOOPING,  loop    );

			if(alGetError() != AL_NO_ERROR)
			{
				printf("Could not create a source");
			}


			sourceNumeration.insert(make_pair(name,numberOfSources));

			numberOfSources++;

			alSourcePlay(Sources[sourceNumeration.at(name)]);

		} else {
			printf("Buffer with such name not found");
			return;
		}
	} else {

		
		SourcesPos[sourceNumeration.at(name)][0] = sourcePos[0];
		SourcesPos[sourceNumeration.at(name)][1] = sourcePos[1];
		SourcesPos[sourceNumeration.at(name)][2] = sourcePos[2];

		SourcesVel[sourceNumeration.at(name)][0] = sourceVel[0];
		SourcesVel[sourceNumeration.at(name)][1] = sourceVel[1];
		SourcesVel[sourceNumeration.at(name)][2] = sourceVel[2];


		alSourcefv(Sources[sourceNumeration.at(name)], AL_POSITION, SourcesPos[sourceNumeration.at(name)]);
		alSourcefv(Sources[sourceNumeration.at(name)], AL_VELOCITY, SourcesVel[sourceNumeration.at(name)]);

		if(alGetError() != AL_NO_ERROR)
		{
			printf("Could not update source position");
		}

		alSourcePlay(Sources[sourceNumeration.at(name)]);

		
	}
}

void AudioEngine::StopSound(const std::string name)
{
	if (sourceNumeration.find(name) != sourceNumeration.end()) 
	{
		alSourceStop(Sources[sourceNumeration.at(name)]);
	}
}

void AudioEngine::PauseSound(const std::string name)
{
	if (sourceNumeration.find(name) != sourceNumeration.end()) 
	{
		alSourcePause(Sources[sourceNumeration.at(name)]);
	}
}

// Updates the position of a source using x, y and z coordinates.
void AudioEngine::UpdateSourcePos(const std::string name, ALfloat sourcePos[])
{

	if (sourceNumeration.find(name) != sourceNumeration.end()) 
	{
		SourcesPos[sourceNumeration.at(name)][0] = sourcePos[0];
		SourcesPos[sourceNumeration.at(name)][1] = sourcePos[1];
		SourcesPos[sourceNumeration.at(name)][2] = sourcePos[2];

		alSourcefv(Sources[sourceNumeration.at(name)], AL_POSITION, SourcesPos[sourceNumeration.at(name)]);
		alSourcefv(Sources[sourceNumeration.at(name)], AL_VELOCITY, SourcesVel[sourceNumeration.at(name)]);
	}

}

// Same as above except without an array
void AudioEngine::UpdateSourcePosFloats(const std::string name, ALfloat x, ALfloat y, ALfloat z)
{
	
	if (sourceNumeration.find(name) != sourceNumeration.end()) 
	{
		SourcesPos[sourceNumeration.at(name)][0] = x;
		SourcesPos[sourceNumeration.at(name)][1] = y;
		SourcesPos[sourceNumeration.at(name)][2] = z;

		alSource3f(Sources[sourceNumeration.at(name)], AL_POSITION, x, y, z);
	}


}

// Changes the listener position
void AudioEngine::UpdateListenerValues(ALfloat lisPos[], ALfloat lisVel[], ALfloat lisOri[])
{
	ListenerPos[0] = lisPos[0];
	ListenerPos[1] = lisPos[1];
	ListenerPos[2] = lisPos[2];

	ListenerVel[0] = lisVel[0];
	ListenerVel[1] = lisVel[1];
	ListenerVel[2] = lisVel[2];
	
	ListenerOri[0] = lisOri[0];
	ListenerOri[1] = lisOri[1];
	ListenerOri[2] = lisOri[2];
	ListenerOri[3] = lisOri[3];
	ListenerOri[4] = lisOri[4];
	ListenerOri[5] = lisOri[5];

	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

}




