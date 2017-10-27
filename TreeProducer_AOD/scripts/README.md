# SIMPS/Neutrons MC Production

## GEN-SIM Step
```
cmsrel CMSSW_7_1_20_patch3
cd CMSSW_7_1_20_patch3/src
cmsenv
mkdir -p ./SIMP10/Neutrons/
cd ./SIMP10/Neutrons/
for i in {1..12}; do gfal-copy srm://maite.iihe.ac.be:8443/pnfs/iihe/cms/store/user/isdebruy/SIMPs/LHEfiles/M_10/SIMP_13TeV_M-10_${i}.lhe.gz file://$(pwd)/; done

gunzip ./*.gz

sed -i 's/9000006/2112/g' ./SIMP_13TeV_M-100_*

./runmany.sh
```

## Step1 - Step2

```
cmsrel CMSSW_8_0_21
cd CMSSW_8_0_21/src
cmsenv
mkdir -p ./SIMP10/Step1/Neutrons
mkdir -p ./SIMP10/Step2/Neutrons
cd ./SIMP10/Step1/Neutrons
./runmany.sh

#after completion of step1
cd ../../Step2/Neutrons
./runmany.sh
```