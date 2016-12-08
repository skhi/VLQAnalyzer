import FWCore.ParameterSet.Config as cms

defaultHLTParameters = cms.PSet(
                                trigNameLabel              = cms.InputTag("TriggerUserData", "triggerNameTree"),
                                trigBitLabel               = cms.InputTag("TriggerUserData", "triggerBitTree"),
                                eventFiltersNameLabel      = cms.InputTag("METUserData", "triggerNameTree"),
                                eventFiltersBitLabel       = cms.InputTag("METUserData", "triggerBitTree"),
                                )

