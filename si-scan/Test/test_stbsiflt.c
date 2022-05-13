/*******************************************************************************
 *  Copyright @ 2020
 *
 *  Functions for cert si sgt table filt & parse
 *
 *
 *******************************************************************************/

/**
 * @brief   Functions for cert si sgt table filt & parse
 * @file    cert_sitbl_sgt.h
 * @date    2021-01-22
 */





#include <stdio.h>
#include <string.h>
#include <conio.h>

// third party header files

// Ocean Blue Software header files

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

#include "FilterWrapper.h"



// CERT Module header files
#include "cert_log.h"

#define TAG "TEST_STBSIFLT"

static U8BIT sgt_sec_0[] =
{
    0x91, 0xf1, 0x0f, 0x00, 0x01, 0xc3, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x6c, 0x5f, 0x04, 0x00, 0x00,
    0x00, 0x01, 0x88, 0x17, 0x65, 0x6e, 0x67, 0x43, 0x68, 0x61, 0x6e, 0x6e, 0x65, 0x6c, 0x20, 0x4c,
    0x69, 0x73, 0x74, 0x20, 0x47, 0x65, 0x72, 0x6d, 0x61, 0x6e, 0x79, 0x88, 0x1e, 0x66, 0x72, 0x65,
    0x4c, 0x69, 0x73, 0x74, 0x65, 0x20, 0x64, 0x65, 0x73, 0x20, 0x43, 0x68, 0x61, 0x69, 0x6e, 0x65,
    0x73, 0x20, 0x41, 0x6c, 0x6c, 0x65, 0x6d, 0x61, 0x67, 0x6e, 0x65, 0x88, 0x19, 0x64, 0x65, 0x75,
    0x4b, 0x61, 0x6e, 0x61, 0x6c, 0x6c, 0x69, 0x73, 0x74, 0x65, 0x20, 0x44, 0x65, 0x75, 0x74, 0x73,
    0x63, 0x68, 0x6c, 0x61, 0x6e, 0x64, 0x49, 0x04, 0x7f, 0x41, 0x55, 0x54, 0x49, 0x04, 0x7f, 0x43,
    0x48, 0x45, 0x49, 0x04, 0xff, 0x44, 0x45, 0x55, 0xf0, 0x94, 0x00, 0x07, 0x04, 0x57, 0x00, 0x01,
    0x01, 0x92, 0x00, 0x00, 0xf0, 0x3e, 0x48, 0x1f, 0x19, 0x10, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6d,
    0x53, 0x70, 0x61, 0x72, 0x6b, 0x20, 0x54, 0x65, 0x73, 0x74, 0x0c, 0x6d, 0x75, 0x78, 0x42, 0x5f,
    0x54, 0x56, 0x5f, 0x48, 0x44, 0x5f, 0x31, 0x5f, 0x04, 0x00, 0x00, 0x00, 0x01, 0x93, 0x11, 0x10,
    0x53, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x53, 0x70, 0x61, 0x72, 0x6b, 0x20, 0x4c, 0x69, 0x73, 0x74,
    0xd1, 0x02, 0x03, 0xea, 0x00, 0x05, 0x04, 0x57, 0x00, 0x01, 0x0f, 0x9e, 0x00, 0x00, 0xf0, 0x3e,
    0x48, 0x1f, 0x01, 0x10, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x53, 0x70, 0x61, 0x72, 0x6b, 0x20,
    0x54, 0x65, 0x73, 0x74, 0x0c, 0x6d, 0x75, 0x78, 0x42, 0x5f, 0x54, 0x56, 0x5f, 0x53, 0x44, 0x5f,
    0x31, 0x5f, 0x04, 0x00, 0x00, 0x00, 0x01, 0x93, 0x11, 0x10, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6d,
    0x53, 0x70, 0x61, 0x72, 0x6b, 0x20, 0x4c, 0x69, 0x73, 0x74, 0xd1, 0x02, 0x07, 0xd2, 0x05, 0x61,
    0xd5, 0xf9
};

