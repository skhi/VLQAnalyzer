#ifndef ELECTRONSELECTOR_HH
#define ELECTRONSELECTOR_HH

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
using namespace edm ;

class ElectronSelector {
public:
    ElectronSelector   (edm::ParameterSet const& pars, edm::Event& evt);
    ~ElectronSelector();

    // methods declaration
    
    std::vector<unsigned int> size() const;
    bool isTight(int const & el) const;
    bool isMedium(int const & el) const;
    bool isLoose(int const & el) const;
    TLorentzVector p4(int const & el) const;
    double iso(int const & el) const;

private:
    edm::InputTag elCharge_        ;
    edm::InputTag elD0_            ;
    edm::InputTag elDz_            ;
    edm::InputTag elE_             ;
    edm::InputTag elEta_           ;
    edm::InputTag elHoE_           ;
    edm::InputTag elIso03_         ;
    edm::InputTag elKey_           ;
    edm::InputTag elMass_          ;
    edm::InputTag elPhi_           ;
    edm::InputTag elPt_            ;
    edm::InputTag elY_             ;
    edm::InputTag eldEtaIn_        ;
    edm::InputTag eldPhiIn_        ;
    edm::InputTag elfull5x5siee_   ;
    edm::InputTag elhasMatchedConVeto_   ;
    edm::InputTag elisEB_          ;
    edm::InputTag elisLoose_       ;
    edm::InputTag elisMedium_      ;
    edm::InputTag elisTight_       ;
    edm::InputTag elisVeto_        ;
    edm::InputTag elmissHits_      ;
    edm::InputTag elooEmooP_       ;
    edm::InputTag elscEta_         ;
    
    typedef Handle<vector<float>>  hfloat;
    
    hfloat elCharge             ;
    hfloat elD0                 ;
    hfloat elDz                 ;
    hfloat elE                  ;
    hfloat elEta                ;
    hfloat elHoE                ;
    hfloat elIso03              ;
    hfloat elKey                ;
    hfloat elMass               ;
    hfloat elPhi                ;
    hfloat elPt                 ;
    hfloat elY                  ;
    hfloat eldEtaIn             ;
    hfloat eldPhiIn             ;
    hfloat elfull5x5siee        ;
    hfloat elhasMatchedConVeto  ;
    hfloat elisEB               ;
    hfloat elisLoose            ;
    hfloat elisMedium           ;
    hfloat elisTight            ;
    hfloat elisVeto             ;
    hfloat elmissHits           ;
    hfloat elooEmooP            ;
    hfloat elscEta              ;
    
    double elMinPt_                  ;
    double elMaxEta_                 ;
    string elIDType_                 ;
    
};
#endif

