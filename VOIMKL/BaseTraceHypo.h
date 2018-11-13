#ifndef BaseTraceHypo_H
#define BaseTraceHypo_H
#include "stadfx.h"

using namespace arma;

class CHypo;
class CMeasurements;

class CBaseTraceHypo{
protected:
	int Nmiss;
	//bool UpdateWithM = true; //проверяем способ обновления трассы - через измерения или предсказанное значение перенесется в обновление
	//mutable mat Pconst = zeros<mat>(N, N);
	mat P=zeros<mat>(N,N);
	colvec x=zeros<vec>(N);
	mat Q = zeros<mat>(N, N);
public:
	CBaseTraceHypo();
	~CBaseTraceHypo();
	void IncNmiss();
	void NullNmiss(); //зануление при обновлении 
	const int GetNmiss();
	void UpdateState(mat P, colvec x); //для обновления по предсказаниям или измерениям
	//bool GetUpdateWithM();
};

class CTrace: public CBaseTraceHypo{
public:
	CTrace();
	CTrace(CHypo &&hypo);
	~CTrace();
};

class CHypo : public CBaseTraceHypo{
	friend class CTrace;
private:
	int Napprove;
public:
	CHypo(CMeasurements &newM);
	~CHypo();
	const int GetNapprove();
	void IncApprove();
	void NullNapprove();//
	CTrace HypoToTrace();
};
#endif BaseTraceHypo_H