import FWCore.ParameterSet.Config as cms

partonToParticleFlowChs = cms.EDProducer('P2PFChsProducer',
    Partons_Source =  cms.InputTag("genParticles","","HLT"),
    ParticleFlow_Source = cms.InputTag("particleFlow","","RECO"),
)
