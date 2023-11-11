#include <map>
#include <iostream>
#include <string>
#include "HW2_Visualizer.cpp"
#include "HW2_Visualizer.h"
#include <math.h>
#include <random>
#include "SDL.h"
#include <vector>

using namespace std;

class Plane {
protected:
	double wait_time;

private:
	double pos;
	double vel;
	double distance;
	double loiter_time;
	bool at_SCE;
	string origin;
	string destination;

	map<pair<string, string>, double> flight_dist{
		{make_pair("SCE","PHL"),160},
		{make_pair("SCE","ORD"),640},
		{make_pair("SCE","EWR"),220}
	};

public:
	Plane(string from, string to);
	virtual ~Plane();
	void operate(double dt);
	double getpos();
	double getvel();
	double getloiter();
	string getorigin();
	string getdestination();
	bool getat_SCE();

	void setvel(double vel);
	void setloiter(double loiter_time);
	double distance_to_SCE();

	virtual double time_on_ground() = 0;
	virtual string plane_type();
	static double draw_from_normal_dist(double mean, double standard_deviation);
};

class Airliner : public Plane{
private:
	string Airline;
public:
	Airliner(string Airline, string from, string to);
	~Airliner();
	string plane_type();
	double time_on_ground();
};

class GeneralAviation : public Plane{
public:
	GeneralAviation(string from, string to);
	~GeneralAviation();
	double time_on_ground();
};

class ATC {
private:
	
public:
	ATC();
	~ATC();

};
 
//Question 3 {
double Plane::getpos() { 
	return pos; 
}

double Plane::getvel() {
	return vel;
}

double Plane::getloiter() {
	return loiter_time;
}

string Plane::getorigin() {
	return origin;
}

string Plane::getdestination() {
	return destination;
}

bool Plane::getat_SCE() {
	return at_SCE;
}

void Plane::setvel(double vel) {
	this->vel = vel;
};

void Plane::setloiter(double loiter_time) {
	this->loiter_time = loiter_time;
};

void Plane::operate(double dt) {
	if (loiter_time != 0) {
		loiter_time -= dt;
		if (loiter_time < 0) loiter_time = 0;
		return;
	}
	else if (wait_time != 0) {
		wait_time -= dt;
		if (wait_time < 0) wait_time = 0;
		return;
	}
	else if (pos < distance) {
		pos += vel * dt; at_SCE = 0;
		return;
	}
	else if (destination == "SCE") at_SCE = 1;

	wait_time = time_on_ground();
	destination = origin;
	pos = 0.0;
};

GeneralAviation::GeneralAviation(string from, string to) :Plane(from, to) {}
GeneralAviation::~GeneralAviation() {}
double GeneralAviation::time_on_ground() {
	wait_time = draw_from_normal_dist(1800, 600);
	return wait_time;
}

Plane::Plane(string from, string to) {
	origin = from;
	destination = to;
	if (origin == "SCE")
		distance = this->flight_dist[{origin, destination}];
	else distance = this->flight_dist[{destination, origin}];
	pos = 0;
	vel = 0;
	wait_time = 0;
	loiter_time = 0;
	at_SCE = 0;
}

Plane::~Plane() {}

double Plane::distance_to_SCE() {
	if (destination == "SCE") return distance - pos;
	else return 1000;
};

string Plane::plane_type() {
	return "GA";
}

double Plane::draw_from_normal_dist(double mean, double standard_deviation){
	random_device rd{};
	mt19937 gen{ rd() };
	normal_distribution<> d{ mean,standard_deviation };
	return d(gen);
}

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

int main() {

	return 0;
}