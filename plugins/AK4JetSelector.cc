// header include file
#include "Analysis/VLQAnalyzer/interface/AK4JetSelector.h"


using namespace std;
using namespace edm;


AK4JetSelector::AK4JetSelector (edm::ParameterSet const& pars, edm::Event& evt):

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
jetnMultip_          (pars.getParameter<edm::InputTag>("jetnMultipLabel")),
jetHFHadronEnergy_   (pars.getParameter<edm::InputTag>("jetHFHadronEnergyLabel")),
jetcHadEnergy_       (pars.getParameter<edm::InputTag>("jetcHadEnergyLabel")),
jetcEMEnergy_        (pars.getParameter<edm::InputTag>("jetcEMEnergyLabel")),
jetnumDaughters_     (pars.getParameter<edm::InputTag>("jetnumDaughtersLabel")),
jetcMultip_          (pars.getParameter<edm::InputTag>("jetcMultipLabel")),
jetY_                (pars.getParameter<edm::InputTag>("jetYLabel")),
jetArea_             (pars.getParameter<edm::InputTag>("jetAreaLabel")),
jetMinPt_            (pars.getParameter<double>("jetMinPt")),
jetMaxEta_           (pars.getParameter<double>("jetMaxEta")),
jetCSVCut_           (pars.getParameter<double>("jetCSVCut")),
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
    evt.getByLabel(jetnMultip_,         jetnMultip      );
    evt.getByLabel(jetHFHadronEnergy_ , jetHFHadronEnergy);
    evt.getByLabel(jetcHadEnergy_,      jetcHadEnergy   );
    evt.getByLabel(jetcEMEnergy_ ,      jetcEMEnergy    );
    evt.getByLabel(jetnumDaughters_,    jetnumDaughters );
    evt.getByLabel(jetcMultip_,         jetcMultip      );
    evt.getByLabel(jetY_,               jetY            );
    evt.getByLabel(jetArea_,            jetArea         );
    
    
}

AK4JetSelector::~AK4JetSelector(){
    
}


// methods definition

std::vector<unsigned int>  AK4JetSelector::size() const{
    
    vector<unsigned int> jetCollection;
    for(unsigned int ind = 0; ind< (jetPt.product())->size(); ++ind){

        if((jetPt.product())->at(ind) < jetMinPt_) continue;
        if(fabs((jetEta.product())->at(ind)) > jetMaxEta_) continue;
        if(!isLoose(ind))continue; // needs modification once the jet IDs are clear
        
        jetCollection.push_back(ind);
    }
    return jetCollection;
}

std::vector<unsigned int>  AK4JetSelector::bsize() const{
    
    vector<unsigned int> bJetCollection;
    for(unsigned int ind = 0; ind< (jetPt.product())->size(); ++ind){
        
        if((jetPt.product())->at(ind) < jetMinPt_) continue;
        if(fabs((jetEta.product())->at(ind)) > jetMaxEta_) continue;
        if(!isLoose(ind))continue;
        if((jetCSV.product())->at(ind) < jetCSVCut_)continue;
        
        bJetCollection.push_back(ind);
    }
    return bJetCollection;
}


bool AK4JetSelector::isLoose(int const & jet) const{
    
    double NHF  = (jetnHadEnergy.product())->at(jet);
    double NEMF = (jetnEMEnergy.product())->at(jet);
    double CHF  = (jetcHadEnergy.product())->at(jet);
    double CEMF = (jetcEMEnergy.product())->at(jet);
    double CHM  = (jetcMultip.product())->at(jet);
    double NumConst = (jetcMultip.product())->at(jet)+(jetnMultip.product())->at(jet);
    
    if(NHF  < 0.99  &&
       NEMF < 0.99  &&
       CHF  > 0     &&
       CHM  > 0     &&
       CEMF < 0.99  &&
       NumConst > 1)return true;
    
    return false;
    
}


TLorentzVector AK4JetSelector::p4(int const & jet) const{
    TLorentzVector p4;
    p4.SetPtEtaPhiE( (jetPt.product())->at(jet), (jetEta.product())->at(jet), (jetPhi.product())->at(jet), (jetEnergy.product())->at(jet) );
    return  p4;
}

unsigned int AK4JetSelector::fwdInd(double fwdMinPt) const{
    
    unsigned int index = 999;
    double maxEta = 0;
    for(unsigned int ind = 0; ind< (jetPt.product())->size(); ++ind){
        
        double pt  = (jetPt.product())->at(ind);
        double eta = (jetEta.product())->at(ind);
        
        if(pt < jetMinPt_ || pt < fwdMinPt) continue;
        if(fabs(eta) > jetMaxEta_) continue;
        
        if(fabs(eta) > maxEta){
            maxEta = fabs(eta);
            index = ind;
        }
    }
    
    return index;
}




