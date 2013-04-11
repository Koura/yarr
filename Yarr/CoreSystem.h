#ifndef _CORESYSTEM_H_
#define _CORESYSTEM_H_

#include "Window32.h"

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
	Window32* m_window;
};
#endif