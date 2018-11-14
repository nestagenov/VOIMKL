
#include "stdafx.h"
#include "FilterKalman.h"


CKalmanFilter::CKalmanFilter()
{

	P_Const << 10000, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 10000, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 10000, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 10000, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 10000, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 10000, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 10000, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 10000, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 10000;
	//P_0.eye(n, n);


}

CKalmanFilter::CKalmanFilter(int n_n, int m_m)
{

}

void CKalmanFilter::InitialVariableMatrix(colvec & x_0, mat P_01)
{
	this->x_0 = x_0;
	this->P_Const = P_01;

}

void CKalmanFilter::InitialNoiseMatrix(mat R, mat Q)
{
	this->R = R;
	this->Q = Q;
}

void CKalmanFilter::SetFKMatrix(mat U, mat F, mat H)
{
	//можно заменить на то что вообще задать Г H F, в самом начале.
	this->U = U;
	this->F = F;
	this->H = H;
}

void CKalmanFilter::Prediction(double dt)
{
	update_F(dt);

	this->x_pred = F * x_0;

	this->P = F * P_Const * F.t() + Q;
	//this->P = F * P_0 * F.transpose() + U * Q * U.transpose();
}

void CKalmanFilter::Predict(CMeasurement firstMeasure, CMeasurement secondMeasure)
{
	P = F * P_Const * F.t() + U * Q * U.t();
	mat R_Meas = firstMeasure.R + secondMeasure.R;
	S = R_Meas + H * P * H.t();
	v = firstMeasure.z - secondMeasure.z;
}

void CKalmanFilter::Predict(CBaseTraceHypo Trace, CMeasurement Measure, double dt)
{
	this->Dt = dt;
	update_F(dt);
	update_U(dt);

	x_pred = F * Trace.x;
	//x_pred = F * x_0;
	z_pred = H * x_pred;
	v = Measure.z - z_pred;


	P = F * P * F.t() + U * Q * U.t();
	S = R + H * P * H.t();
}


void CKalmanFilter::Measurement()
{
	z_pred = H * x_pred;
	v = z - z_pred;
	S = R + H * P * H.t();
}

void CKalmanFilter::Measurement(colvec new_z)
{
	this->z = new_z;
	z_pred = H * x_pred;
	v = z - z_pred;
	S = R + H * P * H.t();
}

void CKalmanFilter::Update()
{
	W = P * H.t() * S.i();
	x_pred = x_pred + W * v;
	P = P - W * S * W.t();

}

void CKalmanFilter::UpdateMeasure(CBaseTraceHypo Trace)
{
	W = P * H.t() * S.t();
	P = P - W * S * W.i();
	x_pred = x_pred + W * v;

	Trace.NullNmiss();
}

void CKalmanFilter::UpdatePredict(CBaseTraceHypo Trace, double dt)
{
	update_F(dt);
	update_U(dt);

	this->x_pred = F * x_pred;
	this->P = F * P * F.t() + U * Q * U.t();

	Trace.IncNmiss();
}

colvec DecartToPolar(const colvec &c)
{
	/*double x, y, z;
	double vx, vy, vz;
	double pr = sqrt(x * x + y * y);
	double pf = atan2(x, y);
	double pdot = (x * vx + y * vy) / pf;

	colvec polar_vector(3);
	polar_vector << pr, pf, pdot;*/
	colvec polar_vector(3);
	return polar_vector;
}

void CKalmanFilter::UpdateEKF(const colvec &z)
{
	// написать функцию конвертации из декартовых координат в полярные координаты 
	Measurement(z);

	W = P * H.t() * S.i();
	x_pred = x_pred + W * v;
	P = P - W * S * W.t();

}

void CKalmanFilter::makeMatrix_Q(mat G, double a)
{
	this->Q = U * U.t() * a * a;
}

void CKalmanFilter::makeMatrix_R()
{
	this->R <<
		1, 0, 0,
		0, 1, 0,
		0, 0, 1;
}

void CKalmanFilter::makeMatrix_F()
{
	this->F << 1, 0, 0, Dt, 0, 0, Dt_squared, 0, 0,
		0, 1, 0, 0, Dt, 0, 0, Dt_squared, 0,
		0, 0, 1, 0, 0, Dt, 0, 0, Dt_squared,
		0, 0, 0, 1, 0, 0, Dt, 0, 0,
		0, 0, 0, 0, 1, 0, 0, Dt, 0,
		0, 0, 0, 0, 0, 1, 0, 0, Dt,
		0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1;
}

void CKalmanFilter::update_F(double dt)
{
	double ddt = dt * dt;

	this->F << 1, 0, 0, dt, 0, 0, ddt, 0, 0,
		0, 1, 0, 0, dt, 0, 0, ddt, 0,
		0, 0, 1, 0, 0, dt, 0, 0, ddt,
		0, 0, 0, 1, 0, 0, dt, 0, 0,
		0, 0, 0, 0, 1, 0, 0, dt, 0,
		0, 0, 0, 0, 0, 1, 0, 0, dt,
		0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1;

}
void CKalmanFilter::makeMatrix_H()
{

	this->H << 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0;


	/*	this->H << 0, 0, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1;*/

}

void CKalmanFilter::makeMatrix_Q()
{
	Q = U_9x3 * Q_3 * U_9x3.t();
}

void CKalmanFilter::makeMatrix_Q()
{
	Q = U * Q_1 * U.t();
}

void CKalmanFilter::makeMatrix_U()
{
	this->U << Dt_squared, Dt_squared, Dt_squared, Dt, Dt, Dt, 1, 1, 1;
}

void CKalmanFilter::update_U(double dt)
{
	double dt_squared = (dt * dt) / 2;
	this->U << dt_squared, dt_squared, dt_squared, dt, dt, dt, 1, 1, 1;
}

mat CKalmanFilter::getMatrix_P()
{
	return this->P;
}

colvec CKalmanFilter::getVector_x()
{
	return this->x_pred;
}

void CKalmanFilter::setDt(double Dt)
{
	this->Dt = Dt;
}



