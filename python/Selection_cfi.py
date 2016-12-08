import FWCore.ParameterSet.Config as cms

signalSelectionParameters = cms.PSet(
                                       lep_pt             = cms.double(40),
                                       lep_eta            = cms.double(2.1),
                                       met_et             = cms.double(50),
                                       jet_pt             = cms.double(200),
                                       jet_eta            = cms.double(2.4),
                                       min_bdisc          = cms.double(0.869),
                                       max_bdisc          = cms.double(1),
                                       min_mt             = cms.double(0),
                                       max_mt             = cms.double(130),
                                       min_dr             = cms.double(1.5),
                                       max_dr             = cms.double(99),
                                       min_dphi           = cms.double(2.0),
                                       max_dphi           = cms.double(99),
                                       fwd_jet_eta        = cms.double(2.4),
                                       min_st             = cms.double(500),
                                       )

ttbarSelectionParameters = cms.PSet(
                                     lep_pt             = cms.double(40),
                                     lep_eta            = cms.double(2.1),
                                     met_et             = cms.double(60),
                                     jet_pt             = cms.double(100),
                                     jet_eta            = cms.double(2.4),
                                     min_bdisc          = cms.double(0.869),
                                     max_bdisc          = cms.double(1),
                                     min_mt             = cms.double(0),
                                     max_mt             = cms.double(130),
                                     min_dr             = cms.double(0),
                                     max_dr             = cms.double(1.5),
                                     min_dphi           = cms.double(0),
                                     max_dphi           = cms.double(99),
                                     fwd_jet_eta        = cms.double(0),
                                     min_st             = cms.double(200),
                                     )

wjetSelectionParameters = cms.PSet(
                                     lep_pt             = cms.double(40),
                                     lep_eta            = cms.double(2.1),
                                     met_et             = cms.double(50),
                                     jet_pt             = cms.double(200),
                                     jet_eta            = cms.double(2.4),
                                     min_bdisc          = cms.double(-1),
                                     max_bdisc          = cms.double(0.869),
                                     min_mt             = cms.double(0),
                                     max_mt             = cms.double(130),
                                     min_dr             = cms.double(1.5),
                                     max_dr             = cms.double(99),
                                     min_dphi           = cms.double(2.0),
                                     max_dphi           = cms.double(99),
                                     fwd_jet_eta        = cms.double(2.4),
                                     min_st             = cms.double(500),
                                     )

