import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMPTREE")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

    fileNames = cms.untracked.vstring(
#										'/store/mc/RunIISummer16DR80Premix/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/110000/00086432-1CB2-E611-9E62-485B39897219.root'
'file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SUS-RunIISummer16DR80Premix-00068_SIMPs_M200.root'
)
)

#process.triggerSelection = cms.EDFilter( "TriggerResultsFilter",
    #triggerConditions = cms.vstring(
      #'HLT_DiCentralPFJet170_CFMax0p1_v*',
      #'HLT_DiCentralPFJet220_CFMax0p3_v*',
      #'HLT_DiCentralPFJet330_CFMax0p5_v*',
      #'HLT_DiCentralPFJet430_v*',
      #'HLT_DiCentralPFJet170_v*',
      #'HLT_SingleCentralPFJet170_CFMax0p1_v*'),
    #hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
    #l1tResults = cms.InputTag( "" ),
    #l1tIgnoreMask = cms.bool( False ),
    #l1techIgnorePrescales = cms.bool( False ),
    #daqPartitions = cms.uint32( 1 ),
    #throw = cms.bool( True )
#)

#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.triggerSelection =  HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    #HLTPaths = ['HLT_DiCentralPFJet170_CFMax0p1_v*',
      #'HLT_DiCentralPFJet220_CFMax0p3_v*',
      #'HLT_DiCentralPFJet330_CFMax0p5_v*',
      #'HLT_DiCentralPFJet430_v*',
      #'HLT_DiCentralPFJet170_v*',
      #'HLT_SingleCentralPFJet170_CFMax0p1_v*'],
    #throw = False
#)
    
# Tree producer
process.load("SimpAnalysis.TreeProducer_AOD.Treeproducer_AOD_cfi") 
#process.tree.triggerResults = cms.InputTag("TriggerResults", "", "HLT2") #for XXTo4J
process.tree.pfjetCollection  = cms.InputTag("ak4PFCHSJetsSIMPs") 
process.p = cms.Path(process.tree)

# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('SIMPs_PUMoriond17_AOD_M200.root')
)
