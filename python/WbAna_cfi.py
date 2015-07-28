import FWCore.ParameterSet.Config as cms

from Analysis.VLQAnalyzer.ElectronSelector_cfi import *
from Analysis.VLQAnalyzer.MuonSelector_cfi import *
#from PickGenPart_cfi import *
from Analysis.VLQAnalyzer.AK4JetSelector_cfi import *
from Analysis.VLQAnalyzer.AK8JetSelector_cfi import *
from Analysis.VLQAnalyzer.METSelector_cfi import *
from Analysis.VLQAnalyzer.HLTSelector_cfi import *
from Analysis.VLQAnalyzer.UserSelector_cfi import *

ana = cms.EDFilter("WbAna",
                   processName                = cms.string  ('@'),
                   hltPaths                   = cms.vstring (
                                                             "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL",
                                                             "HLT_Ele27_eta2p1_WP85_Gsf",
                                                             "HLT_PFHT650",
                                                             "HLT_PFHT900",
                                                             ),
                   tightMuParams = tightMuonSelectionParameters.clone(),
                   looseMuParams = looseMuonSelectionParameters.clone(),
                   tightElParams = tightElectronSelectionParameters.clone(),
                   looseElParams = looseElectronSelectionParameters.clone(),

                   selectionParams = myGoogSelectionParameters.clone(),
                   hltParams = defaultHLTSelectionParameters.clone(),
                   
                   ak4JetParams = defaultAK4JetSelectionParameters.clone(),
                   ak8JetParams = defaultAK8JetSelectionParameters.clone(),
                   metParams = defaultMETSelectionParameters.clone(),
                   )

