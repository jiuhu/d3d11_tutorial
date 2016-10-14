//--------------------------------------------------------------------
//
//	Singleton.h
//
//	Provide a class template for Singleton design pattern.
//
//	Team Water 2010
//	MSc Games Programming / MSc Computer Graphics Programming
//	University of Hull
//


/**	Revision History

		Rev 1.0		26 May 2010		Define singleton design

*/

#pragma once

template<class T>
class Singleton
{
public:
	
	/*
		Get the instance of the class.
	*/
	static T * get()
	{
		if (!m_instance) m_instance = new T();
		return m_instance;
	}

	/*
		Release the instance of the class.
	*/
	static void release()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:

	Singleton();
	~Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static T * m_instance;
};
//--------------------------------------------------------------------
	
template<class T> 
T * Singleton<T>::m_instance = nullptr;
//--------------------------------------------------------------------