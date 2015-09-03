// Original Author:  Nikoloz Skhirtladze
//         Created:  July, 19 Feb 2015
//
// bla


// system include files
#include <iostream>
#include <memory>
#include <vector>

// user include files
#include "Analysis/VLQAnalyzer/interface/WbAna.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>

#include <sstream>

// constructor and destructor definition
WbAna::WbAna(const edm::ParameterSet& iConfig) :
pn_                      (iConfig.getParameter<string>            ("processName")),
hltPaths_                (iConfig.getParameter<vector<string>>    ("hltPaths")),
hltParams_               (iConfig.getParameter<edm::ParameterSet> ("hltParams")),
tightMuParams_           (iConfig.getParameter<edm::ParameterSet> ("tightMuParams")),
looseMuParams_           (iConfig.getParameter<edm::ParameterSet> ("looseMuParams")),
tightElParams_           (iConfig.getParameter<edm::ParameterSet> ("tightElParams")),
looseElParams_           (iConfig.getParameter<edm::ParameterSet> ("looseElParams")),
ak4JetParams_            (iConfig.getParameter<edm::ParameterSet> ("ak4JetParams")),
ak8JetParams_            (iConfig.getParameter<edm::ParameterSet> ("ak8JetParams")),
metParams_               (iConfig.getParameter<edm::ParameterSet> ("metParams")),
selectionParams_         (iConfig.getParameter<edm::ParameterSet> ("selectionParams"))

{
    produces<unsigned>("ngoodAK4Jets");
    produces<unsigned>("ngoodAK8Jets");
    produces<unsigned>("nbtaggedlooseAK4");
    produces<unsigned>("nTJets");
    produces<unsigned>("nHJets");
    produces<unsigned>("nWJets");
    produces<double>("htak4jets");
    produces<double>("htak8jets");
    produces<double>("maxetaak4");
    produces<double>("MassLeading2AK8");
    produces<double>("DeltaEtaLeading2AK8");
    produces<double>("pt1stAK8");
    produces<double>("pt2ndAK8");
    produces<double>("mass1stAK8");
    produces<double>("mass2ndAK8");
    produces<vector<unsigned> >("ak4goodjets");
    produces<vector<unsigned> >("ak8goodjets");
    produces<vector<unsigned>>("bjetIdxs");
    produces<vector<unsigned>>("tjetIdxs");
    produces<vector<unsigned>>("hjetIdxs");
    produces<vector<unsigned>>("wjetIdxs");
    
    //register your products
    /* Examples
     produces<ExampleData2>();
     //if do put with a label
     produces<ExampleData2>("label");
     //if you want to put into the Run
     produces<ExampleData2,InRun>();
     */
    //now do what ever other initialization is needed
    
}


WbAna::~WbAna() {
}



//
// member functions
//


