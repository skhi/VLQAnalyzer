#include <iostream>
#include "Analysis/VLQAna/interface/ElectronMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;
using namespace edm ;

ElectronMaker::ElectronMaker (edm::ParameterSet const& iConfig, edm::ConsumesCollector && iC) :
t_elCharge            (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elChargeLabel"))),
t_elD0                (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elD0Label"))),
t_elDz                (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elDzLabel"))),
t_elE                 (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elELabel"))),
t_elEta               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elEtaLabel"))),
t_elHoE               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elHoELabel"))),
t_elIso03             (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elIso03Label"))),
t_elKey               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elKeyLabel"))),
//t_elMass              (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elMassLabel"))),
t_elPhi               (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elPhiLabel"))),
t_elPt                (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elPtLabel"))),
//t_elY                 (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elYLabel"))),
t_eldEtaIn            (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("eldEtaInLabel"))),
t_eldPhiIn            (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("eldPhiInLabel"))),
t_elfull5x5siee       (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elfull5x5sieeLabel"))),
t_elhasMatchedConVeto (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elhasMatchedConVetoLabel"))),
t_elvidLoose          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidLooseLabel"))),
t_elvidMedium         (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidMediumLabel"))),
t_elvidTight          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidTightLabel"))),
t_elvidVeto           (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidVetoLabel"))),
t_elvidHEEP           (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elvidHEEPLabel"))),
t_elmissHits          (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elmissHitsLabel"))),
t_elooEmooP           (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elooEmooPLabel"))),
t_elscEta             (iC.consumes<vector<float>>(iConfig.getParameter<edm::InputTag>("elscEtaLabel"))),
elPtMin_              (iConfig.getParameter<double>("elPtMin")),
elPtMax_              (iConfig.getParameter<double>("elPtMax")),
elAbsEtaMax_          (iConfig.getParameter<double>("elAbsEtaMax"))
{
    std::string elidtypestr = iConfig.getParameter<std::string>("elidtype") ;
    if ( elidtypestr == "LOOSE" ) type_ = LOOSE ;
    else if ( elidtypestr == "MEDIUM" ) type_ = MEDIUM ;
    else if ( elidtypestr == "TIGHT" ) type_ = TIGHT ;
    else if ( elidtypestr == "VETO" ) type_ = VETO ;
    else edm::LogError(">>>>ERROR>>>>ElectronMaker::ElectronMaker>>>>  WrongElectronIdType: ") << type_<< " Check electron id type !!!" ;
}

ElectronMaker::~ElectronMaker () {}

void ElectronMaker::operator () (edm::Event& evt, vlq::ElectronCollection& electrons) {
    
    Handle<vector<float>> h_elCharge             ; evt.getByToken(t_elCharge            , h_elCharge            );
    Handle<vector<float>> h_elD0                 ; evt.getByToken(t_elD0                , h_elD0                );
    Handle<vector<float>> h_elDz                 ; evt.getByToken(t_elDz                , h_elDz                );
    Handle<vector<float>> h_elE                  ; evt.getByToken(t_elE                 , h_elE                 );
    Handle<vector<float>> h_elEta                ; evt.getByToken(t_elEta               , h_elEta               );
    Handle<vector<float>> h_elHoE                ; evt.getByToken(t_elHoE               , h_elHoE               );
    Handle<vector<float>> h_elIso03              ; evt.getByToken(t_elIso03             , h_elIso03             );
    Handle<vector<float>> h_elKey                ; evt.getByToken(t_elKey               , h_elKey               );
  //  Handle<vector<float>> h_elMass               ; evt.getByToken(t_elMass              , h_elMass              );
    Handle<vector<float>> h_elPhi                ; evt.getByToken(t_elPhi               , h_elPhi               );
    Handle<vector<float>> h_elPt                 ; evt.getByToken(t_elPt                , h_elPt                );
  //  Handle<vector<float>> h_elY                  ; evt.getByToken(t_elY                 , h_elY                 );
    Handle<vector<float>> h_eldEtaIn             ; evt.getByToken(t_eldEtaIn            , h_eldEtaIn            );
    Handle<vector<float>> h_eldPhiIn             ; evt.getByToken(t_eldPhiIn            , h_eldPhiIn            );
    Handle<vector<float>> h_elfull5x5siee        ; evt.getByToken(t_elfull5x5siee       , h_elfull5x5siee       );
    Handle<vector<float>> h_elhasMatchedConVeto  ; evt.getByToken(t_elhasMatchedConVeto , h_elhasMatchedConVeto );
    Handle<vector<float>> h_elvidLoose           ; evt.getByToken(t_elvidLoose          , h_elvidLoose          );
    Handle<vector<float>> h_elvidMedium          ; evt.getByToken(t_elvidMedium         , h_elvidMedium         );
    Handle<vector<float>> h_elvidTight           ; evt.getByToken(t_elvidTight          , h_elvidTight          );
    Handle<vector<float>> h_elvidVeto            ; evt.getByToken(t_elvidVeto           , h_elvidVeto           );
    Handle<vector<float>> h_elvidHEEP            ; evt.getByToken(t_elvidHEEP           , h_elvidHEEP           );
    Handle<vector<float>> h_elmissHits           ; evt.getByToken(t_elmissHits          , h_elmissHits          );
    Handle<vector<float>> h_elooEmooP            ; evt.getByToken(t_elooEmooP           , h_elooEmooP           );
    Handle<vector<float>> h_elscEta              ; evt.getByToken(t_elscEta             , h_elscEta             );
    
    for (unsigned iel = 0; iel < (h_elPt.product())->size(); ++iel) {
        
        double elPt = (h_elPt.product())->at(iel) ;
        double elAbsEta  = std::abs((h_elEta.product())->at(iel)) ;
        double elIso = (h_elIso03.product())->at(iel) ;
        double dEtaIn =(h_eldEtaIn.product())->at(iel);
        double dPhiIn =(h_eldPhiIn.product())->at(iel);
        double full5x5siee =(h_elfull5x5siee.product())->at(iel);
        double HoE =(h_elHoE.product())->at(iel);
        double D0 =(h_elD0.product())->at(iel);
        double Dz =(h_elDz.product())->at(iel);
        double ooEmooP =(h_elooEmooP.product())->at(iel);
        double hasMatchedConVeto=(h_elhasMatchedConVeto.product())->at(iel);
        double missHits=(h_elmissHits.product())->at(iel);
        bool   isEB = (h_elscEta.product())->at(iel) < 1.479 ;
        
        bool elisLoose  = passElId("LOOSE" , isEB, dEtaIn, dPhiIn, full5x5siee, HoE, D0, Dz, ooEmooP, elIso, hasMatchedConVeto, missHits);
        bool elisMedium = passElId("MEDIUM", isEB, dEtaIn, dPhiIn, full5x5siee, HoE, D0, Dz, ooEmooP, elIso, hasMatchedConVeto, missHits);
        bool elisTight  = passElId("TIGHT" , isEB, dEtaIn, dPhiIn, full5x5siee, HoE, D0, Dz, ooEmooP, elIso, hasMatchedConVeto, missHits);
        bool elisVeto   = passElId("VETO"  , isEB, dEtaIn, dPhiIn, full5x5siee, HoE, D0, Dz, ooEmooP, elIso, hasMatchedConVeto, missHits);
        
        bool passId(false);
        if (type_ == LOOSE  && elisLoose ) passId = true ;
        else if (type_ == MEDIUM && elisMedium) passId = true ;
        else if (type_ == TIGHT  && elisTight ) passId = true ;
        else if (type_ == VETO   && elisVeto  ) passId = true ;
        else passId = false ;
        
        if (elPt > elPtMin_ && elPt < elPtMax_ && elAbsEta < elAbsEtaMax_ && passId ){
            vlq::Electron electron ;
            TLorentzVector  elP4;
            elP4.SetPtEtaPhiE( (h_elPt.product())->at(iel), (h_elEta.product())->at(iel), (h_elPhi.product())->at(iel), (h_elE.product())->at(iel) ) ;
            electron.setP4                (elP4)                                      ;
            electron.setIndex             (iel)                                       ;
            electron.setCharge            (h_elCharge            .product()->at(iel)) ;
            electron.setD0                (h_elD0                .product()->at(iel)) ;
            electron.setDz                (h_elDz                .product()->at(iel)) ;
            electron.setE                 (h_elE                 .product()->at(iel)) ;
            electron.setEta               (h_elEta               .product()->at(iel)) ;
            electron.setHoE               (h_elHoE               .product()->at(iel)) ;
            electron.setIso03             (h_elIso03             .product()->at(iel)) ;
            electron.setKey               (h_elKey               .product()->at(iel)) ;
//            electron.setMass              (h_elMass              .product()->at(iel)) ;
            electron.setPhi               (h_elPhi               .product()->at(iel)) ;
            electron.setPt                (h_elPt                .product()->at(iel)) ;
//            electron.setY                 (h_elY                 .product()->at(iel)) ;
            electron.setdEtaIn            (h_eldEtaIn            .product()->at(iel)) ;
            electron.setdPhiIn            (h_eldPhiIn            .product()->at(iel)) ;
            electron.setfull5x5siee       (h_elfull5x5siee       .product()->at(iel)) ;
            electron.sethasMatchedConVeto (h_elhasMatchedConVeto .product()->at(iel)) ;
            electron.setisEB              (isEB) ;
            electron.setisLoose           (elisLoose ) ;
            electron.setisMedium          (elisMedium) ;
            electron.setisTight           (elisTight ) ;
            electron.setisVeto            (elisVeto  ) ;
            electron.setmissHits          (h_elmissHits          .product()->at(iel)) ;
            electron.setooEmooP           (h_elooEmooP           .product()->at(iel)) ;
            electron.setscEta             (h_elscEta             .product()->at(iel)) ;
            
            electrons.push_back(electron) ;
        }
        
    }
    
}


bool ElectronMaker::passElId(string WP, bool isEB, float dEtaIn, float dPhiIn, float full5x5, float hoe, float d0, float dz, float ooemoop,float Iso03,bool conv,int missHits){
    
    bool pass = false;
    if(WP == "VETO"){
        if(isEB){
            pass = (fabs(dEtaIn) < 0.0152) && (fabs(dPhiIn) < 0.216) && (full5x5 < 0.0114) && (hoe < 0.181) && (fabs(d0) < 0.0564) && (fabs(dz) < 0.472) && (ooemoop < 0.207) && (Iso03 < 0.126)  && !conv && (missHits <= 2);
        }
        else{
            pass = (fabs(dEtaIn) < 0.0113) && (fabs(dPhiIn) < 0.237) && (full5x5 < 0.0352) && (hoe < 0.116) && (fabs(d0) < 0.222) && (fabs(dz) < 0.921) && (ooemoop < 0.174) && (Iso03 < 0.144) && !conv && (missHits <= 3);
        }
    }
    else if(WP == "LOOSE"){
        if(isEB){
            pass = (fabs(dEtaIn) <   0.00477) && (fabs(dPhiIn) <   0.222) && (full5x5 <   0.011) && (hoe < 0.298) && (fabs(d0) < 0.05) && (fabs(dz) < 0.10) && (ooemoop <  0.241) && (Iso03 <  0.0994)  && !conv && (missHits <= 1);
        }
        else{
            pass = (fabs(dEtaIn) < 0.00868) && (fabs(dPhiIn) < 0.213) && (full5x5 <  0.0314) && (hoe < 0.101) && (fabs(d0) < 0.10) && (fabs(dz) < 0.20) && (ooemoop < 0.14) && (Iso03 < 0.107)  && !conv && (missHits <= 1);
        }
    }
    else if(WP == "MEDIUM"){
        if(isEB){
            pass = (fabs(dEtaIn) < 0.0103) && (fabs(dPhiIn) < 0.0336) && (full5x5 < 0.0101) && (hoe < 0.0876) && (fabs(d0) < 0.0118) && (fabs(dz) < 0.373) && (ooemoop < 0.0174) && (Iso03 < 0.0766)  && !conv && (missHits <= 2);
        }
        else{
            pass = (fabs(dEtaIn) < 0.00773) && (fabs(dPhiIn) < 0.114) && (full5x5 <  0.0283) && (hoe < 0.0678) && (fabs(d0) < 0.0739) && (fabs(dz) < 0.602) && (ooemoop < 0.0898) && (Iso03 < 0.0678) && !conv && (missHits <= 1);
        }
    }
    else if(WP == "TIGHT"){
        if(isEB){
            pass = (fabs(dEtaIn) < 0.00308) && (fabs(dPhiIn) < 0.0816) && (full5x5 < 0.00998) && (hoe < 0.0414) && (fabs(d0) < 0.05) && (fabs(dz) <  0.10) && (ooemoop <   0.0129) && (Iso03 <  0.0588)  && !conv && (missHits <= 1);
        }
        else{
            pass = (fabs(dEtaIn) < 0.00605) && (fabs(dPhiIn) < 0.0394) && (full5x5 < 0.0292) && (hoe < 0.0641) && (fabs(d0) < 0.1) && (fabs(dz) < 0.2) && (ooemoop <  0.0129)  && (Iso03 < 0.0571) && !conv && (missHits <= 1);
        }
    }
    
    return pass;
}
