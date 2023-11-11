#include <map>
#include <iostream>
#include <string>
#include "HW2_Visualizer.cpp"
#include "HW2_Visualizer.h"
#include <math.h>
#include <random>
#include "SDL.h"
#include <vector>
//main.cpp compiles ------- HW2_Visualizer.cpp does not
using namespace std;

//Question 2
class Plane {
protected: //protected variables
	double wait_time;

private: //private variables 
	double pos;
	double vel;
	double distance;
	double loiter_time;
	bool at_SCE;
	string origin;
	string destination;
	//Question 1
	map<pair<string, string>, double> flight_dist{  //container for origin and distances
		{make_pair("SCE","PHL"),160}, //make_pair connects the multiple strings
		{make_pair("SCE","ORD"),640},
		{make_pair("SCE","EWR"),220}
	};

public: //public variables and functions
	Plane(string from, string to); 
	virtual ~Plane();
	void operate(double dt);
	double getpos();
	double getvel();
	double getloiter();
	string getorigin();
	string getdestination();
	bool getat_SCE(); //true/false if at SC
	void setvel(double vel); //function for velocity
	void setloiter(double loiter_time); //function for loiter
	double distance_to_SCE();
	virtual double time_on_ground() = 0;
	virtual string plane_type();
	static double draw_from_normal_dist(double mean, double standard_deviation);
};

//Question 4 {
class Airliner : public Plane{ //base classes
private: //private variables
	string Airline;
public: //public variables
	Airliner(string Airline, string from, string to);
	~Airliner();
	string plane_type();
	double time_on_ground();
};

class GeneralAviation : public Plane{ //base classes
public: //public variables and functions
	GeneralAviation(string from, string to);
	~GeneralAviation();
	double time_on_ground();
};
//}

//Question 6 - Partial
class ATC {
private: //private variables
	unsigned int MAX_LANDED_PLANE_NUM = 2;
	unsigned int AIRSPACE_DISTANCE = 50;
public: //public variables
	ATC() {}
	~ATC() {}
	void register_plane();
	void control_traffic();
};

//Question 3 {
//Plane
double Plane::getpos() {  //position
	return pos; 
}
double Plane::getvel() { //velocity
	return vel;
}
double Plane::getloiter() { //loiter time
	return loiter_time;
}
string Plane::getorigin() { //origin
	return origin;
}
string Plane::getdestination() { //destination
	return destination;
}
bool Plane::getat_SCE() { //at state college
	return at_SCE;
}
void Plane::setvel(double vel) { //sets velocity
	this->vel = vel;
};
void Plane::setloiter(double loiter_time) { //sets loiter time
	this->loiter_time = loiter_time;
};
void Plane::operate(double dt) { //operate function flowchart
	if (loiter_time != 0) { //finds loiter time ends
		loiter_time -= dt;
		if (loiter_time < 0) loiter_time = 0;
		return;
	}
	else if (wait_time != 0) { //finds wait time, ends
		wait_time -= dt;
		if (wait_time < 0) wait_time = 0;
		return;
	}
	else if (pos < distance) { //finds distance through calculation, ends
		pos += vel * dt; at_SCE = 0;
		return;
	}
	else if (destination == "SCE") at_SCE = 1; //finds if at State College

	wait_time = time_on_ground();
	destination = origin;
	pos = 0.0;
};
Plane::Plane(string from, string to) { //construct for the plane
	origin = from;
	destination = to;
	if (origin == "SCE")
		distance = this->flight_dist[{origin, destination}]; //origin to destination
	else distance = this->flight_dist[{destination, origin}]; //destination to origin
	pos = 0;	//variables set to 0
	vel = 0;
	wait_time = 0;
	loiter_time = 0;
	at_SCE = 0;
}
Plane::~Plane() {}
double Plane::distance_to_SCE() { 
	if (destination == "SCE") return distance - pos; //returns the distance between State College and desired location
};
string Plane::plane_type() {
	return "GA";
}
double Plane::draw_from_normal_dist(double mean, double standard_deviation){ //premade function from question 3
	random_device rd{};
	mt19937 gen{ rd() };
	normal_distribution<> d{ mean,standard_deviation };
	return d(gen);
}
//}

//Quesiton 4 {
//GeneralAviation 
GeneralAviation::GeneralAviation(string from, string to) :Plane(from, to) {}
GeneralAviation::~GeneralAviation() {}
double GeneralAviation::time_on_ground() { 
	wait_time = draw_from_normal_dist(1800, 600);
	return wait_time;
}

//Airliner
Airliner::Airliner(string Airline, string from, string to) :Plane(from, to){
	this->Airline = Airline;
}
Airliner::~Airliner() {}
string Airliner::plane_type() {
	return Airline;
}
double Airliner::time_on_ground(){
	wait_time = draw_from_normal_dist(1800, 600);
	return wait_time;
}
//}

//int main(int argc, char** argv) {
//	HW2_VIZ viz;
//	//operate();
//	//HW2_VIZ:visualize_plane(plane_type, origin, destination, pos);
//	//while (true){
//	// }
//	return 0;
//}