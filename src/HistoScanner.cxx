#include "HistoScanner.h"
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TF2.h>
#include <TCanvas.h>
#include <iostream>

HistoScanner::HistoScanner() {}

void HistoScanner::Analyze(const std::string& filename, const std::string& histName) {
    TFile* file = TFile::Open(filename.c_str(), "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }

    TH1* hist = (TH1*)file->Get(histName.c_str());
    if (!hist) {
        std::cerr << "Error: Could not find histogram named " << histName << std::endl;
        file->Close();
        return;
    }

    std::cout << "\n=== Stats for " << histName << " ===" << std::endl;
    std::cout << "Events: " << hist->GetEntries() << std::endl;
    std::cout << "Mean:   " << hist->GetMean() << std::endl;
    std::cout << "StdDev: " << hist->GetStdDev() << std::endl;
    std::cout << "==========================\n" << std::endl;

    //Ploting 
    

    TCanvas* canvas = new TCanvas("c1", "Data Viewer", 800, 600);

    if (hist->InheritsFrom(TH2::Class())) {
	std::cout << "2D histogram Detected. Applying a 2D Gaussian Fit..." <<std::endl;
	TF2* gaus2d = new TF2("gaus2d","xygaus");
	hist->Fit(gaus2d, "Q");
	hist->Draw("COLZ");

    }	else {    

    hist->Draw();
    }
}
