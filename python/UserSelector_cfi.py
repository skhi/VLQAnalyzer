
import FWCore.ParameterSet.Config as cms

myGoogSelectionParameters = cms.PSet(
                                     lepMinPt           = cms.double(40),
                                     lepMaxPt           = cms.double(9999),
                                     lepMinEta          = cms.double(0),
                                     lepMaxEta          = cms.double(2.1),
                                     minMet             = cms.double(50),
                                     maxMet             = cms.double(9999),
                                     wMinMass           = cms.double(0),
                                     wMaxMass           = cms.double(130),
                                     JetMinPt           = cms.double(200),
                                     JetMaxPt           = cms.double(9999),
                                     JetMinEta          = cms.double(0),
                                     JetMaxEta          = cms.double(2.5),
                                     JetLepMinDPhi      = cms.double(2.0),
                                     JetLepMaxDPhi      = cms.double(10),
                                     fwdMinPt           = cms.double(30),
                                     fwdMaxPt           = cms.double(9999),
                                     fwdMinEta          = cms.double(2.4),
                                     fwdMaxEta          = cms.double(5),
                                     minSt              = cms.double(500),
                                     maxSt              = cms.double(9999),
                                     )

