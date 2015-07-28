// header include file
#include "Analysis/VLQAnalyzer/interface/MuonSelector.h"
#include <iostream>

using namespace std;
using namespace edm;

MuonSelector::MuonSelector (edm::ParameterSet const& pars, edm::Event& evt):

muCharge_                   (pars.getParameter<edm::InputTag>("muChargeLabel")),
muD0_                       (pars.getParameter<edm::InputTag>("muD0Label")),
muD0err_                    (pars.getParameter<edm::InputTag>("muD0errLabel")),
muDxy_                      (pars.getParameter<edm::InputTag>("muDxyLabel")),
muDxyerr_                   (pars.getParameter<edm::InputTag>("muDxyerrLabel")),
muDz_                       (pars.getParameter<edm::InputTag>("muDzLabel")),
muDzerr_                    (pars.getParameter<edm::InputTag>("muDzerrLabel")),
muE_                        (pars.getParameter<edm::InputTag>("muELabel")),
muEta_                      (pars.getParameter<edm::InputTag>("muEtaLabel")),
muGenMuonCharge_            (pars.getParameter<edm::InputTag>("muGenMuonChargeLabel")),
muGenMuonE_                 (pars.getParameter<edm::InputTag>("muGenMuonELabel")),
muGenMuonEta_               (pars.getParameter<edm::InputTag>("muGenMuonEtaLabel")),
muGenMuonPhi_               (pars.getParameter<edm::InputTag>("muGenMuonPhiLabel")),
muGenMuonPt_                (pars.getParameter<edm::InputTag>("muGenMuonPtLabel")),
muGenMuonY_                 (pars.getParameter<edm::InputTag>("muGenMuonYLabel")),
muGlbTrkNormChi2_           (pars.getParameter<edm::InputTag>("muGlbTrkNormChi2Label")),
muInTrkNormChi2_            (pars.getParameter<edm::InputTag>("muInTrkNormChi2Label")),
muIsGlobalMuon_             (pars.getParameter<edm::InputTag>("muIsGlobalMuonLabel")),
muIsLooseMuon_              (pars.getParameter<edm::InputTag>("muIsLooseMuonLabel")),
muIsPFMuon_                 (pars.getParameter<edm::InputTag>("muIsPFMuonLabel")),
muIsSoftMuon_               (pars.getParameter<edm::InputTag>("muIsSoftMuonLabel")),
muIsMediumMuon_             (pars.getParameter<edm::InputTag>("muIsMediumMuonLabel")),
muIsTightMuon_              (pars.getParameter<edm::InputTag>("muIsTightMuonLabel")),
muIsTrackerMuon_            (pars.getParameter<edm::InputTag>("muIsTrackerMuonLabel")),
muIso04_                    (pars.getParameter<edm::InputTag>("muIso04Label")),
muKey_                      (pars.getParameter<edm::InputTag>("muKeyLabel")),
muMass_                     (pars.getParameter<edm::InputTag>("muMassLabel")),
muNumberMatchedStations_    (pars.getParameter<edm::InputTag>("muNumberMatchedStationsLabel")),
muNumberOfPixelLayers_      (pars.getParameter<edm::InputTag>("muNumberOfPixelLayersLabel")),
muNumberOfValidTrackerHits_ (pars.getParameter<edm::InputTag>("muNumberOfValidTrackerHitsLabel")),
muNumberTrackerLayers_      (pars.getParameter<edm::InputTag>("muNumberTrackerLayersLabel")),
muNumberValidMuonHits_      (pars.getParameter<edm::InputTag>("muNumberValidMuonHitsLabel")),
muNumberValidPixelHits_     (pars.getParameter<edm::InputTag>("muNumberValidPixelHitsLabel")),
muPhi_                      (pars.getParameter<edm::InputTag>("muPhiLabel")),
muPt_                       (pars.getParameter<edm::InputTag>("muPtLabel")),
muSumChargedHadronPt_       (pars.getParameter<edm::InputTag>("muSumChargedHadronPtLabel")),
muSumNeutralHadronPt_       (pars.getParameter<edm::InputTag>("muSumNeutralHadronPtLabel")),
muSumPUPt_                  (pars.getParameter<edm::InputTag>("muSumPUPtLabel")),
muSumPhotonPt_              (pars.getParameter<edm::InputTag>("muSumPhotonPtLabel")),
muY_                        (pars.getParameter<edm::InputTag>("muYLabel")),
muMinPt_                    (pars.getParameter<double>("muMinPt")),
muMaxEta_                   (pars.getParameter<double>("muMaxEta")),
muMaxIso_                    (pars.getParameter<double>("muMaxIso")),
muIDType_                   (pars.getParameter<std::string>("muIDType"))
{
    
    evt.getByLabel(muCharge_                  ,muCharge                  );
    evt.getByLabel(muD0_                      ,muD0                      );
    evt.getByLabel(muD0err_                   ,muD0err                   );
    evt.getByLabel(muDxy_                     ,muDxy                     );
    evt.getByLabel(muDxyerr_                  ,muDxyerr                  );
    evt.getByLabel(muDz_                      ,muDz                      );
    evt.getByLabel(muDzerr_                   ,muDzerr                   );
    evt.getByLabel(muE_                       ,muE                       );
    evt.getByLabel(muEta_                     ,muEta                     );
    evt.getByLabel(muGenMuonCharge_           ,muGenMuonCharge           );
    evt.getByLabel(muGenMuonE_                ,muGenMuonE                );
    evt.getByLabel(muGenMuonEta_              ,muGenMuonEta              );
    evt.getByLabel(muGenMuonPhi_              ,muGenMuonPhi              );
    evt.getByLabel(muGenMuonPt_               ,muGenMuonPt               );
    evt.getByLabel(muGenMuonY_                ,muGenMuonY                );
    evt.getByLabel(muGlbTrkNormChi2_          ,muGlbTrkNormChi2          );
    evt.getByLabel(muInTrkNormChi2_           ,muInTrkNormChi2           );
    evt.getByLabel(muIsGlobalMuon_            ,muIsGlobalMuon            );
    evt.getByLabel(muIsLooseMuon_             ,muIsLooseMuon             );
    evt.getByLabel(muIsPFMuon_                ,muIsPFMuon                );
    evt.getByLabel(muIsSoftMuon_              ,muIsSoftMuon              );
    evt.getByLabel(muIsMediumMuon_            ,muIsMediumMuon            );
    evt.getByLabel(muIsTightMuon_             ,muIsTightMuon             );
    evt.getByLabel(muIsTrackerMuon_           ,muIsTrackerMuon           );
    evt.getByLabel(muIso04_                   ,muIso04                   );
    evt.getByLabel(muKey_                     ,muKey                     );
    evt.getByLabel(muMass_                    ,muMass                    );
    evt.getByLabel(muNumberMatchedStations_   ,muNumberMatchedStations   );
    evt.getByLabel(muNumberOfPixelLayers_     ,muNumberOfPixelLayers     );
    evt.getByLabel(muNumberOfValidTrackerHits_,muNumberOfValidTrackerHits);
    evt.getByLabel(muNumberTrackerLayers_     ,muNumberTrackerLayers     );
    evt.getByLabel(muNumberValidMuonHits_     ,muNumberValidMuonHits     );
    evt.getByLabel(muNumberValidPixelHits_    ,muNumberValidPixelHits    );
    evt.getByLabel(muPhi_                     ,muPhi                     );
    evt.getByLabel(muPt_                      ,muPt                      );
    evt.getByLabel(muSumChargedHadronPt_      ,muSumChargedHadronPt      );
    evt.getByLabel(muSumNeutralHadronPt_      ,muSumNeutralHadronPt      );
    evt.getByLabel(muSumPUPt_                 ,muSumPUPt                 );
    evt.getByLabel(muSumPhotonPt_             ,muSumPhotonPt             );
    evt.getByLabel(muY_                       ,muY                       );
    
}


