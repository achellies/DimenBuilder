#ifndef _SHARE_PTR_H_
#define _SHARE_PTR_H_

/*class for counted reference semantics
	*-deletes the object to which it refers when the last share_ptr
	* that refers to it is destroyed
*/

template <class _T>
class share_ptr
{
public:

	//initialize pointer with existing pointer
	//-requires that the pointer p is a return value of new
	explicit share_ptr(_T* p=0)
	: m_ptr(p), m_ccbRef(new long(1))
	{}

	//copy pointer (one more owner)
	share_ptr (const share_ptr<_T>& p) throw()
	: m_ptr(p.m_ptr), m_ccbRef(p.m_ccbRef)
	{
		++*m_ccbRef;
	}

	//destructor (delete value if this was the last owner)
	~share_ptr () throw()
	{
		dispose();
	}

	//assignment (unshare old and share new value)
	share_ptr<_T>& operator= (const share_ptr<_T>& p) throw()
	{
		if (this != &p)
		{
			dispose();
			m_ptr = p.m_ptr;
			m_ccbRef = p.m_ccbRef;
			++*m_ccbRef;
		}
		return *this;
	}

	BOOL operator== (const share_ptr<_T>& p) throw()
	{
		return (this == &p)?TRUE:FALSE;
	}
	
	//access the value to which the pointer refers
	_T& operator*() const throw()
	{
		return *m_ptr;
	}
	
	_T* operator->() const throw()
	{
		return m_ptr;
	}

	_T *get() const throw()
	{	
		// return wrapped pointer
		return ((_T *)m_ptr);
	}

	operator bool()
	{
		return (m_ptr != 0)?TRUE:FALSE;
	}
private:
	void dispose()
	{
		if (--*m_ccbRef == 0)
		{
			delete m_ccbRef;
			delete m_ptr;
		}
	}
private:
	_T* m_ptr;		// pointer to the value
	long* m_ccbRef;// shared number of owners
};


#endif