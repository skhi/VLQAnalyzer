// -*- C++ -*-
//
// Package:    Analysis/VLQAna
// Class:      SingleLepAnaSkim
//
/**\class VLQAna SingleLepAnaSkim.cc Analysis/VLQAna/plugins/SingleLepAnaSkim.cc
 Description: [one line class summary]
 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Devdatta Majumder
//         Created:  Fri, 27 Feb 2015 16:09:10 GMT
// Modified: Sadia Khalil
//           25 Mar 2016 17:11 CDT
//

#include <iostream>
#include <memory>
#include <vector>


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "AnalysisDataFormats/BoostedObjects/interface/GenParticleWithDaughters.h"
#include "AnalysisDataFormats/BoostedObjects/interface/ResolvedVjj.h"

#include "Analysis/VLQAna/interface/Utilities.h"
#include "Analysis/VLQAna/interface/DileptonCandsProducer.h"
#include "Analysis/VLQAna/interface/CandidateFilter.h"
#include "Analysis/VLQAna/interface/MuonMaker.h"
#include "Analysis/VLQAna/interface/ElectronMaker.h"
#include "Analysis/VLQAna/interface/JetMaker.h"
#include "Analysis/VLQAna/interface/HT.h"
#include "Analysis/VLQAna/interface/ApplyLeptonSFs.h"
#include "Analysis/VLQAna/interface/CandidateCleaner.h"
#include "Analysis/VLQAna/interface/METMaker.h"
#include "Analysis/VLQAna/interface/PickGenPart.h"
#include "Analysis/VLQAna/interface/JetID.h"
#include "Analysis/VLQAna/interface/MassReco.h"
#include "Analysis/VLQAna/interface/BTagSFUtils.h"

#include <TFile.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLorentzVector.h>
#include <TFitResult.h>

//
// class declaration
//

class SingleLepAnaSkim : public edm::EDFilter {
public:
    explicit SingleLepAnaSkim(const edm::ParameterSet&);
    ~SingleLepAnaSkim();
    int hltDecision(const edm::ParameterSet & param);
    void printing(std::string str){std::cout << str<<"\n";}
    
private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    void fillAdditionalPlots( vlq::ElectronCollection goodElectrons,double evtwt);
    double GetDYNLOCorr(const double dileppt);
    double ZptCorr(vlq::Candidate, double, double);
    double htCorr(double ht, double p0, double p1);
    bool solve_nu(const TLorentzVector &vlep, const TLorentzVector &vnu, double wmass, double& nuz1, double& nuz2);
    void adjust_e_for_mass(TLorentzVector& v, double mass);
    
    // ----------member data ---------------------------
    edm::EDGetTokenT<string>   t_evttype         ;
    edm::EDGetTokenT<double>   t_evtwtGen        ;
    edm::EDGetTokenT<double>   t_evtwtPV         ;
    edm::EDGetTokenT<double>   t_evtwtPVLow      ;
    edm::EDGetTokenT<double>   t_evtwtPVHigh     ;
    edm::EDGetTokenT<unsigned> t_npv             ;
    edm::EDGetTokenT<bool>     t_hltdecision_ele ;
    edm::EDGetTokenT<bool>     t_hltdecision_mu  ;
    edm::EDGetTokenT<double>   t_toppt           ;
    edm::ParameterSet GenHSelParams_             ;
    edm::ParameterSet genParams_                 ;
    const bool sys_                              ;
    bool btagsf_bcUp_                            ;
    bool btagsf_bcDown_                          ;
    bool btagsf_lUp_                             ;
    bool btagsf_lDown_                           ;
    const bool PileupUp_                         ;
    const bool PileupDown_                       ;
    const bool applyLeptonSFs_                   ;
    const bool applyBTagSFs_                     ;
    const bool applyHtCorr_                      ;
    const bool applyTopPtCorr_                   ;
    const double jecShift_                       ;
    const double jerShift_                       ;
    ApplyLeptonSFs musf                          ;
    ApplyLeptonSFs elesf                         ;
    METMaker metmaker                            ;
    MuonMaker muonmaker                          ;
    ElectronMaker electronmaker                  ;
    JetMaker jetAK4maker                         ;
    JetMaker jetAK4BTaggedmaker                  ;
    JetMaker jetAK8maker                         ;
    JetMaker jetWTaggedmaker                     ;
    edm::Service<TFileService> fs                ;
    std::map<std::string, TH1D*> h1_             ;
    std::map<std::string, TH2D*> h2_             ;
    const std::string fnamebtagSF_               ;
    std::unique_ptr<BTagSFUtils> btagsfutils_    ;
    vlq::ElectronCollection signalElectrons      ;
    vlq::MuonCollection signalMuons              ;
    vlq::JetCollection goodAK4Jets               ;
    vlq::JetCollection goodAK8Jets               ;
    vlq::MetCollection goodMet                   ;
    edm::ParameterSet signalSelection_           ;
    edm::ParameterSet wjetSelection_             ;
    edm::ParameterSet ttbarSelection_            ;
};

using namespace std;

// constructors and destructor
SingleLepAnaSkim::SingleLepAnaSkim(const edm::ParameterSet& iConfig) :
t_evttype               (consumes<string> (iConfig.getParameter<edm::InputTag>("evttype"))),
t_evtwtGen              (consumes<double> (iConfig.getParameter<edm::InputTag>("evtwtGen"))),
t_evtwtPV               (consumes<double>  (iConfig.getParameter<edm::InputTag>("evtwtPV"))),
t_evtwtPVLow            (consumes<double>  (iConfig.getParameter<edm::InputTag>("evtwtPVLow"))),
t_evtwtPVHigh           (consumes<double>  (iConfig.getParameter<edm::InputTag>("evtwtPVHigh"))),
t_npv                   (consumes<unsigned>(iConfig.getParameter<edm::InputTag>("npv"))),
t_hltdecision_ele       (consumes<bool>    (iConfig.getParameter<edm::InputTag>("hltdecisionEle"))),
t_hltdecision_mu        (consumes<bool>    (iConfig.getParameter<edm::InputTag>("hltdecisionMu"))),
t_toppt                 (consumes<double>  (iConfig.getParameter<edm::InputTag>("toppt"))),
GenHSelParams_          (iConfig.getParameter<edm::ParameterSet> ("GenHSelParams")),
sys_                    (iConfig.getParameter<bool>              ("sys")),
btagsf_bcUp_            (iConfig.getParameter<bool>              ("btagsf_bcUp")),
btagsf_bcDown_          (iConfig.getParameter<bool>              ("btagsf_bcDown")),
btagsf_lUp_             (iConfig.getParameter<bool>              ("btagsf_lUp")),
btagsf_lDown_           (iConfig.getParameter<bool>              ("btagsf_lDown")),
PileupUp_               (iConfig.getParameter<bool>              ("PileupUp")),
PileupDown_             (iConfig.getParameter<bool>              ("PileupDown")),
applyLeptonSFs_         (iConfig.getParameter<bool>              ("applyLeptonSFs")),
applyBTagSFs_           (iConfig.getParameter<bool>              ("applyBTagSFs")),
applyHtCorr_            (iConfig.getParameter<bool>              ("applyHtCorr")),
applyTopPtCorr_         (iConfig.getParameter<bool>              ("applyTopPtCorr")),
jecShift_               (iConfig.getParameter<double>            ("jecShift")),
jerShift_               (iConfig.getParameter<double>            ("jerShift")),
musf                    (iConfig.getParameter<edm::ParameterSet> ("musfParams")),
elesf                   (iConfig.getParameter<edm::ParameterSet> ("elesfParams")),
metmaker                (iConfig.getParameter<edm::ParameterSet> ("metselParams"),consumesCollector()),
muonmaker               (iConfig.getParameter<edm::ParameterSet> ("muselParams"),consumesCollector()),
electronmaker           (iConfig.getParameter<edm::ParameterSet> ("elselParams"),consumesCollector()),
jetAK4maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK4selParams"),consumesCollector()),
jetAK4BTaggedmaker      (iConfig.getParameter<edm::ParameterSet> ("jetAK4BTaggedselParams"),consumesCollector()),
jetAK8maker             (iConfig.getParameter<edm::ParameterSet> ("jetAK8selParams"),consumesCollector()),
jetWTaggedmaker         (iConfig.getParameter<edm::ParameterSet> ("jetWTaggedselParams"),consumesCollector()),
fnamebtagSF_            (iConfig.getParameter<std::string>       ("fnamebtagSF")),
btagsfutils_            (new BTagSFUtils(fnamebtagSF_,BTagEntry::OP_MEDIUM,30., 670., 30., 670., 20., 1000.)),
signalSelection_        (iConfig.getParameter<edm::ParameterSet> ("signalSelection")),
wjetSelection_          (iConfig.getParameter<edm::ParameterSet> ("wjetSelection")),
ttbarSelection_         (iConfig.getParameter<edm::ParameterSet> ("ttbarSelection"))
{
    cout <<"constructor finished" << endl;
}


SingleLepAnaSkim::~SingleLepAnaSkim() {}

bool SingleLepAnaSkim::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
    using namespace edm;
    
    // set all objects vectors to zero
    
    signalElectrons.clear();
    signalMuons.clear();
    goodMet.clear();
    goodAK4Jets.clear();
    goodAK8Jets.clear();
    
    /*
    
    Handle<string>   h_evttype          ; evt.getByToken(t_evttype        , h_evttype     ) ;
    Handle<double>   h_evtwtGen         ; evt.getByToken(t_evtwtGen       , h_evtwtGen    ) ;
    Handle<double>   h_evtwtPV          ; evt.getByToken(t_evtwtPV        , h_evtwtPV     ) ;
    Handle<double>   h_evtwtPVLow       ; evt.getByToken(t_evtwtPVLow     , h_evtwtPVLow  ) ;
    Handle<double>   h_evtwtPVHigh      ; evt.getByToken(t_evtwtPVHigh    , h_evtwtPVHigh ) ;
    Handle<unsigned> h_npv              ; evt.getByToken(t_npv            , h_npv         ) ;
    Handle<bool>     h_hltdecision_mu   ; evt.getByToken(t_hltdecision_mu , h_hltdecision_mu ) ;
    Handle<bool>     h_hltdecision_ele  ; evt.getByToken(t_hltdecision_ele, h_hltdecision_ele ) ;
    Handle<double>   h_toppt            ; evt.getByToken(t_toppt          , h_toppt       ) ;
*/
    
  //  h1_["truePU"]->Fill(*h_evtwtPV.product());
  //  h1_["nPU"]   ->Fill(*h_npv.product());
    
    
    //// Single lepton analysis skim
    
    muonmaker(evt, signalMuons) ;
    electronmaker(evt, signalElectrons) ;
    
    jetAK4maker(evt, goodAK4Jets);
    
    CandidateCleaner cleanjets(0.4);
    cleanjets(goodAK4Jets, signalMuons);
    cleanjets(goodAK4Jets, signalElectrons);
    

    h1_["events"]   ->Fill(1);
    
    if( (signalElectrons.size() + signalMuons.size()) >= 1){
        
        TLorentzVector ele_p4;
        TLorentzVector mu_p4;
        if(signalElectrons.size() > 0){
            ele_p4 = signalElectrons.at(0).getP4();
        }
        else if(signalMuons.size() > 0){
            mu_p4 = signalMuons.at(0).getP4();
        }
        else{
        }
        
        // leading lepton pt > 30
        double max_pt = TMath::Max(ele_p4.Pt(),mu_p4.Pt());
        if( max_pt < 30. ) return false;
    }
    else{
        return false;
    }
    
    // leading jet pt > 50
    if(goodAK4Jets.size() > 0 && goodAK4Jets.at(0).getP4().Pt() < 50.) return false;
    if(goodAK4Jets.size() == 0) return false;
    
    return true;
}

