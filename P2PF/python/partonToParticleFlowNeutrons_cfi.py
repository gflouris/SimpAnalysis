import FWCore.ParameterSet.Config as cms

partonToParticleFlowNeutrons = cms.EDProducer('P2PFProducerNeutrons',
    Partons_Source =  cms.InputTag("genParticles","","HLT"),
    ParticleFlow_Source = cms.InputTag("particleFlow","","RECO"),
)
