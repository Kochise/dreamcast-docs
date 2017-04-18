/*  Metrowerks Standard Library  */

/*  $Date: 1999/03/30 21:02:17 $ 
 *  $Revision: 1.8 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  locale.cpp
 **/

#include <ios>
#include <streambuf>
#include <locale>
#include <stdexcept>
#include <typeinfo>

//#ifndef _MSL_NO_MEMBER_TEMPLATE
#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

size_t locale::id::id_count_s = 0;

_RefCountedPtr<__locale_imp<true> > locale::global_s;

#ifdef _MSL_NO_MEMBER_TEMPLATE
	#define MAKE_LOCALE(MyFacet)                              \
		locale::locale(const locale& other, MyFacet* f)       \
		{                                                     \
			if (f == 0)                                       \
				imp_ = other.imp_;                            \
			else {                                            \
				imp_ = new __locale_imp<true>(*other.imp_);   \
				imp_->replace(*f);                            \
				imp_->name() = "*";                           \
			}                                                 \
		}

	MAKE_LOCALE(_STD::collate<char>)
	MAKE_LOCALE(_STD::ctype<char>)
	typedef _STD::codecvt<char, char, mbstate_t> __codecvt1;
	MAKE_LOCALE(__codecvt1)
	MAKE_LOCALE(_STD::numpunct<char>)
	MAKE_LOCALE(_STD::num_get<char>)
	typedef _STD::num_get<char, char*> __num_get1;
	MAKE_LOCALE(__num_get1)
	MAKE_LOCALE(_STD::num_put<char>)
	MAKE_LOCALE(_STD::timepunct<char>)
	MAKE_LOCALE(_STD::time_get<char>)
	MAKE_LOCALE(_STD::time_put<char>)
	MAKE_LOCALE(_STD::moneypunct<char>)
	typedef _STD::moneypunct<char, true> __moneypunct1;
	MAKE_LOCALE(__moneypunct1)
	MAKE_LOCALE(_STD::money_get<char>)
	MAKE_LOCALE(_STD::money_put<char>)
	#ifndef _MSL_NO_WCHART
		MAKE_LOCALE(_STD::collate<wchar_t>)
		MAKE_LOCALE(_STD::ctype<wchar_t>)
		typedef _STD::codecvt<wchar_t, char, mbstate_t> __codecvt2;
		MAKE_LOCALE(__codecvt2)
		MAKE_LOCALE(_STD::numpunct<wchar_t>)
		MAKE_LOCALE(_STD::num_get<wchar_t>)
		MAKE_LOCALE(_STD::num_put<wchar_t>)
		MAKE_LOCALE(_STD::timepunct<wchar_t>)
		MAKE_LOCALE(_STD::time_get<wchar_t>)
		MAKE_LOCALE(_STD::time_put<wchar_t>)
		MAKE_LOCALE(_STD::moneypunct<wchar_t>)
		typedef _STD::moneypunct<wchar_t, true> __moneypunct2;
		MAKE_LOCALE(__moneypunct2)
		MAKE_LOCALE(_STD::money_get<wchar_t>)
		MAKE_LOCALE(_STD::money_put<wchar_t>)
	#endif

	#undef MAKE_LOCALE
#endif

#ifdef _MSL_NO_MEMBER_TEMPLATE
	bool
	locale::operator()(const string& s1, const string& s2) const
	{
		return bool(_USE_FACET(_STD::collate<char>, *this).compare(
			s1.data(), s1.data()+s1.size(), s2.data(), s2.data()+s2.size()
		) < 0);
	}

	#ifndef _MSL_NO_WCHART
		bool
		locale::operator()(const wstring& s1, const wstring& s2) const
		{
			return bool(_USE_FACET(_STD::collate<wchar_t>, *this).compare(
				s1.data(), s1.data()+s1.size(), s2.data(), s2.data()+s2.size()
			) < 0);
		}
	#endif
#endif

