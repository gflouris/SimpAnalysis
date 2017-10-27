#!/bin/bash

#cd /storage_mnt/storage/user/gflouris/Analysis/SIMPS/SignalProduction/Standard/CMSSW_7_1_20_patch3/src/SIMP10/Neutrons/ 
cd PPWWDD

source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc481
#scramv1 project CMSSW CMSSW_7_1_20_patch3
#cd ./CMSSW_7_1_20_patch3/src/
eval `scramv1 runtime -sh`

export X509_USER_PROXY=/user/$USER/x509up_u$(id -u $USER)

#fal-copy srm://maite.iihe.ac.be:8443/pnfs/iihe/cms/store/user/isdebruy/SIMPs/LHEfiles/M_10/SIMP_13TeV_M-10_IDDD.lhe.gz file:./
#unzip SIMP_13TeV_M-10_IDDD.lhe.gz 

#p /storage_mnt/storage/user/gflouris/Analysis/SIMPS/SignalProduction/Standard/CMSSW_7_1_20_patch3/src/SIMP10/SUS-RunIISummer15GS-00146_IDDD_cfg.py ./
cmsRun ./SUS-RunIISummer15GS-00146_IDDD_cfg.py > JobIDDD.log 2>&1
rm SIMP_13TeV_M-10_IDDD.lhe