// ------------ method called to produce the data  ------------
bool WbAna::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
    using namespace edm;

   
    h1_["events"] -> Fill(1) ;


    // Declare instances of objects selections
    HLTSelector hlt(hltParams_, evt);
    
  //  bool isGoodTrig = hlt.isGoodHLTPath(hltPaths_);
  //  if(!isGoodTrig) return false;
    
    MuonSelector tightMu(tightMuParams_, evt);
    MuonSelector looseMu(looseMuParams_, evt);

    ElectronSelector tightEl(tightElParams_, evt);
    ElectronSelector looseEl(looseElParams_, evt);
    
    AK4JetSelector ak4Jet(ak4JetParams_, evt);
    AK8JetSelector ak8Jet(ak8JetParams_, evt);
    
    METSelector met(metParams_, evt);
    UserSelector mySelector(selectionParams_);
    
    UserSelector mySelectorNew(selectionParams_);
    
    
    // Vector collections of indexes
    uintvec tightMuColl(tightMu.size());
    uintvec looseMuColl(looseMu.size());
    
    uintvec tightElColl(tightEl.size());
    uintvec looseElColl(looseEl.size());
    
    uintvec ak4JetColl(ak4Jet.size());
    uintvec ak4BJetColl(ak4Jet.bsize());
    uintvec ak8JetColl(ak8Jet.size());
    
    h1_["ak4JetMult"] -> Fill(ak4JetColl.size()) ;
    h1_["ak8JetMult"] -> Fill(ak8JetColl.size()) ;

    // apply ak4 jet and lepton cleaning
    applyAK4JetElCleaning(ak4JetColl, ak4Jet, tightEl);
    applyAK4JetMuCleaning(ak4JetColl, ak4Jet, tightMu);
    
    // apply ak4 b jet and lepton cleaning
    applyAK4JetElCleaning(ak4BJetColl, ak4Jet, tightEl);
    applyAK4JetMuCleaning(ak4BJetColl, ak4Jet, tightMu);

    
    h1_["ak4CJetMult"] -> Fill(ak4JetColl.size()) ;
    h1_["ak8CJetMult"] -> Fill(ak8JetColl.size()) ;
    
    h1_["tightMuMult"] -> Fill(tightMuColl.size()) ;
    h1_["looseMuMult"] -> Fill(looseMuColl.size()) ;
    
    
    h1_["tightElMult"] -> Fill(tightElColl.size()) ;
    h1_["looseElMult"] -> Fill(looseElColl.size()) ;
    
    
    h1_["met"] -> Fill(met.pt()) ;
    

    TLorentzVector lepP4;
    if( (tightMuColl.size() + tightElColl.size()) == 1){
        
        if(tightMuColl.size() == 1){
            lepP4 = tightMu.p4(tightMuColl[0]);
        }
        else if(tightElColl.size() ==1 ){
            lepP4 = tightEl.p4(tightElColl[0]);
        }
        else{
            edm::LogError("WBAna") << " >>>> Something is wrong with lepton selection. "  ;
        }
        
        TLorentzVector matchedAK8TLVec;
        if(ak4JetColl.size() > 0){
            
            for(unsigned int ak4 = 0;  ak4 < ak4JetColl .size(); ak4++){
                
                TLorentzVector ak4tlvec = ak4Jet.p4(ak4JetColl[ak4]);
                cout <<"ak4 jet [" << ak4 <<" ] " << " pt: " << ak4tlvec.Pt() << endl;
            }
            
            bool isMatch = false;
            double dr_min = 0.4;
            TLorentzVector ak4tlvec = ak4Jet.p4(ak4JetColl[0]);
            for(unsigned int ak8 = 0;  ak8 < ak8JetColl .size(); ak8++){
                
                TLorentzVector ak8tlvec = ak8Jet.p4(ak8JetColl[ak8]);
                cout <<"ak8 jet [" << ak8 <<" ] " << " pt: " << ak8tlvec.Pt() << endl;
                double dr = ak4tlvec.DeltaR(ak8tlvec);
                if(dr < dr_min){
                    dr_min = dr;
                    isMatch = true;
                    matchedAK8TLVec = ak8tlvec;
                }
            }
        }
        
        if(ak4BJetColl.size() > 0){
            mySelector.setLepP4(lepP4);
            mySelector.setMETP4(met.p4());
            mySelector.setJetP4(ak4Jet.p4(ak4BJetColl[0]));
            mySelector.setFwdJetP4(ak4Jet.p4(ak4Jet.fwdInd(30)));
           
            
            h1_["lepPt"] ->Fill(lepP4.Pt());
            h1_["lepEta"] ->Fill(lepP4.Eta());
            
            int NCut = mySelector.getCutflow();
            for(int iCutFlow = 0; iCutFlow <= NCut; iCutFlow++){
                
                std::string iCut = CutFlowCase[iCutFlow];
                
                std::string name = ("MET"+iCut).c_str();
                h1_[name] ->Fill(met.pt());
                
                name = ("MT"+iCut).c_str();
                h1_[name] ->Fill(mySelector.getWMass());
                
                name = ("LepPt"+iCut).c_str();
                h1_[name] ->Fill(lepP4.Pt());
                
                name = ("LepEta"+iCut).c_str();
                h1_[name] ->Fill(lepP4.Eta());
                
                name = ("JetPt"+iCut).c_str();
                h1_[name] ->Fill( (ak4Jet.p4(ak4JetColl[0])).Pt() );
                
                name = ("LepJetDPhi"+iCut).c_str();
                h1_[name] ->Fill(mySelector.getLJDPhi());
                
                name = ("TriMass"+iCut).c_str();
                h1_[name] ->Fill(mySelector.getMass());
                
                name = ("ST"+iCut).c_str();
                h1_[name] ->Fill(mySelector.getSt());
                
                name = ("ForwardJetEta"+iCut).c_str();
                h1_[name] ->Fill((ak4Jet.p4(ak4Jet.fwdInd(30))).Eta());
                
                name = ("ForwardJetPt"+iCut).c_str();
                h1_[name] ->Fill((ak4Jet.p4(ak4Jet.fwdInd(30))).Pt());
                
                name = ("AK4JetMult"+iCut).c_str();
                h1_[name] ->Fill(ak4JetColl.size());
                
                name = ("AK4BJetMult"+iCut).c_str();
                h1_[name] ->Fill(ak4BJetColl.size());
                
                name = ("LeadingAK4BJetPt"+iCut).c_str();
                h1_[name] ->Fill(ak4Jet.p4(ak4BJetColl[0]).Pt());
                
                if(ak4JetColl.size() > 1){
                    name = ("SecLeadingAK4JetPt"+iCut).c_str();
                    h1_[name] ->Fill(ak4Jet.p4(ak4JetColl[1]).Pt());
                
                }
            }
        }
    }
    
    
    
    


    
    return true ;
    
}

