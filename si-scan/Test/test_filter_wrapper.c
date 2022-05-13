#include <techtype.h>
#include <dbgfuncs.h>


#include "stbhwc.h"
#include "stbheap.h"
#include "stbuni.h"

#include "stbsiflt.h"
#include "stbdpc.h"
#include "stbsitab.h"
#include "ap_si.h"

#include "cert_sitbl.h"
#include "cert_sitbl_sgt.h"


#include "FilterForDtvkitWrapper.h"

#include "test_filter_wrapper.h"


#include "cert_log.h"

#define TAG "TEST-FILTER-WRAPPER"

//extern void TEST_DPSetSiganlType(U8BIT path, E_STB_DP_SIGNAL_TYPE type);

static void *sgp_Filter = NULL;

static U8BIT sg_exit_flag = 0;

// B: Local function declare
static void Init_Test_Filter_Wrapper();

static void pid_flt_cb( U8BIT path, U16BIT bytes, U16BIT pfilt_id);

static void ReceiveNitTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec);
static void cert_Show_NitTable(SI_NIT_TABLE *nit_tbl_ptr);
static void cert_Show_NitTable_Linkage(SI_LINKAGE_DESC_ENTRY *link_des_ptr);
static void cert_Show_NitTable_Transport(SI_NIT_TRANSPORT_ENTRY *transport_ptr);
static void cert_Show_NitTable_Delivery_Des(SI_DELIVERY_SYS_DESC_TYPE delivery_type, SI_DELIVERY_SYS_DESC *delivery_des_ptr);

static void ReceiveSgtTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec);


// E: Local function declare

void Test_Wrapper_PidFilter()
{
    U16BIT pidflt = 0;

    Wrapper_DMXInitialise(0, 1);
    Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-730\\HD_muxB_001.trp");

    pidflt = Wrapper_DMXGrabPIDFilter(0, 0x10, pid_flt_cb);

    Wrapper_DMXStartPIDFilter(0,  pidflt);

    Wrapper_StartTsLoop(0);

    Wrapper_DMXReleasePIDFilter(0, pidflt);

}



void Test_Wrapper_SecFilter()
{
    U16BIT pidflt = 0;
    U16BIT secflt = 0;

    U8BIT match[8];
    U8BIT mask[8];


    Wrapper_DMXInitialise(0, 1);
    Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\Germany Operators\\HD+\\8669-728\\HD_muxA_001.trp");

    pidflt = Wrapper_DMXGrabPIDFilter(0, 0x11, pid_flt_cb);

    secflt = Wrapper_DMXGrabSectFilter(0, pidflt);

    // table id
    match[0] = 0x46;
    match[1] = 0x04;
    match[2] = 0x57;

    mask[0] = 0xff;
    mask[1] = 0xff;
    mask[2] = 0xff;

    Wrapper_DMXSetupSectFilter(0, secflt, match, mask, 0, FALSE);

    Wrapper_DMXStartPIDFilter(0,  pidflt);

    Wrapper_EnableTsLoop();
    Wrapper_StartTsLoop(0);
    Wrapper_DisableTsLoop();
    
    Wrapper_DMXReleaseSectFilter(0, secflt);
    Wrapper_DMXReleasePIDFilter(0, pidflt);

}


void Test_Wrapper_FilterNIT()
{
    void *pFilter = NULL;

    Init_Test_Filter_Wrapper();

    Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-730\\HD_muxB_010.trp");

    sgp_Filter = STB_SIRequestNit(0, ONE_SHOT_REQUEST, ReceiveNitTable, APP_SI_NIT_RECEIVED);

    STB_DPSetSignalType(0, SIGNAL_QPSK);

    Wrapper_EnableTsLoop();
    Wrapper_StartTsLoop(0);
    Wrapper_DisableTsLoop();

    while (1 != sg_exit_flag)
    {
        ;
    }

    sg_exit_flag = 0;

    STB_SICancelTableRequest(sgp_Filter);
    sgp_Filter = NULL;
}