MuonSelector::~MuonSelector(){
    
}




// methods declaration

vector<unsigned int> MuonSelector::size() const {
    
    vector<unsigned int> muCollection;
    for(unsigned int ind = 0; ind< (muPt.product())->size(); ++ind) {
        if((muPt.product())->at(ind) < muMinPt_) continue;
        if(fabs((muEta.product())->at(ind)) > muMaxEta_) continue;
        if(muIDType_ == "TIGHT"){
            if(!isTight(ind)) continue;
            if(fabs((muIso04.product())->at(ind)) > muMaxIso_ ) continue;
        }
        else if(muIDType_ == "MEDIUM"){
            if(!isMedium(ind)) continue;
        }
        else if(muIDType_ == "LOOSE"){
            if(!isLoose(ind)) continue;
            if(fabs((muIso04.product())->at(ind)) > muMaxIso_ ) continue;
        }
        else{
            edm::LogError("MuonSelector::size") << " >>>> Wrong Muon ID Type: " << muIDType_<< " Check muon ID type !!!" ;
        }
        muCollection.push_back(ind);
    }
    
    return muCollection;
}

bool MuonSelector::isTight(int const & mu) const{ return ((muIsTightMuon.product())->at(mu)); }
bool MuonSelector::isMedium(int const & mu) const{ return ((muIsMediumMuon.product())->at(mu)); }
bool MuonSelector::isLoose(int const & mu) const { return ((muIsLooseMuon.product())->at(mu)); }
TLorentzVector MuonSelector::p4(int const & mu) const {
    TLorentzVector P4;
    P4.SetPtEtaPhiE( (muPt.product())->at(mu), (muEta.product())->at(mu), (muPhi.product())->at(mu), (muE.product())->at(mu) );
    return  P4;
}
double MuonSelector::iso(int const & mu) const { return ((muIso04.product())->at(mu)); }





