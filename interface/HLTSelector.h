#ifndef HLTSELECTOR_H
#define HLTSELECTOR_H

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

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


using namespace std;
using namespace edm;

class HLTSelector {
    
public:
    
    HLTSelector (edm::ParameterSet const& pars, edm::ConsumesCollector && iC);
    ~HLTSelector();
    bool isGoodHLTPath(const std::vector<std::string> hltNames) const;
    bool isGoodFilter(const std::vector<std::string> filterNames) const;
    void setEvent(edm::Event& evt);
    
private:
    
    edm::EDGetTokenT<std::vector<string>> trigName_    ;
    edm::EDGetTokenT<std::vector<float>> trigBit_     ;
    edm::EDGetTokenT<std::vector<string>> eventFiltersName_   ;
    edm::EDGetTokenT<std::vector<float>> eventFiltersBit_    ;
    
    Handle <vector<string>> trigName ;
    Handle <vector<float>> trigBit ;
    Handle <vector<string>> eventFiltersName   ;
    Handle <vector<float>> eventFiltersBit    ;
    
    
    
};

#endif