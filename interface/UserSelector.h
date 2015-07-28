#ifndef USERSELECTOR_H
#define USERSELECTOR_H

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


class UserSelector {
    
public:
        
    UserSelector (edm::ParameterSet const& pars);
    ~UserSelector();
    
    // methods declaration
    
    bool isValidSelection() const;
    void setLepP4(const TLorentzVector & lep);
    void setMETP4(const TLorentzVector & met);
    void setJetP4(const TLorentzVector & jet);
    void setFwdJetP4(const TLorentzVector & fwd);
    double getSt() const;
    double getMass() const;
    double getWMass() const;
    double getLJDPhi() const;
    double getLJDR() const ;
    int getCutflow() const;
    
    
    
    

private:
        
    edm::ParameterSet selectionParams_ ;

    double lepMinPt_                ;
    double lepMaxPt_                ;
    double lepMinEta_               ;
    double lepMaxEta_               ;
    double minMet_                  ;
    double maxMet_                  ;
    double wMinMass_                ;
    double wMaxMass_                ;
    double JetMinPt_                ;
    double JetMaxPt_                ;
    double JetMinEta_               ;
    double JetMaxEta_               ;
    double JetLepMinDPhi_           ;
    double JetLepMaxDPhi_           ;
    double fwdMinPt_                ;
    double fwdMaxPt_                ;
    double fwdMinEta_               ;
    double fwdMaxEta_               ;
    double minSt_                   ;
    double maxSt_                   ;

    TLorentzVector lepP4_           ;
    TLorentzVector metP4_           ;
    TLorentzVector jetP4_           ;
    TLorentzVector fwdP4_           ;
};

#endif