locale
locale::global(const locale& loc)
{
	_RefCountedPtr<__locale_imp<true> > result = global_s;
	if (result == 0)
		result = classic().imp_;
	global_s = loc.imp_;
//	if (loc.name() != "*")
//		setlocale(LC_ALL, loc.name().c_str()); hh 990407 No setlocale support in Hitachi C Lib
	return locale(result);
}

const locale&
locale::classic()
{
	static locale C = make_classic();
	return C;
}

locale
locale::make_classic()
{
	_RefCountedPtr<__locale_imp<true> > result = new __locale_imp<true>;
	result->name() = "C";
	return locale(result);
}

#ifndef _MSL_NO_WCHART

	// ctype<wchar_t>

	template<>
	locale::id ctype<wchar_t>::id;

	// hh 980803 added.  non-standard
	template<>
	wstring
	ctype<wchar_t>::widen(const string& s) const
	{
		wstring result;
		result.resize(s.size());
		const char* s0 = s.c_str();
		widen(s0, s0 + s.size(), &result[0]);
		return result;
	}

	template<>
	const wchar_t*
	ctype<wchar_t>::do_is(const wchar_t* low, const wchar_t* high, mask* vec) const
	{
		const wchar_t* p;
		for (p = low; p < high; ++p)
			vec[p-low] = classify(*p);
		return high;
	}

	template<>
	const wchar_t*
	ctype<wchar_t>::do_scan_is(mask m, const wchar_t* low, const wchar_t* high) const
	{
		const wchar_t* p;
		for (p = low; p < high; ++p)
			if (classify(*p) & m)
				break;
		return p;
	}

	template<>
	const wchar_t*
	ctype<wchar_t>::do_scan_not(mask m, const wchar_t* low, const wchar_t* high) const
	{
		const wchar_t* p;
		for (p = low; p < high; ++p)
			if (!(classify(*p) & m))
				break;
		return p;
	}

	template<>
	const wchar_t*
	ctype<wchar_t>::do_toupper(wchar_t* low, const wchar_t* high) const
	{
		for (;low < high; ++low)
			*low = towupper(*low);
		return high;
	}

	template<>
	const wchar_t*
	ctype<wchar_t>::do_tolower(wchar_t* low, const wchar_t* high) const
	{
		for (;low < high; ++low)
			*low = towlower(*low);
		return high;
	}

	template<>
	const char*
	ctype<wchar_t>::do_widen(const char* low, const char* high, wchar_t* dest) const
	{
		while (low < high)
			*dest++ = wchar_t(*low++);
		return high;
	}

	template<>
	const wchar_t*
	ctype<wchar_t>::do_narrow(const wchar_t* low, const wchar_t* high, char dfault, char* dest) const
	{
		while (low < high)
			*dest++ = do_narrow(*low++, dfault);
		return high;
	}

	// hh 990330
	template<>
	ctype_base::mask
	ctype<wchar_t>::classify(wchar_t c) const
	{
		if (iswpunct(c))
			return punct;
		bool cn = (bool)iswcntrl(c);
		bool s = (bool)iswspace(c);
		if (cn & !s)
			return mask(0x01);
		else if (cn & s)
			return mask(0x02);
		else if (!cn & s)
			return mask(0x04);
		if (iswxdigit(c))
		{
			if (iswdigit(c))
				return mask(xdigit | digit);
			if (iswlower(c))
				return mask(xdigit | lower);
			return mask(xdigit | upper);
		}
		if (iswlower(c))
			return lower;
		if (iswupper(c))
			return upper;
		return mask(0);
	}

#endif

// ctype<char>

// hh 990109
#define __ct ctype_base::mask(0x01)
#define __mt ctype_base::mask(0x02)
#define __sp ctype_base::mask(0x04)
#define __pt ctype_base::mask(0x08)
#define __hd ctype_base::mask(0x30)
#define __lw ctype_base::mask(0x40)
#define __up ctype_base::mask(0x80)
#define __hl ctype_base::mask(0x60)
#define __hu ctype_base::mask(0xA0)

