#include "Manager.h"
#include <cstring>
#include <algorithm>

#pragma warning(disable:4996)

using namespace std;
/*De*/
Manager::~Manager()
{
	if (fout.is_open())
		fout.close();
}

void Manager::Run(const char* filepath)
{
	ifstream fin;																	//Input file
	fin.open(filepath);

	fout.open(RESULT_LOG_PATH,ios::app);

	Result result;

	if (!fin) { 
		result = CommandFileNotExist;
		fout << "====== SYSTEM ======" << endl;
		fout << "CommandFileNotExist" << endl;
		fout << "====================" << endl;
		return; }
	
	char line[128] = { 0 };																//Variable that store one line
	char line2[128] = { 0 };
	char* CMM = NULL;																			//Store command																		//Store after command
	
	/*Read txt file*/
	while (fin.getline(line, 64))
	{																						//Store command	
		CMM = strtok(line, " \n");
		if (strcmp(CMM, "LOAD")==0)
		{
			char* ARR;
			ARR = strtok(NULL, " ");
			result = Load(ARR);
		}															

		else if (strcmp(CMM, "PRINT") == 0) {
			result = Print(); 
		}

		else if (strcmp(CMM, "DFS")==0)
		{
			char* start = strtok(NULL, " ");;
			char* end = strtok(NULL, " ");;

			/*exception handling*/
			if (start == NULL || end == NULL) result = VertexKeyNotExist;
			else if (atoi(start) < 0 || atoi(end) < 0) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(start)) == NULL) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(end)) == NULL) result = InvalidVertexKey;
			else result = FindPathDfs(atoi(start), atoi(end));
			
		}

		else if (strcmp(CMM, "DIJKSTRA")==0)
		{
			char* start = strtok(NULL, " ");;
			char* end = strtok(NULL, " ");;

			/*exception handling*/
			if (start == NULL || end == NULL) result = VertexKeyNotExist;
			else if (atoi(start) < 0 || atoi(end) < 0) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(start)) == NULL) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(end)) == NULL) result = InvalidVertexKey;
			else result = FindShortestPathDijkstraUsingSet(atoi(start), atoi(end));
			
		}

		else if (strcmp(CMM, "DIJKSTRAMIN")==0)
		{
			char* start = strtok(NULL, " ");;
			char* end = strtok(NULL, " ");;

			/*exception handling*/
			if (start == NULL || end == NULL) result = VertexKeyNotExist;
			else if (atoi(start) < 0 || atoi(end) < 0) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(start)) == NULL) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(end)) == NULL) result = InvalidVertexKey;
			else result = FindShortestPathDijkstraUsingMinHeap(atoi(start), atoi(end));
			
		}

		else if (strcmp(CMM, "BELLMANFORD")==0)
		{
			char* start = strtok(NULL, " ");;
			char* end = strtok(NULL, " ");;

			/*exception handling*/
			if (start == NULL || end == NULL) result = VertexKeyNotExist;
			else if (atoi(start) < 0 || atoi(end) < 0) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(start)) == NULL) result = InvalidVertexKey;
			else if (m_graph.FindVertex(atoi(end)) == NULL) result = InvalidVertexKey;
			else result = FindShortestPathBellmanFord(atoi(start), atoi(end));
		}
		else
		{
			fout << "===== " << CMM << " =====" << endl;
			fout << "NonDefinedCommand" << endl;
			fout << "==================" << endl;
			result = NonDefinedCommand;
		}
		PrintError(result,CMM);
	}
	return;
	// TODO: implement
}
void Manager::PrintError(Result result, char* CMM)
{
	if (result != Success)
	{
		if (result == LoadFileNotExist) {
			fout << "===== " << CMM << " =====" << endl;
			fout << "LoadFileNotExist" << endl;
			fout << "==================" << endl;
		}
		else if (result == GraphNotExist) {
			fout << "===== " << CMM << " =====" << endl;
			fout << "GraphNotExist" << endl;
			fout << "==================" << endl;
		}
		else if (result == VertexKeyNotExist) {
			fout << "===== " << CMM << " =====" << endl;
			fout << "VertexKeyNotExist" << endl;
			fout << "==================" << endl;
		}
		else if (result == InvalidVertexKey) {
			fout << "===== " << CMM << " =====" << endl;
			fout << "InvalidVertexKey" << endl;
			fout << "==================" << endl;
		}
		else if (result == InvalidAlgorithm) {
			fout << "===== " << CMM << " =====" << endl;
			fout << "InvalidAlgorithm" << endl;
			fout << "==================" << endl;
		}
		else if (result == NegativeCycleDetected) {
			fout << "===== " << CMM << " =====" << endl;
			fout << " NegativeCycleDetected " << endl;
			fout << "==================" << endl;
		}
		fout << endl;
	}
	fout << "=================" << endl;
	fout << "Error code: " << result << endl;
	fout << "=================" << endl << endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
	ifstream fin_map;
	fin_map.open("mapdata.txt");

	if (fin_map.fail()) { return LoadFileNotExist; }

	int input_size;
	int weight;
	char line[40] = { 0, };

	fin_map.getline(line, 40);															//get one line
	input_size = atoi(strtok(line, " "));											//get size of matrix

	for (int i = 0; i < input_size; i++)											//count row
	{
		fin_map.getline(line, 40);														//get next one line
		m_graph.AddVertex(i);
		weight = atoi(strtok(line, " "));											//get one number
		for (int j = 0; j < input_size; j++)
		{
			if (weight != 0) { m_graph.AddEdge(i, j, weight); }						//add edge to gragh
			if(j != (input_size - 1)) weight = atoi(strtok(NULL, " "));				//get one number
		}
	}

	fout << "===== LOAD =====" << endl;
	fout << "Success" << endl;
	fout << "================" << endl << endl;
	return Success;
	// TODO: implement
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
	if (m_graph.Size() == 0)
	{
		//PrintError_one(GraphNotExist);	//if there are no data
		return GraphNotExist;
	}
	m_graph.Print(fout);
	return Success;
	// TODO: implement
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) return GraphNotExist;											//exception handling
	else if (m_graph.IsNegativeEdge() == true) return InvalidAlgorithm;						//if there are negative number in map
	
	std::vector<int> re_DFS = m_graph.FindPathDfs(startVertexKey, endVertexKey);

	fout << "===== DFS =====" << endl;
	//Print by vector 
	fout << "shortest path: ";
	for (int i = 0; i < re_DFS.size()-1; i++)
	{
		fout << re_DFS[i] << " ";
	}
	fout << endl;
	fout << "sorted nodes: ";
	sort(re_DFS.begin(), re_DFS.end()-1);
	for (int i = 0; i < re_DFS.size() - 1; i++)
	{
		fout << re_DFS[i] << " ";
	}
	fout << endl;
	fout << "path length: "<<re_DFS[re_DFS.size()-1];
	fout << endl;
	fout << "================" << endl << endl;
	return Success;
	// TODO: implement
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { return GraphNotExist; }											//if there are no data in graph
	else if (m_graph.IsNegativeEdge() == true) return InvalidAlgorithm;							//if there are negative number in map
	std::vector<int> re_Dijkstra = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);

	fout << "===== DIJKSTRA =====" << endl;	//Print by vector 
	fout << "shortest path: ";
	for (int i = re_Dijkstra.size() - 1; i > 0 ; i--)
	{
		fout << re_Dijkstra[i] << " ";
	}
	fout << endl;
	fout << "sorted nodes: ";
	sort(re_Dijkstra.begin()+1, re_Dijkstra.end());
	for (int i = 1; i < re_Dijkstra.size(); i++)
	{
		fout << re_Dijkstra[i] << " ";
	}
	fout << endl;
	fout << "path length: " << re_Dijkstra[0];
	fout << endl;
	fout << "================" << endl << endl;
	return Success;
	// TODO: implement
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { return GraphNotExist; }											//if there are no data in graph
	else if (m_graph.IsNegativeEdge() == true) return InvalidAlgorithm;							//if there are negative number in map
	std::vector <int> v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);
	fout << "===== DIJKSTRAMIN =====" << endl;
	fout << "shortest path: ";
	for (int i = v.size() - 1; i > 0; i--)
	{
		fout << v[i] << " ";
	}
	fout << endl;
	fout << "sorted nodes: ";
	sort(v.begin() + 1, v.end());
	for (int i = 1; i < v.size(); i++)
	{
		fout << v[i] << " ";
	}
	fout << endl;
	fout << "path length: " << v[0];
	fout << endl;
	fout << "================" << endl << endl;
	return Success;
	// TODO: implement
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
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0) { return GraphNotExist; }									//if there are no data in graph
	std::vector <int> v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);
		
	if (v.back() == 900) return NegativeCycleDetected;									//detect negative cycle 

	fout << "===== BELLMANFORD =====" << endl;
	fout << "shortest path: ";
	for (int i = v.size() - 1; i > 0; i--){
		fout << v[i] << " ";						//print out path
	}
	fout << endl;
	fout << "sorted nodes: ";
	sort(v.begin() + 1, v.end());
	for (int i = 1; i < v.size(); i++)
	{
		fout << v[i] << " ";
	}
	fout << endl;
	fout << "path length: " << v[0];
	fout << endl;
	fout << "================" << endl << endl;
	return Success;
	// TODO: implement
}
