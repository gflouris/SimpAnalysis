# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms
process = cms.Process("P2PF")
import optparse

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

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

#process.partonToParticleFlow.ParticleFlow_Source = cms.InputTag("pfNoPileUpJME")

process.Parton2PFSeq = cms.Sequence(
                                process.partonToParticleFlowNeutrons
                                +process.SIMPsPFPtrs
				+process.goodOfflinePrimaryVertices
			        +process.pfPileUpJME
				+process.pfNoPileUpJME
 		                +process.ak4PFCHSJetsSIMPs
                                +process.ak4PFJetsSIMPs

)

process.path = cms.Path(process.Parton2PFSeq)



process.out = cms.OutputModule("PoolOutputModule",

    outputCommands = cms.untracked.vstring(
     #'drop *',
     'keep *'

),
   fileName = cms.untracked.string("SUS-RunIISummer16DR80Premix-00068_NeutronGun_test.root")
)

process.output_step = cms.EndPath(process.out)
#process.schedule.extend([process.output_step])
#process.options.allowUnscheduled = cms.untracked.bool(True)
