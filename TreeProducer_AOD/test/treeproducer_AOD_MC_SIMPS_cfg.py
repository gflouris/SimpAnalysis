import FWCore.ParameterSet.Config as cms

process = cms.Process("SIMPTREE")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
 duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

    fileNames = cms.untracked.vstring(

"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_400/SUS-RunIISummer16DR80Premix-00068_SIMP_M400_2.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_2.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_3.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_4.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_5.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_6.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_7.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_8.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_9.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_11.root",
#"file:///user/gflouris/Analysis/SIMPS/SignalProduction/P2PF_Ntuples/CMSSW_8_0_21/src/SimpAnalysis/P2PF/test/SIMPS_10/SUS-RunIISummer16DR80Premix-00068_SIMP_M10_12.root",




)
)

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
    )
)

# Add an ESPrefer to override JEC that might be available from the global tag
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')

process.load("JetMETCorrections.Configuration.CorrectedJetProducers_cff")
process.load("JetMETCorrections.Configuration.JetCorrectors_cff")
from JetMETCorrections.Configuration.JetCorrectors_cff import ak4PFCHSL1FastL2L3CorrectorChain
process.ak4PFCHSJetsCorr = process.ak4PFCHSJetsL1.clone()
process.ak4PFCHSJetsCorr.correctors = cms.VInputTag('ak4PFCHSL1FastL2L3Corrector')
process.ak4PFCHSJetsCorr.src = cms.InputTag('ak4PFCHSJetsSIMPs')

# Tree producer
process.load("SimpAnalysis.TreeProducer_AOD.Treeproducer_AOD_cfi")
process.tree.pfjetCollection  = cms.InputTag("ak4PFCHSJetsCorr")
#process.tree.pfjetCollection  = cms.InputTag("ak4PFCHSJetsSIMPs") #uncorrected


process.p = cms.Path(process.ak4PFCHSL1FastL2L3CorrectorChain*process.ak4PFCHSJetsCorr*process.tree)

# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('SIMPs_PUMoriond17_AOD_SIMP_M400.root')
)
