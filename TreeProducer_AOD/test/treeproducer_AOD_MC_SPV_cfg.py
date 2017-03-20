import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMPTREE")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8', '')


process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2000) )

process.source = cms.Source("PoolSource",
 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

    fileNames = cms.untracked.vstring(#'file:///user/gflouris/pickevents_HT-1000To1500_ChFMax0p04_AODSIM.root'
'root://cms-xrd-global.cern.ch//store/mc/RunIISummer16DR80Premix/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/0075291F-AAB4-E611-A618-A0000420FE80.root',

)
)


from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
process.jec = cms.ESSource('PoolDBESSource',
    CondDBSetup,
    connect = cms.string('sqlite:Summer16_23Sep2016V4_MC.db'),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016V4_MC_AK4PFchs'),
            label  = cms.untracked.string('AK4PFchs')
        ),
    )
)

# Add an ESPrefer to override JEC that might be available from the global tag
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')



# Remove first PV
# Create goodOfflinePrimaryVertrices
# Run CHS
# Correct jets
# Tree producer
######################
from CommonTools.ParticleFlow.pfPileUp_cfi  import pfPileUp as _pfPileUp
from CommonTools.ParticleFlow.TopProjectors.pfNoPileUp_cfi import pfNoPileUp as _pfNoPileUp
from CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi import *


process.pfPileUpSPV = _pfPileUp.clone(PFCandidates='particleFlowPtrs',
                                      Vertices = 'SPVgoodOfflinePrimaryVertices',
                                      checkClosestZVertex = False,
                                      verbose = False)
process.pfNoPileUpSPV = _pfNoPileUp.clone(topCollection = 'pfPileUpSPV',
                                          bottomCollection = 'particleFlowPtrs', 
                                      verbose = False)


process.SPVgoodOfflinePrimaryVertices = goodOfflinePrimaryVertices.clone()
process.SPVgoodOfflinePrimaryVertices.src = src = cms.InputTag("pfchsSecondPV:SecondOfflinePrimaryVerices")

process.load('SimpAnalysis.PFCHS_SecondPV.pfchs_SecondPV_cfi')

process.load('RecoJets.Configuration.RecoPFJets_cff')
from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets

process.ak4PFCHSJetsSPV = ak4PFJets.clone(
    rParam = 0.4,
    jetPtMin = 5.0,
    src = "pfNoPileUpSPV",
)





process.load("SimpAnalysis.TreeProducer_AOD.Treeproducer_AOD_cfi")
process.treeSPV = process.tree.clone()
process.treeSPV.pfjetCollection = cms.InputTag("ak4PFCHSJetsSPV")
process.treeSPV.pfRho = cms.InputTag("fixedGridRhoFastjetAll")
process.treeSPV.vertexCollection = cms.InputTag("SPVgoodOfflinePrimaryVertices")
process.treeSPV.isData = cms.untracked.bool(False)

#############################

process.treeCorr = process.tree.clone()
process.treeCorr.pfjetCollection  = cms.InputTag("ak4PFJetsCHS")
process.treeCorr.pfRho = cms.InputTag("fixedGridRhoFastjetAll")
process.treeCorr.isData = cms.untracked.bool(False)


process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.AOD
switchOnVIDPhotonIdProducer(process, dataFormat)
my_id_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']
for idmod in my_id_modules:
	setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

process.p = cms.Path(process.egmPhotonIDSequence
		    +process.treeCorr
                    +process.pfchsSecondPV
                    +process.SPVgoodOfflinePrimaryVertices
                    +process.pfPileUpSPV
                    +process.pfNoPileUpSPV
                    +process.ak4PFCHSJetsSPV
                    +process.treeSPV
)
# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('output_tree_SPV_QCD.root')
)






process.out = cms.OutputModule("PoolOutputModule",

    outputCommands = cms.untracked.vstring(
     #'drop *',
     'keep *'

),
   fileName = cms.untracked.string("outputfile_SPV_debug.root")
)

process.output_step = cms.EndPath(process.out)


