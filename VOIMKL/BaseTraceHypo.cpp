#include "BaseTraceHypo.h"
using namespace std;

CBaseTraceHypo::CBaseTraceHypo()
{
	this->Nmiss = 0;
}

CBaseTraceHypo::~CBaseTraceHypo()
{}

void CBaseTraceHypo::IncNmiss()
{
	this->Nmiss++;
}

void CBaseTraceHypo::NullNmiss()
{
	this->Nmiss = 0;
}

const int CBaseTraceHypo::GetNmiss()
{
	return this->Nmiss;
}

////const bool CBaseTraceHypo::GetUpdateWithM()
//{
//	return this->GetUpdateWithM;
//}

CTrace::CTrace() :CBaseTraceHypo()
{}

CTrace::CTrace(CHypo &&hypo)
{
	x = std::move(hypo.x);
	P = std::move(hypo.P);
	Q = std::move(hypo.Q);
	this->Nmiss = 0;
}

CTrace::~CTrace()
{

}

CHypo::CHypo(CMeasurements &newM) : CBaseTraceHypo()
{
	this->x(0) = newM.Coordinates.x;
	this->x(3) = newM.Coordinates.y;
	this->x(6) = newM.Coordinates.z;
	this->Napprove = 0;
	for (int i1 = 0, r1=0; i1 < N; i1+3, r1++)
	{
		for (int i2 = 0, r2=0; i2 < N; i2 + 3, r2++)
		{
			this->P(i1, i2) = newM.GetR()(r1, r2);
		}
	}
	this->Q = constQ;
}

CHypo::~CHypo()
{

}

const int CHypo::GetNapprove()
{
	return this->Napprove;
}

void CHypo::IncApprove()
{
	Napprove++;
}

void CHypo::NullNapprove()
{
	this->Napprove = 0;
}

CTrace CHypo::HypoToTrace()
{
	CTrace resTrace(std::move(*this));
	return resTrace;
}