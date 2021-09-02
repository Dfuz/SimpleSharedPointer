#pragma once
#include <iostream>
#include <atomic>

template<typename T>
class SharedPointer final
{
private:
	uint64_t* refCount = nullptr;
	T* _pointer = nullptr;

	inline void cleanUp()
	{
		--(*refCount);
		if (*refCount == 0)
		{
			delete _pointer;
			delete refCount;
		}
	}
public:
	/*default constructors*/
	SharedPointer() = delete;
	explicit SharedPointer(T* pointer) : 
		_pointer(pointer), refCount(new uint64_t{1}) {};
	explicit SharedPointer(const T& value) :
		_pointer(new T{value}), refCount(new uint64_t{1}) {};
	explicit SharedPointer(T&& pointer)
	{
		_pointer = new T(std::move(pointer));
		refCount = new uint64_t{1};
	}

	/*copy semantics*/
	// copy constructor
	SharedPointer(const SharedPointer& anotherPtr)
	{
		this->_pointer = anotherPtr._pointer;
		this->refCount = anotherPtr.refCount;
		if (anotherPtr._pointer) ++(*this->refCount);
	}
	// copy assignment
	SharedPointer& operator=(const SharedPointer& anotherObj)
	{
		cleanUp();
		this->_pointer = anotherObj._pointer;
		this->refCount = anotherObj.refCount;
		++(*refCount);
	}

	/*move semantics*/
	// move constructor
	explicit SharedPointer(SharedPointer&& tempObject)
	{
		this->_pointer = tempObject._pointer;
		this->refCount = tempObject.refCount;
		tempObject._pointer = tempObject.refCount = nullptr;
	}
	// move assignment
	SharedPointer& operator=(SharedPointer&& tempObject)
	{
		cleanUp();
		this->_pointer = tempObject._pointer;
		this->refCount = tempObject.refCount;
		tempObject._pointer = tempObject.refCount = nullptr;
	}

	~SharedPointer()
	{
		std::cout << "Decrementing destructor!" << std::endl;
		if (--(*refCount) == 0)
		{
			std::cout << "Memory free!" << std::endl;
			delete refCount;
			delete _pointer;
		}
	}

	/*operators*/
	operator bool()	const { return _pointer != nullptr; };
	T& operator*()	const { return *_pointer; };
	T* operator->()	const { return _pointer; };

	/*members*/
	uint64_t getCount() const { return *refCount; }
};
