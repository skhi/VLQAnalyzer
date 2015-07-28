#ifndef METSELECTOR_H
#define METSELECTOR_H

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


class METSelector {
    
public:
        
    METSelector (edm::ParameterSet const& pars, edm::Event& evt);
    ~METSelector();
    
    
    
    // methods declaration
    
    double pt() const;
    double phi() const;
    double px() const;
    double py() const;
    TLorentzVector p4() const;
    
    
private:
        
    edm::InputTag metPhi_    ;
    edm::InputTag metPt_     ;
    edm::InputTag metPx_     ;
    edm::InputTag metPy_     ;
    
    
    typedef Handle<vector<float>>  hfloat;
                          
    hfloat metPhi             ;
    hfloat metPt              ;
    hfloat metPx              ;
    hfloat metPy              ;

    
    
};

#endif