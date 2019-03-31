#include "graph.h"
using namespace std;
class dispatcher
{
public:
    vector<car> car_list;
    vector<road> road_list;
    vector<cross> cross_list;
    graph G;
    map<string,road> crossIds_to_road;
    dispatcher(vector<car> Car,vector<road> Road,vector<cross> Cross);
    vector<result> go();
    void sort_plantime();
};

class CompLess
{
public:
    bool operator ()(const car& Item1, const car& Item2) 
    { 
        return Item1.plantime < Item2.plantime; 
    }
};

dispatcher::dispatcher(vector<car> Car,vector<road> Road,vector<cross> Cross)
{ 
    this->car_list = Car;
    this->road_list = Road;
    this->cross_list = Cross;
    graph g(Road,Cross);
    this->G = g;
    for(unsigned int i = 0;i<Road.size();i++){
        string crossIds = Road[i].from + "to" + Road[i].to;
        this->crossIds_to_road.insert(pair<string,road>(crossIds,Road[i]));
        if(Road[i].isDuplex){
            crossIds = Road[i].to + "to" + Road[i].from;
            this->crossIds_to_road.insert(pair<string,road>(crossIds,Road[i]));
        }
    }
}

vector<result> dispatcher::go()
{
    sort_plantime();
    vector<result> result_list;
    int counter = 0;
    int time_counter = 0;
    int timer[3] = {15,15,15};
    for(unsigned int i = 0;i<this->car_list.size();i++)
    {
        
        string from = this->car_list[i].from;
        string to = this->car_list[i].to;
        vector<cross> cross_list;
        cross_list = this->G.Floyd(from,to);
        // for(unsigned int i = 0; i<cross_list.size();i++){
        //  cout<<cross_list[i].id<<"->";
        // }
        //cout<<endl;
        vector<road> road_list;
        for(unsigned int j = 0; j<cross_list.size()-1;j++){
            string crossIds = cross_list[j].id + "to" + cross_list[j+1].id;
            road_list.push_back(this->crossIds_to_road[crossIds]);
            //if(j==cross_list.size()-2) cout<<crossIds<<" "<<road_list[j].id<<" "<<this->crossIds_to_road[crossIds].id<<endl;
        }
        
        //cout<<road_list[road_list.size()-1].id<<endl;
        result res(this->car_list[i],this->car_list[i].plantime + counter/timer[time_counter],road_list);
        result_list.push_back(res);
        counter += 1;
        if(counter > (int)(car_list.size()/3) && counter <= (int)(2*car_list.size()/3)) time_counter = 1;
        if(counter > (int)(2*car_list.size()/3)) time_counter = 2;
    }
    return result_list;
}

void dispatcher::sort_plantime()
{
    vector<car> car_list_sorted;
    vector<int> key_list;
    map<int,vector<car>> speed_to_cars;
    for(unsigned int i = 0;i<this->car_list.size();i++){
        if(speed_to_cars.count(this->car_list[i].maxspeed)>0){
            speed_to_cars[this->car_list[i].maxspeed].push_back(this->car_list[i]);
        }
        else{
            vector<car> che;
            che.push_back(car_list[i]);
            key_list.push_back(this->car_list[i].maxspeed);
            speed_to_cars.insert(pair<int,vector<car>>(this->car_list[i].maxspeed,che));
        }
    }

    sort(key_list.rbegin(),key_list.rend());
    vector<vector<car>> car_list_temp;
    for(unsigned int i = 0;i<key_list.size();i++){
        sort(speed_to_cars[key_list[i]].begin(),speed_to_cars[key_list[i]].end(),CompLess());
        vector<car> cc;
        for(unsigned int j = 0;j<speed_to_cars[key_list[i]].size();j++){
            cc.push_back(speed_to_cars[key_list[i]][j]);
            car_list_sorted.push_back(speed_to_cars[key_list[i]][j]);
        }
        car_list_temp.push_back(cc);
    }
    this->car_list = car_list_sorted;
}