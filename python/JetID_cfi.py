import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.Jet_cfi import * 

defaultAK4JetIDParameters = cms.PSet(
    defaultAK4JetParameters, 
    quality                    = cms.string  ("LOOSE"),
    )

defaultAK8JetIDParameters = cms.PSet(
    defaultAK8JetParameters, 
    quality                    = cms.string  ("LOOSE"),
    )
