import FWCore.ParameterSet.Config as cms

defaultMETParameters = cms.PSet(
                                   metPhiLabel           = cms.InputTag("met", "metPhi"),
                                   metPtLabel            = cms.InputTag("met", "metPt"),
                                   metPxLabel            = cms.InputTag("met", "metPx"),
                                   metPyLabel            = cms.InputTag("met", "metPy"),
                                   )