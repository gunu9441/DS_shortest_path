#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define DFS_FIRST_PATH

using namespace std;
Graph::Graph()
{
	m_pVHead = NULL;
	m_vSize = 0;
	// TODO: implement
}
Graph::~Graph()
{
	Vertex* temp = m_pVHead;
	while(temp)
	{
		Vertex* deleted = temp;
		Edge* deleted_temp = temp->GetHeadOfEdge();
		while(deleted_temp)
		{
			Edge* deleted = deleted_temp;
			deleted_temp = deleted_temp->GetNext();
			delete deleted;
		}
		temp = temp->GetNext();
		delete deleted;
	}
	// TODO: implement
}

/// <summary>
/// add vertex with vertexNum at the end of the linked list for the vertics
/// </summary>
///
/// <param name="vertexKey">
/// the key for the vertex
/// </param>
void Graph :: AddVertex(int vertexKey)
{
	Vertex* new_vertex = new Vertex(vertexKey);									//allocate new Vertex

	if (m_pVHead == NULL) { m_pVHead = new_vertex; m_vSize++; return; }			//if there are no vertex
	
	Vertex* cur = m_pVHead;														//'cur' is Vertex pointer that point head

	while (cur->GetNext()) { cur = cur->GetNext(); }							//find location of new data

	m_vSize++;																	//count up size

	cur->SetNext(new_vertex); return;											//current pointer's next is new vertex
}
/// <summary>
/// add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
/// [startVertexKey] ---weight---> [endVertexKey]
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key of the edge
/// </param>
/// <param name="endVertexKey">
/// the end vertex key of the edge
/// </param>
/// <param name="weight">
/// the weight of the edge
/// </param>
void Graph :: AddEdge(int startVertexKey, int endVertexKey, int weight)
{
	if (m_vSize == 1)															//if the size of vetex is 1
	{
		m_pVHead->AddEdge(endVertexKey, weight);								//add edge to head
		return;																	//end
	}

	Vertex* cur = m_pVHead;														//vertex pointer that is initialize to head

	/*find vertex that has startkey*/
	while (cur)
	{
		if (cur->GetKey() == startVertexKey) break;								//if current vertex key is start key, break loop
		cur = cur->GetNext();													//move vertex pointer to next
	}
	cur->AddEdge(endVertexKey, weight);											//if we find proper vertex, add edge
	return;																		//end of function
}
/// <summary>
/// get the vertex which the key is vertexNum
/// </summary>
///
/// <param name="key">
/// the key of the vertex to find
/// </param>
///
/// <returns>
/// the vertex which the key is vertexNum
/// </returns>
Vertex* Graph :: FindVertex(int key)
{
	Vertex* cur = m_pVHead;											//vertex pointer
	
	/*find target vertex*/
	while (cur)
	{
		if (cur->GetKey() == key) { break; }						//find target vertex
		cur = cur->GetNext();										//move vertex pointer to next
	}
	if (cur == NULL) { return NULL; }								//cant find target vertex
	else return cur;												//find target vertex and return vertex
}
/// <summary>
/// get the number of the vertics
/// </summary>
///
/// <returns>
/// the number of the vertics
/// </returns>
int Graph :: Size() const
{
	Vertex* cur = m_pVHead;								//vertex pointer
	int counter = 0;									//variable that count size of vertex

	while (cur)
	{
		counter++;										//increase counter
		cur = cur->GetNext();							//move vertex pointer to next
	}
	return counter;										//return size of vertex
}
/// <summary>
/// memory free for the vertics
/// </summary>
void Graph :: Clear()
{
	Vertex* cur = m_pVHead;								//vertex pointer
	Vertex* temp;										//variable that store vertex to be earased

	while(cur)
	{
		temp = cur;										//store vertex to be earased
		cur = cur->GetNext();							//move vertex pointer to next

		delete temp;									//delete target vertex
	}
	return;												//end of function
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <param name="fout">
/// file stream for the result log
/// </param>
void Graph :: Print(std::ofstream& fout)
{
	Vertex* cur_vertex = m_pVHead;						//pointer that stoer vertex
	Edge* cur_edge;										//variable that store edge	
		
	fout << "====== PRINT ======" << endl;

	for (int i = 0; i < m_vSize; i++)
	{
		cur_edge = cur_vertex->GetHeadOfEdge();							//set edge pointer
		/*if there are no value*/
		if (cur_edge == NULL)											//if current edge is NULL
		{
			for (int j = 0; j < m_vSize; j++) { fout << "0 "; }			//file out 0
		}
		/*if there are edge*/
		else
		{
			for (int j = 0; j < m_vSize; j++)
			{
				if (j < cur_edge->GetKey()) fout << "0" << " ";			//if edge's number is not correct to j variable, file out 0
				else if (j == cur_edge->GetKey())						//if we find edge's number
				{
					fout << cur_edge->GetWeight() << " ";				//print out current edge's weight
					if (cur_edge->GetNext() != NULL) cur_edge = cur_edge->GetNext();			//move pointer to next
				}
				else fout << "0" << " ";								//if current edge's number is lower than j, file out 0
			}
		}
		fout << endl;							
		cur_vertex = cur_vertex->GetNext();					//move to next vertex pointer
	}
	fout << "===================" << endl << endl;
	return;													//end of function
}
/// <summary>
/// check whether the graph has negative edge or not.
/// </summary>
///
/// <returns>
/// true if the graph has negative edge.
/// false otherwise.
/// </returns>
bool Graph :: IsNegativeEdge()
{
	Vertex* cur_ver = m_pVHead;
	Edge* cur_edge;

	while (cur_ver)
	{
		cur_edge = cur_ver->GetHeadOfEdge();				//set edge pointer

		while (cur_edge)
		{
			if (cur_edge->GetWeight() < 0) { return true; }	//print edge to text
			cur_edge = cur_edge->GetNext();					//move to next edge
		}
		cur_ver = cur_ver->GetNext();					//move to next vertex pointer
	}
	return false;										//if there are no negative edge, return false
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with DFS (stack)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// the key list of the vertics which are included in the path<para/>
/// the last element should be the total cost<para/>
/// for the special case, it would be others
/// </returns>
std::vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey)

{
	Vertex* cur = m_pVHead;								//first vertex
	pair<int, int> pair_data;							//pair<current vertex number, previous vertex number>
	Stack<pair<int,int> > stack;							//stack that store pair<current vertex number, previous vertex number>
	vector<int> v;										//vector that store path
	Edge* next;

	int vec_num = 0;
	int count = 0;
	bool* visited = new bool[m_vSize];									//check visited vertex

	for (int i = 0; i < m_vSize; i++) { visited[i] = false; }			//initialize array

	/*Find the most first Vertex*/
	while (cur)
	{
		if (cur->GetKey() == startVertexKey) break;						//find target vertex
		cur = cur->GetNext();											//move vertex pointer to next
	}

	/*Push Most first Vertex*/
	pair_data = make_pair(cur->GetKey(), vec_num);						//make pair (current key value, vector number)
	stack.Push(pair_data);												//input vertex key value to stack

	v.push_back(stack.Top().first);										//input top value's key to vector
	visited[stack.Top().first] = true;									//input vertex to stack
	stack.Pop();														//Pop stack

	vec_num++;															//Plus vector number

	/*'next' is adjacent Vertex*/ /*start of targeting*/
	while (1)
	{
		next = cur->GetHeadOfEdge();									//the most adjacent vertex list
		while (next)
		{
			pair_data = make_pair(next->GetKey(), vec_num);				//make pair (edge's key, vector number)
			stack.Push(pair_data);										//push data to stack
			if (visited[next->GetKey()] == true) { stack.Pop(); }		//if key is already exist
			else count++;												//if key is the first value, count up 

			//if (next->GetNext() == NULL) break;							//if the end of edge, break the loop
			next = next->GetNext();										//move edge pointer to next
		}

		/*if we reach to dead end*/
		if (count == 0) 													//if key is already exist
		{
			int vec_size = v.size();										//store size of vector
			/*find vertex that are false*/
			while (visited[stack.Top().first] != false) { stack.Pop(); }			//if stack's top value is already exist in vector, pop stack
			/*remove vertex from vector*/
			for (int i = stack.Top().second; i < vec_size; i++) { v.pop_back(); }	//remove vector element
		}

		count = 0;																	//initialization

		v.push_back(stack.Top().first);												//input top value's key to vector
		visited[stack.Top().first] = true;											//input vertex to stack
		/*end of targeting*/
		if (stack.Top().first == endVertexKey) { stack.Pop(); break; }				//if pointer reach to end vertex
		
		stack.Pop();																//pop from stack because we put to vector
		cur = m_pVHead;																//initialize to head
		while (cur->GetKey() != v.back()) {cur = cur->GetNext();}					//find target vertex
		vec_num++;																	//increase vectore number
	}
	/*make total weight*/
	Vertex* cur_ver = m_pVHead;
	Edge* cur_edge;
	int total_weight = 0;

	for (int i = 0; i < v.size()-1 ; i++)
	{
		cur_ver = m_pVHead;															//initialize to head
		while (cur_ver->GetKey() != v[i]) { cur_ver = cur_ver-> GetNext(); }		//find target vertex
		cur_edge = cur_ver->GetHeadOfEdge();										//first edge of one vertex
		while (1)
		{
			if (cur_edge->GetKey() == v[i + 1]) { total_weight += cur_edge->GetWeight(); break; }
			else cur_edge = cur_edge->GetNext();
		}
	}
	v.push_back(total_weight);											//push total weight to vector
	return  v;															//return vector
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// the key list of the vertics which are included in the shortest path<para/>
/// the last element should be the total cost<para/>
/// for the special case, it would be others
/// </returns>
std::vector<int> Graph :: FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	set<pair<int, pair<int, int> > > s;
	pair<int, int> small_pair_data;										//pair data
	pair<int, pair<int, int> > big_pair_data;							//pair data that store distance, current vertex, previous vertex
	set<pair<int, pair<int,int> > > ::iterator it;						//distance, ver_num, prev_ver_num
	vector<int> v;														//vector that store path
	Edge* cur_edge;														//store current edge

	int counter = 0;
	int prev_ver_num = startVertexKey;

	int* distance = new int[m_vSize];									//array that check distance
	int* visit = new int[m_vSize];										//array that check visit
	int* path = new int[m_vSize];										//array that check previous vertex

	/*initialize each array*/
	for (int i = 0; i < m_vSize; i++) { distance[i] = 900; }
	for (int i = 0; i < m_vSize; i++) { visit[i] = 0; }
	for (int i = 0; i < m_vSize; i++) { path[i] = -1; }

	Vertex* cur_ver = m_pVHead;											//current vertex pointer

	/*Start*/
	while (cur_ver->GetKey() != startVertexKey) { cur_ver = cur_ver->GetNext(); }			//find startvertex

	distance[cur_ver->GetKey()] = 0;														//set startvertex's distance to 0

	visit[cur_ver->GetKey()] = 1;															//set current vertex's visit to 1
	
	while (1)
	{
		cur_edge = cur_ver->GetHeadOfEdge();																//cur_edge is current vertex's head edge
		/*set adjacent vertex's distance*/
		while (1)
		{
			if (visit[cur_edge->GetKey()] != 1 && distance[cur_edge->GetKey()] > distance[cur_ver->GetKey()] + cur_edge->GetWeight())		//if current edge is never visited, distance is bigger than updated distance(current vertex's distance + edge weight)
			{
				distance[cur_edge->GetKey()] = distance[cur_ver->GetKey()] + cur_edge->GetWeight();			//current edge's distance is updated distance(current vertex's distance + edge weight)
				path[cur_edge->GetKey()] = cur_ver->GetKey();												//current edge's path is current edge
				small_pair_data = make_pair(cur_edge->GetKey(), prev_ver_num);								//make pair that store current edge and previous vertex
				big_pair_data = make_pair(distance[cur_edge->GetKey()],small_pair_data);					//make pair that store distance, current edge and previous vertex
				s.insert(big_pair_data);																	//insert to set
			}
			if (cur_edge->GetNext() == NULL) break;															//if we reach to end, break the loop
			cur_edge = cur_edge->GetNext();																	//move to next edge
		}//small while

		it = s.begin();												//the first element of set

		visit[it->second.first] = 1;								//set smallest vertex's vist to 1

		/*if we find lowest path, the first element of set is endvertexKety*/
		if (it->second.first == endVertexKey)
		{
			int vec_num = it->second.second;
			v.push_back(it->first);									//input total weight to vector
			v.push_back(it->second.first);							//push vertex number
			while (1)
			{
				v.push_back(vec_num);								//push vertex number to vector
				if (vec_num == startVertexKey) break;				//if vertex number is start key, break the loop
				vec_num = path[vec_num];							//vec_num is next previous vertex number
			}
			return v;												//return vector
		}
		/*set vertex pointer to new vertex*/
		cur_ver = m_pVHead;											
		while (1)
		{
			if (cur_ver->GetKey() == it->second.first) break;
			else cur_ver = cur_ver->GetNext();
		}
		prev_ver_num = cur_ver->GetKey();							//store vertex number before changing
		s.erase(it);												//pop the most first value
	}//big while
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// the key list of the vertics which are included in the shortest path<para/>
/// the last element should be the total cost<para/>
/// for the special case, it would be others
/// </returns>
std::vector<int> Graph :: FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	MinHeap <int, pair<int, int> > MHeap;								
	pair<int, int> small_pair_data;										//pair data that store current vertex number and previous vertex number
	vector<int> v;														//vector that store path
	Edge* cur_edge;	

	int counter = 0;
	int prev_ver_num = startVertexKey;

	int* distance = new int[m_vSize];									//array that check distance
	int* visit = new int[m_vSize];										//array that check visit
	int* path = new int[m_vSize];										//array that check previous vertex

	/*initialize each array*/
	for (int i = 0; i < m_vSize; i++) { distance[i] = 900; }
	for (int i = 0; i < m_vSize; i++) { visit[i] = 0; }
	for (int i = 0; i < m_vSize; i++) { path[i] = -1; }

	Vertex* cur_ver = m_pVHead;

	/*Start*/
	while (cur_ver->GetKey() != startVertexKey) { cur_ver = cur_ver->GetNext(); }			//find startvertex

	distance[cur_ver->GetKey()] = 0;														//set startvertex's distance to 0

	visit[cur_ver->GetKey()] = 1;															//set startvertex's visit to 1

	while (1)
	{
		cur_edge = cur_ver->GetHeadOfEdge();
		/*set adjacent vertex's distance*/ /*update*/
		while (cur_edge)
		{
			/*if current edge is never visited, current edge's distance is bigger than updated distance(current vertex distance + current edge's weight)*/
			if (visit[cur_edge->GetKey()] != 1 && distance[cur_edge->GetKey()] > distance[cur_ver->GetKey()] + cur_edge->GetWeight())
			{
				distance[cur_edge->GetKey()] = distance[cur_ver->GetKey()] + cur_edge->GetWeight();
				path[cur_edge->GetKey()] = cur_ver->GetKey();
				small_pair_data = make_pair(cur_edge->GetKey(), prev_ver_num);
				MHeap.Push(distance[cur_edge->GetKey()], small_pair_data);
			}
			cur_edge = cur_edge->GetNext();
		}//small while

		pair<int, pair<int, int> > it = MHeap.Top();								//the first element of set

		visit[it.second.first] = 1;												//set smallest vertex's vist to 1

		/*if we find lowest path, the first element of set is endvertexKety*/
		if (it.second.first == endVertexKey)
		{
			int vec_num = it.second.second;
			v.push_back(it.first);												//input total weight to vector
			v.push_back(it.second.first);										//push vertex number
			while (1)
			{
				v.push_back(vec_num);
				if (vec_num == startVertexKey) break;							//if we push every path to vector, break the loop
				vec_num = path[vec_num];										//vector number is current vector number's path value
			}
			return v;
		}

		/*set vertex pointer to new vertex*/
		cur_ver = m_pVHead;
		while (1)
		{
			if (cur_ver->GetKey() == it.second.first) break;
			else cur_ver = cur_ver->GetNext();
		}
		prev_ver_num = cur_ver->GetKey();
		MHeap.Pop();													//pop the most first value
	}//big while
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// the key list of the vertics which are included in the shortest path<para/>
/// the last element should be the total cost<para/>
/// for the special case, it would be others
/// </returns>
std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	Vertex* cur_ver = m_pVHead;
	vector<int> v;														//store way and total weight
	Edge* cur_edge;
	int find_ver;
	int temp_vertex;
	int* distance = new int[m_vSize];									//array that check distance
	int* path = new int[m_vSize];										//array that check previous vertex

	/*initialize each array*/
	for (int i = 0; i < m_vSize; i++) { distance[i] = 999; }
	for (int i = 0; i < m_vSize; i++) { path[i] = -1; }

	/*find first vertex and update first vertex's distance*/
	while (1)
	{
		if (cur_ver->GetKey() == startVertexKey) { break; }			//we find start vertex
		else cur_ver = cur_ver->GetNext();
	}	

	distance[cur_ver->GetKey()] = 0;
	
	/*start of Process*/
	for (int i = 0; i < m_vSize; i++)
	{
		cur_ver = m_pVHead;
		while (cur_ver)
		{/*search adjacent vertex*/
			cur_edge = cur_ver->GetHeadOfEdge();
			while (cur_edge)
			{
				if (distance[cur_edge->GetKey()] > distance[cur_ver->GetKey()] + cur_edge->GetWeight())
				{
					distance[cur_edge->GetKey()] = distance[cur_ver->GetKey()] + cur_edge->GetWeight();					//add previous distance and current weight to current edge's distance		
					path[cur_edge->GetKey()] = cur_ver->GetKey();														//input previous vertex to current edge's path
				}
				cur_edge = cur_edge->GetNext();																		//move pointer
			}
			cur_ver = cur_ver->GetNext();
		}
	}//big for state

/*check negative weight*/
	bool neg_check = false;

	cur_ver = m_pVHead;
	while (cur_ver)
	{/*search adjacent vertex*/
		cur_edge = cur_ver->GetHeadOfEdge();
		while (cur_edge)
		{
			/*if current edge's distance is bigger than updated distance(current vertex distance + current edge's weight)*/
			if (distance[cur_edge->GetKey()] > distance[cur_ver->GetKey()] + cur_edge->GetWeight())
			{
				distance[cur_edge->GetKey()] = distance[cur_ver->GetKey()] + cur_edge->GetWeight();					//add previous distance and current weight to current edge's distance		
				path[cur_edge->GetKey()] = cur_ver->GetKey();														//input previous vertex to current edge's path
				neg_check = true;																					//negative check variable is true(it means negative cycle is exist)
			}
			cur_edge = cur_edge->GetNext();																			//move pointer
		}
		cur_ver = cur_ver->GetNext();
	}

	/*negative weight is exist*/
	if (neg_check == true) { v.push_back(900); return v; }		

	/*negative weight is not exist*/
	else
	{
		int number = endVertexKey;
		v.push_back(distance[number]);
		while (1)
		{
			v.push_back(number);
			if (number == startVertexKey) break;
			number = path[number];
		}
		return  v;
	}

}
