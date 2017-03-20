import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMPTREE")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#/store/mc/RunIISummer16DR80Premix/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/110000/00086432-1CB2-E611-9E62-485B39897219.root'

'/store/data/Run2016G/JetHT/RECO/PromptReco-v1/000/278/822/00000/FEFE8155-5264-E611-B3E6-02163E0145B9.root'
)
)


from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.AOD
switchOnVIDPhotonIdProducer(process, dataFormat)
my_id_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']
for idmod in my_id_modules:
	setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

# Tree producer
process.load("SimpAnalysis.TreeProducer_AOD.Treeproducer_AOD_cfi")
#process.tree.triggerResults = cms.InputTag("TriggerResults", "", "HLT2") #for XXTo4J
process.tree.triggerName = cms.vstring(
"HLT_DiCentralPFJet170_v1","HLT_DiCentralPFJet170_v2","HLT_DiCentralPFJet170_v3", "HLT_DiCentralPFJet170_v4", "HLT_DiCentralPFJet170_v5",
"HLT_SingleCentralPFJet170_CFMax0p1_v1",  "HLT_SingleCentralPFJet170_CFMax0p1_v1",  "HLT_SingleCentralPFJet170_CFMax0p1_v3",  "HLT_SingleCentralPFJet170_CFMax0p1_v4", "HLT_SingleCentralPFJet170_CFMax0p1_v5")


process.p = cms.Path(process.egmPhotonIDSequence * process.tree)

# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('Data_AOD.root')
)
