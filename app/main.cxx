#include "Banalyzer.h"
#include "HistoScanner.h"
#include <TFile.h>
#include <TApplication.h>
#include <iostream>
#include <string>

void PrintUsage() {
    std::cout << "How to use broot:\n";
    std::cout << "  broot --process <raw_file.root> <tree_name> <slope> <intercept>\n";
    std::cout << "  broot --analyze <processed_file.root> <histogram_name>\n";
    std::cout << "  broot --full <raw_file.root> <tree_name> <slope> <intercept>\n";
}

int main(int argc, char** argv) {
    // Basic check: all commands need at least 4 arguments
    if (argc < 4) {
        PrintUsage();
        return 1;
    }

    std::string mode = argv[1];
    std::string filename = argv[2];
    std::string objectName = argv[3];

    // Initialize the ROOT UI environment
    TApplication app("app", &argc, argv);

    if (mode == "--process") {
        // Advanced check: process needs 6 arguments
        if (argc < 6) { 
            std::cerr << "Error: missing slope and intercept!\n"; 
            PrintUsage();
            return 1; 
        }
        
        // Convert terminal text to decimal numbers
        double slope = std::stod(argv[4]);
        double intercept = std::stod(argv[5]);
        
        std::cout << "processing raw data with m=" << slope << " b=" << intercept << "..." << std::endl;
        Banalyzer analyzer(slope, intercept);
        TH1D* spectrum = analyzer.ProcessData(filename, objectName);
        if (spectrum) {
            TFile* outFile = new TFile("broot_calibrated.root", "RECREATE");
            spectrum->Write();
            outFile->Close();
            std::cout << "done! saved to broot_calibrated.root" << std::endl;
        }
    } 
    else if (mode == "--analyze") {
        std::cout << "analyzing plot..." << std::endl;
        HistoScanner scanner;
        scanner.Analyze(filename, objectName);
        
        app.Run();
    } 
    else if (mode == "--full") {
        // Advanced check: full pipeline needs 6 arguments
        if (argc < 6) { 
            std::cerr << "Error: missing slope and intercept!\n"; 
            PrintUsage();
            return 1; 
        }
        
        // Convert terminal text to decimal numbers
        double slope = std::stod(argv[4]);
        double intercept = std::stod(argv[5]);

        std::cout << "running full pipeline with m=" << slope << " b=" << intercept << "..." << std::endl;
        Banalyzer analyzer(slope, intercept);
        TH1D* spectrum = analyzer.ProcessData(filename, objectName);
        if (spectrum) {
            TFile* outFile = new TFile("broot_calibrated.root", "RECREATE");
            spectrum->Write();
            outFile->Close();
            
            HistoScanner scanner;
            scanner.Analyze("broot_calibrated.root", "histEnergy");
            
            app.Run();
        }
    } 
    else {
        std::cerr << "unknown mode: " << mode << "\n";
        PrintUsage();
        return 1;
    }

    return 0;
}
