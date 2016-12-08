#! /bin/python

def job_list(isData):
    if isData:
        jobList = [
                   ['/SingleMuon/skhi-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-642b48c1c707cb5cfa93fc168fde448b/USER', 'SingleMuon_ICHEP', '40', ''],
                   ['/SingleElectron/skhi-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-642b48c1c707cb5cfa93fc168fde448b/USER', 'SingleElectron_ICHEP', '40', '']
                   ]
        return jobList
    else:
        jobList = [
                   ['/TT_TuneCUETP8M1_13TeV-powheg-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER', 'TTBar', '10',''],
                   ['/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-100To200', '10',''],
                   ['/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-200To400', '10',''],
                   ['/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-400To600', '10',''],
                   ['/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-600To800', '10',''],
                   ['/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-800To1200', '10',''],
                   ['/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-1200To2500', '10',''],
                   ['/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','WJetsToLNu_HT-2500ToInf', '10',''],
                   ['/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','ST_t-channel', '10',''],
                   ['/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/asparker-RunIISpring16MiniAODv2_B2GAnaFW_80x_V2p0-9c09e10dd1f806cf9fdf5818b1c7d288/USER','ST_t-channel_antitop', '10',''],
                   ]
        return jobList



                   
                   
                   
                   
                   
                   
                   
                   
                   