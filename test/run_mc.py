#! /bin/python
import os
from string import *
import subprocess
import glob
from allJobList import *
from optparse import OptionParser


parser = OptionParser()

parser.add_option('--inputCfg', metavar='C', type='string', action='store',
                  default='crab_dummy_os2lana_mc.py',
                  dest='inputCfg',
                  help='input config tag to be used')

parser.add_option('--outLabel', metavar='L', type='string', action='store',
                  default='single_lep',
                  dest='outLabel',
                  help='output tag to be used')

parser.add_option('--channelType', metavar='S', type='string', action='store',
                  default='MuEle',
                  dest='channelType',
                  help='Channel type: Wel, Wmu')

parser.add_option('--isData', metavar='I', type='int', action='store',
                  default=0,
                  dest='isData',
                  help='run on data or MC')



(options, args) = parser.parse_args()

#set the parameter options in os2lana.py
if options.isData == 1:
    isData       = 'isData=True'
    puOfficial   = 'doPUReweightingOfficial=False'
    applySF      = 'applyLeptonSFs=False'
    optimizeReco = 'optimizeReco=False'
else:
    isData       = 'isData=False'
    puOfficial   = 'doPUReweightingOfficial=False'
    applySF      = 'applyLeptonSFs=True'
    optimizeReco = 'optimizeReco=True'



jobList = job_list(options.isData)

mode = 'zdecaymode=zelel'
for job in jobList:
    print '------prepare to run on :  ' + job[0] + ' -----------'
    f = open(options.inputCfg, 'r')
    instring = f.read()
    baseList = job[0].split('/')
    outname = job[1] + '_' + options.outLabel
    a0 = instring.replace( 'DUMMY_WORKDIR', "'"+options.outLabel+"'")
    a1 = a0.replace( 'DUMMY_DATASET', "'"+job[0]+"'" )
    a2 = a1.replace( 'DATa', "'"+isData+"'")
#    a3 = a2.replace( 'MODE', "'"+mode+"'")
    a4 = a2.replace( 'LEPSF', "'"+applySF+"'")
    a5 = a4.replace( 'PUOFF', "'"+puOfficial+"'")
    a6 = a5.replace( 'DUMMY_NUMBER',  job[2])
    if 'Tprime' in baseList[1] or 'Bprime' in baseList[1]:
        a7 = a6.replace( 'FILTERSIGNAL', "'filterSignal=True'")
        a8 = a7.replace('SIGNALTYPE', "'signalType="+job[3]+"'")
    else:
        a7 = a6.replace( ', FILTERSIGNAL', '')
        a8 = a7.replace( ', SIGNALTYPE', '')
    a9 = a8.replace( 'DUMMY_NAME', "'"+outname+"'" )
    a10 = a9.replace( 'DUMMY_SITE',"'"+'T2_CH_CERN'+"'")
    a11 = a10.replace( 'DUMMY_OUTPUT_PATH', "'"+'/store/group/phys_b2g/skhi/SingleLepBW/'+options.channelType+"'")
    if options.isData:
        a12 = a11.replace('DUMMY_BASE', "'LumiBased'")
    else:
        a12 = a11.replace('DUMMY_BASE', "'FileBased'")
    a13 = a12.replace('OPTIMIZERECO', "'"+optimizeReco+"'")
    # Dump the contents of the crab config to the screen
    print '------ Config : ------- '
    print a13
    #create a directory if it doesn't exist
    c = 'mkdir '+options.channelType
    if not os.path.isdir(options.channelType):
         subprocess.call( [c], shell=True )
    # open the output file
    crabName = 'crab_' + outname + '.py'
    fout = open( options.channelType+'/'+crabName, 'w')
    # write the text to the output file
    fout.write( a13 )
    fout.close()
    print '------ CRAB starting up! ------'
    # now submit the job:
    s = 'crab submit -c ' + options.channelType+'/'+crabName
    print s
    # and submit:
    subprocess.call( [s], shell=True )