// ------------ method called once each job just before starting event loop  ------------
void WbAna::beginJob() {
    
    h1_["events"] = fs->make<TH1D>("events", "events", 1, 0.5, 1.5) ;
    
    h1_["tightMuMult"] = fs->make<TH1D>("tightMuMult", "tightMuMult", 5, -0.5, 4.5) ;
    h1_["looseMuMult"] = fs->make<TH1D>("looseMuMult", "looseMuMult", 5, -0.5, 4.5) ;
    
    
    h1_["tightElMult"] = fs->make<TH1D>("tightElMult", "tightElMult", 5, -0.5, 4.5) ;
    h1_["looseElMult"] = fs->make<TH1D>("looseElMult", "looseElMult", 5, -0.5, 4.5) ;
    
    
    h1_["ak4JetMult"] = fs->make<TH1D>("ak4JetMult", "ak4JetMult", 10, -0.5, 9.5) ;
    h1_["ak8JetMult"] = fs->make<TH1D>("ak8JetMult", "ak8JetMult", 10, -0.5, 9.5) ;
    
    h1_["ak4CJetMult"] = fs->make<TH1D>("ak4CJetMult", "ak4CJetMult", 10, -0.5, 9.5) ;
    h1_["ak8CJetMult"] = fs->make<TH1D>("ak8CJetMult", "ak8CJetMult", 10, -0.5, 9.5) ;
    
    h1_["met"] = fs->make<TH1D>("met", "met", 100, 0, 500) ;
    
    h1_["lepPt"] = fs->make<TH1D>("lepPt", "lepPt", 100, 0, 500) ;
    h1_["lepEta"] = fs->make<TH1D>("lepEta", "lepEta", 60, -3, 3) ;
    

    for(int iCutFlow = 0; iCutFlow < NUM_CUTFLOW; iCutFlow++){
        
        std::string iCut = CutFlowCase[iCutFlow];
        
        std::string name = ("MET"+iCut).c_str();
        h1_[name.c_str()] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 1000);
        
        name = ("MT"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 500);
        
        name = ("LepPt"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 1000);
        
        name = ("LepEta"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(),  60, -3, 3);
        
        name = ("JetPt"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 1000);
        
        name = ("LepJetDPhi"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 35, 0, 3.5);
        
        name = ("TriMass"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(),  200, 0, 2000);
        
        name = ("ST"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 150, 0, 1500);
        
        name = ("ForwardJetEta"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, -5.0, 5.0);
        
        name = ("ForwardJetPt"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 500);
        
        name = ("AK4JetMult"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 10, -0.5, 9.5);
        
        name = ("AK4BJetMult"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 10, -0.5, 9.5);
        
        name = ("LeadingAK4BJetPt"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 1000);
        

        name = ("SecLeadingAK4JetPt"+iCut).c_str();
        h1_[name] = fs->make<TH1D>(name.c_str(), name.c_str(), 100, 0, 1000);
    }
}

