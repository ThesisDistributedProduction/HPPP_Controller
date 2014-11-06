
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from RequestMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef RequestMessageSupport_1502787215_h
#define RequestMessageSupport_1502787215_h

/* Uses */
#include "RequestMessage.h"



#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(RequestMessageTypeSupport, RequestMessage);

DDS_DATAWRITER_CPP(RequestMessageDataWriter, RequestMessage);
DDS_DATAREADER_CPP(RequestMessageDataReader, RequestMessageSeq, RequestMessage);


#else

DDS_TYPESUPPORT_C(RequestMessageTypeSupport, RequestMessage);
DDS_DATAWRITER_C(RequestMessageDataWriter, RequestMessage);
DDS_DATAREADER_C(RequestMessageDataReader, RequestMessageSeq, RequestMessage);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif  /* RequestMessageSupport_1502787215_h */
