
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from MaxProductionReachedMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef MaxProductionReachedMessage_94301380_h
#define MaxProductionReachedMessage_94301380_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif


#define MaxProductionReachedMessage_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *MaxProductionReachedMessageTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct MaxProductionReachedMessageSeq;

#ifndef NDDS_STANDALONE_TYPE
    class MaxProductionReachedMessageTypeSupport;
    class MaxProductionReachedMessageDataWriter;
    class MaxProductionReachedMessageDataReader;
#endif

#endif

            
    
class MaxProductionReachedMessage                                        
{
public:            
#ifdef __cplusplus
    typedef struct MaxProductionReachedMessageSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef MaxProductionReachedMessageTypeSupport TypeSupport;
    typedef MaxProductionReachedMessageDataWriter DataWriter;
    typedef MaxProductionReachedMessageDataReader DataReader;
#endif

#endif
    
    DDS_Long  turbineId;

    DDS_Long  localAndMaxDiff;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* MaxProductionReachedMessage_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(MaxProductionReachedMessageSeq, MaxProductionReachedMessage);
        
NDDSUSERDllExport
RTIBool MaxProductionReachedMessage_initialize(
        MaxProductionReachedMessage* self);
        
NDDSUSERDllExport
RTIBool MaxProductionReachedMessage_initialize_ex(
        MaxProductionReachedMessage* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool MaxProductionReachedMessage_initialize_w_params(
        MaxProductionReachedMessage* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void MaxProductionReachedMessage_finalize(
        MaxProductionReachedMessage* self);
                        
NDDSUSERDllExport
void MaxProductionReachedMessage_finalize_ex(
        MaxProductionReachedMessage* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void MaxProductionReachedMessage_finalize_w_params(
        MaxProductionReachedMessage* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void MaxProductionReachedMessage_finalize_optional_members(
        MaxProductionReachedMessage* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool MaxProductionReachedMessage_copy(
        MaxProductionReachedMessage* dst,
        const MaxProductionReachedMessage* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* MaxProductionReachedMessage_94301380_h */
