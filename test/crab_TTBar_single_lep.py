from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")

config.General.requestName = 'TTBar_single_lep'
config.General.workArea = 'single_lep_test_v2'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'SingleLepAna_cfg.py'
config.JobType.pyCfgParams = ['isData=False',  'doPUReweightingOfficial=False', 'applyLeptonSFs=True', 'optimizeReco=True']
config.JobType.inputFiles = ['Spring16_25nsV6_DATA_L2L3Residual_AK4PFchs.txt',
                             'Spring16_25nsV6_DATA_L2Relative_AK8PFchs.txt',
                             'Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt',
                             'Spring16_25nsV6_MC_L2Relative_AK8PFchs.txt',
                             'Spring16_25nsV6_MC_Uncertainty_AK4PFchs.txt',
                             'Spring16_25nsV6_DATA_L2L3Residual_AK8PFchs.txt',
                             'Spring16_25nsV6_DATA_L3Absolute_AK4PFchs.txt',
                             'Spring16_25nsV6_DATA_Uncertainty_AK8PFchs.txt',
                             'Spring16_25nsV6_MC_L3Absolute_AK4PFchs.txt',
                             'Spring16_25nsV6_MC_Uncertainty_AK8PFchs.txt',
                             'Spring16_25nsV6_DATA_L2Relative_AK4PFchs.txt',
                             'Spring16_25nsV6_DATA_L3Absolute_AK8PFchs.txt',
                             'Spring16_25nsV6_MC_L2Relative_AK4PFchs.txt',
                             'Spring16_25nsV6_MC_L3Absolute_AK8PFchs.txt',
                             'PUDistMC_2015_25ns_Startup_PoissonOOTPU.root',
                             'RunII2015_25ns_PUXsec65550nb.root',
                             'RunII2015_25ns_PUXsec69000nb.root',
                             'RunII2015_25ns_PUXsec72450nb.root',
                             'btag-eff-subjet.root']

config.section_("Data")
config.Data.inputDataset = '/TT_TuneCUETP8M1_13TeV-powheg-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = '/store/group/phys_b2g/skhi/SingleLepBW/MuEle'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
config.section_('User')
