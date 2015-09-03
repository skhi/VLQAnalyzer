// header include file
#include "Analysis/VLQAnalyzer/interface/ElectronSelector.h"
#include <iostream>

using namespace std;
using namespace edm ;

ElectronSelector::ElectronSelector   (edm::ParameterSet const& pars, edm::Event& evt) :

elCharge_            (pars.getParameter<edm::InputTag>("elChargeLabel")),
elD0_                (pars.getParameter<edm::InputTag>("elD0Label")),
elDz_                (pars.getParameter<edm::InputTag>("elDzLabel")),
elE_                 (pars.getParameter<edm::InputTag>("elELabel")),
elEta_               (pars.getParameter<edm::InputTag>("elEtaLabel")),
elHoE_               (pars.getParameter<edm::InputTag>("elHoELabel")),
elIso03_             (pars.getParameter<edm::InputTag>("elIso03Label")),
elKey_               (pars.getParameter<edm::InputTag>("elKeyLabel")),
elMass_              (pars.getParameter<edm::InputTag>("elMassLabel")),
elPhi_               (pars.getParameter<edm::InputTag>("elPhiLabel")),
elPt_                (pars.getParameter<edm::InputTag>("elPtLabel")),
elY_                 (pars.getParameter<edm::InputTag>("elYLabel")),
eldEtaIn_            (pars.getParameter<edm::InputTag>("eldEtaInLabel")),
eldPhiIn_            (pars.getParameter<edm::InputTag>("eldPhiInLabel")),
elfull5x5siee_       (pars.getParameter<edm::InputTag>("elfull5x5sieeLabel")),
elhasMatchedConVeto_ (pars.getParameter<edm::InputTag>("elhasMatchedConVetoLabel")),
elisEB_              (pars.getParameter<edm::InputTag>("elisEBLabel")),
elisLoose_           (pars.getParameter<edm::InputTag>("elisLooseLabel")),
elisMedium_          (pars.getParameter<edm::InputTag>("elisMediumLabel")),
elisTight_           (pars.getParameter<edm::InputTag>("elisTightLabel")),
elisVeto_            (pars.getParameter<edm::InputTag>("elisVetoLabel")),
elmissHits_          (pars.getParameter<edm::InputTag>("elmissHitsLabel")),
elooEmooP_           (pars.getParameter<edm::InputTag>("elooEmooPLabel")),
elscEta_             (pars.getParameter<edm::InputTag>("elscEtaLabel")),
elMinPt_             (pars.getParameter<double>("elMinPt")),
elMaxEta_            (pars.getParameter<double>("elMaxEta")),
elIDType_            (pars.getParameter<std::string>("elIDType"))
{
    evt.getByLabel(elCharge_            , elCharge            );
    evt.getByLabel(elD0_                , elD0                );
    evt.getByLabel(elDz_                , elDz                );
    evt.getByLabel(elE_                 , elE                 );
    evt.getByLabel(elEta_               , elEta               );
    evt.getByLabel(elHoE_               , elHoE               );
    evt.getByLabel(elIso03_             , elIso03             );
    evt.getByLabel(elKey_               , elKey               );
    evt.getByLabel(elMass_              , elMass              );
    evt.getByLabel(elPhi_               , elPhi               );
    evt.getByLabel(elPt_                , elPt                );
    evt.getByLabel(elY_                 , elY                 );
    evt.getByLabel(eldEtaIn_            , eldEtaIn            );
    evt.getByLabel(eldPhiIn_            , eldPhiIn            );
    evt.getByLabel(elfull5x5siee_       , elfull5x5siee       );
    evt.getByLabel(elhasMatchedConVeto_ , elhasMatchedConVeto );
    evt.getByLabel(elisEB_              , elisEB              );
    evt.getByLabel(elisLoose_           , elisLoose           );
    evt.getByLabel(elisMedium_          , elisMedium          );
    evt.getByLabel(elisTight_           , elisTight           );
    evt.getByLabel(elisVeto_            , elisVeto            );
    evt.getByLabel(elmissHits_          , elmissHits          );
    evt.getByLabel(elooEmooP_           , elooEmooP           );
    evt.getByLabel(elscEta_             , elscEta             );
}

ElectronSelector::~ElectronSelector(){
    

}



// methods declaration

vector<unsigned int> ElectronSelector::size() const{
    
    vector<unsigned int> elCollection;
    for(unsigned int ind = 0; ind< (elPt.product())->size(); ++ind){
        if((elPt.product())->at(ind) < elMinPt_) continue;
        if(fabs((elEta.product())->at(ind)) > elMaxEta_) continue;
        if(elIDType_ == "TIGHT"){
            if(!isTight(ind)) continue;
        }
        else if(elIDType_ == "MEDIUM"){
            if(!isMedium(ind)) continue;
        }
        else if(elIDType_ == "LOOSE"){
            if(!isLoose(ind)) continue;
        }
        else{
            edm::LogError("ElectronSelector::size") << " >>>> Wrong Electron ID Type: " << elIDType_<< " Check electron ID type !!!" ;
        }
        elCollection.push_back(ind);
    }
    
    return elCollection;
}