// ------------ method called once each job just before starting event loop  ------------
void SingleLepAnaSkim::beginJob() {
    
    h1_["truePU"] = fs->make<TH1D>("truePU", "truePU", 51, -0.5, 50.5);
    h1_["nPU"] = fs->make<TH1D>("nPU", "nPU", 51, -0.5, 50.5);
    h1_["events"] = fs->make<TH1D>("events", "events", 1, 0.5, 1.5);
    
}




bool SingleLepAnaSkim::solve_nu(const TLorentzVector &vlep, const TLorentzVector &vnu, double wmass, double& nuz1, double& nuz2){
    //
    // Purpose: Solve for the neutrino longitudinal z-momentum that makes
    // the leptonic W have mass WMASS.
    //
    // Inputs:
    // ev - The event to solve.
    // wmass - The desired W mass.
    //
    // Outputs:
    // nuz1 - First solution (smaller absolute value).
    // nuz2 - Second solution.
    //
    // Returns:
    // True if there was a real solution. False if there were only
    // imaginary solutions. (In that case, we just set the imaginary
    // part to zero.)
    //
    TLorentzVector tmp;
    tmp = vlep;
    bool discrim_flag = true;
    
    //std::cout << "Before: " << vlep.Pt() << " " << vlep.Eta() << " " << vlep.Phi() << " " << vlep.M() << std::endl;
    
    
    double x = vlep.X()*vnu.X() + vlep.Y()*vnu.Y() + wmass*wmass/2;
    double a = vlep.Z()*vlep.Z() - vlep.E()*vlep.E();
    double b = 2*x*vlep.Z();
    double c = x*x - vnu.Perp2() * vlep.E()*vlep.E();
    double d = b*b - 4*a*c;
    if (d < 0){
        d = 0;
        discrim_flag = false;
    }
    
    nuz1 = (-b + sqrt(d))/2/a;
    nuz2 = (-b - sqrt(d))/2/a;
    if (abs(nuz1) > abs(nuz2))
        swap (nuz1, nuz2);
    
    //std::cout << "After: " << vlep.Pt() << " " << vlep.Eta() << " " << vlep.Phi() << " " << vlep.M() << std::endl;
    if (tmp != vlep){
        std::cout << "Before: " << tmp.Pt() << " " << tmp.Eta() << " " << tmp.Phi() << " " << tmp.M() << std::endl;
        std::cout << "After: " << vlep.Pt() << " " << vlep.Eta() << " " << vlep.Phi() << " " << vlep.M() << std::endl;
    }
    return discrim_flag;
}

void SingleLepAnaSkim::adjust_e_for_mass(TLorentzVector& v, double mass){
    //
    // Purpose: Adjust the energy component of V (leaving the 3-vector part
    // unchanged) so that it has mass MASS.
    //
    // Inputs:
    // v - The 4-vector to scale.
    // mass - The desired mass of the 4-vector.
    //
    // Outputs:
    // v - The scaled 4-vector.
    //
    v.SetE(sqrt(v.Vect().Mag2() + mass*mass));
}





void SingleLepAnaSkim::endJob() {
    
    return ;
}

DEFINE_FWK_MODULE(SingleLepAnaSkim);


  

