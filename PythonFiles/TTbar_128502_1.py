import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes

process = cms.Process("LJMetCom")

#Arguments from condor submit script which are used more than once
condorIsMC = bool(True)
relBase    = str('/uscms_data/d2/sapta/work/LJMetCode_fromGena/Dilepton_Feb25/CMSSW_5_3_7_patch4')
condorJSON = str('None')

# Dilepton calculator options
process.load('LJMet.Com.DileptonCalc_cfi')
process.DileptonCalc.isMc     = condorIsMC
process.DileptonCalc.dataType = cms.string('None')

############################################################
#
# FWLite application options
#
process.ljmet = cms.PSet(
    isMc = cms.bool(condorIsMC),
    runs = cms.vint32([])
)

#Exclude unnecessary calculators
process.ljmet.excluded_calculators = cms.vstring(
    'WprimeCalc',
    'LjetsTopoCalc',
    'LjetsTopoCalcNew',
    'StopCalc'
    ) 
############################################################
#
# Event selector options
#
process.event_selector = cms.PSet(

    selection = cms.string('DileptonSelector'),
    isMc      = cms.bool(condorIsMC),

    # cuts
    #HLT
    trigger_cut              = cms.bool(True),
    dump_trigger             = cms.bool(False),

    #Can use same trigger paths for data and MC since MC is always one of the data versions
    trigger_path_ee          = cms.vstring('HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15',
                                           'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v16',
                                           'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17',
                                           'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v18',
                                           'HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v19'),
    
    trigger_path_em          = cms.vstring('HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4', 'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5',
                                           'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6', 'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7',
                                           'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8', 'HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9',
                                           'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4', 'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5',
                                           'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6', 'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7',
                                           'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8', 'HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9'),

    trigger_path_mm          = cms.vstring('HLT_Mu17_Mu8_v16', 'HLT_Mu17_Mu8_v17', 'HLT_Mu17_Mu8_v18',
                                           'HLT_Mu17_Mu8_v19', 'HLT_Mu17_Mu8_v21', 'HLT_Mu17_Mu8_v22',
                                           'HLT_Mu17_TkMu8_v9',  'HLT_Mu17_TkMu8_v10', 'HLT_Mu17_TkMu8_v11',
                                           'HLT_Mu17_TkMu8_v12', 'HLT_Mu17_TkMu8_v13', 'HLT_Mu17_TkMu8_v14'),    

    pv_cut                   = cms.bool(False),
    hbhe_cut                 = cms.bool(False),

    jet_cuts                 = cms.bool(False),
    jet_minpt                = cms.double(20.0),
    jet_maxeta               = cms.double(5),
    min_jet                  = cms.int32(0),
    max_jet                  = cms.int32(4000),

    muon_cuts                = cms.bool(True),
    min_muon                 = cms.int32(0),
    muon_minpt               = cms.double(10.0),
    muon_maxeta              = cms.double(2.5),
    max_muon                 = cms.int32(20),

    electron_cuts            = cms.bool(True),
    min_electron             = cms.int32(0),
    electron_minpt           = cms.double(10.0),
    electron_maxeta          = cms.double(2.5),
    max_electron             = cms.int32(20),

    min_lepton               = cms.int32(2),

    met_cuts                 = cms.bool(False),
    min_met                  = cms.double(0.0),

    btag_cuts                = cms.bool(False),
    btagOP                   = cms.string("CSVM"),
    btag_1                   = cms.bool(True),
    btag_2                   = cms.bool(True),
    btag_3                   = cms.bool(False),

    trigger_collection       = cms.InputTag('TriggerResults::HLT'),
    pv_collection            = cms.InputTag('goodOfflinePrimaryVertices'),
    jet_collection           = cms.InputTag('goodPatJetsPFlow'),
    muon_collection          = cms.InputTag('selectedPatMuonsPFlowLoose'),
    electron_collection      = cms.InputTag('selectedPatElectronsPFlowLoose'),
    met_collection           = cms.InputTag('patMETsPFlow'),

    #JEC_txtfile              = cms.string(relBase+'/src/LJMet/Com/cond/Summer12_V2_DATA_AK5PF_UncertaintySources.txt'),
    JEC_txtfile              = cms.string(relBase+'/src/LJMet/Com/cond/txt/Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt'),
    JECup		     = cms.bool(False),
    JECdown                  = cms.bool(False),
    JERup                    = cms.bool(False),
    JERdown                  = cms.bool(False),

    BTagUncertUp             = cms.bool(False),
    BTagUncertDown           = cms.bool(True),  


    do53xJEC                 = cms.bool(True),

    MCL1JetPar               = cms.string(relBase+'/src/LJMet/Com/data/START53_V7G_L1FastJet_AK5PFchs.txt'),
    MCL2JetPar               = cms.string(relBase+'/src/LJMet/Com/data/START53_V7G_L2Relative_AK5PFchs.txt'),
    MCL3JetPar               = cms.string(relBase+'/src/LJMet/Com/data/START53_V7G_L3Absolute_AK5PFchs.txt'),

    DataL1JetPar             = cms.string(relBase+'/src/LJMet/Com/data/FT_53_V10_AN3_L1FastJet_AK5PFchs.txt'),
    DataL2JetPar             = cms.string(relBase+'/src/LJMet/Com/data/FT_53_V10_AN3_L2Relative_AK5PFchs.txt'),
    DataL3JetPar             = cms.string(relBase+'/src/LJMet/Com/data/FT_53_V10_AN3_L3Absolute_AK5PFchs.txt'),
    DataResJetPar            = cms.string(relBase+'/src/LJMet/Com/data/FT_53_V10_AN3_L2L3Residual_AK5PFchs.txt'),
    keepFullMChistory        = cms.bool(True)

)

