#ifndef _CORESYSTEM_H_
#define _CORESYSTEM_H_

#include "GenWindow.h"
#include "IRenderer.h"
#include "AudioEngine.h"

class CoreSystem
{
public:
	CoreSystem();
	CoreSystem(const CoreSystem&);
	~CoreSystem();
	bool Initialize();
	void Shutdown();
	void Run();
	void SetWindow(GenWindow*);
	void SetGraphics();
	void SetGraphics(IRenderer*);
	bool InitGraphics();
	bool InitAudio()

private:
	GenWindow* m_window;
	IRenderer* m_renderer;
	AudioEngine* m_audio;
};
#endif