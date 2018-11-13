#ifndef VOI_H
#define VOI_H
#include "stadfx.h"
#include <vector>
#include "Measurements.h"
#include "BaseTraceHypo.h"
#include <Hungarian.h>

class CVOI{
private:
	std::vector<CSection> BankOfSection; 
	bool FirstTry; // флажок на первый обход - "без ассоциации"
	mutable double Bmin, Bmax; // границы обзора, по которому работаем
	double FirstAngle;  // первый угол после Вmin
	int CurrentSector; // текущий сектор, с которым идет работа сейчас
	HungarianAlgorithm HungAlgo;
public:
	CVOI();
	~CVOI();
	void SetSizeZone(double bmin, double bmax); // Устанавливаем Вmin и Вmax в классе 
	void associate();
	int DetectSector(double azimutAngle); //определяет к какому сектору принадлежит угол на входе
	void pushMeasurements(CResultOfScan newres); // получаем измерения в подходящий сектор
	void pushSectorObserved(double time, double b); // получаем метку времени с углом
	void TimeToStartAssociation(double time);// проверяем не начать ли ассоциацию
};
#endif VOI_H