#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Run.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

#include "Analysis/VLQAna/interface/PickGenPart.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include <TFile.h>
#include <TH1D.h>

class EventCleaner : public edm::EDFilter {
public:
    explicit EventCleaner(const edm::ParameterSet&) ;
    ~EventCleaner() ;
private:
    virtual void beginJob() override;
    virtual bool filter(edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    virtual void beginRun(edm::Run const& run, edm::EventSetup const& es);
    virtual void endRun(edm::Run const& run, edm::EventSetup const& es);
    
    double GetLumiWeightsPVBased (const std::string file, const std::string hist, const unsigned npv) ;
    
    edm::LumiReWeighting LumiWeights_;
    edm::LumiReWeighting LumiWeightsLow_;
    edm::LumiReWeighting LumiWeightsHigh_;
    
    edm::InputTag l_runno                                  ;
    edm::InputTag l_lumisec                                ;
    edm::InputTag l_evtno                                  ;
    edm::InputTag l_trigName                               ;
    edm::InputTag l_trigBit                                ;
    edm::InputTag l_metFiltersName                         ;
    edm::InputTag l_metFiltersBit                          ;
    edm::InputTag l_lheEvtProd                             ;
    std::string   l_genEvtInfoProd                         ;
    edm::InputTag l_vtxRho                                 ;
    edm::InputTag l_vtxZ                                   ;
    edm::InputTag l_vtxNdf                                 ;
    edm::InputTag l_npv                                    ;
    edm::InputTag l_puNtrueInt                             ;
    std::vector<std::string> hltMuPaths_                   ;
    std::vector<std::string> hltElePaths_                  ;
    std::vector<std::string> metFilters_                   ;
    const bool isData_                                     ;
    const bool doPUReweightingOfficial_                    ;
    const std::string file_PVWt_                           ;
    const std::string file_PUDistData_                     ;
    const std::string file_PUDistDataLow_                  ;
    const std::string file_PUDistDataHigh_                 ;
    const std::string file_PUDistMC_                       ;
    const std::string hist_PVWt_                           ;
    const std::string hist_PUDistData_                     ;
    const std::string hist_PUDistMC_                       ;
    const bool cleanEvents_                                ;
    const bool storeLHEWts_                                ;
    edm::EDGetTokenT<GenEventInfoProduct> t_genEvtInfoProd ;
    edm::EDGetTokenT<LHEEventProduct> t_lheEvtProd         ;
    std::vector<std::string> lhe_weight_labels_            ;
    edm::ParameterSet   topParams_                         ;
    PickGenPart         picktop                            ;
    
    edm::Handle <std::vector<std::string>> h_trigName                                     ;
    edm::Handle <std::vector<std::string>> h_metFiltersName                               ;
    
    

    
};

EventCleaner::EventCleaner(const edm::ParameterSet& iConfig) :
l_runno                 (iConfig.getParameter<edm::InputTag>            ("runnoLabel")),
l_lumisec               (iConfig.getParameter<edm::InputTag>            ("lumisecLabel")),
l_evtno                 (iConfig.getParameter<edm::InputTag>            ("evtnoLabel")),
l_trigName              (iConfig.getParameter<edm::InputTag>            ("trigNameLabel")),
l_trigBit               (iConfig.getParameter<edm::InputTag>            ("trigBitLabel")),
l_metFiltersName        (iConfig.getParameter<edm::InputTag>            ("metFiltersNameLabel")),
l_metFiltersBit         (iConfig.getParameter<edm::InputTag>            ("metFiltersBitLabel")),
l_lheEvtProd            (iConfig.getParameter<std::string>              ("lheProdName")),
l_genEvtInfoProd        (iConfig.getParameter<std::string>              ("genEvtInfoProdName")),
l_vtxRho                (iConfig.getParameter<edm::InputTag>            ("vtxRhoLabel")),
l_vtxZ                  (iConfig.getParameter<edm::InputTag>            ("vtxZLabel")),
l_vtxNdf                (iConfig.getParameter<edm::InputTag>            ("vtxNdfLabel")),
l_npv                   (iConfig.getParameter<edm::InputTag>            ("npvLabel")),
l_puNtrueInt            (iConfig.getParameter<edm::InputTag>            ("puNtrueIntLabel")),
hltMuPaths_             (iConfig.getParameter<std::vector<std::string>> ("hltMuPaths")),
hltElePaths_            (iConfig.getParameter<std::vector<std::string>> ("hltElePaths")),
metFilters_             (iConfig.getParameter<std::vector<std::string>> ("metFilters")),
isData_                 (iConfig.getParameter<bool>                     ("isData")),
doPUReweightingOfficial_(iConfig.getParameter<bool>                     ("DoPUReweightingOfficial")),
file_PVWt_              (iConfig.getParameter<std::string>              ("File_PVWt")),
file_PUDistData_        (iConfig.getParameter<std::string>              ("File_PUDistData")),
file_PUDistDataLow_     (iConfig.getParameter<std::string>              ("File_PUDistDataLow")),
file_PUDistDataHigh_    (iConfig.getParameter<std::string>              ("File_PUDistDataHigh")),
file_PUDistMC_          (iConfig.getParameter<std::string>              ("File_PUDistMC")),
hist_PVWt_              (iConfig.getParameter<std::string>              ("Hist_PVWt")),
hist_PUDistData_        (iConfig.getParameter<std::string>              ("Hist_PUDistData")),
hist_PUDistMC_          (iConfig.getParameter<std::string>              ("Hist_PUDistMC")),
cleanEvents_            (iConfig.getParameter<bool>                     ("cleanEvents")),
storeLHEWts_            (iConfig.getParameter<bool>                     ("storeLHEWts")),
topParams_              (iConfig.getParameter<edm::ParameterSet>        ("topParams")),
picktop                 (topParams_,consumesCollector()                               )
{
    
    consumes<unsigned int>            (l_runno         ) ;
    consumes<unsigned int>            (l_lumisec       ) ;
    consumes<ULong64_t>               (l_evtno         ) ;
  //  consumes<std::vector<std::string>>(l_trigName      ) ;
    consumes<std::vector<std::string>, edm::InRun>(l_trigName) ;
    consumes<std::vector<float>>      (l_trigBit       ) ;
 // consumes<std::vector<std::string>>(l_metFiltersName) ;
    consumes<std::vector<std::string>, edm::InRun>(l_metFiltersName) ;
    consumes<std::vector<float>>      (l_metFiltersBit ) ;
    consumes<std::vector<float>>      (l_vtxRho        ) ;
    consumes<std::vector<float>>      (l_vtxZ          ) ;
    consumes<std::vector<int>>        (l_vtxNdf        ) ;
    consumes<int>                     (l_npv           ) ;
    consumes<int>                     (l_puNtrueInt    ) ;
    
    if ( !isData_ ) {
    }
    
    if (doPUReweightingOfficial_) {
        LumiWeights_     = edm::LumiReWeighting(file_PUDistMC_, file_PUDistData_    , hist_PUDistMC_, hist_PUDistData_) ;
        LumiWeightsLow_  = edm::LumiReWeighting(file_PUDistMC_, file_PUDistDataLow_ , hist_PUDistMC_, hist_PUDistData_) ;
        LumiWeightsHigh_ = edm::LumiReWeighting(file_PUDistMC_, file_PUDistDataHigh_, hist_PUDistMC_, hist_PUDistData_) ;
    }
    t_genEvtInfoProd = consumes<GenEventInfoProduct>(l_genEvtInfoProd) ;
    if ( storeLHEWts_ ) {
        consumes<LHERunInfoProduct>({"externalLHEProducer"});
        t_lheEvtProd = consumes<LHEEventProduct>(l_lheEvtProd) ;
    }
    produces<int>("evtno");
    produces<int>("lumisec");
    produces<int>("runno");
    produces<bool>("isData");
    produces<bool>("hltdecisionEle");
    produces<bool>("hltdecisionMu");
    produces<std::string>("evttype");
    produces<double>("evtwtGen");
    produces<double>("evtwtPV");
    produces<double>("evtwtPVLow");
    produces<double>("evtwtPVHigh");
    produces<unsigned>("npv");
    produces<int>("npuTrue");
    produces<double>("htHat");
    produces<std::vector<int>>("lhewtids") ;
    produces<std::vector<double>>("lhewts") ;
    produces<double>("toppt");
    
}


EventCleaner::~EventCleaner() {}

bool EventCleaner::filter(edm::Event& evt, const edm::EventSetup& iSetup) {
    using namespace edm;
    using namespace std;
    
    typedef Handle <vector<string>> hstring ;
    typedef Handle <vector<float>> hfloat ;
    typedef Handle <vector<int>> hint ;
    
    Handle<unsigned int> h_runno    ; evt.getByLabel (l_runno                  , h_runno                );
    Handle<unsigned int> h_lumisec  ; evt.getByLabel (l_lumisec                , h_lumisec              );
    Handle<ULong64_t> h_evtno       ; evt.getByLabel (l_evtno                  , h_evtno                );
   // hstring h_trigName              ; evt.getByLabel (l_trigName               , h_trigName             );
    hfloat  h_trigBit               ; evt.getByLabel (l_trigBit                , h_trigBit              );
   // hstring h_metFiltersName        ; evt.getByLabel (l_metFiltersName         , h_metFiltersName       );
    hfloat  h_metFiltersBit         ; evt.getByLabel (l_metFiltersBit          , h_metFiltersBit        );
    hfloat  h_vtxRho                ; evt.getByLabel (l_vtxRho                 , h_vtxRho               );
    hfloat  h_vtxZ                  ; evt.getByLabel (l_vtxZ                   , h_vtxZ                 );
    hint    h_vtxNdf                ; evt.getByLabel (l_vtxNdf                 , h_vtxNdf               );
    Handle<int>   h_npv             ; evt.getByLabel (l_npv                    , h_npv                  );
    Handle<int>   h_puNtrueInt      ; evt.getByLabel (l_puNtrueInt             , h_puNtrueInt           );
    
    const int runno  ( (2*isData_ - 1) * (*h_runno) )   ; //// If MC, -ve sign for runno
    const int lumisec( (2*isData_ - 1) * (*h_lumisec) ) ; //// If MC, -ve sign for lumisec
    const int evtno  ( (2*isData_ - 1) * (*h_evtno) )   ; //// If MC, -ve sign for evtno
    
    
    // Separate muon and electron hlt triggers
    
    // muon trigger
    unsigned int hltdecisions(0) ;
    for ( const string& myhltpath : hltMuPaths_ ) {
        vector<string>::const_iterator it ;
        for (it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it ) {
            if ( it->find(myhltpath) < std::string::npos) {
               // hltdecisions |= int((h_trigBit.product())->at( it - (h_trigName.product())->begin() )) << ( it - (h_trigName.product())->begin() ) ;
                hltdecisions = (h_trigBit.product())->at( it - (h_trigName.product())->begin() ) ;
            }
        }
    }
    bool hltdecisionMu(false);
    if ( hltMuPaths_.size() > 0 && !hltdecisions) hltdecisionMu=false;
    else hltdecisionMu=true;
    
    // electron trigger
    hltdecisions = 0 ;
    for ( const string& myhltpath : hltElePaths_ ) {
        vector<string>::const_iterator it ;
        for (it = (h_trigName.product())->begin(); it != (h_trigName.product())->end(); ++it ) {
            if ( it->find(myhltpath) < std::string::npos) {
              //  hltdecisions |= int((h_trigBit.product())->at( it - (h_trigName.product())->begin() )) << ( it - (h_trigName.product())->begin() ) ;
                hltdecisions = (h_trigBit.product())->at( it - (h_trigName.product())->begin() ) ;
            }
        }
    }
    
    
    bool hltdecisionEle(false);
    if ( hltElePaths_.size() > 0 && !hltdecisions) hltdecisionEle=false;
    else hltdecisionEle=true;
    
    
    
    if ( isData_ ) {
        bool metfilterdecision(1) ;
        for ( const string& metfilter : metFilters_ ) {
            vector<string>::const_iterator it ;
            for (it = (h_metFiltersName.product())->begin(); it != (h_metFiltersName.product())->end(); ++it) {
                if ( it->find(metfilter) < std::string::npos) {
                    metfilterdecision *= (h_metFiltersBit.product())->at( it - (h_metFiltersName.product())->begin() ) ;
                }
            }
        }
        if ( !metfilterdecision ) return false ;
    }
    
    int npv(*h_npv);
    
    for ( unsigned ipv = 0; ipv < (h_vtxRho.product())->size(); ++ipv) {
      double vtxRho     = (h_vtxRho.product())->at(ipv) ;
      double vtxZ       = (h_vtxZ.product())->at(ipv) ;
      double vtxNdf     = (h_vtxNdf.product())->at(ipv) ;
      if ( abs(vtxRho) < 2. && abs(vtxZ) <= 24. && vtxNdf > 4 ) ++npv ;
    }
    
    if ( npv < 1 ) return false;
    
    double evtwtGen(1.0) ;
    double htHat(0.0);
    std::vector<int> lhewtids;
    std::vector<double> lhewts;
    if ( !isData_ && storeLHEWts_ ) {
        //Handle<GenEventInfoProduct> h_genEvtInfoProd;
        //evt.getByToken(t_genEvtInfoProd, h_genEvtInfoProd);
        //evtwtGen = h_genEvtInfoProd->weight() ;
        //evtwtGen /= abs(evtwtGen) ;
        //if (h_genEvtInfoProd->binningValues().size()>0) htHat = h_genEvtInfoProd->binningValues()[0];
        
        Handle<LHEEventProduct> h_lheEvtProd;
        evt.getByToken(t_lheEvtProd, h_lheEvtProd);
        double nominal_wt = h_lheEvtProd->weights()[0].wgt ; // h_lheEvtProd->hepeup().XWGTUP ; //h_lheEvtProd->originalXWGTUP();
        lhewtids.reserve(h_lheEvtProd->weights().size()) ;
        lhewts.reserve(h_lheEvtProd->weights().size()) ;
        for (unsigned iwt = 0; iwt < h_lheEvtProd->weights().size(); ++iwt) {
            lhewtids.push_back(std::stoi(h_lheEvtProd->weights()[iwt].id)) ;
            lhewts.push_back(h_lheEvtProd->weights()[iwt].wgt / nominal_wt) ;
        }
        
        std::vector<lhef::HEPEUP::FiveVector> lheParticles = h_lheEvtProd->hepeup().PUP;
        for(size_t idxPart = 0; idxPart < lheParticles.size();++idxPart){
            unsigned absPdgId = TMath::Abs(h_lheEvtProd->hepeup().IDUP[idxPart]);
            unsigned status = h_lheEvtProd->hepeup().ISTUP[idxPart];
            if(status==1 &&((absPdgId >=1 &&absPdgId<=6) || absPdgId == 21)){
                htHat += sqrt(pow(lheParticles[idxPart][0],2.) + pow(lheParticles[idxPart][1],2.));
            }
        }
        
    }
    else {
        lhewtids.push_back(-999999);
        lhewts.push_back(-999999) ;
    }
    
    int npuTrue(-1);
    double evtwtPV(1.0) ;
    double evtwtPVLow(1.0) ;
    double evtwtPVHigh(1.0) ;
    double topPtWeight = 1.0;
    if ( !isData_ ) {
        npuTrue = *h_puNtrueInt ;
        if ( doPUReweightingOfficial_ ) {
            evtwtPV *= LumiWeights_.weight(npuTrue) ;
            evtwtPVLow *= LumiWeightsLow_.weight(npuTrue) ;
            evtwtPVHigh *= LumiWeightsHigh_.weight(npuTrue) ;
        }
        
        vlq::GenParticleCollection top = picktop(evt) ;
        
        GenParticleCollection genPartsInfo;
        genPartsInfo = picktop(evt) ;

        // apply top pt reweighting
        
        std::vector<TLorentzVector> tops;
        for (auto& gen : genPartsInfo){
            if (abs(gen.getPdgID()) == 6 && abs(gen.getStatus()) == 22 ){
                tops.push_back( gen.getP4() );
            }
        }
        
        
        if(tops.size() == 2){
            
            double pt1 = tops[0].Pt();
            double pt2 = tops[1].Pt();
            topPtWeight = TMath::Sqrt(TMath::Exp(0.0615 - 0.0005 * pt1) * TMath::Exp(0.0615 - 0.0005 * pt2));
        }
    }
    
    

    
    
    
    string evttype(isData_ ? "EvtType_Data" : "EvtType_MC");
    

    auto_ptr<int>ptr_evtno(new int(evtno));
    auto_ptr<int>ptr_lumisec(new int(lumisec));
    auto_ptr<int>ptr_runno(new int(runno));
    auto_ptr<bool>ptr_isData(new bool(isData_));
    auto_ptr<bool>ptr_hltdecision_ele(new bool(hltdecisionEle));
    auto_ptr<bool>ptr_hltdecision_mu(new bool(hltdecisionMu));
    auto_ptr<string>ptr_evttype(new string(evttype));
    auto_ptr<double>ptr_evtwtGen(new double(evtwtGen));
    auto_ptr<double>ptr_evtwtPV(new double(evtwtPV));
    auto_ptr<double>ptr_evtwtPVLow(new double(evtwtPVLow));
    auto_ptr<double>ptr_evtwtPVHigh(new double(evtwtPVHigh));
    auto_ptr<unsigned>ptr_npv(new unsigned(npv));
    auto_ptr<int>ptr_npuTrue(new int(npuTrue));
    auto_ptr<double>ptr_htHat(new double(htHat));
    auto_ptr<std::vector<int>> ptr_lhewtids(new std::vector<int>(lhewtids));
    auto_ptr<std::vector<double>> ptr_lhewts(new std::vector<double>(lhewts));
    auto_ptr<double>ptr_toppt(new double(topPtWeight));
    
    evt.put(ptr_evtno,      "evtno");
    evt.put(ptr_lumisec,    "lumisec");
    evt.put(ptr_runno,      "runno");
    evt.put(ptr_isData,     "isData");
    evt.put(ptr_hltdecision_ele,"hltdecisionEle");
    evt.put(ptr_hltdecision_mu,"hltdecisionMu");
    evt.put(ptr_evttype,    "evttype");
    evt.put(ptr_evtwtGen,   "evtwtGen");
    evt.put(ptr_evtwtPV,    "evtwtPV");
    evt.put(ptr_evtwtPVLow, "evtwtPVLow");
    evt.put(ptr_evtwtPVHigh,"evtwtPVHigh");
    evt.put(ptr_npv,        "npv");
    evt.put(ptr_npuTrue,    "npuTrue");
    evt.put(ptr_htHat,      "htHat");
    evt.put(ptr_lhewtids,   "lhewtids") ;
    evt.put(ptr_lhewts,     "lhewts") ;
    evt.put(ptr_toppt,      "toppt") ;
    
    return true ;
    
}


void EventCleaner::beginJob() {
}

void EventCleaner::endJob() {

}

void EventCleaner::beginRun(edm::Run const& run, edm::EventSetup const& es) {
    
    run.getByLabel (l_trigName               , h_trigName             );
    run.getByLabel (l_metFiltersName         , h_metFiltersName       );
}


void EventCleaner::endRun(edm::Run const& run, edm::EventSetup const& es) {
    
}

double EventCleaner::GetLumiWeightsPVBased (const std::string file, const std::string hist, const unsigned npv) { 
    double wtPU(1) ;
    TFile f(file.c_str()) ;
    TH1D* hwt = dynamic_cast<TH1D*>( f.Get( hist.c_str() ) ) ; 
    wtPU = npv > 0 && npv <= 60 ? hwt->GetBinContent(npv) : 1.; 
    delete hwt ; 
    f.Close() ; 
    return wtPU ;
}

DEFINE_FWK_MODULE(EventCleaner);
