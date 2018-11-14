#include "stdafx.h"

using namespace std;
using namespace arma;


class CKalmanFilter
{
public:
	CKalmanFilter();
	CKalmanFilter(int n, int m);

	void InitialVariableMatrix(colvec & x_0, mat P_0);
	void SetFKMatrix(mat U, mat H, mat F);
	void InitialNoiseMatrix(mat, mat);

	mat getMatrix_P();
	colvec getVector_x();
	void setDt(double);

	void makeMatrix_Q(mat, double);
	void makeMatrix_Q();
	void makeMatrix_R();
	void makeMatrix_U();
	void makeMatrix_F();
	void makeMatrix_H();


	void update_F(double);
	void update_U(double);

	void Predict(CMeasurement firstMeasure, CMeasurement secondMeasure);
	void Predict(CBaseTraceHypo Trace, CMeasurement Measure, double);

	void UpdateMeasure(CBaseTraceHypo, double);
	void UpdatePredict(CBaseTraceHypo);

	void Prediction(double);
	void Measurement(colvec new_z);
	void Measurement();
	void Update();
	void UpdateEKF(const colvec &);

protected:
	//CKalmanFilter() {}

	int n; // размерность вектора состояний
	int m; // размерность вектора измерений
	double Dt; // 
	double Dt_squared;
	
	//mat::fixed<9, 9> P; //  ковариационная матрица ошибки оценки вектора состояния
	//mat::fixed<9, 9> F; // Матрица перехода между состояниями.
	//mat::fixed<1, 9> U; // матрица Г
	//mat::fixed<3, 3> S; // Матрица обновления
	//mat::fixed<3, 9> H; // Матрица наблюдения. Матрица отображающая отношение измерения и состояния
	//mat::fixed<9, 3> W; // Вессовая матрица. Матрица коэффициентов усиления.
	//mutable mat::fixed<3, 3> R; // Матрица шума измерения
	//mutable mat::fixed<9, 9> Q; // Матрица шума состояния 

	mat P; //  ковариационная матрица ошибки оценки вектора состояния
	mat F; // Матрица перехода между состояниями.
	mat U; // матрица Г
	mat S; // Матрица обновления
	mat H; // Матрица наблюдения. Матрица отображающая отношение измерения и состояния
	mat W; // Вессовая матрица. Матрица коэффициентов усиления.
	mutable mat R; // Матрица шума измерения
	mutable mat Q; // Матрица шума состояния 
	mat Q_3; // Матрица Q размерности 3 на 3
	mat Q_1; // Матрица Q размерности 1 на 1
	mat U_9x3; // Матрица U размерности 9 на 3

	//Априорные данные
	mutable mat P_Const; //	Начальная ковариационная матрица
	colvec x_0 = colvec(n); // Начальный вектор состояний. Вектор состояния динамической системы, который является случайным Гауссовским процессом

	colvec x_pred;  //Вектор в котором будет хранится предсказанное состояние.
	colvec z_pred; //
	colvec z; //Вектор пришедший с ПОИ. Измерения с РЛС.
	colvec v; //Вектор рассогласования/невязки.

};

