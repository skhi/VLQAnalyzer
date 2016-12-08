#ifndef JETID_H
#define JETID_H

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <TLorentzVector.h>
#include <TMath.h>

using namespace std;
using namespace edm;

class JetID {
    
public: // interface
    
    enum Quality_t { LOOSE, TIGHT, TIGHTLEPVETO, N_QUALITY};
    
    JetID() {}
    JetID(JetID&) {}
    
    JetID( edm::ParameterSet const & params, edm::ConsumesCollector & iC ) :
    l_jetPt              (params.getParameter<edm::InputTag> ("jetPtLabel")),
    l_jetEta             (params.getParameter<edm::InputTag> ("jetEtaLabel")),
    l_jetPhi             (params.getParameter<edm::InputTag> ("jetPhiLabel")),
    l_jetMass            (params.getParameter<edm::InputTag> ("jetMassLabel")),
    l_jetEnergy          (params.getParameter<edm::InputTag> ("jetEnergyLabel")),
    l_jetnHadEnergy      (params.getParameter<edm::InputTag> ("jetnHadEnergyLabel")),
    l_jetnEMEnergy       (params.getParameter<edm::InputTag> ("jetnEMEnergyLabel")),
  //  l_jetHFHadronEnergy  (params.getParameter<edm::InputTag> ("jetHFHadronEnergyLabel")),
    l_jetcHadEnergy      (params.getParameter<edm::InputTag> ("jetcHadEnergyLabel")),
    l_jetcEMEnergy       (params.getParameter<edm::InputTag> ("jetcEMEnergyLabel")),
    l_jetnumDaughters    (params.getParameter<edm::InputTag> ("jetnumDaughtersLabel")),
    l_jetcMultip         (params.getParameter<edm::InputTag> ("jetcMultipLabel")),
    l_jetnMultip         (params.getParameter<edm::InputTag> ("jetnMultipLabel")),
    l_jetMuonEnergy      (params.getParameter<edm::InputTag> ("jetMuonEnergyLabel"))
    {
        
        iC.consumes<vector<float>> (l_jetPt             );
        iC.consumes<vector<float>> (l_jetEta            );
        iC.consumes<vector<float>> (l_jetPhi            );
        iC.consumes<vector<float>> (l_jetMass           );
        iC.consumes<vector<float>> (l_jetEnergy         );
        iC.consumes<vector<float>> (l_jetnHadEnergy     );
        iC.consumes<vector<float>> (l_jetnEMEnergy      );
     //   iC.consumes<vector<float>> (l_jetHFHadronEnergy );
        iC.consumes<vector<float>> (l_jetcHadEnergy     );
        iC.consumes<vector<float>> (l_jetcEMEnergy      );
        iC.consumes<vector<float>> (l_jetnumDaughters   );
        iC.consumes<vector<float>> (l_jetcMultip        );
        iC.consumes<vector<float>> (l_jetnMultip        );
        iC.consumes<vector<float>> (l_jetMuonEnergy     );
        
        std::string qualityStr = params.getParameter<std::string>("quality");
        
        if      ( qualityStr == "LOOSE") quality_ = LOOSE;
        else if ( qualityStr == "TIGHT") quality_ = TIGHT;
        else if ( qualityStr == "TIGHTLEPVETO") quality_ = TIGHTLEPVETO;
        else quality_ = LOOSE;
    }
    
    
    bool operator()( edm::Event& evt, int const & ijet) {
        return isJet( evt, ijet );
    }

