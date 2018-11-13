#ifndef SECTION_H
#define SECTION_H
#include <vector>
#include "Measurements.h"
#include "BaseTraceHypo.h"
class CHypo;
class CTrace;

class CSection{
private:
	std::vector<CMeasurements> BankMeasurements;
	std::vector<CTrace> BankTrace;
	std::vector<CHypo> BankHypo;
	double AzimutMin, AzimutMax; // границы этого сектора
	double Lasttime; // последнее время, когда обновляли этот сектор
public:
	CSection();
	~CSection();
	const double GetLasttime();
	void SetLasttime(double lasttime); 
	void DecreaseUntochedCounters(); // инкрементировать счетчики пропусков
	void removeOutdatedObjects(); // удалить объекты, не обновлявшиеся на этом цикле
	const double GetAzimutMin(); 
	const double GetAzimutMax();
	const std::vector<CTrace> &GetBankTrace();
	const std::vector<CHypo> &GetBankHypo();
	std::vector<CMeasurements> &GetBankMeasurements();
	const std::vector<CMeasurements> &GetBankMeasurements() const;
	void SectionHypoToTrace();
};
#endif // SECTION_H
