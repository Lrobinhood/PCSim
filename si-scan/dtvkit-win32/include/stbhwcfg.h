/***************************************************************************
 * Copyright (c) 2014 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description:
 */

#ifndef _STBHWCFG_H_
#define _STBHWCFG_H_

#include "techtype.h"
#include "stbhwtun.h"

typedef struct
{
    int ts_input_idx;
    int frontend_idx;
    int signal_types;
    int support_dvbt2;
    int support_dvbs2;
} stb_tuner_cfg;

#define AML_MAX_TUNER_NUM 8
#define AML_MAX_CAM_NUM 2
#define AML_MAX_DMX_NUM 16

typedef struct
{
    int           is_set_tsout;
    int           is_ciplus_mode;
    int           tsout_source;
    int           is_set_tssource;
    int           camPlug_tssource;
    int           camUnplug_tssource;
    int           is_changeTo_utf8;
    char          encodec_source[16];
    int           dev_id;
    int           host_mode;
} stb_cam_cfg;

typedef struct
{
    int           encrypt;
} stb_pvr_cfg;

typedef struct
{
    int           net_id_max;
    int           orig_net_id_max;
    int           usr_def_orig_net_id;
    int           net_id_change_update;
} stb_network_id_cfg;

typedef struct
{
    int           is_not_match_orignetid;
    int           is_not_match_tsid;
} stb_epg_cfg;

typedef struct
{
    int           sdt_timeout;
    int           pat_timeout;
    int           pmt_timeout;
    int           nit_timeout;
    int           cat_timeout;
    int           bat_timeout;
    int           tot_timeout;
    int           tdt_timeout;
    int           eit_timeout;
} stb_sipsi_timeout;

typedef struct
{
    unsigned char     srate_auto;
    unsigned int     srate_auto_value;
} stb_demo_cap;


typedef enum
{
    SIPSI_PAT = 0,
    SIPSI_PMT,
    SIPSI_SDT,
    SIPSI_NIT,
    SIPSI_CAT,
    SIPSI_BAT,
    SIPSI_TOT,
    SIPSI_TDT,
    SIPSI_EIT
} E_SI_PSI_TYPE;

typedef struct
{
    BOOLEAN analog_enabled;
    BOOLEAN dvbs_enabled;
    BOOLEAN dvbt_enabled;
    BOOLEAN dvbc_enabled;
    BOOLEAN isdbt_enabled;
    char file_path[128];
} S_CAPTURE_ADC_CFG;

typedef struct
{
    stb_tuner_cfg tuners[AML_MAX_TUNER_NUM];
    stb_cam_cfg   cam[AML_MAX_CAM_NUM];
    int dmx_cap[AML_MAX_DMX_NUM];
    int           tuner_num;
    int           demux_num;
    int           recorder_num;
    int           ci_slot_num;
    int           vdec_num;
    int           adec_num;
    int           demux;
    int           cam_num;
    stb_pvr_cfg   pvr;
    char          country_code[3];
    stb_network_id_cfg network;
    stb_sipsi_timeout sipsi;
    stb_demo_cap demo_cap;
    int           service_without_sdt;
    int           resource_manager_by_prio;
    S_CAPTURE_ADC_CFG capture_adc;
    stb_epg_cfg epg_cfg;
} stb_hardware_cfg;

typedef union
{
    struct
    {
        U8BIT symbol_rate_auto;
        U8BIT symbol_rate_value;
    } dvbc;
    struct
    {
        U8BIT unused;
    } dvbt;
} U_STB_DEMO_CAPABILITY;

extern stb_hardware_cfg aml_hw_cfg;

extern void STB_CfgInitialise(void);
extern int STB_Get_IsChangeUtf8(int *isChange, char *encodec_source);

int STB_EpgGetIsNotMatchOrigNetId();

int STB_EpgGetIsNotMatchTsId();

/**
 * @brief   get country code from cfg
 * @param   country code
 */
int STB_Get_Country_Code(char *country_code);

/**
 * @brief   get max value that orig_net_id_max and net_id_max from cfg
 * @param   net_id_max
 * @param   orig_net_id_max
 */
void STB_Get_Max_Network_Id(int            *net_id_max, int *orig_net_id_max);

/**
 * @brief   get user define value about orig_net_id from cfg
 * @return  usr_def_orig_net_id
 */
int STB_Get_Usr_Orig_Net_Id();

/**
 * @brief   get support that network id changed whether auto update channels
 * @return  net_id_change_update
 */
int STB_NetId_Change_Update_Ch();

/**
 * @brief   get si/psi timeout from cfg
 * @return  usr_def_orig_net_id
 */
int STB_Get_SI_PSI_Timeout(E_SI_PSI_TYPE sipsi_type);

/**
 * @brief   get config of whether need to add service without sdt to service list
 * @return  1 if support, 0 otherwise
 */
int STB_Get_Service_WithoutSDT();

/**
 * @brief   get dynamic prop
   @param   name prop name
   @param   buf returned value
   @param   len length of buf
   @return  TRUE if got, FALSE otherwise
 */
BOOLEAN STB_Get_Prop(const char *name, char *buf, int len);

/**
 * @brief   set dynamic prop
   @param   name prop name
   @param   value set value
 */
void STB_Set_Prop(const char *name, const char *value);

/**
 * @brief   Get cam work mode[ci/ciplus]
 * @return  1 for ciplus 0 for ci
 */
int STB_Cam_Is_CIPlus_Mode();

/**
 * @brief   get ca dev id value
 * @param   slot is used for which device is select
 */
int STB_Get_Ca_devid(int slot);

/**
 * @brief   get demo Capability
 * @param   eType demo type
 */
BOOLEAN STB_GetDemoCapabilityByType(E_STB_TUNE_SIGNAL_TYPE eType, U_STB_DEMO_CAPABILITY *pCap);

/**
 * @brief   get config of whether resource mananger is by priority
 * @return  TRUE if yes, FALSE otherwise
 */
BOOLEAN STB_Is_ResourceManager_ByPrio();

/**
 * @brief   get source with and without cam.
 * @return  TRUE if yes.
 */
BOOLEAN STB_GetCamSource(U8BIT *input_with_card, U8BIT *input_without_card);

/**
 * @brief   get config of capture ADC Data
 * @return  S_CAPTURE_ADC_CFG cfg.
 */
S_CAPTURE_ADC_CFG STB_GetCaptureADCCfg();

/**
 * @brief   get cam CI host mode.
 * @return  host mode 2:ask user to confirm, others: no need
 */
int STB_GetCIHostMode(void);

#endif
