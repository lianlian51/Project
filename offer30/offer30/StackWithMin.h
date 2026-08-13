#pragma once
#include <stack>
#include <iostream>
#include <assert.h>

template<class T>
class StackWithMin
{
public:
	StackWithMin() {};
	virtual ~StackWithMin() {};

	T& Top();
	const T& Top() const;

	void Push(const T& data);
	void Pop();

	const T& Min() const;

	bool Empty() const;
	size_t Size() const;

private:
	std::stack<T> m_data;
	std::stack<T> m_min;
};

template<class T>
void StackWithMin<T>::Push(const T& data)
{
	m_data.push(data);
	if (m_min.empty() || data < m_min.top())
		m_min.push(data);
	else
		m_min.push(m_min.top());
}

template<class T>
void StackWithMin<T>::Pop()
{
	assert(m_data.size() > 0 && m_min.size() > 0);
	m_data.pop();
	m_min.pop();
}

template<class T>
T& StackWithMin<T>::Top()
{
	return m_data.top();
}

template<class T>
const T& StackWithMin<T>::Top() const 
{
	return m_data.top();
}

template<class T>
const T& StackWithMin<T>::Min()const 
{
	assert(m_data.size() > 0 && m_min.size() > 0);
	return m_min.top();
}

template<class T>
bool StackWithMin<T>::Empty() const
{
	return m_data.empty();
}

template<class T>
size_t StackWithMin<T>::Size() const
{
	return m_data.size();
}

