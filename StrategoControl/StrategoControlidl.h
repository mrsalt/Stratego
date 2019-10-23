
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Feb 25 23:25:51 2004
 */
/* Compiler settings for StrategoControl.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __StrategoControlidl_h__
#define __StrategoControlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DStrategoControl_FWD_DEFINED__
#define ___DStrategoControl_FWD_DEFINED__
typedef interface _DStrategoControl _DStrategoControl;
#endif 	/* ___DStrategoControl_FWD_DEFINED__ */


#ifndef ___DStrategoControlEvents_FWD_DEFINED__
#define ___DStrategoControlEvents_FWD_DEFINED__
typedef interface _DStrategoControlEvents _DStrategoControlEvents;
#endif 	/* ___DStrategoControlEvents_FWD_DEFINED__ */


#ifndef __StrategoControl_FWD_DEFINED__
#define __StrategoControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class StrategoControl StrategoControl;
#else
typedef struct StrategoControl StrategoControl;
#endif /* __cplusplus */

#endif 	/* __StrategoControl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __StrategoControlLib_LIBRARY_DEFINED__
#define __StrategoControlLib_LIBRARY_DEFINED__

/* library StrategoControlLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_StrategoControlLib;

#ifndef ___DStrategoControl_DISPINTERFACE_DEFINED__
#define ___DStrategoControl_DISPINTERFACE_DEFINED__

/* dispinterface _DStrategoControl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DStrategoControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A1A0215D-3505-4748-AE90-C231081B5B93")
    _DStrategoControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DStrategoControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DStrategoControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DStrategoControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DStrategoControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DStrategoControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DStrategoControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DStrategoControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DStrategoControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DStrategoControlVtbl;

    interface _DStrategoControl
    {
        CONST_VTBL struct _DStrategoControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DStrategoControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DStrategoControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DStrategoControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DStrategoControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DStrategoControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DStrategoControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DStrategoControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DStrategoControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DStrategoControlEvents_DISPINTERFACE_DEFINED__
#define ___DStrategoControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DStrategoControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DStrategoControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DA56CC2C-8811-4831-9222-29333DF90474")
    _DStrategoControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DStrategoControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DStrategoControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DStrategoControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DStrategoControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DStrategoControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DStrategoControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DStrategoControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DStrategoControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DStrategoControlEventsVtbl;

    interface _DStrategoControlEvents
    {
        CONST_VTBL struct _DStrategoControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DStrategoControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DStrategoControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DStrategoControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DStrategoControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DStrategoControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DStrategoControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DStrategoControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DStrategoControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_StrategoControl;

#ifdef __cplusplus

class DECLSPEC_UUID("9CCB537E-5273-43CB-BEA9-75D9E716AA46")
StrategoControl;
#endif
#endif /* __StrategoControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


