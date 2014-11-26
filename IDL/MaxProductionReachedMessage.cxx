

/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from MaxProductionReachedMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "dds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "cdr/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "osapi/osapi_heap.h" 
    #endif
#else
    #include "ndds_standalone_type.h"
#endif

#include "MaxProductionReachedMessage.h"

/* ========================================================================= */
const char *MaxProductionReachedMessageTYPENAME = "MaxProductionReachedMessage";

DDS_TypeCode* MaxProductionReachedMessage_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member MaxProductionReachedMessage_g_tc_members[2]=
        {

        {
            (char *)"turbineId",/* Member name */
            {
                0,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
                        0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_KEY_MEMBER , /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
                        NULL/* Ignored */
        }, 
                {
            (char *)"localAndMaxDiff",/* Member name */
            {
                1,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
                        0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
                        NULL/* Ignored */
        }
    };

    static DDS_TypeCode MaxProductionReachedMessage_g_tc =
        {{
            DDS_TK_STRUCT,/* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"MaxProductionReachedMessage", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            MaxProductionReachedMessage_g_tc_members, /* Members */
            DDS_VM_NONE  /* Ignored */         
        }}; /* Type code for MaxProductionReachedMessage*/

    if (is_initialized) {
        return &MaxProductionReachedMessage_g_tc;
    }

    MaxProductionReachedMessage_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    MaxProductionReachedMessage_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &MaxProductionReachedMessage_g_tc;
}

RTIBool MaxProductionReachedMessage_initialize(
    MaxProductionReachedMessage* sample) {
    return MaxProductionReachedMessage_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool MaxProductionReachedMessage_initialize_ex(
    MaxProductionReachedMessage* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
            DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return MaxProductionReachedMessage_initialize_w_params(
            sample,&allocParams);

}

RTIBool MaxProductionReachedMessage_initialize_w_params(
    MaxProductionReachedMessage* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (allocParams) {} /* To avoid warnings */

    if (!RTICdrType_initLong(&sample->turbineId)) {
        return RTI_FALSE;
    }     

    if (!RTICdrType_initLong(&sample->localAndMaxDiff)) {
        return RTI_FALSE;
    }     

    return RTI_TRUE;
}

void MaxProductionReachedMessage_finalize(
    MaxProductionReachedMessage* sample)
{

    MaxProductionReachedMessage_finalize_ex(sample,RTI_TRUE);
}

void MaxProductionReachedMessage_finalize_ex(
    MaxProductionReachedMessage* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    MaxProductionReachedMessage_finalize_w_params(
            sample,&deallocParams);
}

void MaxProductionReachedMessage_finalize_w_params(
    MaxProductionReachedMessage* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample) {} /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

}

void MaxProductionReachedMessage_finalize_optional_members(
    MaxProductionReachedMessage* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
            &deallocParamsTmp;

    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool MaxProductionReachedMessage_copy(
    MaxProductionReachedMessage* dst,
    const MaxProductionReachedMessage* src)
{

    if (!RTICdrType_copyLong (
           &dst->turbineId, &src->turbineId)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
           &dst->localAndMaxDiff, &src->localAndMaxDiff)) { 
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'MaxProductionReachedMessage' sequence class.
 */
#define T MaxProductionReachedMessage
#define TSeq MaxProductionReachedMessageSeq
#define T_initialize_w_params MaxProductionReachedMessage_initialize_w_params
#define T_finalize_w_params   MaxProductionReachedMessage_finalize_w_params
#define T_copy       MaxProductionReachedMessage_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_w_params
#undef T_initialize_w_params
#undef TSeq
#undef T

