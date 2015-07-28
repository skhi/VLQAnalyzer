import FWCore.ParameterSet.Config as cms

from Analysis.VLQAnalyzer.AK8Jet_cfi import *

defaultAK8JetSelectionParameters = cms.PSet(
                                            defaultAK8JetParameters,
                                            jetMinPt            = cms.double(200),
                                            jetMaxEta           = cms.double(2.5),
                                            jetIDType           = cms.string('LOOSE'),
                                            )