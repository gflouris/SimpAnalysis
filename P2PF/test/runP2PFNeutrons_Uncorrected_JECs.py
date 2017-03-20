# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms
process = cms.Process("P2PF")
import optparse

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(500)
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))

process.source = cms.Source('PoolSource',
 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
 fileNames = cms.untracked.vstring(
'file:///user/gflouris/Analysis/SIMPS/SignalProduction/ParticleGun/CMSSW_8_0_21/src/SUS-RunIISummer16DR80Premix-00068.root'
#	'file:///storage_mnt/storage/user/gflouris/Analysis/SIMPS/SignalProduction/Standard/CMSSW_8_0_21/src/SIMP200/Step2/SUS-RunIISummer16DR80Premix-00068_1.root',
#        'file:///storage_mnt/storage/user/gflouris/Analysis/SIMPS/SignalProduction/Standard/CMSSW_8_0_21/src/SIMP200/Step2/SUS-RunIISummer16DR80Premix-00068_2.root',
#        'file:///storage_mnt/storage/user/gflouris/Analysis/SIMPS/SignalProduction/Standard/CMSSW_8_0_21/src/SIMP200/Step2/SUS-RunIISummer16DR80Premix-00068_3.root',

),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-500))

############################
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')



###P2PF
process.load('SimpAnalysis.P2PF.partonToParticleFlowNeutrons_cfi')

process.load('RecoJets.Configuration.RecoPFJets_cff')
from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets

process.ak4PFCHSJetsSIMPs = ak4PFJets.clone(
    rParam = 0.4,
    jetPtMin = 5.0,
    #src = "partonToParticleFlow:particleFlowSIMPs",
    src = "pfNoPileUpJME",
)



process.ak4PFJetsSIMPs = ak4PFJets.clone(
    rParam = 0.4,
    jetPtMin = 5.0,
    src = "partonToParticleFlowNeutrons:particleFlowSIMPs",
    #src = "pfNoPileUpJME",
)


from RecoParticleFlow.PFProducer.particleFlowTmpPtrs_cfi import *
process.SIMPsPFPtrs = particleFlowTmpPtrs.clone(
	src = cms.InputTag('partonToParticleFlowNeutrons:particleFlowSIMPs')
)



######################




from CommonTools.ParticleFlow.pfPileUp_cfi  import pfPileUp as _pfPileUp
from CommonTools.ParticleFlow.TopProjectors.pfNoPileUp_cfi import pfNoPileUp as _pfNoPileUp
from CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi import *

process.pfPileUpJME = _pfPileUp.clone(#PFCandidates='particleFlowPtrs',
			      PFCandidates='SIMPsPFPtrs',
                              Vertices = 'goodOfflinePrimaryVertices',
                              checkClosestZVertex = False )
process.pfNoPileUpJME = _pfNoPileUp.clone(topCollection = 'pfPileUpJME',
				#bottomCollection = 'particleFlowPtrs' )
					bottomCollection = 'SIMPsPFPtrs' )



###################

###P2PF
process.load('SimpAnalysis.P2PF.SubAddPt_cfi')

process.SubPt = process.subAddPt.clone()
process.SubPt.AddPt_Bool = cms.bool(False)
process.SubPt.ParticleFlow_Source = cms.InputTag("ak4PFCHSJetsSIMPs")

process.AddPt = process.subAddPt.clone()
process.AddPt.AddPt_Bool = cms.bool(True)
process.AddPt.ParticleFlow_Source = cms.InputTag("ak4PFCHSJetsCorr")

#process.partonToParticleFlow.ParticleFlow_Source = cms.InputTag("pfNoPileUpJME")
####JECs
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
process.ak4PFCHSJetsCorr.src = cms.InputTag('ak4PFCHSJetsSIMPs')






process.Parton2PFSeq = cms.Sequence(
                                process.partonToParticleFlowNeutrons
                                +process.SIMPsPFPtrs
				                +process.goodOfflinePrimaryVertices
			                    +process.pfPileUpJME
				                +process.pfNoPileUpJME
 		                        +process.ak4PFCHSJetsSIMPs
                                +process.ak4PFJetsSIMPs
				                #+process.SubPt
                                +process.ak4PFCHSL1FastL2L3ResidualCorrectorChain
                                +process.ak4PFCHSJetsCorr
                                #+process.AddPt

)

process.path = cms.Path(process.Parton2PFSeq)



process.out = cms.OutputModule("PoolOutputModule",

    outputCommands = cms.untracked.vstring(
     #'drop *',
     'keep *'

),
   fileName = cms.untracked.string("SUS-RunIISummer16DR80Premix-00068_NeutronGun_JECs_GetRandom.root")
)

process.output_step = cms.EndPath(process.out)
#process.schedule.extend([process.output_step])
#process.options.allowUnscheduled = cms.untracked.bool(True)
