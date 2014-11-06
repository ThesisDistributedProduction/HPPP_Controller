
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from TurbineDataMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef TurbineDataMessage_1363016663_h
#define TurbineDataMessage_1363016663_h

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


#define TurbineDataMessage_LAST_MEMBER_ID 2
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *TurbineDataMessageTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct TurbineDataMessageSeq;

#ifndef NDDS_STANDALONE_TYPE
    class TurbineDataMessageTypeSupport;
    class TurbineDataMessageDataWriter;
    class TurbineDataMessageDataReader;
#endif

#endif

            
    
class TurbineDataMessage                                        
{
public:            
#ifdef __cplusplus
    typedef struct TurbineDataMessageSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef TurbineDataMessageTypeSupport TypeSupport;
    typedef TurbineDataMessageDataWriter DataWriter;
    typedef TurbineDataMessageDataReader DataReader;
#endif

#endif
    
    DDS_Long  turbineId;

    DDS_Long  maxProduction;

    DDS_Long  currentProduction;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* TurbineDataMessage_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(TurbineDataMessageSeq, TurbineDataMessage);
        
NDDSUSERDllExport
RTIBool TurbineDataMessage_initialize(
        TurbineDataMessage* self);
        
NDDSUSERDllExport
RTIBool TurbineDataMessage_initialize_ex(
        TurbineDataMessage* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool TurbineDataMessage_initialize_w_params(
        TurbineDataMessage* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void TurbineDataMessage_finalize(
        TurbineDataMessage* self);
                        
NDDSUSERDllExport
void TurbineDataMessage_finalize_ex(
        TurbineDataMessage* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void TurbineDataMessage_finalize_w_params(
        TurbineDataMessage* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void TurbineDataMessage_finalize_optional_members(
        TurbineDataMessage* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool TurbineDataMessage_copy(
        TurbineDataMessage* dst,
        const TurbineDataMessage* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* TurbineDataMessage_1363016663_h */
