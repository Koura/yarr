#ifndef _INTRUSIVEPTR_H_
#define _INTRUSIVEPTR_H_

template<class T>
class IntrusivePtr 
{
public: 
	IntrusivePtr(T* p) : ptr(p){};
	IntrusivePtr(const IntrusivePtr<T>& other) { this->ptr = other.ptr; if(ptr) ptr->Grab();};
	~IntrusivePtr() { if (ptr) ptr->Release(); ptr=0;};
	T* GetPtr() const { return ptr;};
	T& operator*() { return *ptr;};
	T* operator->() { return ptr;};
	
template<class U>
	bool operator==(const IntrusivePtr<U>& other) const{ return (this->ptr == other.ptr);};	
template<class U>
	bool operator<(const IntrusivePtr<U>& other) const{ return (this->ptr < other.ptr);};	
template<class U>
	bool operator>(const IntrusivePtr<U>& other) const{ return (this->ptr > other.ptr);};
private:
	T* ptr;
};
#endif