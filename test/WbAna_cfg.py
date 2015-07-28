import FWCore.ParameterSet.Config as cms

process = cms.Process("WbAna")

from infiles_cfi import *

process.source = cms.Source(
                            "PoolSource",
                            fileNames = cms.untracked.vstring(
                                'root://cmsxrootd-site.fnal.gov//store/user/devdatta/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/B2GAnaFW_Run2Spring15_25ns_v74x_V3/150703_105335/0000/B2GEDMNtuple_1.root'
                                                              )
                            )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Analysis.VLQAnalyzer.WbAna_cfi")
                          

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(
                                                         "WbAnalyzer.root"
                                                         )
                                   )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("Wb.root"),
                               SelectEvents = cms.untracked.PSet(
                                                                 SelectEvents = cms.vstring('p')
                                                                 ),
                               outputCommands = cms.untracked.vstring(
                                                                      "drop *",
                                                                      )
                               )

process.p = cms.Path(
                     process.ana
                     )
process.outpath = cms.EndPath(process.out)



