
import FWCore.ParameterSet.Config as cms

from Analysis.VLQAnalyzer.Muon_cfi import *

tightMuonSelectionParameters = cms.PSet(
                                        defaultMuonParameters,
                                        muMinPt = cms.double(10),
                                        muMaxEta = cms.double(2.4),
                                        muMaxIso = cms.double(0.12),
                                        muIDType = cms.string("TIGHT"),
                                        )


looseMuonSelectionParameters = cms.PSet(
                                        defaultMuonParameters,
                                        muMinPt = cms.double(10),
                                        muMaxEta = cms.double(2.4),
                                        muMaxIso = cms.double(0.2),
                                        muIDType = cms.string("LOOSE"),
                                        )