ctype_base::mask __mask_map[ctype<char>::table_size] =
{
//	 -0    -1    -2    -3    -4    -5    -6    -7    -8    -9    -A    -B    -C    -D    -E    -F
	__ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __mt, __mt, __mt, __mt, __mt, __ct, __ct, // 0-
	__ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, __ct, // 1-
	__sp, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, __pt, // 2-
	__hd, __hd, __hd, __hd, __hd, __hd, __hd, __hd, __hd, __hd, __pt, __pt, __pt, __pt, __pt, __pt, // 3-
	__pt, __hu, __hu, __hu, __hu, __hu, __hu, __up, __up, __up, __up, __up, __up, __up, __up, __up, // 4-
	__up, __up, __up, __up, __up, __up, __up, __up, __up, __up, __up, __pt, __pt, __pt, __pt, __pt, // 5-
	__pt, __hl, __hl, __hl, __hl, __hl, __hl, __lw, __lw, __lw, __lw, __lw, __lw, __lw, __lw, __lw, // 6-
	__lw, __lw, __lw, __lw, __lw, __lw, __lw, __lw, __lw, __lw, __lw, __pt, __pt, __pt, __pt, __ct  // 7-
};

template <>
ctype<char>::ctype(const mask* tab, bool del, size_t refs)
	: locale::facet(refs),
	table_(tab),
	owns_(del)
{
	if (table_ == 0)
	{
		table_ = classic_table();
		owns_ = false;
	}
}

template <>
ctype<char>::~ctype()
{
	if (owns_)
		delete [] table_;
}

template<>
const char*
ctype<char>::is(const char* low, const char* high, mask* vec) const
{
	for (const char* p = low; p < high; ++low)
		vec[p-low] = table_[(unsigned char)*p];
	return high;
}

template<>
const char*
ctype<char>::scan_is(mask m, const char* low, const char* high) const
{
	const char* p;
	for (p = low; p < high; ++p)
		if (table_[(unsigned char)*p] & m)
			break;
	return p;
}

template<>
const char*
ctype<char>::scan_not(mask m, const char* low, const char* high) const
{
	const char* p;
	for (p = low; p < high; ++p)
		if (!(table_[(unsigned char)*p] & m))
			break;
	return p;
}

template<>
locale::id ctype<char>::id;

template<>
const char*
ctype<char>::do_toupper(char* low, const char* high) const
{
	for (;low < high; ++low)
		*low = char(_STD::toupper(*low));
	return high;
}

template<>
const char*
ctype<char>::do_tolower(char* low, const char* high) const
{
	for (;low < high; ++low)
		*low = char(_STD::tolower(*low));
	return high;
}

// ctype_byname<char>

template<>
ctype_byname<char>::ctype_byname(const char* name, size_t refs)
	: ctype(0, false, refs),
	loc_(name),
	facet_(_USE_FACET(ctype<char>, loc_))
{
}

// codecvt<char, char, mbstate_t>

template <>
codecvt<char, char, mbstate_t>::codecvt(size_t refs)
	: _Generic_codecvt(refs)
{
}

template <>
locale::id codecvt<char, char, mbstate_t>::id;

// hh 990109  No longer used
//	template <>
//	codecvt_base::result
//	codecvt<char, char, mbstate_t>::do_nothing(
//		const char* from, const char* from_end, const char*& from_next,
//		char* to, char* to_limit, char*& to_next) const
//	{
//		size_t len = size_t(from_end - from);
//		size_t temp = size_t(to_limit - to);
//		result r = noconv;
//		if (len > temp)
//			len = temp;
//		from_next = from;
//		to_next = to;
//		memcpy(to, from, len);
//		return r;
//	}

