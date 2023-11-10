#include <map>
#include <iostream>
#include <string>
#include "HW2_Visualizer.cpp"
#include "HW2_Visualizer.h"
#include <math.h>
#include <random>

using namespace std;

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

void setvel(double vel) {
	vel = vel;
};

void setloiter(double loiter_time) {
	loiter_time = loiter_time;
};

void Plane::operate(double dt) {
	if (loiter_time != 0) loiter_time -= dt;
	else if (wait_time != 0) wait_time -= dt;
	else if (pos < distance) {
		pos += vel * dt; at_SCE = 0;
	}
	else if (destination == "SCES") at_SCE = 1;

	wait_time = time_on_ground();
	destination = origin;
	pos = 0.0;
};
double Plane::distance_to_SCE() {
	if (destination == "SCE") return distance - pos;
	else return 1000;
};

string plane_type() {
	return "GA";
}

double draw_from_normal_dist(double mean, double standard_deviation){
	random_device rd{};
	mt19937 gen{ rd() };
	normal_distribution<> d{ mean,standard_deviation };
	return d(gen);
}

class Plane{
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

	const Plane(string from, string to);
	string getorigin();
	string getdestination();
	string from;
	string to;
	string origin = from;
	string destination = to;
};
class Airliner {
private:
	string Airline;
public:
	const Airliner(string Airline, string from, string to) {
		string plane_type();
		double time_on_ground();
	}
	Airliner(string Airline, string from, string to) {
		this->Airline = Airline;
	}
	string plane_type() { return Airline; }
	double time_on_ground(double wait_time) {
		wait_time = draw_from_normal_dist(1800, 600);
		return wait_time;
	}
};

class GeneralAviation {
public:
	GeneralAviation(string from, string to);
	double time_on_ground() {
		double wait_time = draw_from_normal_dist(600, 60);
		return wait_time;
	}
	double time_on_ground();
	
};
