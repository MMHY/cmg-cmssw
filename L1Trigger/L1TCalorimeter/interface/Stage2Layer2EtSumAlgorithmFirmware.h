///
/// Description: Firmware headers
///
/// Implementation:
///    Concrete firmware implementations
///
/// \author: Jim Brooke - University of Bristol
///

//
//

#ifndef Stage2Layer2EtSumAlgorithmFirmware_H
#define Stage2Layer2EtSumAlgorithmFirmware_H

#include "L1Trigger/L1TCalorimeter/interface/Stage2Layer2EtSumAlgorithm.h"
#include "L1Trigger/L1TCalorimeter/interface/CaloParamsHelper.h"

namespace l1t {

  // Imp1 is for v1 and v2
  class Stage2Layer2EtSumAlgorithmFirmwareImp1 : public Stage2Layer2EtSumAlgorithm {
  public:
    Stage2Layer2EtSumAlgorithmFirmwareImp1(CaloParamsHelper* params);
    virtual ~Stage2Layer2EtSumAlgorithmFirmwareImp1();
    virtual void processEvent(const std::vector<l1t::CaloTower> & towers,
			      std::vector<l1t::EtSum> & sums);
  private:
    CaloParamsHelper* params_;
    int32_t etSumEtThresholdHwEt_;
    int32_t etSumEtThresholdHwMet_;
    int32_t etSumEtaMinEt_;
    int32_t etSumEtaMaxEt_;
    int32_t etSumEtaMinMet_;
    int32_t etSumEtaMaxMet_;

  };

}

#endif
