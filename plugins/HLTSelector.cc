// header include file
#include "Analysis/VLQAnalyzer/interface/HLTSelector.h"

using namespace std;
using namespace edm;


HLTSelector::HLTSelector (edm::ParameterSet const& pars, edm::Event& evt):

trigName_          (pars.getParameter<edm::InputTag>("trigNameLabel")),
trigBit_           (pars.getParameter<edm::InputTag>("trigBitLabel"))

{
    evt.getByLabel (trigName_      , trigName   );
    evt.getByLabel (trigBit_       , trigBit    );
    
    
    
}

HLTSelector::~HLTSelector(){
    
}



bool HLTSelector::isGoodHLTPath(const std::vector<std::string> hltNames) const{
    
    unsigned int hltDecision(0);
    for ( const string& myHltPath : hltNames ) {
        vector<string>::const_iterator it ;
        for (it = (trigName.product())->begin(); it != (trigName.product())->end(); ++it ) {
            std::size_t found = it->find(myHltPath);
            if ( found!=std::string::npos ) {
                std::string name = (trigName.product()) -> at (it - (trigName.product())->begin()) ;
                hltDecision = int((trigBit.product())->at(it - (trigName.product())->begin())) ;
            }
        }
    }
    
    if (hltDecision == 0)
        return false ;
    else
        return true;
}
