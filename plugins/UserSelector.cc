// header include file
#include "Analysis/VLQAnalyzer/interface/UserSelector.h"
#include <iostream>

using namespace std;
using namespace edm;


UserSelector::UserSelector (edm::ParameterSet const& pars):

lepMinPt_           (pars.getParameter<double>("lepMinPt")),
lepMaxPt_           (pars.getParameter<double>("lepMaxPt")),
lepMinEta_          (pars.getParameter<double>("lepMinEta")),
lepMaxEta_          (pars.getParameter<double>("lepMaxEta")),
minMet_             (pars.getParameter<double>("minMet")),
maxMet_             (pars.getParameter<double>("maxMet")),
wMinMass_           (pars.getParameter<double>("wMinMass")),
wMaxMass_           (pars.getParameter<double>("wMaxMass")),
JetMinPt_           (pars.getParameter<double>("JetMinPt")),
JetMaxPt_           (pars.getParameter<double>("JetMaxPt")),
JetMinEta_          (pars.getParameter<double>("JetMinEta")),
JetMaxEta_          (pars.getParameter<double>("JetMaxEta")),
JetLepMinDPhi_      (pars.getParameter<double>("JetLepMinDPhi")),
JetLepMaxDPhi_      (pars.getParameter<double>("JetLepMaxDPhi")),
fwdMinPt_           (pars.getParameter<double>("fwdMinPt")),
fwdMaxPt_           (pars.getParameter<double>("fwdMaxPt")),
fwdMinEta_          (pars.getParameter<double>("fwdMinEta")),
fwdMaxEta_          (pars.getParameter<double>("fwdMaxEta")),
minSt_              (pars.getParameter<double>("minSt")),
maxSt_              (pars.getParameter<double>("maxSt"))
{
    
}

UserSelector::~UserSelector(){
    
}


void UserSelector::setLepP4(const TLorentzVector & lepP4){
    
    if(lepP4.Pt() < 1){
         edm::LogError("UserSelector::setLepTLVec") << " >>>> TLorentzVector is empty " ;
    }
    lepP4_ = lepP4;
}

void UserSelector::setMETP4(const TLorentzVector & metP4){
    
    if(metP4.Pt() < 1){
        edm::LogError("UserSelector::setMETTLVec") << " >>>> TLorentzVector is empty " ;
    }
    
    metP4_ = metP4;
}

void UserSelector::setJetP4(const TLorentzVector & jetP4){
    
    if(jetP4.Pt() < 1){
        edm::LogError("UserSelector::setJetTLVec") << " >>>> TLorentzVector is empty " ;
    }
    
    jetP4_ = jetP4;
}

void UserSelector::setFwdJetP4(const TLorentzVector & fwdP4){
    
    if(fwdP4.Pt() < 1){
        edm::LogError("UserSelector::setFwdJetTLVec") << " >>>> TLorentzVector is empty " ;
    }
    
    fwdP4_ = fwdP4;
}


double UserSelector::getSt() const{
    
    return (lepP4_.Pt() + metP4_.Pt() + jetP4_.Pt());
}

double UserSelector::getMass() const{
    
    return ((lepP4_ + metP4_ + jetP4_).M());
}

double UserSelector::getWMass() const{
    
    return (TMath::Sqrt( 2*lepP4_.Pt() * metP4_.Pt() * ( 1 - TMath::Cos(lepP4_.DeltaPhi(metP4_) ) ) ));
}

double UserSelector::getLJDPhi() const{
    
    return (jetP4_.DeltaPhi(lepP4_));
}


double UserSelector::getLJDR() const{
    
    return (jetP4_.DeltaR(lepP4_));
}

int UserSelector::getCutflow() const{
    
    
    double mt   = TMath::Sqrt( 2*lepP4_.Pt() * metP4_.Pt() * ( 1 - TMath::Cos(lepP4_.DeltaPhi(metP4_) ) ) );
    double dphi = fabs(jetP4_.DeltaPhi(lepP4_));
    double st   = (lepP4_.Pt() + metP4_.Pt() + jetP4_.Pt());
    
    double lepPt        = lepP4_.Pt();
    double lepEta       = fabs(lepP4_.Eta());
    double jetPt        = jetP4_.Pt();
    double jetEta       = fabs(jetP4_.Eta());
    double fwdPt        = fwdP4_.Pt();
    double fwdEta       = fabs(fwdP4_.Eta());
    double met          = metP4_.Pt();
    
    if(!(lepPt      > lepMinPt_          &&      lepPt      < lepMaxPt_         ))  return 0;
    if(!(lepEta     > lepMinEta_         &&      lepEta     < lepMaxEta_        ))  return 1;
    if(!(met        > minMet_            &&      met        < maxMet_           ))  return 2;
    if(!(mt         > wMinMass_          &&      mt         < wMaxMass_         ))  return 3;
    if(!(jetPt      > JetMinPt_          &&      jetPt      < JetMaxPt_         ))  return 4;
    if(!(jetEta     > JetMinEta_         &&      jetEta     < JetMaxEta_        ))  return 5;
    if(!(dphi       > JetLepMinDPhi_     &&      dphi       < JetLepMaxDPhi_    ))  return 6;
    if(!(fwdPt      > fwdMinPt_          &&      fwdPt      < fwdMaxPt_         ))  return 7;
    if(!(fwdEta     > fwdMinEta_         &&      fwdEta     < fwdMaxEta_        ))  return 8;
    if(!(st         > minSt_             &&      st         < maxSt_            ))  return 9;
    
    return 10;
    
}




bool UserSelector::isValidSelection() const{
    
    
    double mt   = TMath::Sqrt( 2*lepP4_.Pt() * metP4_.Pt() * ( 1 - TMath::Cos(lepP4_.DeltaPhi(metP4_) ) ) );
    double dphi = fabs(jetP4_.DeltaPhi(lepP4_));
    double st   = (lepP4_.Pt() + metP4_.Pt() + jetP4_.Pt());
    
    double lepPt        = lepP4_.Pt();
    double lepEta       = fabs(lepP4_.Eta());
    double jetPt        = jetP4_.Pt();
    double jetEta       = fabs(jetP4_.Eta());
    double fwdPt        = fwdP4_.Pt();
    double fwdEta       = fabs(fwdP4_.Eta());
    double met          = metP4_.Pt();
    
    
    if(!(lepPt      > lepMinPt_          &&      lepPt      < lepMaxPt_         ))  return false;
    if(!(lepEta     > lepMinEta_         &&      lepEta     < lepMaxEta_        ))  return false;
    if(!(met        > minMet_            &&      met        < maxMet_           ))  return false;
    if(!(mt         > wMinMass_          &&      mt         < wMaxMass_         ))  return false;
    if(!(jetPt      > JetMinPt_          &&      jetPt      < JetMaxPt_         ))  return false;
    if(!(jetEta     > JetMinEta_         &&      jetEta     < JetMaxEta_        ))  return false;
    if(!(dphi       > JetLepMinDPhi_     &&      dphi       < JetLepMaxDPhi_    ))  return false;
    if(!(fwdPt      > fwdMinPt_          &&      fwdPt      < fwdMaxPt_         ))  return false;
    if(!(fwdEta     > fwdMinEta_         &&      fwdEta     < fwdMaxEta_        ))  return false;
    if(!(st         > minSt_             &&      st         < maxSt_            ))  return false;
    
    return true;
}




