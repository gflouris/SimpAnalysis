#!/bin/bash

#name=$LS_JOBNAME
#id=$IIDD
pwd

#cd /user/gflouris/Analysis/SIMPS/SignalProduction/Standard/CMSSW_8_0_21/src/SIMP10/Step1/Neutrons/ 
cd PPWWDD

source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530
#scramv1 project CMSSW CMSSW_7_1_20_patch3
#cd ./CMSSW_7_1_20_patch3/src/
eval `scramv1 runtime -sh`
export X509_USER_PROXY=/user/$USER/x509up_u$(id -u $USER)


cp ./SUS-RunIISummer16DR80Premix-00068_IDDD_cfg.py ./
cmsRun ./SUS-RunIISummer16DR80Premix-00068_IDDD_cfg.py > JobIDDD.log 2>&1