    bool isJet(edm::Event& evt, int const & ijet) {
        
        
        evt.getByLabel (l_jetPt               , h_jetPt             );
        evt.getByLabel (l_jetEta              , h_jetEta            );
        evt.getByLabel (l_jetPhi              , h_jetPhi            );
        evt.getByLabel (l_jetMass             , h_jetMass           );
        evt.getByLabel (l_jetEnergy           , h_jetEnergy         );
        evt.getByLabel (l_jetnHadEnergy       , h_jetnHadEnergy     );
        evt.getByLabel (l_jetnEMEnergy        , h_jetnEMEnergy      );
      //  evt.getByLabel (l_jetHFHadronEnergy   , h_jetHFHadronEnergy );
        evt.getByLabel (l_jetcHadEnergy       , h_jetcHadEnergy     );
        evt.getByLabel (l_jetcEMEnergy        , h_jetcEMEnergy      );
        evt.getByLabel (l_jetnumDaughters     , h_jetnumDaughters   );
        evt.getByLabel (l_jetcMultip          , h_jetcMultip        );
        evt.getByLabel (l_jetnMultip          , h_jetnMultip        );
        evt.getByLabel (l_jetMuonEnergy       , h_jetMuonEnergy     );
        
        TLorentzVector jetP4Raw ;
        jetP4Raw.SetPtEtaPhiE( (h_jetPt.product())->at(ijet),
                              (h_jetEta.product())->at(ijet),
                              (h_jetPhi.product())->at(ijet),
                              (h_jetEnergy.product())->at(ijet) ) ;
        
        
        // cache some variables
        double chf = 0.0;
        double nhf = 0.0;
        double cef = 0.0;
        double nef = 0.0;
        int    nch = 0;
        int    nnh = 0;
       // double mue = 0;
        int    nconstituents = 0;
        
        chf             = (h_jetcHadEnergy.product())->at(ijet);// / jetP4Raw.E() ;
        nhf             = (h_jetnHadEnergy.product())->at(ijet); /// jetP4Raw.E() ;
        cef             = (h_jetcEMEnergy.product())->at(ijet); // / jetP4Raw.E() ;
        nef             = (h_jetnEMEnergy.product())->at(ijet); // / jetP4Raw.E() ;
        nch             = (h_jetcMultip.product())->at(ijet) ;
        nnh             = (h_jetnMultip.product())->at(ijet) ;
       // mue             = (h_jetMuonEnergy.product())->at(ijet)/ jetP4Raw.E() ;
        nconstituents   = nnh + nch;
        
        
        //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID
        
        float jeteta = (h_jetEta.product())->at(ijet);
        bool isGood = true;
        
        // Jet LOOSE ID selection
        if ( quality_ == LOOSE){
            if(std::abs(jeteta) < 2.7){
                
                if(nhf >= 0.99) isGood = false;
                if(nef >= 0.99) isGood = false;
                if(nconstituents <= 1) isGood = false;
                
                if(std::abs(jeteta) < 2.4){
                    if(chf <= 0)    isGood = false;
                    if(nch <= 0)    isGood = false;
                    if(cef >= 0.99) isGood = false;
                }
            }
            else if(std::abs(jeteta) < 3.0){
                
                if(nef >= 0.9)  isGood = false;
                if(nnh <= 2)    isGood = false;
            }
            else if(std::abs(jeteta) < 5.0){
                if(nef >= 0.9)  isGood = false;
                if(nnh <= 10)   isGood = false;
            }
        }
        else if ( quality_ == TIGHT){
            
            edm::LogError("JetID::JetID") << " >>>> Jet TIGHT ID is not implemented yet !!! "  ;
            isGood = false;
        }
        
        return isGood;
    }
    
private: // member variables
    
    Quality_t quality_;
    
    
    edm::InputTag l_jetPt              ;
    edm::InputTag l_jetEta             ;
    edm::InputTag l_jetPhi             ;
    edm::InputTag l_jetMass            ;
    edm::InputTag l_jetEnergy          ;
    edm::InputTag l_jetnHadEnergy      ;
    edm::InputTag l_jetnEMEnergy       ;
    edm::InputTag l_jetHFHadronEnergy  ;
    edm::InputTag l_jetcHadEnergy      ;
    edm::InputTag l_jetcEMEnergy       ;
    edm::InputTag l_jetnumDaughters    ;
    edm::InputTag l_jetcMultip         ;
    edm::InputTag l_jetnMultip         ;
    edm::InputTag l_jetMuonEnergy      ;
    
    Handle <vector<float>>  h_jetPt             ;
    Handle <vector<float>>  h_jetEta            ;
    Handle <vector<float>>  h_jetPhi            ;
    Handle <vector<float>>  h_jetMass           ;
    Handle <vector<float>>  h_jetEnergy          ;
    Handle <vector<float>>  h_jetnHadEnergy     ;
    Handle <vector<float>>  h_jetnEMEnergy      ;
    Handle <vector<float>>  h_jetHFHadronEnergy ;
    Handle <vector<float>>  h_jetcHadEnergy     ;
    Handle <vector<float>>  h_jetcEMEnergy      ;
    Handle <vector<float>>  h_jetnumDaughters   ;
    Handle <vector<float>>  h_jetcMultip        ;
    Handle <vector<float>>  h_jetnMultip        ;
    Handle <vector<float>>  h_jetMuonEnergy     ;
};

#endif 
