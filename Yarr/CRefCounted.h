#ifndef _CREFCOUNTED_H_
#define _CREFCOUNTED_H_

class CRefCounted
{
public:

	CRefCounted() : count(1) {};
	void Grab() {++count;};
	void Release() {if(--count <= 0) { delete this;} };
private:
	int count;
};
#endif