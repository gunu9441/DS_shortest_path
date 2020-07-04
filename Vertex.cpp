#include "Vertex.h"

Vertex :: Vertex()
{
	m_key = NULL;
	m_size = NULL;
	m_pEHead = NULL;
	m_pNext = NULL;
}
Vertex::Vertex(int key)
{
	m_key = key;
	m_size = NULL;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex :: ~Vertex()
{
}


/// <summary>
/// set the next pointer of this vertex
/// </summary>
void Vertex::SetNext(Vertex* pNext) { m_pNext = pNext; }
/// <summary>
/// get the key of this vertex
/// </summary>
///
/// <returns>
/// the key of this vertex
/// </returns>
int Vertex::GetKey() const { return m_key; }
/// <summary>
/// get the next pointer of this vertex
/// </summary>
///
/// <returns>
/// the next pointer of this vertex
/// </returns>
Vertex* Vertex::GetNext() const { return m_pNext; }
/// <summary>
/// get the number of the edges
/// </summary>
///
/// <returns>
/// the number of the edges
/// </returns>

int Vertex :: Size() const
{
	Edge* cur = m_pEHead;
	int counter = 0;

	while (cur->GetNext()) { cur = cur->GetNext(); counter++; }

	return  counter;
}
/// <summary>
/// add edge with edgeNum at the end of the linked list for the edges
/// </summary>
///
/// <param name="edgeKey">
/// the key of the vertex for the edge
/// </param>
/// <param name="weight">
/// the weight of the edge
/// </param>
void Vertex::AddEdge(int edgeKey, int weight)
{
	Edge* cur = m_pEHead;

	Edge * new_edge = new Edge(edgeKey, weight);			//allocate edge

	if (cur == NULL) { m_pEHead = new_edge; m_size++; return; }

	while (cur->GetNext() != NULL) { cur = cur->GetNext(); }

	cur->SetNext(new_edge);

	m_size++;
}
/// <summary>
/// get the head pointer of the edge
/// </summary>
///
/// <returns>
/// the ehad pointer of the edge
/// </returns>
Edge* Vertex::GetHeadOfEdge() const { return m_pEHead; }
/// <summary>
/// memory free for edges
/// </summary>
void Vertex::Clear() 
{
	Edge* deleted = m_pEHead;
	Edge* temp;

	while (deleted)
	{	
		temp = deleted;									//store deleted data
		deleted = deleted->GetNext();					//move to next deleted data

		delete temp;									//delete temp data
	}
	return;


}
