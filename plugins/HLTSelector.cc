// header include file
#include "Analysis/VLQAna/interface/HLTSelector.h"
#include <iostream>

using namespace std;
using namespace edm;


HLTSelector::HLTSelector (edm::ParameterSet const& pars, edm::ConsumesCollector && iC):
trigName_          ( iC.consumes<vector<string>>(pars.getParameter<edm::InputTag>("trigNameLabel")) ),
trigBit_           ( iC.consumes<vector<float>>(pars.getParameter<edm::InputTag>("trigBitLabel")) ),
eventFiltersName_  ( iC.consumes<vector<string>>(pars.getParameter<edm::InputTag>("eventFiltersNameLabel")) ),
eventFiltersBit_   ( iC.consumes<vector<float>>(pars.getParameter<edm::InputTag>("eventFiltersBitLabel")) )
{ 
cout<<"HLT constructor"<<endl;
}



HLTSelector::~HLTSelector(){}


void HLTSelector::setEvent(edm::Event& evt){
    
    evt.getByToken (trigName_      , trigName   );
    evt.getByToken (trigBit_       , trigBit    );
    evt.getByToken (eventFiltersName_      , eventFiltersName    );
    evt.getByToken (eventFiltersBit_       , eventFiltersBit    );
}


bool HLTSelector::isGoodHLTPath(const std::vector<std::string> hltNames) const{
    
    if(hltNames.size() == 0) return true;
    
    
    unsigned int hltDecision(0);
    for ( const string& myHltPath : hltNames ) {
        vector<string>::const_iterator it ;
        if(hltDecision) break;
        for (it = (trigName.product())->begin(); it != (trigName.product())->end(); ++it ) {
            std::size_t found = it->find(myHltPath);
            if ( found!=std::string::npos ) {
                std::string name = (trigName.product()) -> at(it - (trigName.product())->begin()) ;                
                hltDecision = int((trigBit.product())->at(it - (trigName.product())->begin())) ;
                if(hltDecision) break;
            }
        }
    }
    
    if (hltDecision == 0)
        return false ;
    else
        return true;
}

bool HLTSelector::isGoodFilter(const std::vector<std::string> filterNames) const{
    
    if(filterNames.size() == 0) return true;
    
    
    unsigned int filterDecision(1);
    for ( const string& myFilterPath : filterNames ) {
        vector<string>::const_iterator it ;
        if(!filterDecision) break;
        for (it = (eventFiltersName.product())->begin(); it != (eventFiltersName.product())->end(); ++it ) {
            std::size_t found = it->find(myFilterPath);
            if ( found!=std::string::npos ) {
                std::string name = (eventFiltersName.product()) -> at(it - (eventFiltersName.product())->begin()) ;
                filterDecision = int((eventFiltersBit.product())->at(it - (eventFiltersName.product())->begin())) ;
                if(!filterDecision) break;
            }
        }
    }
    
    if (filterDecision == 0)
        return false ;
    else
        return true;
}



