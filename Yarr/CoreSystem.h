#ifndef _CORESYSTEM_H_
#define _CORESYSTEM_H_

#include "GenWindow.h"
#include "IRenderer.h"

class CoreSystem
{
public:
	CoreSystem();
	CoreSystem(const CoreSystem&);
	~CoreSystem();
	bool Initialize();
	void Shutdown();
	void Run();

private:
	GenWindow* m_window;
	IRenderer* m_renderer;
};
#endif