#######################################################
#
# Input files
#
process.inputs = cms.PSet (
    nEvents    = cms.int32(-1),
    skipEvents = cms.int32(0),
    lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange()),
    fileNames  = cms.vstring(
                                              'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/FED3CFD3-5325-E211-83CB-003048FFD7C2.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/88CE3EC1-5425-E211-8AC9-003048678A7E.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/FC2E2F0C-5425-E211-B0AD-00304867915A.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/7A6F5997-5325-E211-B329-001A928116E0.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/B072C190-5425-E211-94AB-001A928116C0.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/0E59CA3D-5525-E211-A21D-0018F3D0966C.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/0A794275-5225-E211-9C1E-001A928116E0.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/F4C34131-5325-E211-9603-003048FFD7A2.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/5A77F4A3-5525-E211-9261-002618943904.root',
                 'dcache:///pnfs/cms/WAX/11/store/results/B2G/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/USER/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/0000/2CCBAB22-5425-E211-B414-00304867918A.root',

    )
)

# JSON
if not condorIsMC:
    JsonFile = relBase+'/src/LJMet/Com/data/json/'+condorJSON
    myList   = LumiList.LumiList(filename=JsonFile).getCMSSWString().split(',')
    process.inputs.lumisToProcess.extend(myList)
        
        
        
#######################################################
#
# Output
#
process.outputs = cms.PSet (
    outputName = cms.string('TTbar_1'),
    treeName   = cms.string('ljmet'),
)

#######################################################
#
# Object selector options
#

# Primary vertex
process.load('PhysicsTools.SelectorUtils.pvSelector_cfi')
process.pvSelector.pvSrc   = cms.InputTag('goodOfflinePrimaryVertices')
process.pvSelector.minNdof = cms.double(4.0)
process.pvSelector.maxZ    = cms.double(24.0)
process.pvSelector.maxRho  = cms.double(2.0)

# jets
process.load('PhysicsTools.SelectorUtils.pfJetIDSelector_cfi') 
process.pfJetIDSelector.version = cms.string('FIRSTDATA')
process.pfJetIDSelector.quality = cms.string('LOOSE')