static U8BIT sgt_sec_1[] =
{
    0x91, 0xf0, 0xd6, 0x00, 0x01, 0xc3, 0x01, 0x01, 0xff, 0xff, 0xf0, 0x00, 0xf0, 0xc7, 0x00, 0x06,
    0x04, 0x57, 0x00, 0x01, 0x1f, 0x42, 0x00, 0x00, 0xf0, 0x3e, 0x48, 0x1f, 0x16, 0x10, 0x53, 0x74,
    0x72, 0x65, 0x61, 0x6d, 0x53, 0x70, 0x61, 0x72, 0x6b, 0x20, 0x54, 0x65, 0x73, 0x74, 0x0c, 0x6d,
    0x75, 0x78, 0x42, 0x5f, 0x54, 0x56, 0x5f, 0x53, 0x44, 0x5f, 0x32, 0x5f, 0x04, 0x00, 0x00, 0x00,
    0x01, 0x93, 0x11, 0x10, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x53, 0x70, 0x61, 0x72, 0x6b, 0x20,
    0x4c, 0x69, 0x73, 0x74, 0xd1, 0x02, 0x07, 0xd4, 0x00, 0x08, 0x04, 0x57, 0x00, 0x01, 0x27, 0x12,
    0x00, 0x00, 0xf0, 0x3e, 0x48, 0x1f, 0x0a, 0x10, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x53, 0x70,
    0x61, 0x72, 0x6b, 0x20, 0x54, 0x65, 0x73, 0x74, 0x0c, 0x6d, 0x75, 0x78, 0x42, 0x5f, 0x52, 0x61,
    0x64, 0x69, 0x6f, 0x5f, 0x31, 0x5f, 0x04, 0x00, 0x00, 0x00, 0x01, 0x93, 0x11, 0x10, 0x53, 0x74,
    0x72, 0x65, 0x61, 0x6d, 0x53, 0x70, 0x61, 0x72, 0x6b, 0x20, 0x4c, 0x69, 0x73, 0x74, 0xd1, 0x02,
    0x0b, 0xba, 0x00, 0x00, 0x04, 0x57, 0x00, 0x01, 0x27, 0x14, 0x00, 0x00, 0xf0, 0x27, 0x48, 0x1d,
    0x01, 0x0d, 0x45, 0x4e, 0x44, 0x20, 0x6f, 0x66, 0x20, 0x54, 0x56, 0x20, 0x4c, 0x43, 0x4e, 0x0d,
    0x45, 0x4e, 0x44, 0x20, 0x6f, 0x66, 0x20, 0x54, 0x56, 0x20, 0x4c, 0x43, 0x4e, 0x5f, 0x04, 0x00,
    0x00, 0x00, 0x01, 0x93, 0x00, 0x8a, 0x9e, 0xa6, 0x32
};


static void *sgp_Filter = NULL;

E_STB_DP_SIGNAL_TYPE g_sig_type = SIGNAL_COFDM;


// B: Local Function Declare
void ReceiveSgtTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec);
void ReceiveNitTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec);
void cert_Show_NitTable(SI_NIT_TABLE *nit_tbl_ptr);
void cert_Show_NitTable_Linkage(SI_LINKAGE_DESC_ENTRY *link_des_ptr);
void cert_Show_NitTable_Transport(SI_NIT_TRANSPORT_ENTRY *transport_ptr);
void cert_Show_NitTable_Delivery_Des(SI_DELIVERY_SYS_DESC_TYPE delivery_type, SI_DELIVERY_SYS_DESC *delivery_des_ptr);

void ParserFun(U8BIT *pBuf, U32BIT u32DataLen);

// E: Loal Function Declare

void Test_SiFilterTask()
{
    STB_SITerrInitialise();

    CERT_LOG_INFO(TAG, "[%s] Input any key to exit!", __FUNCTION__);

    getch();
}


void Test_SiFilterTable()
{
    void *pFilter = NULL;

    STB_SITerrInitialise();

    pFilter = cert_STB_SIRequestSgt(0, ONE_SHOT_REQUEST, 0x776/*sg_SGT_Pid*/, SI_XTID_MATCH_DONT_CARE, SI_XTID_MASK_DONT_CARE,
                                    ReceiveSgtTable, APP_SI_SGT_RECEIVED);

    Test_InjectSectionData(pFilter, sizeof(sgt_sec_0), sgt_sec_0);
    Test_InjectSectionData(pFilter, sizeof(sgt_sec_1), sgt_sec_1);

    CERT_LOG_INFO(TAG, "[%s] Input any key to exit!", __FUNCTION__);
    getch();

    STB_SICancelTableRequest(pFilter);
}



