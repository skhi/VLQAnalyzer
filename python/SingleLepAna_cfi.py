import FWCore.ParameterSet.Config as cms

from Analysis.VLQAna.ZCandSelector_cfi import *
from Analysis.VLQAna.ApplyLeptonSFs_cfi import *
from Analysis.VLQAna.ElectronMaker_cfi import *
from Analysis.VLQAna.MuonMaker_cfi import *
from Analysis.VLQAna.PickGenPart_cfi import *
from Analysis.VLQAna.JetSelector_cfi import *
from Analysis.VLQAna.METMaker_cfi import *
from Analysis.VLQAna.HLT_cfi import *
from Analysis.VLQAna.Selection_cfi import *

ana = cms.EDFilter("SingleLepAna",
                   
    signalSelection            = signalSelectionParameters.clone(),
    wjetSelection              = wjetSelectionParameters.clone(),
    ttbarSelection             = ttbarSelectionParameters.clone(),
    hltdecisionEle             = cms.InputTag("evtcleaner", "hltdecisionEle"),
    hltdecisionMu              = cms.InputTag("evtcleaner", "hltdecisionMu"),
    evttype                    = cms.InputTag("evtcleaner", "evttype"),
    evtwtGen                   = cms.InputTag("evtcleaner", "evtwtGen"),
    evtwtPV                    = cms.InputTag("evtcleaner", "evtwtPV"),
    evtwtPVLow                 = cms.InputTag("evtcleaner", "evtwtPVLow"),
    evtwtPVHigh                = cms.InputTag("evtcleaner", "evtwtPVHigh"),
    npv                        = cms.InputTag("evtcleaner", "npv"),
    toppt                      = cms.InputTag("evtcleaner", "toppt"),
    btagsf_bcUp                =cms.bool(False),
    btagsf_bcDown              =cms.bool(False),
    btagsf_lUp                 =cms.bool(False),
    btagsf_lDown               =cms.bool(False),
    PileupUp                   =cms.bool(False),
    PileupDown                 =cms.bool(False),
    jecShift 		       = cms.double(0.),
    jerShift 		       = cms.double(1.),
    additionalPlots            = cms.bool(False),
    optimizeReco               = cms.bool(False),
    vlqMass                    = cms.double(1000.),
    bosMass                    = cms.double(91.2),
    applyLeptonSFs             = cms.bool(False),
    applyBTagSFs               = cms.bool(False),
    applyTopPtCorr             = cms.bool(False),
    fnamebtagSF                = cms.string('CSVv2_ichep.csv'),
    applyDYNLOCorr             = cms.bool(False),  
    File_DYNLOCorr             = cms.string('scalefactors_v4.root'),
    Fun_DYNLOCorr              = cms.string('z_ewkcorr/z_ewkcorr_func'),
    DoPUReweightingNPV         = cms.bool(False),
    hltParams                  = defaultHLTParameters.clone(),
    DilepCandParams            = defaultZCandSelectionParameters.clone(
        massMin = cms.double(50),
    ), 
    ZCandParams                = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMaxLeadingLep = cms.double(45),
        ptMin = cms.double(0.),
        ), 
    BoostedZCandParams         = defaultZCandSelectionParameters.clone(
        massMin = cms.double(75),
        massMax = cms.double(105),
        ptMaxLeadingLep = cms.double(45),
        ptMin = cms.double(200.),
        ), 
    GenHSelParams              = genPartParams.clone(), 
    STMin                      = cms.double  (500.),
    HTMin                      = cms.double (150.),
    elesfParams                = defaultWP.clone(
        lepidtype = cms.string("TIGHT"),
        zdecayMode = cms.string("wel"),
        ),
    musfParams                 = defaultWP.clone(
        lepidtype = cms.string("TIGHT"),
        zdecayMode = cms.string("wmu"),
        ),
    metselParams               = defaultMETMakerParameters,
    muselParams                = defaultMuonMakerParameters, 
    elselParams                = defaultElectronMakerParameters, 
    jetAK4selParams            = defaultAK4JetSelectionParameters,
    jetAK4BTaggedselParams     = defaultBTaggedAK4JetSelectionParameters, 
    jetAK8selParams            = defaultAK8JetSelectionParameters,
    jetHTaggedselParams        = defaultHJetSelectionParameters,
    jetWTaggedselParams        = defaultWJetSelectionParameters,
    jetTopTaggedselParams      = defaultTJetSelectionParameters,
    genParams                  = getSelectParams,
    )

