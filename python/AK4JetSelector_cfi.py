import FWCore.ParameterSet.Config as cms


from Analysis.VLQAnalyzer.AK4Jet_cfi import *


defaultAK4JetSelectionParameters = cms.PSet(
					    defaultAK4JetParameters,
                                            jetMinPt            = cms.double(30),
                                            jetMaxEta           = cms.double(5.0),
                                            jetCSVCut           = cms.double(0.843),
                                            jetIDType           = cms.string('LOOSE'),
                                            )
