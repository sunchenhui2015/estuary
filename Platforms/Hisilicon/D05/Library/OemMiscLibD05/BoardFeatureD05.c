/** @file
*
*  Copyright (c) 2016, Hisilicon Limited. All rights reserved.
*  Copyright (c) 2016, Linaro Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include <PlatformArch.h>
#include <Uefi.h>
#include <IndustryStandard/SmBios.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HiiLib.h>
#include <Library/I2CLib.h>
#include <Library/IoLib.h>
#include <Library/OemMiscLib.h>
#include <Library/SerdesLib.h>
#include <Protocol/Smbios.h>


I2C_DEVICE gDS3231RtcDevice = {
  .Socket = 0,
  .Port = 4,
  .DeviceType = DEVICE_TYPE_SPD,
  .SlaveDeviceAddress = 0x68
};

SERDES_POLARITY_INVERT gSerdesPolarityTxDesc[] = {
  {SERDES_INVALID_MACRO_ID, SERDES_INVALID_LANE_NUM}
};

SERDES_POLARITY_INVERT gSerdesPolarityRxDesc[] = {
  {SERDES_INVALID_MACRO_ID, SERDES_INVALID_LANE_NUM}
};

serdes_param_t gSerdesParamNA = {
  .hilink0_mode = EM_HILINK0_HCCS1_8LANE_16,
  .hilink1_mode = EM_HILINK1_HCCS0_8LANE_16,
  .hilink2_mode = EM_HILINK2_PCIE2_8LANE,
  .hilink3_mode = 0x0,
  .hilink4_mode = 0xF,
  .hilink5_mode = EM_HILINK5_SAS1_4LANE,
  .hilink6_mode = 0x0,
  .use_ssc      = 0,
};

serdes_param_t gSerdesParamNB = {
  .hilink0_mode = EM_HILINK0_PCIE1_8LANE,
  .hilink1_mode = EM_HILINK1_PCIE0_8LANE,
  .hilink2_mode = EM_HILINK2_SAS0_8LANE,
  .hilink3_mode = 0x0,
  .hilink4_mode = 0xF,
  .hilink5_mode = EM_HILINK5_PCIE2_2LANE_PCIE3_2LANE,
  .hilink6_mode = 0xF,
  .use_ssc      = 0,
};

serdes_param_t gSerdesParamS1NA = {
  .hilink0_mode = EM_HILINK0_HCCS1_8LANE_16,
  .hilink1_mode = EM_HILINK1_HCCS0_8LANE_16,
  .hilink2_mode = EM_HILINK2_PCIE2_8LANE,
  .hilink3_mode = 0x0,
  .hilink4_mode = 0xF,
  .hilink5_mode = EM_HILINK5_SAS1_4LANE,
  .hilink6_mode = 0x0,
  .use_ssc      = 0,
};

serdes_param_t gSerdesParamS1NB = {
  .hilink0_mode = EM_HILINK0_PCIE1_8LANE,
  .hilink1_mode = EM_HILINK1_PCIE0_8LANE,
  .hilink2_mode = EM_HILINK2_SAS0_8LANE,
  .hilink3_mode = 0x0,
  .hilink4_mode = 0xF,
  .hilink5_mode = EM_HILINK5_PCIE2_2LANE_PCIE3_2LANE,
  .hilink6_mode = 0xF,
  .use_ssc      = 0,
};


EFI_STATUS
OemGetSerdesParam (
 OUT serdes_param_t *ParamA,
 OUT serdes_param_t *ParamB,
 IN  UINT32 SocketId
 )
{
  if (ParamA == NULL || ParamB == NULL) {
    DEBUG((DEBUG_ERROR, "[%a]:[%dL] Param == NULL!\n", __FUNCTION__, __LINE__));
    return EFI_INVALID_PARAMETER;
  }

  if (SocketId == 0) {
    (VOID) CopyMem(ParamA, &gSerdesParamNA, sizeof(*ParamA));
    (VOID) CopyMem(ParamB, &gSerdesParamNB, sizeof(*ParamB));
  } else {
    (VOID) CopyMem(ParamA, &gSerdesParamS1NA, sizeof(*ParamA));
    (VOID) CopyMem(ParamB, &gSerdesParamS1NB, sizeof(*ParamB));
  }

  return EFI_SUCCESS;
}

VOID
OemPcieResetAndOffReset (
  VOID
  )
{
  return;
}

SMBIOS_TABLE_TYPE9 gPcieSlotInfo[] = {
  // PCIe0 Slot 1
  {
    {                                                     // Hdr
      EFI_SMBIOS_TYPE_SYSTEM_SLOTS,                       // Type,
      0,                                                  // Length,
      0                                                   // Handle
    },
    1,                                                    // SlotDesignation
    SlotTypePciExpressX8,     // SlotType
    SlotDataBusWidth8X,       // SlotDataBusWidth
    SlotUsageAvailable,       // SlotUsage
    SlotLengthOther,          // SlotLength
    0x0001,                   // SlotId
    {                         // SlotCharacteristics1
      0,                      // CharacteristicsUnknown  :1;
      0,                      // Provides50Volts         :1;
      0,                      // Provides33Volts         :1;
      0,                      // SharedSlot              :1;
      0,                      // PcCard16Supported       :1;
      0,                      // CardBusSupported        :1;
      0,                      // ZoomVideoSupported      :1;
      0                       // ModemRingResumeSupported:1;
    },
    {                         // SlotCharacteristics2
      0,                      // PmeSignalSupported      :1;
      0,                      // HotPlugDevicesSupported  :1;
      0,                      // SmbusSignalSupported    :1;
      0                       // Reserved                :5;
    },
    0x00,                     // SegmentGroupNum
    0x00,                     // BusNum
    0                         // DevFuncNum
  },

  // PCIe0 Slot 4
  {
    {                                                  // Hdr
      EFI_SMBIOS_TYPE_SYSTEM_SLOTS,                    // Type,
      0,                                               // Length,
      0                                                // Handle
    },
    1,                                                 // SlotDesignation
    SlotTypePciExpressX8,     // SlotType
    SlotDataBusWidth8X,       // SlotDataBusWidth
    SlotUsageAvailable,       // SlotUsage
    SlotLengthOther,          // SlotLength
    0x0004,                   // SlotId
    {                         // SlotCharacteristics1
      0,                      // CharacteristicsUnknown  :1;
      0,                      // Provides50Volts         :1;
      0,                      // Provides33Volts         :1;
      0,                      // SharedSlot              :1;
      0,                      // PcCard16Supported       :1;
      0,                      // CardBusSupported        :1;
      0,                      // ZoomVideoSupported      :1;
      0                       // ModemRingResumeSupported:1;
    },
    {                         // SlotCharacteristics2
      0,                      // PmeSignalSupported      :1;
      0,                      // HotPlugDevicesSupported  :1;
      0,                      // SmbusSignalSupported    :1;
      0                       // Reserved                :5;
    },
    0x00,                     // SegmentGroupNum
    0x00,                     // BusNum
    0                         // DevFuncNum
  }
};


UINT8
OemGetPcieSlotNumber (
  VOID
  )
{
  return  sizeof (gPcieSlotInfo) / sizeof (SMBIOS_TABLE_TYPE9);
}

EFI_STRING_ID gDimmToDevLocator[MAX_SOCKET][MAX_CHANNEL][MAX_DIMM] = {
  {{STRING_TOKEN(STR_LEMON_C10_DIMM_000), STRING_TOKEN(STR_LEMON_C10_DIMM_001), STRING_TOKEN(STR_LEMON_C10_DIMM_002)},
   {STRING_TOKEN(STR_LEMON_C10_DIMM_010), STRING_TOKEN(STR_LEMON_C10_DIMM_011), STRING_TOKEN(STR_LEMON_C10_DIMM_012)},
   {STRING_TOKEN(STR_LEMON_C10_DIMM_020), STRING_TOKEN(STR_LEMON_C10_DIMM_021), STRING_TOKEN(STR_LEMON_C10_DIMM_022)},
   {STRING_TOKEN(STR_LEMON_C10_DIMM_030), STRING_TOKEN(STR_LEMON_C10_DIMM_031), STRING_TOKEN(STR_LEMON_C10_DIMM_032)}},

  {{STRING_TOKEN(STR_LEMON_C10_DIMM_100), STRING_TOKEN(STR_LEMON_C10_DIMM_101), STRING_TOKEN(STR_LEMON_C10_DIMM_102)},
   {STRING_TOKEN(STR_LEMON_C10_DIMM_110), STRING_TOKEN(STR_LEMON_C10_DIMM_111), STRING_TOKEN(STR_LEMON_C10_DIMM_112)},
   {STRING_TOKEN(STR_LEMON_C10_DIMM_120), STRING_TOKEN(STR_LEMON_C10_DIMM_121), STRING_TOKEN(STR_LEMON_C10_DIMM_122)},
   {STRING_TOKEN(STR_LEMON_C10_DIMM_130), STRING_TOKEN(STR_LEMON_C10_DIMM_131), STRING_TOKEN(STR_LEMON_C10_DIMM_132)}}
};

EFI_HII_HANDLE
EFIAPI
OemGetPackages (
  )
{
  return HiiAddPackages (
                        &gEfiCallerIdGuid,
                        NULL,
                        OemMiscLibHi1616EvbStrings,
                        NULL,
                        NULL
                        );
}


