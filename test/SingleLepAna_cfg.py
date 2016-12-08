import sys
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('isData', True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Is data?"
                 )
options.register('lepID', 'TIGHT',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "lepton ID? Choose: 'TIGHT' or 'LOOSE'"
                 )
options.register('outFileName', 'singlelep.root',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Output file name"
                 )
options.register('doPUReweightingOfficial', False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Do pileup reweighting using official recipe"
                 )

options.register('applyLeptonSFs', True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Apply lepton SFs to the MC"
                 )
options.register('applyBTagSFs', True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Apply b-tagging SFs to the MC"
                 )
options.register('applyDYNLOCorr', False, ### Set to true only for DY process ### Only EWK NLO k-factor is applied
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Apply DY EWK k-factor to DY MC"
                 )
options.register('applyTopPtCorr', True, ### Set to true only for ttbar process
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Apply ttbar top ptcorrection to DY MC"
                 )
options.register('FileNames', 'bprime800',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Name of list of input files"
                 )
options.register('optimizeReco', True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Optimize mass reconstruction"
                 )
options.register('applyHtCorr', False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Optimize mass reconstruction"
                 )
options.register('doSkim', False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Produce skim 1 or 0"
                 )
options.register('sys', False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "Do systematics"
                 )
options.register('short', False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "only signal"
                 )

options.setDefault('maxEvents', -1)
options.parseArguments()
print options

hltpaths_mu = [
               "HLT_IsoMu22_v",
               "HLT_IsoTkMu22_v"
               ]
hltpaths_ele = [
                "HLT_Ele27_eta2p1_WPLoose_Gsf_v",
                "HLT_Ele27_eta2p1_WPTight_Gsf_v"
                ]

if options.isData:
    options.optimizeReco = False
    options.applyLeptonSFs = False
    options.applyHtCorr = False
    options.sys = False

process = cms.Process("SingleLepAna")

from inputFiles_cfi import *

process.source = cms.Source(
                            "PoolSource",
                            fileNames = cms.untracked.vstring(
                                                              
#'root://eoscms.cern.ch//eos/cms/store/group/phys_b2g/B2GAnaFW_80X_V2p0_RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/SingleMuon/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160926_071707/0000/B2GEDMNtuple_315.root',
#'file://B2GEDMNtuple_164.root',
#'root://cms-xrd-global.cern.ch//store/group/lpctlbsm/B2GAnaFW_80X_V2p0/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160722_192944/0000/B2GEDMNtuple_164.root',
#                                                              'root://cms-xrd-global.cern.ch//store/group/phys_b2g/B2GAnaFW_80X_V2p0_RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/SingleMuon/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160926_071707/0000/B2GEDMNtuple_1.root',
#    'root://cms-xrd-global.cern.ch//store/group/lpctlbsm/B2GAnaFW_80X_V2p0/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160722_192944/0000/B2GEDMNtuple_1.root',
#	'root://cms-xrd-global.cern.ch//store/group/lpctlbsm/B2GAnaFW_80X_V2p0/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160722_192944/0000/B2GEDMNtuple_101.root',                             
#'root://cms-xrd-global.cern.ch//store/group/phys_b2g/B2GAnaFW_80X_V2p0_RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/SingleElectron/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160926_071743/0000/B2GEDMNtuple_1.root', 
#'root://cms-xrd-global.cern.ch//store/group/lpctlbsm/B2GAnaFW_80X_V2p0/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0/160723_155012/0000/B2GEDMNtuple_1.root',
                                )
                            )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

## Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.load("Analysis.VLQAna.EventCleaner_cff")
process.evtcleaner.isData = options.isData
if options.isData:
    process.evtcleaner.hltMuPaths = cms.vstring (hltpaths_mu)
    process.evtcleaner.hltElePaths = cms.vstring (hltpaths_ele)
else:
    process.evtcleaner.hltMuPaths = cms.vstring()
    process.evtcleaner.hltElePaths = cms.vstring()
process.evtcleaner.DoPUReweightingOfficial = cms.bool(options.doPUReweightingOfficial)
#process.evtcleaner.storeLHEWts = options.storeLHEWts

from Analysis.VLQAna.SingleLepAna_cfi import *



### Z candidate and jet selections
process.ana = ana.clone(
                        applyLeptonSFs = cms.bool(options.applyLeptonSFs),
                        applyBTagSFs = cms.bool(options.applyBTagSFs),
                        applyDYNLOCorr = cms.bool(options.applyDYNLOCorr),
                        optimizeReco = cms.bool(options.optimizeReco),
                        applyHtCorr = cms.bool(options.applyHtCorr),
			applyTopPtCorr = cms.bool(options.applyTopPtCorr),	
                        doSkim       = cms.bool(options.doSkim),
                        sys             = cms.bool(options.sys),
                        short           = cms.bool(options.short),
                        )
