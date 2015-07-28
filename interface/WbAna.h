// Original Author:  Nikoloz Skhirtladze
//         Created:  July, 19 Feb 2015
//
//


// system include files
#include <iostream>
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "Analysis/VLQAnalyzer/interface/MuonSelector.h"
#include "Analysis/VLQAnalyzer/interface/ElectronSelector.h"
#include "Analysis/VLQAnalyzer/interface/AK4JetSelector.h"
#include "Analysis/VLQAnalyzer/interface/AK8JetSelector.h"
#include "Analysis/VLQAnalyzer/interface/METSelector.h"
#include "Analysis/VLQAnalyzer/interface/HLTSelector.h"
#include "Analysis/VLQAnalyzer/interface/UserSelector.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>

#include <sstream>

//
// class declaration
//

class WbAna : public edm::EDFilter {
public:
    explicit WbAna(const edm::ParameterSet&);
    ~WbAna();
    
    typedef std::vector<unsigned int > uintvec;
    
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    void applyAK4JetElCleaning(uintvec & targetColl, const AK4JetSelector  & ak4,  const ElectronSelector    & el, double maxDR = 0.4);
    void applyAK4JetMuCleaning(uintvec & targetColl, const AK4JetSelector  & ak4,  const MuonSelector        & mu, double maxDR = 0.4);
    void applyAK8JetElCleaning(uintvec & targetColl, const AK8JetSelector  & ak8,  const ElectronSelector    & el, double maxDR = 0.4);
    void applyAK8JetMuCleaning(uintvec & targetColl, const AK8JetSelector  & ak8,  const MuonSelector        & mu, double maxDR = 0.4);
    
    static const int NUM_CUTFLOW = 11;
    const std::string  CutFlowCase[NUM_CUTFLOW] = {"_Stage0",
        "_Stage1",
        "_Stage2",
        "_Stage3",
        "_Stage4",
        "_Stage5",
        "_Stage6",
        "_Stage7",
        "_Stage8" ,
        "_Stage9",
        "_Stage10"};
    
    
private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    
    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    
    // ----------member data ---------------------------
    std::string pn_;
    std::vector<std::string> hltPaths_          ;
    edm::ParameterSet hltParams_                ;
    edm::ParameterSet tightMuParams_            ;
    edm::ParameterSet looseMuParams_            ;
    edm::ParameterSet tightElParams_            ;
    edm::ParameterSet looseElParams_            ;
    edm::ParameterSet ak4JetParams_             ;
    edm::ParameterSet ak8JetParams_             ;
    edm::ParameterSet metParams_                ;
    edm::ParameterSet selectionParams_          ;
    
    edm::Service<TFileService> fs               ;
    std::map<std::string, TH1D*> h1_            ;
    std::map<std::string, TH2D*> h2_            ;
    
};

