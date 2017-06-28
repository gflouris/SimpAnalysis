import FWCore.ParameterSet.Config as cms

pfchsSecondPV = cms.EDProducer('PFCHS_SecondPV',
    PV_Source =  cms.InputTag("offlinePrimaryVertices","","RECO"),
    N_Swap  = cms.uint32(1),

)
