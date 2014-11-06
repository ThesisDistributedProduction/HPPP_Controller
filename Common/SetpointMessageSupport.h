
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from SetpointMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef SetpointMessageSupport_986307849_h
#define SetpointMessageSupport_986307849_h

/* Uses */
#include "SetpointMessage.h"



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

DDS_TYPESUPPORT_CPP(SetpointMessageTypeSupport, SetpointMessage);

DDS_DATAWRITER_CPP(SetpointMessageDataWriter, SetpointMessage);
DDS_DATAREADER_CPP(SetpointMessageDataReader, SetpointMessageSeq, SetpointMessage);


#else

DDS_TYPESUPPORT_C(SetpointMessageTypeSupport, SetpointMessage);
DDS_DATAWRITER_C(SetpointMessageDataWriter, SetpointMessage);
DDS_DATAREADER_C(SetpointMessageDataReader, SetpointMessageSeq, SetpointMessage);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif  /* SetpointMessageSupport_986307849_h */
