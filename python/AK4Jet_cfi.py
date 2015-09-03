import FWCore.ParameterSet.Config as cms

defaultAK4JetParameters = cms.PSet(
                                   jetPtLabel              = cms.InputTag("jetsAK4", "jetAK4Pt"),
                                   jetEtaLabel             = cms.InputTag("jetsAK4", "jetAK4Eta"),
                                   jetPhiLabel             = cms.InputTag("jetsAK4", "jetAK4Phi"),
                                   jetMassLabel            = cms.InputTag("jetsAK4", "jetAK4Mass"),
                                   jetEnergyLabel          = cms.InputTag("jetsAK4", "jetAK4E"),
                                   jetFlavourLabel         = cms.InputTag("jetsAK4", "jetAK4Flavour"),
                                   jetCSVLabel             = cms.InputTag("jetsAK4", "jetAK4CSV"),
                                   jetJECLabel             = cms.InputTag("jetsAK4", "jetAK4jecFactor0"),
                                   jetnHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4neutralHadronEnergy"),
                                   jetnEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4neutralEmEnergy"),
                                   jetnMultipLabel         = cms.InputTag("jetsAK4", "jetAK4neutralMultiplicity"),
                                   jetHFHadronEnergyLabel  = cms.InputTag("jetsAK4", "jetAK4HFHadronEnergy"),
                                   jetcHadEnergyLabel      = cms.InputTag("jetsAK4", "jetAK4chargedHadronEnergy"),
                                   jetcEMEnergyLabel       = cms.InputTag("jetsAK4", "jetAK4chargedEmEnergy"),
                                   jetnumDaughtersLabel    = cms.InputTag("jetsAK4", "jetAK4numberOfDaughters"),
                                   jetcMultipLabel         = cms.InputTag("jetsAK4", "jetAK4chargedMultiplicity"),
                                   jetYLabel               = cms.InputTag("jetsAK4", "jetAK4Y"),
                                   jetAreaLabel            = cms.InputTag("jetsAK4", "jetAK4jetArea"),
                                   )