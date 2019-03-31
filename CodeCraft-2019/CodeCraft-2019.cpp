#include <iostream>
#include <fstream>
#include "dispatcher.h"
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Begin" << endl;
	
	if(argc < 5){
		cout << "please input args: carPath, roadPath, crossPath, answerPath" << endl;
		exit(1);
	}
	
	string carPath(argv[1]);
	string roadPath(argv[2]);
	string crossPath(argv[3]);
	string answerPath(argv[4]);
	
	cout << "carPath is " << carPath << endl;
	cout << "roadPath is " << roadPath << endl;
	cout << "crossPath is " << crossPath << endl;
	cout << "answerPath is " << answerPath << endl;
	
	// TODO:read input filebuf
	//predefine some variables
	vector<car> Car;
	vector<road> Road;
	vector<cross> Cross;
	//read Carfile
	ifstream carfile(carPath);
	string line;
	if(carfile)
	{
		vector<string>res;
		while(getline(carfile,line))
		{
			if(line[0] != '#')
			{
				res = split_data(line);
				car che(res);
				Car.push_back(che);
			}
		}
	}
	else
	{
		cout<<"no car file!"<<endl;
		exit(1);
	}
	carfile.close();

	//read roadfile
	ifstream roadfile(roadPath);
	if(roadfile)
	{
		vector<string>res;
		while(getline(roadfile,line))
		{
			if(line[0] != '#')
			{
				res = split_data(line);
				road lu(res);
				Road.push_back(lu);
			}
		}
	}
	else
	{
		cout<<"no road file!"<<endl;
		exit(1);
	}
	roadfile.close();
	
	//read crossfile
	ifstream crossfile(crossPath);
	if(crossfile)
	{
		vector<string>res;
		while(getline(crossfile,line))
		{
			if(line[0] != '#')
			{
				res = split_data(line);
				cross lukou(res);
				Cross.push_back(lukou);
			}
		}
	}
	else
	{
		cout<<"no cross file!"<<endl;
		exit(1);
	}
	crossfile.close();

	//print information of Cars
	// cout<<"print information of Cars:"<<endl;
	// for(unsigned int i = 0;i<Car.size();i++){
	// 	cout<<Car[i].id<<" "<<Car[i].from<<" "<<Car[i].to<<" "<<Car[i].maxspeed<<" "<<Car[i].plantime<<endl;
	// }
	// //print information of Roads
	// cout<<"print information of Roads:"<<endl;
	// for(unsigned int i = 0;i<Road.size();i++){
	// 	cout<<Road[i].id<<" "<<Road[i].length<<" "<<Road[i].maxspeed<<" "<<Road[i].channel<<" "<<Road[i].from<<" "<<Road[i].to<<" "<<Road[i].isDuplex<<endl;
	// }
	// //print information of cross
	// cout<<"print information of cross:"<<endl;
	// for(unsigned int i = 0;i<Cross.size();i++){
	// 	cout<<Cross[i].id<<" "<<Cross[i].roadId[0]<<" "<<Cross[i].roadId[1]<<" "<<Cross[i].roadId[2]<<" "<<Cross[i].roadId[3]<<endl;
	// }

	// TODO:process
	dispatcher dispatch(Car,Road,Cross);
	vector<result> result_list;
	result_list = dispatch.go();
	// for(unsigned int i = 0;i < result_list.size();i++){
	// 	cout<<result_list[i].save_str()<<endl;
	// }
	// cout<<"hh"<<endl;
	// TODO:write output file
	ofstream answerfile(answerPath);
	if(answerfile){
		answerfile<<"#(carId,StartTime,RoadId...)\n";
		for(unsigned int i = 0;i<result_list.size();i++){
			answerfile<<result_list[i].save_str();
			answerfile<<"\n";
		}
	}
	else{
		cout<<"can not open answer.txt!"<<endl;
		exit(1);
	}
	answerfile.close();
	
	return 0;
}