#ifndef _MSL_NO_WCHART

	// codecvt<wchar_t, char, mbstate_t>

	template <>
	codecvt<wchar_t, char, mbstate_t>::codecvt(size_t refs)
		: _Generic_codecvt(refs)
	{
	}

	template <>
	locale::id codecvt<wchar_t, char, mbstate_t>::id;

	template <>
	codecvt_base::result
	codecvt<wchar_t, char, mbstate_t>::do_out(mbstate_t&,
		const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
		char* to, char* to_limit, char*& to_next) const
	{
		size_t ilen = size_t(from_end - from);
		size_t xlen = size_t(to_limit - to);
		size_t n = ilen;
		result r = ok;
		if (xlen < ilen)
		{
			r = partial;
			n = xlen;
		}
		from_next = from;
		to_next = to;
		for (size_t e = 0; e < n; ++e)
			*to_next++ = (char)*from_next++;
		return r;
	}

	template <>
	codecvt_base::result
	codecvt<wchar_t, char, mbstate_t>::do_in(mbstate_t&,
		const char* from, const char* from_end, const char*& from_next,
		wchar_t* to, wchar_t* to_limit, wchar_t*& to_next) const
	{
		size_t xlen = size_t(from_end - from);
		size_t ilen = size_t(to_limit - to);
		size_t n = xlen;
		result r = ok;
		if (ilen < xlen)
		{
			r = partial;
			n = ilen;
		}
		from_next = from;
		to_next = to;
		for (size_t e = 0; e < n; ++e)
			*to_next++ = (wchar_t)*from_next++;
		return r;
	}

#endif

// numpunct<char>

template <>
numpunct<char>::numpunct(size_t refs)
	: _Generic_numpunct(refs)
{
}

template <>
locale::id numpunct<char>::id;

#ifndef _MSL_NO_WCHART

	// numpunct<wchar_t>

	template <>
	numpunct<wchar_t>::numpunct(size_t refs)
		: _Generic_numpunct(refs)
	{
	}

	template <>
	locale::id numpunct<wchar_t>::id;

#endif

// timepunct<char>

template <>
timepunct<char>::timepunct(size_t refs)
	: _Generic_timepunct(refs)
{
}

template <>
locale::id timepunct<char>::id;

template <>
const char*
timepunct<char>::do_weekday_name(size_t d) const
{
	static const char* name[] = {
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", ""
	};
	if (d < 7)
		return name[d];
	return name[7];
}

template <>
const char*
timepunct<char>::do_month_name(size_t m) const
{
	static const char* name[] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December", ""
	};
	if (m < 12)
		return name[m];
	return name[12];
}

template <>
const char*
timepunct<char>::do_am_pm(int hour) const
{
	static const char* name[] = {"am", "pm"};
	return name[hour/12];
}

#ifndef _MSL_NO_WCHART

	// timepunct<wchar_t>

	template <>
	timepunct<wchar_t>::timepunct(size_t refs)
		: _Generic_timepunct(refs)
	{
	}

	template <>
	locale::id timepunct<wchar_t>::id;

	template <>
	const wchar_t*
	timepunct<wchar_t>::do_weekday_name(size_t d) const
	{
		static const wchar_t* name[] = {
			L"Sunday", L"Monday", L"Tuesday", L"Wednesday", L"Thursday", L"Friday", L"Saturday", L""
		};
		if (d < 7)
			return name[d];
		return name[7];
	}

	template <>
	const wchar_t*
	timepunct<wchar_t>::do_month_name(size_t m) const
	{
		static const wchar_t* name[] = {
			L"January", L"February", L"March", L"April", L"May", L"June",
			L"July", L"August", L"September", L"October", L"November", L"December", L""
		};
		if (m < 12)
			return name[m];
		return name[12];
	}

	template <>
	const wchar_t*
	timepunct<wchar_t>::do_am_pm(int hour) const
	{
		static const wchar_t* name[] = {L"am", L"pm"};
		return name[hour/12];
	}

#endif

// moneypunct<char, false>

template <>
moneypunct<char, false>::moneypunct(size_t refs)
	: _Generic_moneypunct(refs)
{
}

template <>
locale::id moneypunct<char, false>::id;

// moneypunct<char, true>

template <>
moneypunct<char, true>::moneypunct(size_t refs)
	: _Generic_moneypunct(refs)
{
}

template <>
locale::id moneypunct<char, true>::id;