void Test_Wrapper_FilterSGT()
{
    void *pFilter = NULL;

    Init_Test_Filter_Wrapper();

    Wrapper_SetTsSource(0, "D:\\StreamSparkTS\\8669-730\\HD_muxB_010.trp");

    sgp_Filter = cert_STB_SIRequestSgt(0, ONE_SHOT_REQUEST, 0x776/*sg_SGT_Pid*/, SI_XTID_MATCH_DONT_CARE, SI_XTID_MASK_DONT_CARE,
                                       ReceiveSgtTable, APP_SI_SGT_RECEIVED);

    STB_DPSetSignalType(0, SIGNAL_QPSK);

    Wrapper_EnableTsLoop();
    Wrapper_StartTsLoop(0);
    Wrapper_DisableTsLoop();

    //UT_PidFilter_2_SectionFilter_Parser("D:\\StreamSparkTS\\8669-731\\HD_muxB_001.trp", 0x0010, 0x0040, ParserFun);

    while (1 != sg_exit_flag)
    {
        ;
    }

    sg_exit_flag = 0;

    STB_SICancelTableRequest(sgp_Filter);
    sgp_Filter = NULL;
}


// B: Local function define
static void Init_Test_Filter_Wrapper()
{
    static U8BIT init_flag = 0;

    if (0 == init_flag)
    {
        STB_SITerrInitialise();

        Wrapper_DMXInitialise(0, 1);

    }

}

static void pid_flt_cb( U8BIT path, U16BIT bytes, U16BIT pfilt_id)
{
    U8BIT buffer[4096];
    
    Wrapper_DMXCopyPIDFilterSect(path, buffer, bytes, pfilt_id);

    for (int i = 0; i < 16; i++)
    {
        CERT_LOG_INFO(TAG, "[%s] Line[%u]: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x", __FUNCTION__, i,
                     buffer[i*16], buffer[i*16 + 1], buffer[i*16 + 2], buffer[i*16 + 3],
                     buffer[i*16 + 4], buffer[i*16 + 5], buffer[i*16 + 6], buffer[i*16 + 7],
                     buffer[i*16 + 8], buffer[i*16 + 9], buffer[i*16 + 10], buffer[i*16 + 11],
                     buffer[i*16 + 12], buffer[i*16 + 13], buffer[i*16 + 14], buffer[i*16 + 15]);

    }
}

static void ReceiveNitTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec)
{
    SI_NIT_TABLE *nit_tbl_ptr = NULL;

    Wrapper_DisableTsLoop();

    CERT_LOG_INFO(TAG, "[%s] B: Parser Nit Table", __FUNCTION__);

    nit_tbl_ptr = STB_SIParseNitTable(0, table_rec);

    cert_Show_NitTable(nit_tbl_ptr);

    STB_SIReleaseNitTable(nit_tbl_ptr);

    CERT_LOG_INFO(TAG, "[%s] E: Parser Nit Table", __FUNCTION__);

    sg_exit_flag = 1;
}

/*

typedef struct si_nit_table
{
   U8BIT version;
   U16BIT net_id;
   SI_STRING_DESC *name_str;
   U16BIT num_multiling_net_names;
   SI_MULTILING_NET_NAME_DESC *multiling_net_name_desc_array;
   U16BIT num_linkage_entries;
   SI_LINKAGE_DESC_ENTRY *linkage_desc_list;
   SI_LINKAGE_DESC_ENTRY *last_linkage_entry;
   SI_STRING_DESC *def_authority;
   U16BIT num_transports;
   SI_NIT_TRANSPORT_ENTRY *transport_list;
   SI_NIT_TRANSPORT_ENTRY *last_transport_entry;
   U16BIT num_change_notifies;
   SI_NIT_CHANGE_NOTIFY_DESC *change_notify_array;
   U16BIT num_messages;
   SI_NIT_MESSAGE_ENTRY *message_array;
   SI_FTA_CONTENT_DESC *fta_content_desc;
   SI_NIT_TARGET_REGION_NAME_DESC *target_region_name_list;
   SI_TARGET_REGION_DESC *target_region_list;
   SI_FREESAT_LINKAGE_DESC *freesat_linkage_desc;
   SI_FREESAT_PREFIX_DESC *freesat_prefix_list;
   SI_URI_LINKAGE_DESC *uri_linkage_list;
} SI_NIT_TABLE;

*/
static void cert_Show_NitTable(SI_NIT_TABLE *nit_tbl_ptr)
{
    U32BIT i = 0;

    ASSERT(NULL != nit_tbl_ptr);

    CERT_LOG_INFO(TAG, "[%s] Begin <<<", __FUNCTION__);

    //Base Info
    CERT_LOG_INFO(TAG, "version:%u", nit_tbl_ptr->version);
    CERT_LOG_INFO(TAG, "net_id:0x%x", nit_tbl_ptr->net_id);
    CERT_LOG_INFO(TAG, "name:%s", (nit_tbl_ptr->name_str->str_ptr == NULL) ? "None" : nit_tbl_ptr->name_str->str_ptr);

    // SI_MULTILING_NET_NAME_DESC
    // To be done ...

    // SI_LINKAGE_DESC_ENTRY
    cert_Show_NitTable_Linkage(nit_tbl_ptr->linkage_desc_list);

    // SI_NIT_TRANSPORT_ENTRY
    cert_Show_NitTable_Transport(nit_tbl_ptr->transport_list);

    CERT_LOG_INFO(TAG, "[%s] END >>>", __FUNCTION__);
}

