// header include file
#include "Analysis/VLQAnalyzer/interface/METSelector.h"

using namespace std;
using namespace edm;


METSelector::METSelector (edm::ParameterSet const& pars, edm::Event& evt):

metPhi_            (pars.getParameter<edm::InputTag>("metPhiLabel")),
metPt_             (pars.getParameter<edm::InputTag>("metPtLabel")),
metPx_             (pars.getParameter<edm::InputTag>("metPxLabel")),
metPy_             (pars.getParameter<edm::InputTag>("metPyLabel"))
{
    evt.getByLabel(metPhi_  ,          metPhi         );
    evt.getByLabel(metPt_ ,            metPt          );
    evt.getByLabel(metPx_ ,            metPx          );
    evt.getByLabel(metPy_,             metPy          );
    
}

METSelector::~METSelector(){
    
}



// methods declaration

double METSelector::pt() const{ return ((metPt.product())->at(0)); }
double METSelector::phi() const{ return ((metPhi.product())->at(0)); }
double METSelector::px() const{ return ((metPx.product())->at(0)); }
double METSelector::py() const{ return ((metPy.product())->at(0)); }

TLorentzVector METSelector::p4() const{
    TLorentzVector p4;
    p4.SetPtEtaPhiM( (metPt.product())->at(0), 0, (metPhi.product())->at(0), 0 );
    return  p4;
}