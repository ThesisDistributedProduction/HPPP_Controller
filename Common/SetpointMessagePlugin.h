
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from SetpointMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef SetpointMessagePlugin_986307849_h
#define SetpointMessagePlugin_986307849_h

#include "SetpointMessage.h"



struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif


#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif


#ifdef __cplusplus
extern "C" {
#endif


#define SetpointMessagePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define SetpointMessagePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define SetpointMessagePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define SetpointMessagePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define SetpointMessagePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern SetpointMessage*
SetpointMessagePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern SetpointMessage*
SetpointMessagePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern SetpointMessage*
SetpointMessagePluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
SetpointMessagePluginSupport_copy_data(
    SetpointMessage *out,
    const SetpointMessage *in);

NDDSUSERDllExport extern void 
SetpointMessagePluginSupport_destroy_data_w_params(
    SetpointMessage *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
SetpointMessagePluginSupport_destroy_data_ex(
    SetpointMessage *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
SetpointMessagePluginSupport_destroy_data(
    SetpointMessage *sample);

NDDSUSERDllExport extern void 
SetpointMessagePluginSupport_print_data(
    const SetpointMessage *sample,
    const char *desc,
    unsigned int indent);


/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
SetpointMessagePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
SetpointMessagePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
SetpointMessagePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
SetpointMessagePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
SetpointMessagePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage *out,
    const SetpointMessage *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const SetpointMessage *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
SetpointMessagePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
SetpointMessagePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
SetpointMessagePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
SetpointMessagePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const SetpointMessage * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
SetpointMessagePlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
SetpointMessagePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const SetpointMessage *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
SetpointMessagePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
SetpointMessagePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    SetpointMessage *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
SetpointMessagePlugin_new(void);

NDDSUSERDllExport extern void
SetpointMessagePlugin_delete(struct PRESTypePlugin *);

#ifdef __cplusplus
}
#endif

        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif        

#endif /* SetpointMessagePlugin_986307849_h */
