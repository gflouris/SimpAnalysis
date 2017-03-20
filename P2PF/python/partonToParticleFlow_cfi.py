import FWCore.ParameterSet.Config as cms

partonToParticleFlow = cms.EDProducer('P2PFProducer',
    Partons_Source =  cms.InputTag("genParticles","","HLT"),
    ParticleFlow_Source = cms.InputTag("particleFlow","","RECO"),
)
