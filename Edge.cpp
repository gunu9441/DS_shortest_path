#include "Edge.h"

Edge::Edge() { m_key = NULL; m_weight = NULL; m_pNext = NULL; }
Edge :: Edge(int key, int weight) { m_key = key; m_weight = weight; m_pNext = NULL;}

/// <summary>
/// set the next pointer of this edge
/// </summary>
///
/// <param name="pNext">
/// the next pointer of this edge
/// </param>
void Edge :: SetNext(Edge* pNext) { m_pNext = pNext; }
/// <summary>
/// get the key of this edge
/// </summary>
///
/// <returns>
/// the key of this edge
/// </returns>
int Edge :: GetKey() const { return m_key; }
/// <summary>
/// get the weight of this edge
/// </summary>
///
/// <returns>
/// the weight of this edge
/// </returns>
int Edge :: GetWeight() const { return m_weight; }
/// <summary>
/// get the next pointer of this edge
/// </summary>S
///
/// <returns>
/// the next pointer of this edge
/// </returns>
Edge* Edge :: GetNext() const { return m_pNext; }