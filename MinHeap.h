#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
// array for the elements which should be heap-sorted
std::vector< std::pair < TKey, TValue > > m_vec;				//Tkey = distance, Tvalue = pair<current_vertex, previous_vertex>

public:
	MinHeap() { m_vec.push_back(std::make_pair(0, std::make_pair(0, 0))); }				//constructor

/// <summary>
/// insert key-value pair
/// </summary>
///
/// <param name="key">
/// the key that is used for sorting
/// </param>
///
/// <param name="value">
/// the value that is managed in this heap
/// </param>
void Push(TKey key, TValue value)						//Tkey = distance, Tvalue = pair<currrent_vertex, preious_vertex>
{
	int currentNode = m_vec.size();	
	m_vec.push_back(std::make_pair(key, value));		//push back to vector	

	std::pair < TKey, TValue > P = m_vec[currentNode / 2];		//P is parent of currentNode
	while (currentNode != 0 && P.first >= key)			//while do not reach to head of min heap and new key is lower than Parent's key
	{
		m_vec[currentNode] = m_vec[currentNode / 2];	//move current node's value to parent node
		currentNode /= 2;								//move current node to parents
		P = m_vec[currentNode / 2];						//P is current node's parent
	}
	m_vec.at(currentNode) = std::make_pair(key, value);		//current node'st vector is new data
	return;
}
/// <summary>
/// remove the minimum element
/// </summary>
void Pop()
{
	if (m_vec.size() == 1) return;							//if there are no data, return 
	std::pair< TKey, TValue > LastE = m_vec.at(m_vec.size()-1);	//LastE is last minheap's value

	m_vec.at(1) = LastE;									//set minheap's first value to Last E
	m_vec.pop_back();										//Pop last value

	Heapify(1);												//sorting
	
}
/// <summary>
/// get the minimum element
/// </summary>
///
/// <returns>
/// the minimum element
/// </returns>
std::pair< TKey, TValue > Top()
{
	return m_vec.at(1);
}
/// <summary>
/// get the key-value pair which the value is the same as the target
/// </summary>
///
/// <returns>
/// the key-value pair which the value is the same as the target
/// </returns>
std::pair < TKey, TValue > Get(TValue target)
{
	std::vector < std::pair < TKey, TValue > > v;


}
/// <summary>
/// check whether this heap is empty or not
/// </summary>
///
/// <returns>
/// true if this heap is empty
/// </returns>
bool IsEmpty()
{
	if (m_vec->size() == 0)								//if vector's size is 0
		return true;									//return true
	else
		return false;									//else return false
}
/// <summary>
/// change the key of the node which the value is the target.<para/>
/// In general, the newKey should be smaller than the old key.<para/>
/// </summary>
///
/// <parma name="target">
/// the target to change the key
/// </param>
///
/// <param name="newKey">
/// new key for the target
/// </param>
//void DecKey(TValue target, TKey newKey)
//{
//}

private:
/// <summary>
/// heap-sort, heapify.<para/>
/// this function can be called recursively
/// </summary>
void Heapify(int index)
{
	int current = index;								//start point of sorting
	int child = index * 2;								//child of start point

	if (child > m_vec.size() - 1) return;				//if child reach to last value, return

	std::pair < TKey, TValue > temp_;
	std::pair < TKey, TValue > temp_child = m_vec.at(child);       

	/*if child is lower than vector size - 1 */
	if (child < m_vec.size() - 1)
	{ 
		temp_ = m_vec.at(child + 1);					//temp_ is child's next vector's value
		if (temp_child.first > temp_.first) child++;	//if child's distance is bigger than temp_, move child to next
	}    

	temp_child = m_vec.at(current);						//current vector's value is child's value
	temp_ = m_vec.at(child);							//child + 1'st value is child (change each two child's value) 
	if (temp_.first < temp_child.first)					//if 			
	{
		m_vec.at(current) = temp_;						//change current vector's value to temp_ 
		m_vec.at(child) = temp_child;					//change child vector's value to temp_child

		Heapify(child);									//sorting
	}
}
};
#endif
