/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	MWRTTI.cp												*/
/*	Purpose...:	RTTI													*/
/*  Copyright.: Copyright © 1993-1999 Metrowerks, Inc.					*/
/************************************************************************/

#include <CPlusLib.h>
#define __NOSTRING__	//	do not include <string>
#include <typeinfo>
#include <string.h>

/************************************************************************/
/*	Purpose..: 	Compare two strings										*/
/*	Input....:	pointer to first string									*/
/*	Input....:	pointer to second string								*/
/*	Return...:	0: equal; >0: s1 > s2; <0: s1 < s2						*/
/************************************************************************/
static int strequal(register const char *s1,register const char *s2)
{
	for (; *s1 == *s2; ++s1, ++s2)
		if (*s1 == '\0')
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

#ifdef MSIPL_USING_NAMESPACE      // hh 980106
	namespace std {
#endif

// hh 980124 type_info implementation moved to <typeinfo>

/************************************************************************/
/* Purpose..: type_info destructor function								*/
/* Input....: ---														*/
/* Return...: ---														*/
/************************************************************************/
//type_info::~type_info() { }

/************************************************************************/
/* Purpose..: type_info == comparision function							*/
/* Input....: type_info reference										*/
/* Return...: true: same types											*/
/************************************************************************/
/*
bool type_info::operator==(const type_info& ti) const
{
	return (strequal(tname,ti.tname) == 0);
}
*/
/************************************************************************/
/* Purpose..: type_info != comparision function							*/
/* Input....: type_info reference										*/
/* Return...: true: same types											*/
/************************************************************************/
/*
bool type_info::operator!=(const type_info& ti) const
{
	return (strequal(tname,ti.tname) != 0);
}
*/
/************************************************************************/
/* Purpose..: type_info collation order function						*/
/* Input....: type_info reference										*/
/* Return...: true: *this precedes type_info							*/
/************************************************************************/
/*
bool type_info::before(const type_info& ti) const
{
	return (strequal(tname,ti.tname) < 0);
}
*/
/************************************************************************/
/* Purpose..: return type name											*/
/* Input....: ---														*/
/* Return...: pointer to type name										*/
/************************************************************************/
/*
const char*	type_info::name() const
{
	return tname;
}
*/
/************************************************************************/
/* Purpose..: type_info copy constructor								*/
/* Input....: type_info reference										*/
/* Return...: ---														*/
/************************************************************************/
/*
type_info::type_info(const type_info& ti)
{
	tname=ti.tname;
}
*/
/************************************************************************/
/* Purpose..: type_info assigment operator								*/
/* Input....: type_info reference										*/
/* Return...: type_info reference										*/
/************************************************************************/
/*
type_info& type_info::operator=(const type_info& ti)
{
	tname=ti.tname;
	return *this;
}
*/
#ifdef MSIPL_USING_NAMESPACE      // hh 980106
	}
#endif

/************************************************************************/
/* Purpose..: RTTI runtime function prototypes							*/
/* Input....: ---														*/
/* Return...: ---														*/
/************************************************************************/

typedef struct type_info_struct type_info_struct;	//	forward

typedef struct type_info_base_list {	//	type info base list
	type_info_struct	*baseti;		//	pointer to bases type_info struct (0: end of list)
	long				offset;			//	offset of base in main class (0x80000000 : ambiguous/no access list follows
}	type_info_base_list;

typedef struct type_info_ambighead {	//	type ambiguous/no access base list header
	void				*baseti;		//	pointer to bases type_info struct (0: end of list)
	long				offset;			//	offset of base in main class (|=0x80000000)
	long				bases;			//	number of type_info_base_list elements (public bases)
}	type_info_ambighead;

struct type_info_struct {				//	type info data structure
	char				*tname;			//	pointer to type name
	type_info_base_list	*baselist;		//	pointer to base list
};

typedef struct RTTIVTableHeader {		//	RTTI header in a vtable
	type_info_struct	*type_info_ptr;	//	pointer to complete class type_info struct
	long				complete_offset;//	offset of complete class
}	RTTIVTableHeader;

extern "C" {
	void	*__get_typeid(void *,long);
	void	*__dynamic_cast(void *,long,type_info_struct *,type_info_struct *,short);
}

static type_info_struct unknown_type = { "???" };

/************************************************************************/
/* Purpose..: Get polymorphic typeid									*/
/* Input....: pointer to object (or 0)									*/
/* Input....: offset of vtable pointer in object						*/
/* Return...: pointer to typeid object									*/
/************************************************************************/
void *__get_typeid(void *obj,long offset)
{
//
//	Note:	the first entry of an object's vtable is a pointer to the typeid object
//
	if(obj==0) throw bad_typeid();
#if CABI_ZEROOFFSETVTABLE

	if((obj=*(void **)(*(char **)((char *)obj+offset)-sizeof(RTTIVTableHeader)))==0)
	{	//	class was compiled withou the RTTI option
		return &unknown_type;
	}

#else

	if((obj=**(void ***)((char *)obj+offset))==0)
	{	//	class was compiled withou the RTTI option
		return &unknown_type;
	}
	
#endif
	return obj;
}

/************************************************************************/
/* Purpose..: dynamnic_cast runtime function							*/
/* Input....: pointer to object (or 0)									*/
/* Input....: offset of vtable pointer in object						*/
/* Input....: pointer to type_info of to type (or 0 for void* cast)		*/
/* Input....: pointer to sub type_info of static type					*/
/* Input....: true: reference cast										*/
/* Return...: pointer to casted expression								*/
/************************************************************************/
extern void __priv_throwbadcast(void);   // hh 980205 prototype for runtime use

void *__dynamic_cast(void *obj,long offset,type_info_struct *typeinfo,type_info_struct *subtypeinfo,short isref)
{
	RTTIVTableHeader	*vthead;
	type_info_base_list	*list;
	long				loffset;
	void				*completeclass;
	int					i,n;

	if(obj==0) return 0;

#if CABI_ZEROOFFSETVTABLE
	vthead=*(RTTIVTableHeader **)((char *)obj+offset)-1;
#else
	vthead=*(RTTIVTableHeader **)((char *)obj+offset);
#endif

	if(vthead->type_info_ptr)
	{	//	class was compiled with the RTTI option
		completeclass=(char *)obj+vthead->complete_offset;
		if(typeinfo==0 || (strequal(vthead->type_info_ptr->tname,typeinfo->tname) == 0))
		{	//	success: cast to void* or to complete class
			return completeclass;
		}
	
		if((list=vthead->type_info_ptr->baselist)!=0) for(; list->baseti; list++)
		{	//	check base classes
			if(list->offset&0x80000000)
			{	//	ambiguous/access match
				loffset=(list->offset&0x7fffffff);	
				n=((type_info_ambighead *)list)->bases;
				if(vthead->complete_offset+loffset==0 && (strequal(list->baseti->tname,typeinfo->tname) == 0))
				{	//	check bases
					list=(type_info_base_list *)((type_info_ambighead *)list+1);
					for(i=0; i<n; i++,list++)
					{
						if(vthead->complete_offset+list->offset==0 && (strequal(list->baseti->tname,subtypeinfo->tname) == 0))
						{
							return (char *)completeclass+list->offset;
						}
					}
					break;	//	cast cannot be successful
				}
				else
				{	//	skip ambiguous/no access class
					list=(type_info_base_list *)((type_info_ambighead *)list+1);
					list+=(n-1);
				}		
			}
			else
			{
				if(strequal(list->baseti->tname,typeinfo->tname) == 0)
				{	//	success: cast to public unambiguous base class
					return (char *)completeclass+list->offset;
				}
			}
		}
	}
	if(isref) throw bad_cast();
//	if(isref) __priv_throwbadcast();
	return 0;
}

// hh 980124 type_info implementation moved to <typeinfo>
