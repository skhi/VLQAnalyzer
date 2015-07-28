import FWCore.ParameterSet.Config as cms

from Analysis.VLQAnalyzer.MET_cfi import *

defaultMETSelectionParameters = cms.PSet(
                                defaultMETParameters,
                                mettype = cms.string(""),
                                metPtMin = cms.double(0),
                                )