process.ana.elselParams.elidtype = cms.string(options.lepID)
process.ana.muselParams.muidtype = cms.string(options.lepID)
process.ana.muselParams.muIsoMax = cms.double(0.15)
process.ana.musfParams.lepidtype = cms.string(options.lepID)
process.ana.elesfParams.lepidtype = cms.string(options.lepID)
#process.ana.BoostedZCandParams.ptMin = cms.double(150.)#not used in analysis
process.ana.jetAK8selParams.jetPtMin = cms.double(200)
process.ana.jetAK4BTaggedselParams.jetPtMin = cms.double(50)
process.ana.STMin = cms.double(1000.)
process.ana.vlqMass = cms.double(1200.) #M=1000
process.ana.bosonMass = cms.double(91.2) #Z
process.ana.recoPt = cms.double(0.)



if options.sys:
    process.anabcUp = process.ana.clone(
                                        sys = cms.bool(True),
                                        btagsf_bcUp = cms.bool(True),
                                        )
    process.anabcDown = process.ana.clone(
                                          sys = cms.bool(True),
                                          btagsf_bcDown = cms.bool(True),
                                          )
    process.analightUp = process.ana.clone(
                                           sys = cms.bool(True),
                                           btagsf_lUp = cms.bool(True),
                                           )
    process.analightDown = process.ana.clone(
                                             sys = cms.bool(True),
                                             btagsf_lDown = cms.bool(True),
                                             )
    process.anaJecUp = process.ana.clone(
                                         sys = cms.bool(True),
                                         #jecShift = cms.double(1),
                                         )
    process.anaJecUp.jetAK4selParams.jecShift = cms.double(1.)
    process.anaJecDown = process.ana.clone(
                                           sys = cms.bool(True),
                                           #jecShift = cms.double(-1),
                                           )
    process.anaJecDown.jetAK4selParams.jecShift = cms.double(-1.)
    process.anaJerUp = process.ana.clone(
                                         sys = cms.bool(True),
                                         #jerShift = cms.double(2),
                                         )
    process.anaJerUp.jetAK4selParams.jerShift = cms.int32(2)
    process.anaJerDown = process.ana.clone(
                                           sys = cms.bool(True),
                                           #jerShift = cms.double(0),
                                           )
    process.anaJerDown.jetAK4selParams.jerShift = cms.int32(0)
    process.anaPileupUp = process.ana.clone(
                                            sys = cms.bool(True),
                                            PileupUp = cms.bool(True),
                                            )
    process.anaPileupDown = process.ana.clone(
                                              sys = cms.bool(True),
                                              PileupDown = cms.bool(True),
                                              )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(
                                                         options.outFileName
                                                         )
                                   )

outCommand = ['keep *', 'drop *_evtcleaner_*_*', 'drop *_photons_*_*', 'drop *_photonjets_*_*', 'drop *_*Puppi_*_*', 'drop *_TriggerResults_*_*']

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string(options.outFileName.split('.',1)[0]+'_skim.root'),
                               SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('p')),
                               dropMetaData = cms.untracked.string('DROPPED'),#'type_label_instance_process'
                               outputCommands = cms.untracked.vstring(outCommand )
                               )

## Event counters
from Analysis.EventCounter.eventcounter_cfi import eventCounter
process.allEvents = eventCounter.clone(isData=options.isData)
process.cleanedEvents = eventCounter.clone(isData=options.isData)
process.finalEvents = eventCounter.clone(isData=options.isData)


if options.sys:
    process.p = cms.Path(
                         process.allEvents
                         *process.evtcleaner
                         *cms.ignore(process.ana)
                         *cms.ignore(process.anabcUp)
                         *cms.ignore(process.anabcDown)
                         *cms.ignore(process.analightUp)
                         *cms.ignore(process.analightDown)
                         *cms.ignore(process.anaJecUp)
                         *cms.ignore(process.anaJecDown)
                         *cms.ignore(process.anaJerUp)
                         *cms.ignore(process.anaJerDown)
                         *cms.ignore(process.anaPileupUp)
                         *cms.ignore(process.anaPileupDown)
                         )
elif not options.sys and not options.isData:
    process.p = cms.Path(
                         process.allEvents
                         *process.evtcleaner
                         #*process.cleanedEvents
                         *cms.ignore(process.ana)
                         #*cms.ignore(process.anaH)
                         #* process.finalEvents
                         )
else:
    process.p = cms.Path(
                         process.allEvents
                         *process.evtcleaner
                         *cms.ignore(process.ana)
                         )

if options.doSkim:
    process.outpath = cms.EndPath(process.out)

