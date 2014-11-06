
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from TurbineDataMessage.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef TurbineDataMessageSupport_1363016663_h
#define TurbineDataMessageSupport_1363016663_h

/* Uses */
#include "TurbineDataMessage.h"



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

DDS_TYPESUPPORT_CPP(TurbineDataMessageTypeSupport, TurbineDataMessage);

DDS_DATAWRITER_CPP(TurbineDataMessageDataWriter, TurbineDataMessage);
DDS_DATAREADER_CPP(TurbineDataMessageDataReader, TurbineDataMessageSeq, TurbineDataMessage);


#else

DDS_TYPESUPPORT_C(TurbineDataMessageTypeSupport, TurbineDataMessage);
DDS_DATAWRITER_C(TurbineDataMessageDataWriter, TurbineDataMessage);
DDS_DATAREADER_C(TurbineDataMessageDataReader, TurbineDataMessageSeq, TurbineDataMessage);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif  /* TurbineDataMessageSupport_1363016663_h */
