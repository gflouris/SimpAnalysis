import FWCore.ParameterSet.Config as cms

subAddPt = cms.EDProducer('SubAddPt',
    Partons_Source =  cms.InputTag("genParticles","","HLT"),
    ParticleFlow_Source = cms.InputTag("ak4PFCHSJetsSIMPs","",""),
    AddPt_Bool  = cms.bool(True),

)
