#ifndef _IRENDERER_H_
#define _IRENDERER_H_
class IRenderer
{
public:
	IRenderer(){};
	IRenderer(const IRenderer&){};
	virtual ~IRenderer(){};

	virtual bool Initialize(int, int) = 0;
	virtual void Shutdown();
	virtual bool Frame() = 0;
private:
	virtual bool Render() = 0;
};
#endif