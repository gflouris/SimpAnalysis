import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMPTREE")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

    fileNames = cms.untracked.vstring('file:///user/gflouris/pickevents_HT-1000To1500_ChFMax0p04_AODSIM.root'
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


###Correct ak4PFCHS Jets
process.load("JetMETCorrections.Configuration.CorrectedJetProducers_cff")
process.load("JetMETCorrections.Configuration.JetCorrectors_cff")
from JetMETCorrections.Configuration.JetCorrectors_cff import ak4PFCHSL1FastL2L3ResidualCorrectorChain
#process.ak4PFJetsL1L2L3Residual.src = cms.InputTag("ak4PFJetsCHS")
process.ak4PFCHSJetsCorr = process.ak4PFCHSJetsL1.clone()
process.ak4PFCHSJetsCorr.correctors = cms.VInputTag('ak4PFCHSL1FastL2L3ResidualCorrector')


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
                                      checkClosestZVertex = False )
process.pfNoPileUpSPV = _pfNoPileUp.clone(topCollection = 'pfPileUpSPV',
                                          bottomCollection = 'particleFlowPtrs' )

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



process.ak4SPVPFCHSJetsCorr = process.ak4PFCHSJetsL1.clone()
process.ak4SPVPFCHSJetsCorr.correctors = cms.VInputTag('ak4PFCHSL1FastL2L3ResidualCorrector')
process.ak4SPVPFCHSJetsCorr.src = cms.InputTag('ak4PFCHSJetsSPV')



process.load("SimpAnalysis.TreeProducer_AOD.Treeproducer_AOD_cfi")
process.treeSPV = process.tree.clone()
process.treeSPV.pfjetCollection = cms.InputTag("ak4SPVPFCHSJetsCorr")
process.treeSPV.vertexCollection = cms.InputTag("SPVgoodOfflinePrimaryVertices")
#############################
process.treeCorr = process.tree.clone()
process.treeCorr.pfjetCollection  = cms.InputTag("ak4PFCHSJetsCorr")

process.treeRAW = process.tree.clone()
process.treeRAW.pfjetCollection  = cms.InputTag("ak4PFJetsCHS")
process.treeRAW.pfRho = cms.InputTag("fixedGridRhoFastjetAll")

process.p = cms.Path(process.treeRAW)
'''
                    +process.ak4PFCHSL1FastL2L3ResidualCorrectorChain
		    +process.ak4PFCHSJetsCorr
		    +process.treeCorr
                    +process.pfchsSecondPV
                    +process.SPVgoodOfflinePrimaryVertices
                    +process.pfPileUpSPV
                    +process.pfNoPileUpSPV
                    +process.ak4PFCHSJetsSPV
                    +process.ak4SPVPFCHSJetsCorr
                    +process.treeSPV
)
'''
# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('output_tree_SPV.root')
)
