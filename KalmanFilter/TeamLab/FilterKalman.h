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

	int n; // ����������� ������� ���������
	int m; // ����������� ������� ���������
	double Dt; // 
	double Dt_squared;
	
	//mat::fixed<9, 9> P; //  �������������� ������� ������ ������ ������� ���������
	//mat::fixed<9, 9> F; // ������� �������� ����� �����������.
	//mat::fixed<1, 9> U; // ������� �
	//mat::fixed<3, 3> S; // ������� ����������
	//mat::fixed<3, 9> H; // ������� ����������. ������� ������������ ��������� ��������� � ���������
	//mat::fixed<9, 3> W; // �������� �������. ������� ������������� ��������.
	//mutable mat::fixed<3, 3> R; // ������� ���� ���������
	//mutable mat::fixed<9, 9> Q; // ������� ���� ��������� 

	mat P; //  �������������� ������� ������ ������ ������� ���������
	mat F; // ������� �������� ����� �����������.
	mat U; // ������� �
	mat S; // ������� ����������
	mat H; // ������� ����������. ������� ������������ ��������� ��������� � ���������
	mat W; // �������� �������. ������� ������������� ��������.
	mutable mat R; // ������� ���� ���������
	mutable mat Q; // ������� ���� ��������� 
	mat Q_3; // ������� Q ����������� 3 �� 3
	mat Q_1; // ������� Q ����������� 1 �� 1
	mat U_9x3; // ������� U ����������� 9 �� 3

	//��������� ������
	mutable mat P_Const; //	��������� �������������� �������
	colvec x_0 = colvec(n); // ��������� ������ ���������. ������ ��������� ������������ �������, ������� �������� ��������� ����������� ���������

	colvec x_pred;  //������ � ������� ����� �������� ������������� ���������.
	colvec z_pred; //
	colvec z; //������ ��������� � ���. ��������� � ���.
	colvec v; //������ ���������������/�������.

};