/*
typedef struct si_linkage_desc
{
   struct si_linkage_desc *next;
   U32BIT private_data_code;
   U16BIT orig_net_id;
   U16BIT tran_id;
   U16BIT serv_id;
   U8BIT link_type;
   U8BIT data_length;
   U8BIT data;
} SI_LINKAGE_DESC_ENTRY;
*/
static void cert_Show_NitTable_Linkage(SI_LINKAGE_DESC_ENTRY *link_des_ptr)
{
    U32BIT i = 0;
    U32BIT j = 0;

    U8BIT *buf = NULL;
    U8BIT a[6];

    SI_LINKAGE_DESC_ENTRY *tmp_link_ptr = link_des_ptr;

    CERT_LOG_INFO(TAG, "[%s] Begin <<<", __FUNCTION__);

    while (NULL != link_des_ptr)
    {
        i++;

        CERT_LOG_INFO(TAG, "Link[%u] priv_code:0x%x, onid:0x%x, tsid:0x%x, srid:0x%x, type:0x%x",
                           i,
                           link_des_ptr->private_data_code,
                           link_des_ptr->orig_net_id,
                           link_des_ptr->tran_id,
                           link_des_ptr->serv_id,
                           link_des_ptr->link_type);

        CERT_LOG_INFO(TAG, "data_len: %u", link_des_ptr->data_length);

        if (0 != link_des_ptr->data_length)
        {
            buf = STB_GetMemory(6 * link_des_ptr->data_length + 1);
            if (NULL != buf)
            {
                memset(buf, 0, (6 * link_des_ptr->data_length + 1));

                for (j = 0; j < link_des_ptr->data_length; j++)
                {
                    sprintf(a,"0x%x ", *((U8BIT *)(&link_des_ptr->data + j)));
                    strcat(buf, a);
                }

                CERT_LOG_INFO(TAG, "data:%s", buf);
            }

            STB_FreeMemory(buf);
        }

        link_des_ptr = link_des_ptr->next;
    }

    CERT_LOG_INFO(TAG, "[%s] End >>>", __FUNCTION__);
}


/*
typedef struct si_nit_transport_entry
{
   struct si_nit_transport_entry *next;
   U16BIT tran_id;
   U16BIT orig_net_id;
   SI_DELIVERY_SYS_DESC_TYPE del_sys_desc_type;
   SI_DELIVERY_SYS_DESC *del_sys_desc;
   U16BIT num_freq_list_entries;
   U32BIT *freq_list_desc_array;
   U16BIT num_serv_list_entries;
   SI_SERV_LIST_DESC *serv_list_desc_array;
   U16BIT num_lcn_entries;
   SI_LCN_DESC *lcn_desc_array;
   SI_STRING_DESC *def_authority;
   U16BIT num_serv_attr_entries;
   SI_SERV_ATTRIBUTE_DESC *serv_attr_array;
   U16BIT num_nordig_lcn_entries;
   SI_NORDIG_LCN_DESC *nordig_lcn_desc_array;
   U16BIT num_hd_lcn_entries;
   SI_LCN_DESC *hd_lcn_desc_array;
   SI_FTA_CONTENT_DESC *fta_content_desc;
   SI_TARGET_REGION_DESC *target_region_list;
   U16BIT num_ciplus_services;
   SI_CIPLUS_SERVICE *ciplus_service_list;
   SI_CIPLUS_SERVICE *last_ciplus_service;
} SI_NIT_TRANSPORT_ENTRY;
*/
static void cert_Show_NitTable_Transport(SI_NIT_TRANSPORT_ENTRY *transport_ptr)
{
    U32BIT i = 0;

    CERT_LOG_INFO(TAG, "[%s] Begin <<<", __FUNCTION__);

    while (NULL != transport_ptr)
    {
        i++;

        CERT_LOG_INFO(TAG, "Tranport[%u]: tsid:0x%x, onid:0x%x, delivery_type:%u",
                            i, transport_ptr->tran_id, transport_ptr->orig_net_id, transport_ptr->del_sys_desc_type);

        // SI_DELIVERY_SYS_DESC_TYPE, SI_DELIVERY_SYS_DESC
        cert_Show_NitTable_Delivery_Des(transport_ptr->del_sys_desc_type, transport_ptr->del_sys_desc);

        transport_ptr = transport_ptr->next;
    }

    CERT_LOG_INFO(TAG, "[%s] End >>>", __FUNCTION__);
}



