import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMPTREE")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

    fileNames = cms.untracked.vstring(
#										'/store/mc/RunIISummer16DR80Premix/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/110000/00086432-1CB2-E611-9E62-485B39897219.root'
'file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SUS-RunIISummer16DR80Premix-00068_NeutronGun_test.root'
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
############################
# process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
# from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v6', '')

from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
process.jec = cms.ESSource('PoolDBESSource',
    CondDBSetup,
    connect = cms.string('sqlite:JECs/Summer16_23Sep2016V4_MC.db'),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016V4_MC_AK4PFchs'),
            label  = cms.untracked.string('AK4PFchs')
        ),
        # cms.PSet(
        #     record = cms.string('JetCorrectionsRecord'),
        #     tag    = cms.string('JetCorrectorParametersCollection_Fall15_V2_DATA_AK8PFPuppi'),
        #     label  = cms.untracked.string('AK8PFPuppi')
        # ),
        # # ...and so on for all jet types you need
    )
)

# Add an ESPrefer to override JEC that might be available from the global tag
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')



#from JetMETCorrections.Configuration.JetCorrectionEra_cff import *
#JetCorrectionEra.era = 'Summer16_23Sep2016V4' # FIXME for input
process.load("JetMETCorrections.Configuration.CorrectedJetProducers_cff")
process.load("JetMETCorrections.Configuration.JetCorrectors_cff")
from JetMETCorrections.Configuration.JetCorrectors_cff import ak4PFCHSL1FastL2L3ResidualCorrectorChain
#process.ak4PFJetsL1L2L3Residual.src = cms.InputTag("ak4PFJetsCHS")
process.ak4PFCHSJetsCorr = process.ak4PFCHSJetsL1.clone()
process.ak4PFCHSJetsCorr.correctors = cms.VInputTag('ak4PFCHSL1FastL2L3ResidualCorrector')

# Tree producer
process.load("SimpAnalysis.TreeProducer_AOD.Treeproducer_AOD_cfi")
process.tree0 = process.tree.clone()
process.tree0.pfjetCollection = cms.InputTag("ak4PFCHSJetsCorr")
#process.tree.triggerResults = cms.InputTag("TriggerResults", "", "HLT2") #for XXTo4J
process.tree.pfjetCollection  = cms.InputTag("ak4PFCHSJetsSIMPs")


process.p = cms.Path(process.ak4PFCHSL1FastL2L3ResidualCorrectorChain*process.ak4PFCHSJetsCorr*process.tree0*process.tree)

# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('SIMPs_PUMoriond17_AOD_NG.root')
)