#ifndef _MSL_NO_WCHART

	// moneypunct<wchar_t, false>

	template <>
	moneypunct<wchar_t, false>::moneypunct(size_t refs)
		: _Generic_moneypunct(refs)
	{
	}

	template <>
	locale::id moneypunct<wchar_t, false>::id;

	// moneypunct<wchar_t, true>

	template <>
	moneypunct<wchar_t, true>::moneypunct(size_t refs)
		: _Generic_moneypunct(refs)
	{
	}

	template <>
	locale::id moneypunct<wchar_t, true>::id;

#endif

#ifndef _No_Floating_Point

	// Binary Coded Decimal class
	// hh 980802 Added to assist in the printing of floating point values

	_BCD::_BCD(long double x, int limit)
		: exp_(0)
	{	// hh 990401
	#ifdef __MSL_LONGLONG_SUPPORT__
		if (limit <= DECIMAL_DIG)
		{
	#endif
			round_ = false;
			if (limit < 1)  // hh 990328
				limit = 1;
			char buff[512];
			sprintf(buff, "%#.*Le", limit-1,  x);
			mantissa_ = buff;
			// Get exponent
			string::iterator i = mantissa_.begin() + limit + 3;
			while (i != mantissa_.end())
			{
				exp_ *= 10;
				exp_ += short(*i - '0');
				++i;
			}
			i = mantissa_.begin() + limit + 2;
			if (*i == '-')
				exp_ = short(-exp_);
			--i;
			// Remove exponent and decimal point
			mantissa_.erase(i, mantissa_.end());
			mantissa_.erase(mantissa_.begin() + 1);
			for (i = mantissa_.begin(); i != mantissa_.end(); ++i)
				*i -= '0';
	#ifdef __MSL_LONGLONG_SUPPORT__
		}
		else
		{
			round_ = true;
			static const _BCD one_half("5", -1);
			if (x > 0)
			{
				int exp;
				long double frac = frexpl(x, &exp);
				_BCD bit = __two_exp(short(exp));
				while (frac != 0)
				{
					long double integer;
					frac = modfl(2*frac, &integer);
					--exp;
					bit *= one_half;
					if (integer != 0)
						*this += bit;
				}
			}
		}
	#endif
	}

	string
	_BCD::to_string(int precision, int& exponent) const
	{
		string result(mantissa_, 0, size_t(precision+1));
		exponent = exp_;
		string::iterator i = result.end() - 1;
		if (precision < result.size())
		{
			if (round_ && *i >= 5)
			{
				--i;
				while (true)
				{
					if (*i < 9)
					{
						(*i)++;
						break;
					}
					*i = char();
					if (i == result.begin())
					{
						result.insert(result.begin(), char(1));
						result.resize(result.size()-1);
						++exponent;
						break;
					}
					--i;
				}
			}
			result.resize(result.size()-1);
		}
		for (i = result.begin(); i != result.end(); ++i)
			*i += '0';
		return result;
	}

	_BCD::_BCD(const char* mantissa, int exponent)
		: mantissa_(mantissa),
		  exp_((short)exponent),
		  round_(true)
	{
		string::iterator i = mantissa_.begin();
		while (i != mantissa_.end())
			*i++ -= '0';
		trim();
	}

	_BCD&
	_BCD::operator += (_BCD rhs)
	{
		if (rhs.mantissa_.size() == 0)
			return *this;
		if (mantissa_.size() == 0)
		{
			*this = rhs;
			return *this;
		}
		if (exp_ > rhs.exp_)
		{
			rhs.mantissa_.insert(rhs.mantissa_.begin(), size_t(exp_ - rhs.exp_), char());
			rhs.exp_ = exp_;
		}
		else if (exp_ < rhs.exp_)
		{
			mantissa_.insert(mantissa_.begin(), size_t(rhs.exp_ - exp_), char());
			exp_ = rhs.exp_;
		}
		if (rhs.mantissa_.size() > mantissa_.size())
			mantissa_.resize(rhs.mantissa_.size(), char());
		else if (rhs.mantissa_.size() < mantissa_.size())
			rhs.mantissa_.resize(mantissa_.size(), char());
		size_t i = mantissa_.size() - 1;
		char carry = char();
		while (i > 0)
		{
			mantissa_[i] += char(rhs.mantissa_[i] + carry);
			if (mantissa_[i] > 9)
			{
				carry = char(mantissa_[i] / 10);
				mantissa_[i] %= char(10);
			}
			else
				carry = char();
			--i;
		}
		mantissa_[0] += char(rhs.mantissa_[0] + carry);
		if (mantissa_[0] > 9)
		{
			carry = char(mantissa_[0] / 10);
			mantissa_[0] %= char(10);
			mantissa_.insert(mantissa_.begin(), carry);
			++exp_;
		}
		trim();
		return *this;
	}

	_BCD&
	_BCD::operator *= (_BCD rhs)
	{	// hh 990401
	#ifdef __MSL_LONGLONG_SUPPORT__
		if (mantissa_.size() == 0)
			return *this;
		if (rhs.mantissa_.size() == 0)
		{
			*this = rhs;
			return *this;
		}
		_BCD lhs(*this);
		unsigned long long accumulator = 0;
		mantissa_.clear();
		mantissa_.resize(lhs.mantissa_.size() + rhs.mantissa_.size() - 1, char());
		for (long i = (long)mantissa_.size()-1; i >= 0; --i)
		{
			long k = (long)rhs.mantissa_.size() - 1;
			long j = i - k;
			if (j < 0)
			{
				j = 0;
				k = i;
			}
			while (j < lhs.mantissa_.size() && k >= 0)
			{
				accumulator += (unsigned long)lhs.mantissa_[size_t(j)] * rhs.mantissa_[size_t(k)];
				--k;
				++j;
			}
			mantissa_[size_t(i)] = char(accumulator % 10);
			accumulator /= 10;
		}
		exp_ = short(lhs.exp_ + rhs.exp_);
		while (accumulator > 0)
		{
			mantissa_.insert(mantissa_.begin(), char(accumulator % 10));
			accumulator /= 10;
			++exp_;
		}
		trim();
	#endif
		return *this;
	}

	_BCD
	__two_exp(short x)
	{
		static const _BCD one_sixteenth("625", -2);
		static const _BCD one_eighth("125", -1);
		static const _BCD one_fourth("25", -1);
		static const _BCD one_half("5", -1);
		static const _BCD one("1", 0);
		static const _BCD two("2", 0);
		static const _BCD four("4", 0);
		static const _BCD eight("8", 0);
		static const _BCD sixteen("16", 1);
		switch (x)
		{
		case -4:
			return one_sixteenth;
		case -3:
			return one_eighth;
		case -2:
			return one_fourth;
		case -1:
			return one_half;
		case 0:
			return one;
		case 1:
			return two;
		case 2:
			return four;
		case 3:
			return eight;
		case 4:
			return sixteen;
		}
		_BCD temp = __two_exp(short(x/2));
		temp *= temp;
		if (x % 2)
		{
			if (x > 0)
				temp *= two;
			else
				temp *= one_half;
		}
		return temp;
	}

#endif // _No_Floating_Point

#ifndef _MSL_NO_CPP_NAMESPACE
	}
#endif

// hh 980811 reworded dhex, uhex and lhex defines
// hh 980816 ARM/Standard neutral for-scoping
// hh 980902 #ifdef'd out exception code when ndef MSIPL_EXCEPT
// hh 980915 Modified file so that it would work without MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG
// hh 981018 Modified _BCD helper class to not round if it uses sprintf
// hh 981111 Removed dependence on compiler support for default template args in string declarations
// hh 990109 Created a C lib independent ctype_base::mask (suggested by bc).
// hh 990109 do_nothing no longer used
// hh 990120 changed name of MSIPL flags
// hh 990328 Fixed bug in floating point output rounding
// hh 990330 Rewrote classify().  It was completely bonkers
// hh 990401 _BCD::operator *= uses a long long.  Put this and any code that uses it
//           inside of #ifdef __MSL_LONGLONG_SUPPORT__