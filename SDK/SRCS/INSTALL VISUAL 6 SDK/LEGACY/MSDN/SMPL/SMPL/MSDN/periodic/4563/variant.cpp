/*
 * Definition of VARIANT, from OAIDL.H
 */

typedef unsigned short VARTYPE;
typedef struct tagVARIANT VARIANT;

struct tagVARIANT {
   VARTYPE vt;
   WORD wReserved1;
   WORD wReserved2;
   WORD wReserved3;
   union {
      long          lVal;           /* VT_I4                */
      unsigned char bVal;           /* VT_UI1               */
      short         iVal;           /* VT_I2                */
      float         fltVal;         /* VT_R4                */
      double        dblVal;         /* VT_R8                */
      VARIANT_BOOL  bool;           /* VT_BOOL              */
      SCODE         scode;          /* VT_ERROR             */
      CY            cyVal;          /* VT_CY                */
      DATE          date;           /* VT_DATE              */
      BSTR          bstrVal;        /* VT_BSTR              */
      IUnknown      *punkVal;       /* VT_UNKNOWN           */
      IDispatch     *pdispVal;      /* VT_DISPATCH          */
      SAFEARRAY     *parray;        /* VT_ARRAY|*           */
      unsigned char *pbVal;         /* VT_BYREF|VT_UI1      */
      short         *piVal;         /* VT_BYREF|VT_I2       */
      long          *plVal;         /* VT_BYREF|VT_I4       */
      float         *pfltVal;       /* VT_BYREF|VT_R4       */
      double        *pdblVal;       /* VT_BYREF|VT_R8       */
      VARIANT_BOOL  *pbool;         /* VT_BYREF|VT_BOOL     */
      SCODE         *pscode;        /* VT_BYREF|VT_ERROR    */
      CY            *pcyVal;        /* VT_BYREF|VT_CY       */
      DATE          *pdate;         /* VT_BYREF|VT_DATE     */
      BSTR          *pbstrVal;      /* VT_BYREF|VT_BSTR     */
      IUnknown      **ppunkVal;     /* VT_BYREF|VT_UNKNOWN  */
      IDispatch     **ppdispVal;    /* VT_BYREF|VT_DISPATCH */
      SAFEARRAY     **pparray;      /* VT_BYREF|VT_ARRAY|*  */
      VARIANT       *pvarVal;       /* VT_BYREF|VT_VARIANT  */
      void          *byref;         /* Generic Bytes        */
   } u;
};
