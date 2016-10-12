#ifndef _SERDES_LIB_H_
#define _SERDES_LIB_H_

typedef enum hilink0_mode_type {
  EM_HILINK0_HCCS1_8LANE = 0,
  EM_HILINK0_PCIE1_8LANE = 2,
  EM_HILINK0_PCIE1_4LANE_PCIE2_4LANE = 3,
  EM_HILINK0_SAS2_8LANE = 4,
  EM_HILINK0_HCCS1_8LANE_16,
  EM_HILINK0_HCCS1_8LANE_32,
  EM_HILINK0_HCCS1_8LANE_5000,
} hilink0_mode_type_e;

typedef enum hilink1_mode_type {
  EM_HILINK1_SAS2_1LANE = 0,
  EM_HILINK1_HCCS0_8LANE = 1,
  EM_HILINK1_PCIE0_8LANE = 2,
  EM_HILINK1_HCCS0_8LANE_16,
  EM_HILINK1_HCCS0_8LANE_32,
  EM_HILINK1_HCCS0_8LANE_5000,
} hilink1_mode_type_e;

typedef enum hilink2_mode_type {
  EM_HILINK2_PCIE2_8LANE = 0,
  EM_HILINK2_HCCS2_8LANE = 1,
  EM_HILINK2_SAS0_8LANE = 2,
  EM_HILINK2_HCCS2_8LANE_16,
  EM_HILINK2_HCCS2_8LANE_32,
  EM_HILINK2_HCCS2_8LANE_5000,
} hilink2_mode_type_e;

typedef enum hilink5_mode_type {
  EM_HILINK5_PCIE3_4LANE = 0,
  EM_HILINK5_PCIE2_2LANE_PCIE3_2LANE = 1,
  EM_HILINK5_SAS1_4LANE = 2,
} hilink5_mode_type_e;


typedef struct serdes_param {
  hilink0_mode_type_e hilink0_mode;
  hilink1_mode_type_e hilink1_mode;
  hilink2_mode_type_e hilink2_mode;
  UINT32 hilink3_mode;
  UINT32 hilink4_mode;
  hilink5_mode_type_e hilink5_mode;
  UINT32 hilink6_mode;
  UINT32 use_ssc;
} serdes_param_t;

#define SERDES_INVALID_MACRO_ID  0xFFFFFFFF
#define SERDES_INVALID_LANE_NUM  0xFFFFFFFF
#define SERDES_INVALID_RATE_MODE  0xFFFFFFFF

typedef struct {
  UINT32 MacroId;
  UINT32 DsNum;
  UINT32 DsCfg;
} SERDES_POLARITY_INVERT;

EFI_STATUS OemGetSerdesParam (serdes_param_t *ParamA, serdes_param_t *ParamB, UINT32 SocketId);
extern SERDES_POLARITY_INVERT gSerdesPolarityTxDesc[];
extern SERDES_POLARITY_INVERT gSerdesPolarityRxDesc[];
UINT32 GetEthType(UINT8 EthChannel);
VOID SerdesEnableCtleDfe(UINT32 NimbusId, UINT32 Macro, UINT32 Lane, UINT32 LaneMode);

EFI_STATUS
EfiSerdesInitWrap (VOID);
INT32 SerdesReset(UINT32 SiclId, UINT32 Macro);
VOID SerdesLoadFirmware(UINT32 SiclId, UINT32 Macro);

#endif
