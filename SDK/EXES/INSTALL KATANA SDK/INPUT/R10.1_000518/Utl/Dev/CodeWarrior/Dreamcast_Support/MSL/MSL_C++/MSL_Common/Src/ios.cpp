/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:07 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  ios.cpp
 **
 **  Lib++  : The Metrowerks C++ Standard Library,
 **           Version 2.4, January 1998
 **
 **  Copyright (c) 1998 Metrowerks Inc.
 **/

#include <ios>

MSIPL_STD_BEGIN

locale ios_base::imbue (const locale& loc_arg)
{
   WRITE_LOCK(_mutex);
   locale loc_sav = *loc_;
   delete loc_;
   loc_ = new locale(loc_arg);
   size_t i = rvec_size_;
   for ( ; i > 0 ; --i)
        (*(rvec_[i-1].first))(imbue_event, *this, rvec_[i-1].second);
   return  loc_sav;
}

// hh 980507 uninlined to work around current compiler inlining restriction
locale
ios_base::getloc () const 
{
   READ_LOCK(_mutex);
   return *loc_;
}

long& ios_base::iword (int index_arg)
{
   static long l = 0;
   WRITE_LOCK(_mutex);
   MSIPL_TRY 
   {
    if ((size_t)index_arg >= ivecLen_)
    {
        size_t oldLen = ivecLen_;
        if (ivecLen_ == 0)
            ivecLen_ = (size_t)index_arg + 1;
        else {
            while ((size_t)index_arg >= ivecLen_)
                ivecLen_ *= 2;
        }
        long* newivec = new long [ivecLen_];
        int i;
        for (i = 0; i < oldLen; ++i)
           newivec[i] = ivec_[i];
        delete [] ivec_;
        ivec_ = newivec;
        for (; i < ivecLen_; ++i)
            ivec_[i] = 0;
    }
   }
   MSIPL_CATCH
   {
     fmtfl |= badbit;
     return l;
   }
   return ivec_[size_t(index_arg)];
}
 
void*& ios_base::pword (int index_arg)
{
   static void* v = 0;
   WRITE_LOCK(_mutex);
   MSIPL_TRY
   {
    if ((size_t)index_arg >= pvecLen_)
    {
        size_t oldLen = pvecLen_;
        if (pvecLen_ == 0)
            pvecLen_ = (size_t)index_arg + 1;
        else {
            while ((size_t)index_arg >= pvecLen_)
                pvecLen_ *= 2;
        }
        void** newpvec = new void* [pvecLen_];
        int i;
        for (i = 0; i < oldLen; ++i)
           newpvec[i] = pvec_[i];
        delete [] pvec_;
        pvec_ = newpvec;
        for (; i < pvecLen_; ++i)
            pvec_[i] = 0;
    }
   }
   MSIPL_CATCH
   {
      fmtfl |= badbit;
      return v;
   }
   return pvec_[size_t(index_arg)];
}

// inline // hh 980513 uninlined and rewrote to not use vector
void ios_base::register_callback (event_callback fn, int index)
{
	WRITE_LOCK(_mutex);
	if (rvec_size_ >= rvec_max_size_)
	{
		if (rvec_max_size_ == 0)
			rvec_max_size_ = 1;
		else
			rvec_max_size_ *= 2;
		event_pair* oldevents = rvec_;
		rvec_ = new event_pair [rvec_max_size_];
		for (int i = 0; i < rvec_size_; ++i)
			rvec_[i] = oldevents[i];
		delete [] oldevents;
	}
	rvec_[rvec_size_++] = make_pair(fn, index);
}

ios_base::ios_base ()
{
}

ios_base::~ios_base ()
{ 
   size_t i = rvec_size_;
   for ( ; i > 0 ; --i)
        (*(rvec_[i-1].first))(erase_event, *this, rvec_[i-1].second);
   delete loc_;
   delete [] rvec_;
   delete [] ivec_;
   delete [] pvec_;
}

// hh 980514 uninlined
void
ios_base::throwfailure ()
{
#ifdef MSIPL_EXCEPT
   throw failure ("Failure reported");
#else
   fprintf (stderr, "Failure in I/O\n");
   exit (1);
#endif
}

MSIPL_STD_END
