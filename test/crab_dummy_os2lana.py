from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")

config.General.requestName = DUMMY_NAME
config.General.workArea = DUMMY_WORKDIR
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'SingleLepAna_cfg.py'
config.JobType.pyCfgParams = [DATa,  PUOFF, LEPSF, FILTERSIGNAL, SIGNALTYPE, OPTIMIZERECO]
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
			     'PUDistMC_2015_25ns_FallMC_matchData_PoissonOOTPU.root',
                             'RunII2015_25ns_PUXsec65550nb.root',
                             'RunII2015_25ns_PUXsec69000nb.root',
                             'RunII2015_25ns_PUXsec72450nb.root',
                             'btag-eff-subjet.root', 'CSVv2_ichep.csv']

config.section_("Data")
config.Data.inputDataset = DUMMY_DATASET
config.Data.inputDBS = 'phys03'
config.Data.splitting = DUMMY_BASE
config.Data.unitsPerJob = DUMMY_NUMBER
config.Data.ignoreLocality = False
config.Data.publication = False
config.Data.outLFNDirBase = DUMMY_OUTPUT_PATH

config.section_("Site")
config.Site.storageSite = DUMMY_SITE
config.section_('User')
