#include "Measurements.h"
using namespace std;

mat &get_Rconst() {
	static bool initialized = false;
	static colvec INIT_DIAG;
	static mat RCONST = zeros<mat>(M, M);
	if (!initialized) {
		INIT_DIAG << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
		RCONST.diag() = INIT_DIAG;
		initialized = true;
	}
	return RCONST;
}

CMeasurements::CMeasurements(CVector coordinates, double vr, double time):CResultOfScan(coordinates, vr, time)
{
	this->Nmiss = 0;
	this->R = get_Rconst();
}

CMeasurements::CMeasurements(CResultOfScan &newres) :CResultOfScan(newres.Coordinates, newres.Vr, newres.detectionTime)
{
	this->Nmiss = 0;
	this->R = get_Rconst();
}

CMeasurements::~CMeasurements()
{

}

void CMeasurements::IncNmiss()
{
	this->Nmiss++;
}

const int CMeasurements::GetNmiss()
{
	return this->Nmiss;
}

double CMeasurements::FromDekartToAzimut()
{
	return (atan(this->Coordinates.y/this->Coordinates.x));
}

const mat &CMeasurements::GetR()
{
	return this->R;
}