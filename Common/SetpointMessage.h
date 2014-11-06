
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from SetpointMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef SetpointMessage_986307849_h
#define SetpointMessage_986307849_h

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


#define SetpointMessage_LAST_MEMBER_ID 0
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *SetpointMessageTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct SetpointMessageSeq;

#ifndef NDDS_STANDALONE_TYPE
    class SetpointMessageTypeSupport;
    class SetpointMessageDataWriter;
    class SetpointMessageDataReader;
#endif

#endif

            
    
class SetpointMessage                                        
{
public:            
#ifdef __cplusplus
    typedef struct SetpointMessageSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef SetpointMessageTypeSupport TypeSupport;
    typedef SetpointMessageDataWriter DataWriter;
    typedef SetpointMessageDataReader DataReader;
#endif

#endif
    
    DDS_Long  setPoint;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* SetpointMessage_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(SetpointMessageSeq, SetpointMessage);
        
NDDSUSERDllExport
RTIBool SetpointMessage_initialize(
        SetpointMessage* self);
        
NDDSUSERDllExport
RTIBool SetpointMessage_initialize_ex(
        SetpointMessage* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool SetpointMessage_initialize_w_params(
        SetpointMessage* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void SetpointMessage_finalize(
        SetpointMessage* self);
                        
NDDSUSERDllExport
void SetpointMessage_finalize_ex(
        SetpointMessage* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void SetpointMessage_finalize_w_params(
        SetpointMessage* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void SetpointMessage_finalize_optional_members(
        SetpointMessage* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool SetpointMessage_copy(
        SetpointMessage* dst,
        const SetpointMessage* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* SetpointMessage_986307849_h */
