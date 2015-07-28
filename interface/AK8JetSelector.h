#ifndef AK8JETSELECTOR_H
#define AK8JETSELECTOR_H

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <boost/algorithm/string.hpp>
#include <string>
#include <TLorentzVector.h>


using namespace std;
using namespace edm;


class AK8JetSelector {
    
public:
        
    AK8JetSelector (edm::ParameterSet const& pars, edm::Event& evt);
    ~AK8JetSelector();
    
    // methods declaration
    
    std::vector<unsigned int> size() const;
    bool isLoose(int const & jet) const;
    TLorentzVector p4(int const & jet) const;
    unsigned int ak4MatchedInd(const TLorentzVector ak4JetTlVec, const double userDR = 0.5) const;
    
    
private:
    
    edm::InputTag jetPt_              ;
    edm::InputTag jetEta_             ;
    edm::InputTag jetPhi_             ;
    edm::InputTag jetMass_            ;
    edm::InputTag jetEnergy_          ;
    edm::InputTag jetFlavour_         ;
    edm::InputTag jetCSV_             ;
    edm::InputTag jetJEC_             ;
    edm::InputTag jetnHadEnergy_      ;
    edm::InputTag jetnEMEnergy_       ;
    edm::InputTag jetHFHadronEnergy_  ;
    edm::InputTag jetcHadEnergy_      ;
    edm::InputTag jetcEMEnergy_       ;
    edm::InputTag jetnumDaughters_    ;
    edm::InputTag jetcMultip_         ;
    edm::InputTag jetY_               ;
    edm::InputTag jetArea_            ;
    edm::InputTag jettau1_            ;
    edm::InputTag jettau2_            ;
    edm::InputTag jettau3_            ;
    edm::InputTag jetprunedMass_      ;
    edm::InputTag jettrimmedMass_     ;
    edm::InputTag jetwMass_           ;
    
    
    typedef Handle<vector<float>>  hfloat;
                          
    hfloat jetPt             ;
    hfloat jetEta            ;
    hfloat jetPhi            ;
    hfloat jetMass           ;
    hfloat jetEnergy         ;
    hfloat jetFlavour        ;
    hfloat jetCSV            ;
    hfloat jetJEC            ;
    hfloat jetnHadEnergy     ;
    hfloat jetnEMEnergy      ;
    hfloat jetHFHadronEnergy ;
    hfloat jetcHadEnergy     ;
    hfloat jetcEMEnergy      ;
    hfloat jetnumDaughters   ;
    hfloat jetcMultip        ;
    hfloat jetY              ;
    hfloat jetArea           ;
    hfloat jettau1           ;
    hfloat jettau2           ;
    hfloat jettau3           ;
    hfloat jetprunedMass     ;
    hfloat jettrimmedMass    ;
    hfloat jetwMass          ;
    
    
    double jetMinPt_         ;
    double jetMaxEta_        ;
    string jetIDType_        ;
    
};

#endif
