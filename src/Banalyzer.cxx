#include "Banalyzer.h"
#include <TFile.h>
#include <TTree.h>
#include <iostream>

Banalyzer::Banalyzer(double slope, double intercept) 
    : calibrationSlope(slope), calibrationIntercept(intercept) {}

TH1D* Banalyzer::ProcessData(const std::string& filename, const std::string& treeName) {
    TFile* file = TFile::Open(filename.c_str(), "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return nullptr;
    }

    TTree* tree = (TTree*)file->Get(treeName.c_str());
    if (!tree) {
        std::cerr << "Error: Could not find TTree named " << treeName << std::endl;
        file->Close();
        return nullptr;
    }
    
    // NOTE: Change "adc_channel" to match the exact branch name in your raw DAQ file
    double rawADC;
    tree->SetBranchAddress("adc_channel", &rawADC);

    TH1D* histEnergy = new TH1D("histEnergy", "Calibrated Gamma Spectrum;Energy (keV);Counts", 2000, 0, 2000);
    histEnergy->SetDirectory(0); 

    long entries = tree->GetEntries();
    for (long i = 0; i < entries; i++) {
        tree->GetEntry(i);
        double energy = (rawADC * calibrationSlope) + calibrationIntercept;
        histEnergy->Fill(energy);
    }

    file->Close();
    return histEnergy;
}
