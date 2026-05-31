#ifndef BANALYZER_H
#define BANALYZER_H

#include <string>
#include <TH1D.h>

class Banalyzer {
private:
    double calibrationSlope;
    double calibrationIntercept;

public:
    Banalyzer(double slope, double intercept);
    TH1D* ProcessData(const std::string& filename, const std::string& treeName);
};

#endif
