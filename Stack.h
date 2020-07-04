#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
	class StackNode
	{
	public:
		T Data;
		StackNode* pNext;

		StackNode(T data) : Data(data), pNext(NULL) {}
	};

private:
	// the head pointer of the stack
	StackNode* m_pTop;

public:
	Stack()
	{
		m_pTop = NULL;
	}
	~Stack()
	{

	}

	/// <summary>
	/// push the data into this stack
	/// </summary>
	///
	/// <param name="data">
	/// a data to push into this stack
	/// </param>
	void Push(T data)
	{
		StackNode * new_Data = new StackNode(data);

		StackNode * temp = m_pTop; 
		new_Data->pNext = m_pTop; 
		m_pTop = new_Data; 

		if (m_pTop == NULL) {m_pTop = new_Data; return;}
	}
	/// <summary>
	/// pop(remove) the last-in data from this stack
	/// </summary>
	void Pop()
	{
		StackNode * temp = m_pTop; // temp is temporary store
		m_pTop = m_pTop -> pNext; // move m_pTop
		delete temp;

		return;
	}
	/// <summary>
	/// get the last-in data of this stack
	/// </summary>
	/// 
	/// <returns>
	/// the last-in data of this stack
	/// </returns>
	T Top() {return m_pTop->Data;}
	/// <summary>
	/// check whether this stack is empty or not.
	/// </summary>
	///
	/// <returns>
	/// true if this stack is empty.
	/// false otherwise.
	/// </returns>
	bool IsEmpty()
	{
		if (m_pTop == NULL) return true;
		else return false;
	}
};

#endif