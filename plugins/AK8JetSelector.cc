// header include file
#include "Analysis/VLQAnalyzer/interface/AK8JetSelector.h"


using namespace std;
using namespace edm;



AK8JetSelector::AK8JetSelector (edm::ParameterSet const& pars, edm::Event& evt):

jetPt_               (pars.getParameter<edm::InputTag>("jetPtLabel")) ,
jetEta_              (pars.getParameter<edm::InputTag>("jetEtaLabel")),
jetPhi_              (pars.getParameter<edm::InputTag>("jetPhiLabel")),
jetMass_             (pars.getParameter<edm::InputTag>("jetMassLabel")),
jetEnergy_           (pars.getParameter<edm::InputTag>("jetEnergyLabel")),
jetFlavour_          (pars.getParameter<edm::InputTag>("jetFlavourLabel")),
jetCSV_              (pars.getParameter<edm::InputTag>("jetCSVLabel")),
jetJEC_              (pars.getParameter<edm::InputTag>("jetJECLabel")),
jetnHadEnergy_       (pars.getParameter<edm::InputTag>("jetnHadEnergyLabel")),
jetnEMEnergy_        (pars.getParameter<edm::InputTag>("jetnEMEnergyLabel")),
jetHFHadronEnergy_   (pars.getParameter<edm::InputTag>("jetHFHadronEnergyLabel")),
jetcHadEnergy_       (pars.getParameter<edm::InputTag>("jetcHadEnergyLabel")),
jetcEMEnergy_        (pars.getParameter<edm::InputTag>("jetcEMEnergyLabel")),
jetnumDaughters_     (pars.getParameter<edm::InputTag>("jetnumDaughtersLabel")),
jetcMultip_          (pars.getParameter<edm::InputTag>("jetcMultipLabel")),
jetY_                (pars.getParameter<edm::InputTag>("jetYLabel")),
jetArea_             (pars.getParameter<edm::InputTag>("jetAreaLabel")),
jettau1_             (pars.getParameter<edm::InputTag>("jettau1Label")),
jettau2_             (pars.getParameter<edm::InputTag>("jettau2Label")),
jettau3_             (pars.getParameter<edm::InputTag>("jettau3Label")) ,
jetprunedMass_       (pars.getParameter<edm::InputTag>("jetPrunedMassLabel")),
jettrimmedMass_      (pars.getParameter<edm::InputTag>("jetTrimmedMassLabel")) ,
jetwMass_            (pars.getParameter<edm::InputTag>("jetWMassLabel")),
jetMinPt_            (pars.getParameter<double>("jetMinPt")),
jetMaxEta_           (pars.getParameter<double>("jetMaxEta")),
jetIDType_           (pars.getParameter<std::string>("jetIDType"))
{
    
    evt.getByLabel(jetPt_  ,            jetPt           );
    evt.getByLabel(jetEta_ ,            jetEta          );
    evt.getByLabel(jetPhi_ ,            jetPhi          );
    evt.getByLabel(jetMass_,            jetMass         );
    evt.getByLabel(jetEnergy_ ,         jetEnergy       );
    evt.getByLabel(jetFlavour_ ,        jetFlavour      );
    evt.getByLabel(jetCSV_,             jetCSV          );
    evt.getByLabel(jetJEC_ ,            jetJEC          );
    evt.getByLabel(jetnHadEnergy_ ,     jetnHadEnergy   );
    evt.getByLabel(jetnEMEnergy_,       jetnEMEnergy    );
    evt.getByLabel(jetHFHadronEnergy_ , jetHFHadronEnergy);
    evt.getByLabel(jetcHadEnergy_,      jetcHadEnergy   );
    evt.getByLabel(jetcEMEnergy_ ,      jetcEMEnergy    );
    evt.getByLabel(jetnumDaughters_,    jetnumDaughters );
    evt.getByLabel(jetcMultip_,         jetcMultip      );
    evt.getByLabel(jetY_,               jetY            );
    evt.getByLabel(jetArea_,            jetArea         );
    evt.getByLabel(jettau1_,            jettau1         );
    evt.getByLabel(jettau2_,            jettau2         );
    evt.getByLabel(jettau3_,            jettau3         );
    evt.getByLabel(jetprunedMass_,      jetprunedMass   );
    evt.getByLabel(jettrimmedMass_,     jettrimmedMass  );
    evt.getByLabel(jetwMass_,           jetwMass        );
    
    
}


AK8JetSelector::~AK8JetSelector(){
    
    
}

// methods declaration

std::vector<unsigned int>  AK8JetSelector::size() const{
    
    vector<unsigned int> jetCollection;
    for(unsigned int ind = 0; ind< (jetPt.product())->size(); ++ind){
        
        if((jetPt.product())->at(ind) < jetMinPt_) continue;
        if(fabs((jetEta.product())->at(ind)) > jetMaxEta_) continue;
        if(!isLoose(ind))continue;
        
        jetCollection.push_back(ind);
    }
    return jetCollection;
}

// Jet ID
bool AK8JetSelector::isLoose(int const & jet) const { return true; }

TLorentzVector AK8JetSelector::p4(int const & jet) const {
    TLorentzVector p4;
    p4.SetPtEtaPhiE( (jetPt.product())->at(jet), (jetEta.product())->at(jet), (jetPhi.product())->at(jet), (jetEnergy.product())->at(jet) );
    return  p4;
}


unsigned int AK8JetSelector::ak4MatchedInd(const TLorentzVector ak4JetP4, double userDR) const{
    
    if(ak4JetP4.Pt() < 1){
        edm::LogError("AK8JetSelector::ak4MatchedInd") << " >>>> Empty AK4 jet TL Vector "  ;
    }
    
    unsigned int index = 999;
    double minDR = 999.;
    for(unsigned int ind = 0; ind < (jetPt.product())->size(); ++ind){
        
        TLorentzVector p4;
        p4.SetPtEtaPhiE( (jetPt.product())->at(ind), (jetEta.product())->at(ind), (jetPhi.product())->at(ind), (jetEnergy.product())->at(ind) );
  
        double dr = ak4JetP4.DeltaR(p4);
        if(dr < minDR){
            minDR = dr;
            index = ind;
        }
    }
    
    if(minDR < userDR)
        return index;
    else
        return 999;
    
}



