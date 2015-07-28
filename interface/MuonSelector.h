#ifndef MUONSELECTOR_HH
#define MUONSELECTOR_HH

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

class MuonSelector {
    
public:
    MuonSelector (edm::ParameterSet const& pars, edm::Event& evt);
    ~MuonSelector();
    
    // methods declaration
    
    std::vector<unsigned int> size() const;
    bool isTight(int const & mu) const;
    bool isMedium(int const & mu) const;
    bool isLoose(int const & mu) const;
    TLorentzVector p4(int const & mu) const;
    double iso(int const & mu) const;
    

private:
    
    edm::InputTag muCharge_                   ;
    edm::InputTag muD0_                       ;
    edm::InputTag muD0err_                    ;
    edm::InputTag muDxy_                      ;
    edm::InputTag muDxyerr_                   ;
    edm::InputTag muDz_                       ;
    edm::InputTag muDzerr_                    ;
    edm::InputTag muE_                        ;
    edm::InputTag muEta_                      ;
    edm::InputTag muGenMuonCharge_            ;
    edm::InputTag muGenMuonE_                 ;
    edm::InputTag muGenMuonEta_               ;
    edm::InputTag muGenMuonPhi_               ;
    edm::InputTag muGenMuonPt_                ;
    edm::InputTag muGenMuonY_                 ;
    edm::InputTag muGlbTrkNormChi2_           ;
    edm::InputTag muInTrkNormChi2_            ;
    edm::InputTag muIsGlobalMuon_             ;
    edm::InputTag muIsLooseMuon_              ;
    edm::InputTag muIsPFMuon_                 ;
    edm::InputTag muIsSoftMuon_               ;
    edm::InputTag muIsMediumMuon_             ;
    edm::InputTag muIsTightMuon_              ;
    edm::InputTag muIsTrackerMuon_            ;
    edm::InputTag muIso04_                    ;
    edm::InputTag muKey_                      ;
    edm::InputTag muMass_                     ;
    edm::InputTag muNumberMatchedStations_    ;
    edm::InputTag muNumberOfPixelLayers_      ;
    edm::InputTag muNumberOfValidTrackerHits_ ;
    edm::InputTag muNumberTrackerLayers_      ;
    edm::InputTag muNumberValidMuonHits_      ;
    edm::InputTag muNumberValidPixelHits_     ;
    edm::InputTag muPhi_                      ;
    edm::InputTag muPt_                       ;
    edm::InputTag muSumChargedHadronPt_       ;
    edm::InputTag muSumNeutralHadronPt_       ;
    edm::InputTag muSumPUPt_                  ;
    edm::InputTag muSumPhotonPt_              ;
    edm::InputTag muY_                        ;
    
    
    typedef Handle<vector<float>>  hfloat;
    
    hfloat muCharge                  ;
    hfloat muD0                      ;
    hfloat muD0err                   ;
    hfloat muDxy                     ;
    hfloat muDxyerr                  ;
    hfloat muDz                      ;
    hfloat muDzerr                   ;
    hfloat muE                       ;
    hfloat muEta                     ;
    hfloat muGenMuonCharge           ;
    hfloat muGenMuonE                ;
    hfloat muGenMuonEta              ;
    hfloat muGenMuonPhi              ;
    hfloat muGenMuonPt               ;
    hfloat muGenMuonY                ;
    hfloat muGlbTrkNormChi2          ;
    hfloat muInTrkNormChi2           ;
    hfloat muIsGlobalMuon            ;
    hfloat muIsLooseMuon             ;
    hfloat muIsPFMuon                ;
    hfloat muIsSoftMuon              ;
    hfloat muIsMediumMuon            ;
    hfloat muIsTightMuon             ;
    hfloat muIsTrackerMuon           ;
    hfloat muIso04                   ;
    hfloat muKey                     ;
    hfloat muMass                    ;
    hfloat muNumberMatchedStations   ;
    hfloat muNumberOfPixelLayers     ;
    hfloat muNumberOfValidTrackerHits;
    hfloat muNumberTrackerLayers     ;
    hfloat muNumberValidMuonHits     ;
    hfloat muNumberValidPixelHits    ;
    hfloat muPhi                     ;
    hfloat muPt                      ;
    hfloat muSumChargedHadronPt      ;
    hfloat muSumNeutralHadronPt      ;
    hfloat muSumPUPt                 ;
    hfloat muSumPhotonPt             ;
    hfloat muY                       ;
    
    
    double muMinPt_                  ;
    double muMaxEta_                 ;
    double muMaxIso_                 ;
    string muIDType_                 ;
    
};
#endif