static void cert_Show_NitTable_Delivery_Des(SI_DELIVERY_SYS_DESC_TYPE delivery_type, SI_DELIVERY_SYS_DESC *delivery_des_ptr)
{
    U32BIT i = 0;
    SI_T2_DEL_SYS_CELL *t2_cell_ptr = NULL;


    if (NULL == delivery_des_ptr)
    {
        //CERT_LOG_INFO(TAG, "delivery_des_ptr is NULL");

        return;
    }

    CERT_LOG_INFO(TAG, "delivery_type: %u", delivery_type);

    switch (delivery_type)
    {
        case SI_DEL_SYS_DESC_TYPE_TERR:
            if (delivery_des_ptr->terr.is_t2)
            {
                CERT_LOG_INFO(TAG, "[T2] plp_id:%u, t2_system_id:%u, bwidth:%u, mode:%u, num_cells:%u",
                                    delivery_des_ptr->terr.u.t2.plp_id,
                                     delivery_des_ptr->terr.u.t2.t2_system_id,
                                      delivery_des_ptr->terr.u.t2.bwidth,
                                       delivery_des_ptr->terr.u.t2.mode,
                                        delivery_des_ptr->terr.u.t2.num_cells);

                for (i = 0; i < delivery_des_ptr->terr.u.t2.num_cells; i++)
                {
                    t2_cell_ptr = delivery_des_ptr->terr.u.t2.cell + i;

                    CERT_LOG_INFO(TAG,  "T2 Cell[%u] cell_id:%u, num_freqs:%u [%u, %u, %u, %u, %u, %u]",
                                        i + 1,
                                        t2_cell_ptr->cell_id, t2_cell_ptr->num_freqs,
                                        t2_cell_ptr->freq_hz[0],
                                        t2_cell_ptr->freq_hz[1],
                                        t2_cell_ptr->freq_hz[2],
                                        t2_cell_ptr->freq_hz[3],
                                        t2_cell_ptr->freq_hz[4],
                                        t2_cell_ptr->freq_hz[5]);
                }
            }
            else
            {
                CERT_LOG_INFO(TAG, "[T] freq_hz:%u, bwidth:%u, mode:%u",
                                    delivery_des_ptr->terr.u.t1.freq_hz,
                                    delivery_des_ptr->terr.u.t1.bwidth,
                                    delivery_des_ptr->terr.u.t1.mode);

            }

            break;

        case SI_DEL_SYS_DESC_TYPE_SAT:
                 CERT_LOG_INFO(TAG, "[S] freq_hz:%u, pos:%u, srate:%u, polar:%u, ew:%u, fec:%u, s2:%u, modu:%u",
                                        delivery_des_ptr->sat.freq_hz,
                                        delivery_des_ptr->sat.position,
                                        delivery_des_ptr->sat.sym_rate,
                                        delivery_des_ptr->sat.polarity,
                                        delivery_des_ptr->sat.east_west,
                                        delivery_des_ptr->sat.fec_code,
                                        delivery_des_ptr->sat.dvb_s2,
                                        delivery_des_ptr->sat.modulation);

            break;

        case SI_DEL_SYS_DESC_TYPE_CABLE:
                CERT_LOG_INFO(TAG, "To be done ...");

            break;

        default:
            CERT_LOG_INFO(TAG, "Unknow delivery type!");

            break;
    }

}



static void ReceiveSgtTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec)
{
    SI_SGT_TABLE *sgt_tbl_ptr = NULL;

    Wrapper_DisableTsLoop();

    CERT_LOG_INFO(TAG, "[%s] B: Parser Sgt Table", __FUNCTION__);

    sgt_tbl_ptr = cert_STB_SIParseSgtTable(table_rec);

    cert_Show_SgtTable(sgt_tbl_ptr);

    cert_Free_SgtTable(sgt_tbl_ptr);

    CERT_LOG_INFO(TAG, "[%s] E: Parser Sgt Table", __FUNCTION__);

    sg_exit_flag = 1;
}



// E: Local function define

