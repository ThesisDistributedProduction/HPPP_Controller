
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from MaxProductionReachedMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef MaxProductionReachedMessagePlugin_94301380_h
#define MaxProductionReachedMessagePlugin_94301380_h

#include "MaxProductionReachedMessage.h"



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

/* The type used to store keys for instances of type struct
 * MaxProductionReachedMessage.
 *
 * By default, this type is struct MaxProductionReachedMessage
 * itself. However, if for some reason this choice is not practical for your
 * system (e.g. if sizeof(struct MaxProductionReachedMessage)
 * is very large), you may redefine this typedef in terms of another type of
 * your choosing. HOWEVER, if you define the KeyHolder type to be something
 * other than struct MaxProductionReachedMessage, the
 * following restriction applies: the key of struct
 * MaxProductionReachedMessage must consist of a
 * single field of your redefined KeyHolder type and that field must be the
 * first field in struct MaxProductionReachedMessage.
*/
typedef  class MaxProductionReachedMessage MaxProductionReachedMessageKeyHolder;


#define MaxProductionReachedMessagePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define MaxProductionReachedMessagePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define MaxProductionReachedMessagePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define MaxProductionReachedMessagePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
#define MaxProductionReachedMessagePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
 

#define MaxProductionReachedMessagePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define MaxProductionReachedMessagePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern MaxProductionReachedMessage*
MaxProductionReachedMessagePluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern MaxProductionReachedMessage*
MaxProductionReachedMessagePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern MaxProductionReachedMessage*
MaxProductionReachedMessagePluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePluginSupport_copy_data(
    MaxProductionReachedMessage *out,
    const MaxProductionReachedMessage *in);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePluginSupport_destroy_data_w_params(
    MaxProductionReachedMessage *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePluginSupport_destroy_data_ex(
    MaxProductionReachedMessage *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePluginSupport_destroy_data(
    MaxProductionReachedMessage *sample);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePluginSupport_print_data(
    const MaxProductionReachedMessage *sample,
    const char *desc,
    unsigned int indent);


NDDSUSERDllExport extern MaxProductionReachedMessage*
MaxProductionReachedMessagePluginSupport_create_key_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern MaxProductionReachedMessage*
MaxProductionReachedMessagePluginSupport_create_key(void);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePluginSupport_destroy_key_ex(
    MaxProductionReachedMessageKeyHolder *key,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePluginSupport_destroy_key(
    MaxProductionReachedMessageKeyHolder *key);

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
MaxProductionReachedMessagePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
MaxProductionReachedMessagePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
MaxProductionReachedMessagePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
MaxProductionReachedMessagePlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage *out,
    const MaxProductionReachedMessage *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const MaxProductionReachedMessage *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
MaxProductionReachedMessagePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
MaxProductionReachedMessagePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
MaxProductionReachedMessagePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
MaxProductionReachedMessagePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const MaxProductionReachedMessage * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
MaxProductionReachedMessagePlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
MaxProductionReachedMessagePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const MaxProductionReachedMessage *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
MaxProductionReachedMessagePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_instance_to_key(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessageKeyHolder *key, 
    const MaxProductionReachedMessage *instance);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_key_to_instance(
    PRESTypePluginEndpointData endpoint_data,
    MaxProductionReachedMessage *instance, 
    const MaxProductionReachedMessageKeyHolder *key);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_instance_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    DDS_KeyHash_t *keyhash,
    const MaxProductionReachedMessage *instance);

NDDSUSERDllExport extern RTIBool 
MaxProductionReachedMessagePlugin_serialized_sample_to_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    DDS_KeyHash_t *keyhash,
    RTIBool deserialize_encapsulation,
    void *endpoint_plugin_qos); 
     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
MaxProductionReachedMessagePlugin_new(void);

NDDSUSERDllExport extern void
MaxProductionReachedMessagePlugin_delete(struct PRESTypePlugin *);

#ifdef __cplusplus
}
#endif

        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif        

#endif /* MaxProductionReachedMessagePlugin_94301380_h */