// ------------ method called once each job just after ending the event loop  ------------
void WbAna::endJob() {
    return ; 
}



// cleaning for AK4 jets

void WbAna::applyAK4JetElCleaning(uintvec & targetColl, const AK4JetSelector  & ak4, const ElectronSelector  & el, double maxDR){
    
    const std::vector<unsigned int> elSize (el.size());
    
    for(unsigned int j = 0; j < targetColl.size(); j++){
        unsigned int ind_j = targetColl[j];
        
        bool isOverlap = false;
        
        for(unsigned int e = 0; e < elSize.size(); e++){
            unsigned int ind_e = elSize[e];
            
            double dr = ak4.p4(ind_j).DeltaR(el.p4(ind_e));
            
            if(dr < maxDR) isOverlap = true;
        }
        
        if(isOverlap) targetColl.erase (targetColl.begin()+j);
    }
}


void WbAna::applyAK4JetMuCleaning(uintvec & targetColl, const AK4JetSelector  & ak4, const MuonSelector  & mu, double maxDR){
    
    const std::vector<unsigned int> muSize (mu.size());
    
    for(unsigned int j = 0; j < targetColl.size(); j++){
        unsigned int ind_j = targetColl[j];
        
        bool isOverlap = false;
        
        for(unsigned int m = 0; m < muSize.size(); m++){
            unsigned int ind_m = muSize[m];
            
            double dr = ak4.p4(ind_j).DeltaR(mu.p4(ind_m));
            
            if(dr < maxDR) isOverlap = true;
        }
        
        if(isOverlap) targetColl.erase (targetColl.begin()+j);
    }
}


// cleaning for AK8 jets


void WbAna::applyAK8JetElCleaning(uintvec & targetColl, const AK8JetSelector  & ak8, const ElectronSelector  & el, double maxDR){
    
    const std::vector<unsigned int> elSize (el.size());
    
    for(unsigned int j = 0; j < targetColl.size(); j++){
        unsigned int ind_j = targetColl[j];
        
        bool isOverlap = false;
        
        for(unsigned int e = 0; e < elSize.size(); e++){
            unsigned int ind_e = elSize[e];
            
            double dr = ak8.p4(ind_j).DeltaR(el.p4(ind_e));
            
            if(dr < maxDR) isOverlap = true;
        }
        
        if(isOverlap) targetColl.erase (targetColl.begin()+j);
    }
}

void WbAna::applyAK8JetMuCleaning(uintvec & targetColl, const AK8JetSelector  & ak8, const MuonSelector  & mu, double maxDR){
    
    const std::vector<unsigned int> muSize (mu.size());
    
    for(unsigned int j = 0; j < targetColl.size(); j++){
        unsigned int ind_j = targetColl[j];
        
        bool isOverlap = false;
        
        for(unsigned int m = 0; m < muSize.size(); m++){
            unsigned int ind_m = muSize[m];
            
            double dr = ak8.p4(ind_j).DeltaR(mu.p4(ind_m));
            
            if(dr < maxDR) isOverlap = true;
        }
        
        if(isOverlap) targetColl.erase (targetColl.begin()+j);
    }
}




// ------------ method called when starting to processes a run  ------------
/*
 void
 WbAna::beginRun(edm::Run const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when ending the processing of a run  ------------
/*
 void
 WbAna::endRun(edm::Run const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when starting to processes a luminosity block  ------------
/*
 void
 WbAna::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
 void
 WbAna::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
 {
 }
 */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
WbAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

            

//define this as a plug-in
DEFINE_FWK_MODULE(WbAna);
