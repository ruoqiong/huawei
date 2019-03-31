#include<string>
#include<vector>
using namespace std;

//split data like (x,x,x,x)
vector<string> split_data(string a)
{
	vector<string> rec;
	int j = 1;
	for(unsigned int i = 1;i<a.size()-1;i++){
		if(a[i]==','){
			rec.push_back(a.substr(j,i-j));
			j = i+2;
		}
	}
	rec.push_back(a.substr(j,a.size()-1-j));
	return rec;
}

class road
{
public:
	string id;
	int length;
	int maxspeed;
	int channel;
	string from;
	string to;
	bool isDuplex;
	road(){}
	road(vector<string>rec){
		this->id = rec[0];
		this->length = atoi(rec[1].c_str());
		this->maxspeed = atoi(rec[2].c_str());
		this->channel = atoi(rec[3].c_str());
		this->from = rec[4];
		this->to = rec[5];
		this->isDuplex = (rec[6]=="1");
	}
	road(const road& r){
		this->id = r.id;
		this->length = r.length;
		this->maxspeed = r.maxspeed;
		this->channel = r.channel;
		this->from = r.from;
		this->to = r.to;
		this->isDuplex = r.isDuplex;
	}
};

class car
{
public:
	string id;
	string from;
	string to;
	int maxspeed;
	int plantime;
	int speed;
	car(){}
	car(vector<string>rec){
		this->id = rec[0];
		this->from = rec[1];
		this->to = rec[2];
		this->maxspeed = atoi(rec[3].c_str());
		this->plantime = atoi(rec[4].c_str());
	}
	car(const car& c){
		this->id = c.id;
		this->from = c.from;
		this->to = c.to;
		this->maxspeed = c.maxspeed;
		this->plantime = c.plantime;
	}
};

class cross
{
public:
	string id;
	vector<string> roadId;
	cross(vector<string>rec){
		this->id = rec[0];
		this->roadId.push_back(rec[1]);
		this->roadId.push_back(rec[2]);
		this->roadId.push_back(rec[3]);
		this->roadId.push_back(rec[4]);
	}
	cross(const cross& c){
		this->id = c.id;
		this->roadId = c.roadId;
	}
};

class result
{
public:
	vector<road> road_list;
	car c;
	int start_time;
	result(){}
	result(car c,int start_time,vector<road> road_list)
	{
		this->road_list = road_list;
		this->c = c;
		this->start_time = start_time;
	}

	string save_str()
	{
		string res = "(";
		res += this->c.id + "," + to_string(this->start_time) + ","; 
		if(this->road_list.size()>1){
			for(unsigned int i = 0;i<this->road_list.size()-1;i++){
				res += this->road_list[i].id + ",";
			}
		}
		
		res += this->road_list[this->road_list.size()-1].id + ")";
		// cout<<this->road_list[this->road_list.size()-1].id<<endl;
		return res;	
	}

};