void Test_SiFliterLoop_SGT()
{
    void *pFilter = NULL;

    STB_SITerrInitialise();

    sgp_Filter = cert_STB_SIRequestSgt(0, ONE_SHOT_REQUEST, 0x776/*sg_SGT_Pid*/, SI_XTID_MATCH_DONT_CARE, SI_XTID_MASK_DONT_CARE,
                                       ReceiveSgtTable, APP_SI_SGT_RECEIVED);

    g_sig_type = SIGNAL_QPSK;
    UT_PidFilter_2_SectionFilter_Parser("D:\\StreamSparkTS\\8669-731\\HD_muxB_001.trp", 0x776, 0x91, ParserFun);

    CERT_LOG_INFO(TAG, "[%s] Input any key to exit!", __FUNCTION__);
    getch();

    STB_SICancelTableRequest(sgp_Filter);
    sgp_Filter = NULL;
}

void Test_SiFliterLoop_NIT()
{
    void *pFilter = NULL;

    STB_SITerrInitialise();

    sgp_Filter = STB_SIRequestNit(0, ONE_SHOT_REQUEST, ReceiveNitTable, APP_SI_NIT_RECEIVED);

    g_sig_type = SIGNAL_QPSK;
    UT_PidFilter_2_SectionFilter_Parser("D:\\StreamSparkTS\\8669-731\\HD_muxB_001.trp", 0x0010, 0x0040, ParserFun);

    CERT_LOG_INFO(TAG, "[%s] Input any key to exit!", __FUNCTION__);
    getch();

    STB_SICancelTableRequest(sgp_Filter);
    sgp_Filter = NULL;
}




// B: Local Function Define
void ReceiveSgtTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec)
{
    SI_SGT_TABLE *sgt_tbl_ptr = NULL;

    InitSiTblRec();

    CERT_LOG_INFO(TAG, "[%s] B: Parser Sgt Table", __FUNCTION__);

    sgt_tbl_ptr = cert_STB_SIParseSgtTable(table_rec);

    cert_Show_SgtTable(sgt_tbl_ptr);

    cert_Free_SgtTable(sgt_tbl_ptr);

    CERT_LOG_INFO(TAG, "[%s] E: Parser Sgt Table", __FUNCTION__);

    UT_Disable_FilterLoop();
}

void ReceiveNitTable(void *filter_ptr, U32BIT ret_param, SI_TABLE_RECORD *table_rec)
{
    SI_NIT_TABLE *nit_tbl_ptr = NULL;

    InitSiTblRec();

    CERT_LOG_INFO(TAG, "[%s] B: Parser Sgt Table", __FUNCTION__);

    nit_tbl_ptr = STB_SIParseNitTable(table_rec);

    cert_Show_NitTable(nit_tbl_ptr);

    STB_SIReleaseNitTable(nit_tbl_ptr);

    CERT_LOG_INFO(TAG, "[%s] E: Parser Sgt Table", __FUNCTION__);

    UT_Disable_FilterLoop();
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
void cert_Show_NitTable(SI_NIT_TABLE *nit_tbl_ptr)
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
void cert_Show_NitTable_Linkage(SI_LINKAGE_DESC_ENTRY *link_des_ptr)
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

    CERT_LOG_INFO(TAG, "[%s] Begin <<<", __FUNCTION__);
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
void cert_Show_NitTable_Transport(SI_NIT_TRANSPORT_ENTRY *transport_ptr)
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



void cert_Show_NitTable_Delivery_Des(SI_DELIVERY_SYS_DESC_TYPE delivery_type, SI_DELIVERY_SYS_DESC *delivery_des_ptr)
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


void ParserFun(U8BIT *pBuf, U32BIT u32DataLen)
{
    if (NULL != sgp_Filter)
    {
        Test_InjectSectionData(sgp_Filter, u32DataLen, pBuf);
    }
}

// E: Local Function Define



