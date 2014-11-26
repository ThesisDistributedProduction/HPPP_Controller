

/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from TurbineDataMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef TurbineDataMessagePlugin_1363016659_h
#define TurbineDataMessagePlugin_1363016659_h

#include "TurbineDataMessage.h"

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
     * AnotherSimple.
     *
     * By default, this type is struct TurbineDataMessage
     * itself. However, if for some reason this choice is not practical for your
     * system (e.g. if sizeof(struct TurbineDataMessage)
     * is very large), you may redefine this typedef in terms of another type of
     * your choosing. HOWEVER, if you define the KeyHolder type to be something
     * other than struct AnotherSimple, the
     * following restriction applies: the key of struct
     * TurbineDataMessage must consist of a
     * single field of your redefined KeyHolder type and that field must be the
     * first field in struct TurbineDataMessage.
    */
    typedef  class TurbineDataMessage TurbineDataMessageKeyHolder;

    #define TurbineDataMessagePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define TurbineDataMessagePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define TurbineDataMessagePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

     
    #define TurbineDataMessagePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define TurbineDataMessagePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey
     
    #define TurbineDataMessagePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define TurbineDataMessagePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
        Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TurbineDataMessage*
    TurbineDataMessagePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TurbineDataMessage*
    TurbineDataMessagePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TurbineDataMessage*
    TurbineDataMessagePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePluginSupport_copy_data(
        TurbineDataMessage *out,
        const TurbineDataMessage *in);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePluginSupport_destroy_data_w_params(
        TurbineDataMessage *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePluginSupport_destroy_data_ex(
        TurbineDataMessage *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePluginSupport_destroy_data(
        TurbineDataMessage *sample);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePluginSupport_print_data(
        const TurbineDataMessage *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern TurbineDataMessage*
    TurbineDataMessagePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TurbineDataMessage*
    TurbineDataMessagePluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePluginSupport_destroy_key_ex(
        TurbineDataMessageKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePluginSupport_destroy_key(
        TurbineDataMessageKeyHolder *key);

    /* ----------------------------------------------------------------------------
        Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    TurbineDataMessagePlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    TurbineDataMessagePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    TurbineDataMessagePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    TurbineDataMessagePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage *out,
        const TurbineDataMessage *in);

    /* ----------------------------------------------------------------------------
        (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const TurbineDataMessage *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TurbineDataMessagePlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    TurbineDataMessagePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    TurbineDataMessagePlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    TurbineDataMessagePlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const TurbineDataMessage * sample);

    /* --------------------------------------------------------------------------------------
        Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    TurbineDataMessagePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    TurbineDataMessagePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const TurbineDataMessage *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TurbineDataMessagePlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
       TurbineDataMessageKeyHolder *key, 
        const TurbineDataMessage *instance);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        TurbineDataMessage *instance, 
        const TurbineDataMessageKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_instance_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        DDS_KeyHash_t *keyhash,
        const TurbineDataMessage *instance);

    NDDSUSERDllExport extern RTIBool 
    TurbineDataMessagePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    TurbineDataMessagePlugin_new(void);

    NDDSUSERDllExport extern void
    TurbineDataMessagePlugin_delete(struct PRESTypePlugin *);

    #ifdef __cplusplus
}
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* TurbineDataMessagePlugin_1363016659_h */

