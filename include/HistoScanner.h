#ifndef HISTOSCANNER_H
#define HISTOSCANNER_H

#include <string>

class HistoScanner {
public:
    HistoScanner();
    void Analyze(const std::string& filename, const std::string& histName);
};

#endif
