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

using namespace std;
using namespace edm;

class HLTSelector {
    
public:
    
    HLTSelector (edm::ParameterSet const& pars, edm::Event& evt);
    ~HLTSelector();
    bool isGoodHLTPath(const std::vector<std::string> hltNames) const;
    
private:
    
    edm::InputTag trigName_    ;
    edm::InputTag trigBit_     ;
    
    Handle <vector<string>> trigName ;
    Handle <vector<float>> trigBit ;
    
    
    
};

#endif