bool ElectronSelector::isTight(int const & el) const{
    
    // tight electron selections for barrel/endcap
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#PHYS14_selection_alconditions
    
    const std::pair<double,double> DETA           = std::make_pair(0.00926  ,  0.00724);
    const std::pair<double,double> DPHI           = std::make_pair(0.0336   ,  0.0918);
    const std::pair<double,double> FULL5X5        = std::make_pair(0.0101   ,  0.0279);
    const std::pair<double,double> HOVERE         = std::make_pair(0.0597   ,  0.0615);
    const std::pair<double,double> DO             = std::make_pair(0.0111   ,  0.0351);
    const std::pair<double,double> DZ             = std::make_pair(0.0466   ,  0.417);
    const std::pair<double,double> OOEMOOP        = std::make_pair(0.012    ,  0.00999);
    const std::pair<double,double> ISO            = std::make_pair(0.0354   ,  0.0646);
    const std::pair<double,double> HITS           = std::make_pair(2  , 1);
    
    if(fabs((elscEta.product())->at(el)) <= 1.479 ){
        if( fabs((eldEtaIn.product())->at(el))              > DETA.first        ) return false;
        if( fabs((eldPhiIn.product())->at(el))              > DPHI.first        ) return false;
        if( fabs((elfull5x5siee.product())->at(el))         > FULL5X5.first     ) return false;
        if( fabs((elHoE.product())->at(el))                 > HOVERE.first      ) return false;
        if( fabs((elD0.product())->at(el))                  > DO.first          ) return false;
        if( fabs((elDz.product())->at(el))                  > DZ.first          ) return false;
        if( fabs((elIso03.product())->at(el))               > ISO.first         ) return false;
        if( fabs((elooEmooP.product())->at(el))             > OOEMOOP.first     ) return false;
        if( (elhasMatchedConVeto.product())->at(el)                             ) return false;
        if( (elmissHits.product())->at(el)                  >  HITS.first       ) return false;
    }
    else if(fabs((elscEta.product())->at(el)) <= 2.5){
        if( fabs((eldEtaIn.product())->at(el))              > DETA.second       ) return false;
        if( fabs((eldPhiIn.product())->at(el))              > DPHI.second       ) return false;
        if( fabs((elfull5x5siee.product())->at(el))         > FULL5X5.second    ) return false;
        if( fabs((elHoE.product())->at(el))                 > HOVERE.second     ) return false;
        if( fabs((elD0.product())->at(el))                  > DO.second         ) return false;
        if( fabs((elDz.product())->at(el))                  > DZ.second         ) return false;
        if( fabs((elIso03.product())->at(el))               > ISO.second        ) return false;
        if( fabs((elooEmooP.product())->at(el))             > OOEMOOP.second    ) return false;
        if( (elhasMatchedConVeto.product())->at(el)                             ) return false;
        if( (elmissHits.product())->at(el)                  >  HITS.second      ) return false;
    }
    else{
        
        return false;
    }
    
    
    return true;
}


bool ElectronSelector::isMedium(int const & el) const{
    
    // Medium electron selections for barrel/endcap
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#PHYS14_selection_alconditions
    
    const std::pair<double,double> DETA           = std::make_pair(0.008925  , 0.007429 );
    const std::pair<double,double> DPHI           = std::make_pair(0.035973  , 0.067879 );
    const std::pair<double,double> FULL5X5        = std::make_pair(0.009996  , 0.030135 );
    const std::pair<double,double> HOVERE         = std::make_pair(0.050537  , 0.086782 );
    const std::pair<double,double> DO             = std::make_pair(0.012235  , 0.036719 );
    const std::pair<double,double> DZ             = std::make_pair(0.042020  , 0.138142 );
    const std::pair<double,double> OOEMOOP        = std::make_pair(0.091942  , 0.100683 );
    const std::pair<double,double> ISO            = std::make_pair(0.107587  , 0.113254 );
    const std::pair<double,double> HITS           = std::make_pair(1  , 1);
    
    if(fabs((elscEta.product())->at(el)) <= 1.479 ){
        if( fabs((eldEtaIn.product())->at(el))              > DETA.first        ) return false;
        if( fabs((eldPhiIn.product())->at(el))              > DPHI.first        ) return false;
        if( fabs((elfull5x5siee.product())->at(el))         > FULL5X5.first     ) return false;
        if( fabs((elHoE.product())->at(el))                 > HOVERE.first      ) return false;
        if( fabs((elD0.product())->at(el))                  > DO.first          ) return false;
        if( fabs((elDz.product())->at(el))                  > DZ.first          ) return false;
        if( fabs((elIso03.product())->at(el))               > ISO.first         ) return false;
        if( fabs((elooEmooP.product())->at(el))             > OOEMOOP.first     ) return false;
        if( (elhasMatchedConVeto.product())->at(el)                             ) return false;
        if( (elmissHits.product())->at(el)                  >  HITS.first       ) return false;
    }
    else if(fabs((elscEta.product())->at(el)) <= 2.5){
        if( fabs((eldEtaIn.product())->at(el))              > DETA.second       ) return false;
        if( fabs((eldPhiIn.product())->at(el))              > DPHI.second       ) return false;
        if( fabs((elfull5x5siee.product())->at(el))         > FULL5X5.second    ) return false;
        if( fabs((elHoE.product())->at(el))                 > HOVERE.second     ) return false;
        if( fabs((elD0.product())->at(el))                  > DO.second         ) return false;
        if( fabs((elDz.product())->at(el))                  > DZ.second         ) return false;
        if( fabs((elIso03.product())->at(el))               > ISO.second        ) return false;
        if( fabs((elooEmooP.product())->at(el))             > OOEMOOP.second    ) return false;
        if( (elhasMatchedConVeto.product())->at(el)                             ) return false;
        if( (elmissHits.product())->at(el)                  >  HITS.second      ) return false;
    }
    else{
        
        return false;
    }
    
    
    return true;
}


