import FWCore.ParameterSet.Config as cms

from DQMOffline.Ecal.ecal_dqm_source_offline_cff import *
from DQM.HcalMonitorModule.hcal_dqm_source_fileT0_cff import *
from DQMOffline.Trigger.DQMOffline_Trigger_cff import *
from DQM.SiStripMonitorClient.SiStripSourceConfigTier0_cff import *
from DQM.SiPixelCommon.SiPixelOfflineDQM_source_cff import *
from DQM.DTMonitorModule.dtDQMOfflineSources_cff import *
from DQM.RPCMonitorClient.RPCTier0Source_cff import *
from DQM.CSCMonitorModule.csc_dqm_sourceclient_offline_cff import *
from DQM.EcalPreshowerMonitorModule.es_dqm_source_offline_cff import *

DQMOfflineDPG = cms.Sequence( ecal_dqm_source_offline *
                              hcalOfflineDQMSource *
                              triggerOfflineDQMSource *
                              SiStripDQMTier0 *
                              siPixelOfflineDQM_source *
                              dtSources *
                              rpcTier0Source *
                              cscSources *
                              es_dqm_source_offline )

from DQMOffline.Muon.muonMonitors_cff import *
from DQMOffline.JetMET.jetMETDQMOfflineSource_cff import *
from DQMOffline.EGamma.egammaDQMOffline_cff import *
from DQMOffline.RecoB.PrimaryVertexMonitor_cff import *
from DQMOffline.RecoB.dqmAnalyzer_cff import *
from DQM.Physics.DQMPhysics_cff import *

DQMOfflinePOG = cms.Sequence( muonMonitors *
                              jetMETDQMOfflineSource *
                              egammaDQMOffline *
                              pvMonitor *
                              bTagPlots *
                              dqmPhysics )

DQMOffline = cms.Sequence( DQMOfflineDPG * DQMOfflinePOG )

