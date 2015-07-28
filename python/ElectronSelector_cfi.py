import FWCore.ParameterSet.Config as cms

from Analysis.VLQAnalyzer.Electron_cfi import *

tightElectronSelectionParameters = cms.PSet(
                                            defaultElectronParameters,
                                            elMinPt = cms.double(10),
                                            elMaxEta = cms.double(2.4),
                                            elIDType = cms.string("TIGHT"),
                                            )

looseElectronSelectionParameters = cms.PSet(
                                            defaultElectronParameters,
                                            elMinPt = cms.double(10),
                                            elMaxEta = cms.double(2.4),
                                            elIDType = cms.string("LOOSE"),
                                            )