bool ElectronSelector::isLoose(int const & el) const{
    
    // Loose electron selections for barrel/endcap
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#PHYS14_selection_alconditions
    
    const std::pair<double,double> DETA           = std::make_pair(0.0105   , 0.00814);
    const std::pair<double,double> DPHI           = std::make_pair(0.115    , 0.182);
    const std::pair<double,double> FULL5X5        = std::make_pair(0.0103   , 0.0301);
    const std::pair<double,double> HOVERE         = std::make_pair(0.104    , 0.0897);
    const std::pair<double,double> DO             = std::make_pair(0.0261   , 0.118);
    const std::pair<double,double> DZ             = std::make_pair(0.41     , 0.822);
    const std::pair<double,double> OOEMOOP        = std::make_pair(0.102    , 0.126);
    const std::pair<double,double> ISO            = std::make_pair(0.0893   , 0.121);
    const std::pair<double,double> HITS           = std::make_pair(2  , 1);
        
    if(fabs((elscEta.product())->at(el)) <= 1.479 ){
        if( fabs((eldEtaIn.product())->at(el))              > DETA.first        ) return false;
        if( fabs((eldPhiIn.product())->at(el))              > DPHI.first        ) return false;
        if( fabs((elfull5x5siee.product())->at(el))         > FULL5X5.first     ) return false;
        if( fabs((elHoE.product())->at(el))                 > HOVERE.first      ) return false;
        if( fabs((elD0.product())->at(el))                  > DO.first          ) return false;
        if( fabs((elDz.product())->at(el))                  > DZ.first          ) return false;
        if( fabs((elIso03.product())->at(el))               > ISO.first         ) return false;
        if( fabs((elooEmooP.product())->at(el))             > OOEMOOP.first     ) return false;
        if( (elhasMatchedConVeto.product())->at(el)                             ) return false;
        if( (elmissHits.product())->at(el)                  >  HITS.first       ) return false;
    }
    else if(fabs((elscEta.product())->at(el)) <= 2.5){
        if( fabs((eldEtaIn.product())->at(el))              > DETA.second       ) return false;
        if( fabs((eldPhiIn.product())->at(el))              > DPHI.second       ) return false;
        if( fabs((elfull5x5siee.product())->at(el))         > FULL5X5.second    ) return false;
        if( fabs((elHoE.product())->at(el))                 > HOVERE.second     ) return false;
        if( fabs((elD0.product())->at(el))                  > DO.second         ) return false;
        if( fabs((elDz.product())->at(el))                  > DZ.second         ) return false;
        if( fabs((elIso03.product())->at(el))               > ISO.second        ) return false;
        if( fabs((elooEmooP.product())->at(el))             > OOEMOOP.second    ) return false;
        if( (elhasMatchedConVeto.product())->at(el)                             ) return false;
        if( (elmissHits.product())->at(el)                  >  HITS.second      ) return false;
    }
    else{
        
        return false;
    }
    
    
    return true;
}


TLorentzVector ElectronSelector::p4(int const & el) const{
    TLorentzVector p4;
    p4.SetPtEtaPhiE( (elPt.product())->at(el), (elEta.product())->at(el), (elPhi.product())->at(el), (elE.product())->at(el) );
    return  p4;
}

double ElectronSelector::iso(int const & el) const{ return ((elIso03.product())->at(el)); }







