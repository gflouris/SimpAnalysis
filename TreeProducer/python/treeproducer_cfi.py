import FWCore.ParameterSet.Config as cms

tree = cms.EDAnalyzer(
    'TreeProducer',
    hltProcessName   = cms.string("HLT"),
    pfjetCollection  = cms.InputTag("ak5PFJets"),
    vertexCollection = cms.InputTag("offlinePrimaryVertices")
)
