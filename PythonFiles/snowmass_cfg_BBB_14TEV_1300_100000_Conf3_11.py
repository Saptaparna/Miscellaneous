import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes



#
# Parameters that can be set via command line
# when submitting Condor jobs
#
isMc_settable       = True
isSignalMc_settable = False




def FindFile(name):

    fname = 'file.txt'

    return fname



process = cms.Process("LJMetCom")



##################################################################
#
# All input files needed for the job to run
# Specify them here, and they will automatically be correctly
# transferred to Condor when needed
# NOTE: you can define as many or as few entries as you wish,
#       names are up to you
miscFiles = {}
miscFiles['jec_uncertainty']  = '../cond/Summer12_V2_DATA_AK5PF_UncertaintySources.txt'
miscFiles['btag_performance'] = '../cond/btag_performance_db062012.root'
miscFiles['json']             = '../data/json/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
miscFiles['MCL1JetPar']       = '../data/START53_V7G_L1FastJet_AK5PFchs.txt'
miscFiles['MCL2JetPar']       = '../data/START53_V7G_L2Relative_AK5PFchs.txt'
miscFiles['MCL3JetPar']       = '../data/START53_V7G_L3Absolute_AK5PFchs.txt'
miscFiles['DataL1JetPar']     = '../data/FT_53_V10_AN3_L1FastJet_AK5PFchs.txt'
miscFiles['DataL2JetPar']     = '../data/FT_53_V10_AN3_L2Relative_AK5PFchs.txt'
miscFiles['DataL3JetPar']     = '../data/FT_53_V10_AN3_L3Absolute_AK5PFchs.txt'
miscFiles['DataResJetPar']    = '../data/FT_53_V10_AN3_L2L3Residual_AK5PFchs.txt'



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
    runs = cms.vint32([]),
    verbosity = cms.int32(0)
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
# common calculator options
process.load('LJMet.Com.commonCalc_cfi')
process.CommonCalc.dummy_parameter = cms.string('Dummy parameter value')



############################################################
#
# pileup calculator options
process.load('LJMet.Com.pileupCalc_cfi')
process.PileUpCalc.verbosity = process.ljmet.verbosity




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
    muon_maxeta              = cms.double(4.0),
    max_muon                 = cms.int32(20),

    electron_cuts            = cms.bool(True),
    min_electron             = cms.int32(0),
    electron_minpt           = cms.double(10.0),
    electron_maxeta          = cms.double(4.0),
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

    JEC_txtfile              = cms.string(miscFiles['jec_uncertainty']),
    JECup		     = cms.bool(False),
    JECdown                  = cms.bool(False),
    JERup                    = cms.bool(False),
    JERdown                  = cms.bool(False),

    BTagUncertUp             = cms.bool(False),
    BTagUncertDown           = cms.bool(True),  


    do53xJEC                 = cms.bool(True),

    MCL1JetPar               = cms.string(miscFiles['MCL1JetPar']),
    MCL2JetPar               = cms.string(miscFiles['MCL2JetPar']),
    MCL3JetPar               = cms.string(miscFiles['MCL3JetPar']),
    DataL1JetPar             = cms.string(miscFiles['DataL1JetPar']),
    DataL2JetPar             = cms.string(miscFiles['DataL2JetPar']),
    DataL3JetPar             = cms.string(miscFiles['DataL3JetPar']),
    DataResJetPar            = cms.string(miscFiles['DataResJetPar']),

    keepFullMChistory        = cms.bool(True)

)

##################################################################
#
# Input files
#
# NOTE: keep your test inputs in the python files as in
#       this example, and they will be correctly substituted with
#       specified input events when you submit to Condor
#       (
#
#       nEvents and skipEvents are for interactive use, their
#       values will be correctly reset when you submit Condor
#
input_module = 'LJMet.Com.BBB_14TEV_1300_100000_Conf3_11'
process.load(input_module)
process.inputs.nEvents    = cms.int32(-1)
process.inputs.skipEvents = cms.int32(0)



############################################################
#
# JSON
JsonFile = miscFiles['json']
myList   = LumiList.LumiList(filename=JsonFile).getCMSSWString().split(',')
if not condorIsMC:
    process.inputs.lumisToProcess.extend(myList)
        
        
        
#######################################################
#
# Output
#
process.outputs = cms.PSet (
    outputName = cms.string('BBB_14TEV_1300_100000_Conf3_11'),
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
