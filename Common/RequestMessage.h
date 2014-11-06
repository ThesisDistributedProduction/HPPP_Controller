
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from RequestMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef RequestMessage_1502787215_h
#define RequestMessage_1502787215_h

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


#define RequestMessage_LAST_MEMBER_ID 0
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *RequestMessageTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct RequestMessageSeq;

#ifndef NDDS_STANDALONE_TYPE
    class RequestMessageTypeSupport;
    class RequestMessageDataWriter;
    class RequestMessageDataReader;
#endif

#endif

            
    
class RequestMessage                                        
{
public:            
#ifdef __cplusplus
    typedef struct RequestMessageSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef RequestMessageTypeSupport TypeSupport;
    typedef RequestMessageDataWriter DataWriter;
    typedef RequestMessageDataReader DataReader;
#endif

#endif
    
    DDS_Long  msSinceLastWrite;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* RequestMessage_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(RequestMessageSeq, RequestMessage);
        
NDDSUSERDllExport
RTIBool RequestMessage_initialize(
        RequestMessage* self);
        
NDDSUSERDllExport
RTIBool RequestMessage_initialize_ex(
        RequestMessage* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool RequestMessage_initialize_w_params(
        RequestMessage* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void RequestMessage_finalize(
        RequestMessage* self);
                        
NDDSUSERDllExport
void RequestMessage_finalize_ex(
        RequestMessage* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void RequestMessage_finalize_w_params(
        RequestMessage* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void RequestMessage_finalize_optional_members(
        RequestMessage* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool RequestMessage_copy(
        RequestMessage* dst,
        const RequestMessage* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* RequestMessage_1502787215_h */
