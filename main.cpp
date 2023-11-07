#include <map>
#include <iostream>
#include <string>
using namespace std;

void setvel(double vel) {
	this->vel = vel;
}

void setloiter(double loiter_time) {
	this->loiter_time = loiter_time;
}

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

	double setvel();
	double setloiter();
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

	double pos = 0;
	double vel = 0;
	double wait_time = 0;
	double loiter_time = 0;
	bool at_SCE = 0;



};
