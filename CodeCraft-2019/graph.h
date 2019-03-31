#include "io_process.h"
#include <algorithm>
#include <map>
#define INF 1073741823

using namespace std;

class graph
{
public:
    vector<road> road_list;
    vector<cross> cross_list;
    int road_count;
    int cross_count;
    map<string,int> crossid_to_index; 
    vector<vector<int>> D;
    graph();
    graph(vector<road> Road,vector<cross> Cross);
    graph(const graph& rhs);
    vector<cross> Floyd(string cross_from,string cross_to);
    vector<cross> Dijkstra(string cross_from,string cross_to);
};

graph::graph(){}   
graph::graph(vector<road> Road,vector<cross> Cross)
{
    this->cross_list = Cross;
    this->road_list = Road;
    this->cross_count = Cross.size();
    this->road_count = Road.size();
    this->D.resize(this->cross_count);
    for(int i = 0;i<this->cross_count;i++)
    {
        vector<int> d(this->cross_count,INF);
        D[i]=d;
        cross c = this->cross_list[i];
        this->crossid_to_index.insert(pair<string,int>(c.id,i));   
        this->D[i][i] = 0;        
    }
    for(int i = 0;i<this->road_count;i++)
    {
        road r = this->road_list[i];
        int cross_from_index = this->crossid_to_index[r.from];
        int cross_to_index = this->crossid_to_index[r.to];
        this->D[cross_from_index][cross_to_index] = r.length;
        if(r.isDuplex){
            this->D[cross_to_index][cross_from_index] = r.length;
        }
    }
}

graph::graph(const graph& rhs)
{
    this->road_list = rhs.road_list;
    this->cross_list = rhs.cross_list;
    this->road_count = rhs.road_count;
    this->cross_count = rhs.cross_count;
    this->crossid_to_index = rhs.crossid_to_index;
    this->D = rhs.D;
}

vector<cross> graph::Floyd(string cross_from,string cross_to)
{
    int index_from = this->crossid_to_index[cross_from];
	int index_to = this->crossid_to_index[cross_to];
	const int n = this->cross_count;

	vector<vector<int>> FLOYD;
    FLOYD.resize(n);
    for(int i = 0;i<n;i++){
        vector<int> F(n,INF);
        FLOYD[i] = F;
    }
	int path[n][n];
	for(int i = 0; i<this->cross_count; i++){
		for(int j = 0; j<this->cross_count; j++){
			FLOYD[i][j] = this->D[i][j];
			path[i][j] = j;
		}
	}
	for(int k = 0; k<this->cross_count; k++){
		 for(int i = 0; i<this->cross_count; i++){
			 for(int j = 0; j<this->cross_count; j++){
				 if(FLOYD[i][j] > FLOYD[i][k]+FLOYD[k][j]){
					 FLOYD[i][j] = FLOYD[i][k]+FLOYD[k][j];
					 path[i][j] = path[i][k];
				 }
			 }
		 }
	 }
	 vector<cross> trace_cross_list;
	 int index_next = index_from;
	 while(index_next != index_to){
		 trace_cross_list.push_back(this->cross_list[index_next]);
         //cout<<this->cross_list[index_next].id<<"->";
		 index_next = path[index_next][index_to];
	 }
	trace_cross_list.push_back(this->cross_list[index_to]);
    //cout<<this->cross_list[index_to].id<<endl;
    //  for(unsigned int i = 0; i<trace_cross_list.size();i++){
    //      cout<<trace_cross_list[i].id<<"->";
    //  }
    // cout<<endl;
	return trace_cross_list;
}
vector<cross> graph::Dijkstra(string cross_from,string cross_to)
{
    int index_from = this->crossid_to_index[cross_from];
    int index_to = this->crossid_to_index[cross_to];
    vector<int> distance_list = this->D[index_from];
    vector<int> unvisited_distance_list = this->D[index_from];
    unvisited_distance_list[index_from] = INF;
    vector<int> path_list;
    for(int i = 0;i<this->cross_count;i++){
        path_list.push_back(i);
        
    }
    auto min = min_element(unvisited_distance_list.begin(),unvisited_distance_list.end());
    int min_unvisited_distance = *min;
    while(min_unvisited_distance != INF){
        auto index_of_min = distance(unvisited_distance_list.begin(),min);
        for(int i = 0; i<this->cross_count; i++){
            if(distance_list[i] > min_unvisited_distance + this->D[index_of_min][i]){
                distance_list[i] = min_unvisited_distance + this->D[index_of_min][i];
                unvisited_distance_list[i] = distance_list[i];
                path_list[i] = index_of_min;
            }
        }
        unvisited_distance_list[index_of_min] = INF;
        min = min_element(unvisited_distance_list.begin(),unvisited_distance_list.end());
        min_unvisited_distance = *min;
    }

    vector<cross> trace_cross_list; 
    trace_cross_list.push_back(this->cross_list[index_to]);
    int index_previous = path_list[index_to];
    while(index_previous != path_list[index_previous]){
        trace_cross_list.push_back(this->cross_list[index_previous]);
        index_previous = path_list[index_previous];
    }
    trace_cross_list.push_back(this->cross_list[index_previous]);
    trace_cross_list.push_back(this->cross_list[index_from]);
    reverse(trace_cross_list.begin(),trace_cross_list.end());
    return trace_cross_list;
}