/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:06 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  complex.cpp
 **/

#include <complex>

#ifndef _No_Floating_Point

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

#ifdef _MSL_NO_MEMBER_TEMPLATE

	#ifdef _MSL_CX_LIMITED_RANGE

		template <>
		complex<float>&
		complex<float>::operator*=(const complex& rhs)
		{
			float re = re_;
			re_ = re * rhs.real() - im_ * rhs.imag();
			im_ = re * rhs.imag() + im_ * rhs.real();
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator*=(const complex<double>& rhs)
		{
			float re = re_;
			re_ = re * (float)rhs.real() - im_ * (float)rhs.imag();
			im_ = re * (float)rhs.imag() + im_ * (float)rhs.real();
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator*=(const complex<long double>& rhs)
		{
			float re = re_;
			re_ = re * (float)rhs.real() - im_ * (float)rhs.imag();
			im_ = re * (float)rhs.imag() + im_ * (float)rhs.real();
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator*=(const complex& rhs)
		{
			double re = re_;
			re_ = re * rhs.real() - im_ * rhs.imag();
			im_ = re * rhs.imag() + im_ * rhs.real();
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator*=(const complex<float>& rhs)
		{
			double re = re_;
			re_ = re * rhs.real() - im_ * rhs.imag();
			im_ = re * rhs.imag() + im_ * rhs.real();
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator*=(const complex<long double>& rhs)
		{
			double re = re_;
			re_ = re * (double)rhs.real() - im_ * (double)rhs.imag();
			im_ = re * (double)rhs.imag() + im_ * (double)rhs.real();
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator*=(const complex& rhs)
		{
			long double re = re_;
			re_ = re * rhs.real() - im_ * rhs.imag();
			im_ = re * rhs.imag() + im_ * rhs.real();
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator*=(const complex<float>& rhs)
		{
			long double re = re_;
			re_ = re * rhs.real() - im_ * rhs.imag();
			im_ = re * rhs.imag() + im_ * rhs.real();
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator*=(const complex<double>& rhs)
		{
			long double re = re_;
			re_ = re * rhs.real() - im_ * rhs.imag();
			im_ = re * rhs.imag() + im_ * rhs.real();
			return *this;
		}

		// -

		template <>
		complex<float>&
		complex<float>::operator/=(const complex& rhs)
		{
			float denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
			float re = re_;
			re_ = (re * rhs.real() + im_ * rhs.imag()) / denom;
			im_ = (im_ * rhs.real() - re * rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator/=(const complex<double>& rhs)
		{
			float denom = (float)rhs.real() * (float)rhs.real()
			            + (float)rhs.imag() * (float)rhs.imag();
			float re = re_;
			re_ = (re * (float)rhs.real() + im_ * (float)rhs.imag()) / denom;
			im_ = (im_ * (float)rhs.real() - re * (float)rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator/=(const complex<long double>& rhs)
		{
			float denom = (float)rhs.real() * (float)rhs.real()
			            + (float)rhs.imag() * (float)rhs.imag();
			float re = re_;
			re_ = (re * (float)rhs.real() + im_ * (float)rhs.imag()) / denom;
			im_ = (im_ * (float)rhs.real() - re * (float)rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator/=(const complex& rhs)
		{
			double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
			double re = re_;
			re_ = (re * rhs.real() + im_ * rhs.imag()) / denom;
			im_ = (im_ * rhs.real() - re * rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator/=(const complex<float>& rhs)
		{
			double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
			double re = re_;
			re_ = (re * rhs.real() + im_ * rhs.imag()) / denom;
			im_ = (im_ * rhs.real() - re * rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator/=(const complex<long double>& rhs)
		{
			double denom = (double)rhs.real() * (double)rhs.real()
			             + (double)rhs.imag() * (double)rhs.imag();
			double re = re_;
			re_ = (re * (double)rhs.real() + im_ * (double)rhs.imag()) / denom;
			im_ = (im_ * (double)rhs.real() - re * (double)rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator/=(const complex& rhs)
		{
			long double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
			long double re = re_;
			re_ = (re * rhs.real() + im_ * rhs.imag()) / denom;
			im_ = (im_ * rhs.real() - re * rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator/=(const complex<float>& rhs)
		{
			long double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
			long double re = re_;
			re_ = (re * rhs.real() + im_ * rhs.imag()) / denom;
			im_ = (im_ * rhs.real() - re * rhs.imag()) / denom;
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator/=(const complex<double>& rhs)
		{
			long double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
			long double re = re_;
			re_ = (re * rhs.real() + im_ * rhs.imag()) / denom;
			im_ = (im_ * rhs.real() - re * rhs.imag()) / denom;
			return *this;
		}

	#else

		template <>
		complex<float>&
		complex<float>::operator*=(const complex& rhs)
		{
			float a = re_;
			float b = im_;
			float c = rhs.real();
			float d = rhs.imag();
			float ac = a * c;
			float bd = b * d;
			float ad = a * d;
			float bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysignf(isinf(a) ? 1.0F : 0.0F, a);
					b = copysignf(isinf(b) ? 1.0F : 0.0F, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysignf(0.0F, c);
					if (isnan(d))
						d = copysignf(0.0F, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysignf(isinf(c) ? 1.0F : 0.0F, c);
					d = copysignf(isinf(d) ? 1.0F : 0.0F, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysignf(0.0F, a);
					if (isnan(b))
						b = copysignf(0.0F, b);
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysignf(0.0F, a);
						if (isnan(b))
							b = copysignf(0.0F, b);
						if (isnan(c))
							c = copysignf(0.0F, c);
						if (isnan(d))
							d = copysignf(0.0F, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysignf(HUGE_VALF, ( a * c - b * d ));
					im_ = copysignf(HUGE_VALF, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator*=(const complex<double>& rhs)
		{
			float a = re_;
			float b = im_;
			float c = (float)rhs.real();
			float d = (float)rhs.imag();
			float ac = a * c;
			float bd = b * d;
			float ad = a * d;
			float bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysignf(isinf(a) ? 1.0F : 0.0F, a);
					b = copysignf(isinf(b) ? 1.0F : 0.0F, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysignf(0.0F, c);
					if (isnan(d))
						d = copysignf(0.0F, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysignf(isinf(c) ? 1.0F : 0.0F, c);
					d = copysignf(isinf(d) ? 1.0F : 0.0F, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysignf(0.0F, a);
					if (isnan(b))
						b = copysignf(0.0F, b);
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysignf(0.0F, a);
						if (isnan(b))
							b = copysignf(0.0F, b);
						if (isnan(c))
							c = copysignf(0.0F, c);
						if (isnan(d))
							d = copysignf(0.0F, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysignf(HUGE_VALF, ( a * c - b * d ));
					im_ = copysignf(HUGE_VALF, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator*=(const complex<long double>& rhs)
		{
			float a = re_;
			float b = im_;
			float c = (float)rhs.real();
			float d = (float)rhs.imag();
			float ac = a * c;
			float bd = b * d;
			float ad = a * d;
			float bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysignf(isinf(a) ? 1.0F : 0.0F, a);
					b = copysignf(isinf(b) ? 1.0F : 0.0F, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysignf(0.0F, c);
					if (isnan(d))
						d = copysignf(0.0F, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysignf(isinf(c) ? 1.0F : 0.0F, c);
					d = copysignf(isinf(d) ? 1.0F : 0.0F, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysignf(0.0F, a);
					if (isnan(b))
						b = copysignf(0.0F, b);
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysignf(0.0F, a);
						if (isnan(b))
							b = copysignf(0.0F, b);
						if (isnan(c))
							c = copysignf(0.0F, c);
						if (isnan(d))
							d = copysignf(0.0F, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysignf(HUGE_VALF, ( a * c - b * d ));
					im_ = copysignf(HUGE_VALF, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator*=(const complex& rhs)
		{
			double a = re_;
			double b = im_;
			double c = rhs.real();
			double d = rhs.imag();
			double ac = a * c;
			double bd = b * d;
			double ad = a * d;
			double bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysign(isinf(a) ? 1.0 : 0.0, a);
					b = copysign(isinf(b) ? 1.0 : 0.0, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysign(0.0, c);
					if (isnan(d))
						d = copysign(0.0, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysign(isinf(c) ? 1.0 : 0.0, c);
					d = copysign(isinf(d) ? 1.0 : 0.0, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysign(0.0, a);
					if (isnan(b))
						b = copysign(0.0, b);
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysign(0.0, a);
						if (isnan(b))
							b = copysign(0.0, b);
						if (isnan(c))
							c = copysign(0.0, c);
						if (isnan(d))
							d = copysign(0.0, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysign(HUGE_VAL, ( a * c - b * d ));
					im_ = copysign(HUGE_VAL, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator*=(const complex<float>& rhs)
		{
			double a = re_;
			double b = im_;
			double c = rhs.real();
			double d = rhs.imag();
			double ac = a * c;
			double bd = b * d;
			double ad = a * d;
			double bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysign(isinf(a) ? 1.0 : 0.0, a);
					b = copysign(isinf(b) ? 1.0 : 0.0, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysign(0.0, c);
					if (isnan(d))
						d = copysign(0.0, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysign(isinf(c) ? 1.0 : 0.0, c);
					d = copysign(isinf(d) ? 1.0 : 0.0, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysign(0.0, a);
					if (isnan(b))
						b = copysign(0.0, b);
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysign(0.0, a);
						if (isnan(b))
							b = copysign(0.0, b);
						if (isnan(c))
							c = copysign(0.0, c);
						if (isnan(d))
							d = copysign(0.0, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysign(HUGE_VAL, ( a * c - b * d ));
					im_ = copysign(HUGE_VAL, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator*=(const complex<long double>& rhs)
		{
			double a = re_;
			double b = im_;
			double c = (double)rhs.real();
			double d = (double)rhs.imag();
			double ac = a * c;
			double bd = b * d;
			double ad = a * d;
			double bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysign(isinf(a) ? 1.0 : 0.0, a);
					b = copysign(isinf(b) ? 1.0 : 0.0, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysign(0.0, c);
					if (isnan(d))
						d = copysign(0.0, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysign(isinf(c) ? 1.0 : 0.0, c);
					d = copysign(isinf(d) ? 1.0 : 0.0, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysign(0.0, a);
					if (isnan(b))
						b = copysign(0.0, b);
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysign(0.0, a);
						if (isnan(b))
							b = copysign(0.0, b);
						if (isnan(c))
							c = copysign(0.0, c);
						if (isnan(d))
							d = copysign(0.0, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysign(HUGE_VAL, ( a * c - b * d ));
					im_ = copysign(HUGE_VAL, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator*=(const complex& rhs)
		{
			long double a = re_;
			long double b = im_;
			long double c = rhs.real();
			long double d = rhs.imag();
			long double ac = a * c;
			long double bd = b * d;
			long double ad = a * d;
			long double bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysignl(isinf(a) ? 1.0L : 0.0L, a);
					b = copysignl(isinf(b) ? 1.0L : 0.0L, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysignl(0.0L, c);
					if (isnan(d))
						d = copysignl(0.0L, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysignl(isinf(c) ? 1.0L : 0.0L, c);
					d = copysignl(isinf(d) ? 1.0L : 0.0L, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysignl(0.0L, a);
					if (isnan(b))
						b = copysignl(0.0L, b); // hh 980821
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysignl(0.0L, a);
						if (isnan(b))
							b = copysignl(0.0L, b);
						if (isnan(c))
							c = copysignl(0.0L, c);
						if (isnan(d))
							d = copysignl(0.0L, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysignl(HUGE_VALL, ( a * c - b * d ));
					im_ = copysignl(HUGE_VALL, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator*=(const complex<float>& rhs)
		{
			long double a = re_;
			long double b = im_;
			long double c = rhs.real();
			long double d = rhs.imag();
			long double ac = a * c;
			long double bd = b * d;
			long double ad = a * d;
			long double bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysignl(isinf(a) ? 1.0L : 0.0L, a);
					b = copysignl(isinf(b) ? 1.0L : 0.0L, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysignl(0.0L, c);
					if (isnan(d))
						d = copysignl(0.0L, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysignl(isinf(c) ? 1.0L : 0.0L, c);
					d = copysignl(isinf(d) ? 1.0L : 0.0L, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysignl(0.0L, a);
					if (isnan(b))
						b = copysignl(0.0L, b); // hh 980821
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysignl(0.0L, a);
						if (isnan(b))
							b = copysignl(0.0L, b);
						if (isnan(c))
							c = copysignl(0.0L, c);
						if (isnan(d))
							d = copysignl(0.0L, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysignl(HUGE_VALL, ( a * c - b * d ));
					im_ = copysignl(HUGE_VALL, ( a * d + b * c ));
				}
			}
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator*=(const complex<double>& rhs)
		{
			long double a = re_;
			long double b = im_;
			long double c = rhs.real();
			long double d = rhs.imag();
			long double ac = a * c;
			long double bd = b * d;
			long double ad = a * d;
			long double bc = b * c;
			re_ = ac - bd;
			im_ = ad + bc;
			// Recover infinities that computed as NaN+iNaN ... 
			if (isnan(re_) && isnan(im_))
			{
				bool recalc = false;
				if ( isinf(a) || isinf(b) ) // z is infinite
				{
					// "Box" the infinity ... 
					a = copysignl(isinf(a) ? 1.0L : 0.0L, a);
					b = copysignl(isinf(b) ? 1.0L : 0.0L, b);
					// Change NaNs in the other factor to 0 ...
					if (isnan(c))
						c = copysignl(0.0L, c);
					if (isnan(d))
						d = copysignl(0.0L, d);
					recalc = true;
				}
				if ( isinf(c) || isinf(d) ) // w is infinite
				{
					// "Box" the infinity ...
					c = copysignl(isinf(c) ? 1.0L : 0.0L, c);
					d = copysignl(isinf(d) ? 1.0L : 0.0L, d);
					// Change NaNs in the other factor to 0 ...
					if (isnan(a))
						a = copysignl(0.0L, a);
					if (isnan(b))
						b = copysignl(0.0L, b); // hh 980821
					recalc = true;
				}
				if (!recalc) {
					// Recover infinities from overflow cases ... 
					if (isinf(ac) || isinf(bd) || isinf(ad) || isinf(bc))
					{
						// Change all NaNs to 0 ...
						if (isnan(a))
							a = copysignl(0.0L, a);
						if (isnan(b))
							b = copysignl(0.0L, b);
						if (isnan(c))
							c = copysignl(0.0L, c);
						if (isnan(d))
							d = copysignl(0.0L, d);
						recalc = true;
					}
				}
				if (recalc)
				{
					re_ = copysignl(HUGE_VALL, ( a * c - b * d ));
					im_ = copysignl(HUGE_VALL, ( a * d + b * c ));
				}
			}
			return *this;
		}

		// -

		template <>
		complex<float>&
		complex<float>::operator/=(const complex& rhs)
		{
			int ilogbw = 0;
			float a = re_;
			float b = im_;
			float c = rhs.real();
			float d = rhs.imag();
			float logbw = logbf(fmaxf(fabsf(c), fabsf(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbnf(c, -ilogbw);
				d = scalbnf(d, -ilogbw);
			}
			float denom = c * c + d * d;
			re_ = scalbnf((a * c + b * d) / denom, -ilogbw);
			im_ = scalbnf((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysignf(HUGE_VALF, c) * a;
					im_ = copysignf(HUGE_VALF, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysignf(isinf(a) ? 1.0F : 0.0F, a);
					b = copysignf(isinf(b) ? 1.0F : 0.0F, b);
					re_ = copysignf(HUGE_VALF, ( a * c + b * d ));
					im_ = copysignf(HUGE_VALF, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysignf(isinf(c) ? 1.0F : 0.0F, c);
					d = copysignf(isinf(d) ? 1.0F : 0.0F, d);
					re_ = 0.0F * ( a * c + b * d );
					im_ = 0.0F * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator/=(const complex<double>& rhs)
		{
			int ilogbw = 0;
			float a = re_;
			float b = im_;
			float c = (float)rhs.real();
			float d = (float)rhs.imag();
			float logbw = logbf(fmaxf(fabsf(c), fabsf(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbnf(c, -ilogbw);
				d = scalbnf(d, -ilogbw);
			}
			float denom = c * c + d * d;
			re_ = scalbnf((a * c + b * d) / denom, -ilogbw);
			im_ = scalbnf((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysignf(HUGE_VALF, c) * a;
					im_ = copysignf(HUGE_VALF, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysignf(isinf(a) ? 1.0F : 0.0F, a);
					b = copysignf(isinf(b) ? 1.0F : 0.0F, b);
					re_ = copysignf(HUGE_VALF, ( a * c + b * d ));
					im_ = copysignf(HUGE_VALF, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysignf(isinf(c) ? 1.0F : 0.0F, c);
					d = copysignf(isinf(d) ? 1.0F : 0.0F, d);
					re_ = 0.0F * ( a * c + b * d );
					im_ = 0.0F * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<float>&
		complex<float>::operator/=(const complex<long double>& rhs)
		{
			int ilogbw = 0;
			float a = re_;
			float b = im_;
			float c = (float)rhs.real();
			float d = (float)rhs.imag();
			float logbw = logbf(fmaxf(fabsf(c), fabsf(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbnf(c, -ilogbw);
				d = scalbnf(d, -ilogbw);
			}
			float denom = c * c + d * d;
			re_ = scalbnf((a * c + b * d) / denom, -ilogbw);
			im_ = scalbnf((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysignf(HUGE_VALF, c) * a;
					im_ = copysignf(HUGE_VALF, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysignf(isinf(a) ? 1.0F : 0.0F, a);
					b = copysignf(isinf(b) ? 1.0F : 0.0F, b);
					re_ = copysignf(HUGE_VALF, ( a * c + b * d ));
					im_ = copysignf(HUGE_VALF, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysignf(isinf(c) ? 1.0F : 0.0F, c);
					d = copysignf(isinf(d) ? 1.0F : 0.0F, d);
					re_ = 0.0F * ( a * c + b * d );
					im_ = 0.0F * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator/=(const complex& rhs)
		{
			int ilogbw = 0;
			double a = re_;
			double b = im_;
			double c = rhs.real();
			double d = rhs.imag();
			double logbw = logb(fmax(fabs(c), fabs(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbn(c, -ilogbw);
				d = scalbn(d, -ilogbw);
			}
			double denom = c * c + d * d;
			re_ = scalbn((a * c + b * d) / denom, -ilogbw);
			im_ = scalbn((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysign(HUGE_VAL, c) * a;
					im_ = copysign(HUGE_VAL, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysign(isinf(a) ? 1.0 : 0.0, a);
					b = copysign(isinf(b) ? 1.0 : 0.0, b);
					re_ = copysign(HUGE_VAL, ( a * c + b * d ));
					im_ = copysign(HUGE_VAL, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysign(isinf(c) ? 1.0 : 0.0, c);
					d = copysign(isinf(d) ? 1.0 : 0.0, d);
					re_ = 0.0 * ( a * c + b * d );
					im_ = 0.0 * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator/=(const complex<float>& rhs)
		{
			int ilogbw = 0;
			double a = re_;
			double b = im_;
			double c = rhs.real();
			double d = rhs.imag();
			double logbw = logb(fmax(fabs(c), fabs(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbn(c, -ilogbw);
				d = scalbn(d, -ilogbw);
			}
			double denom = c * c + d * d;
			re_ = scalbn((a * c + b * d) / denom, -ilogbw);
			im_ = scalbn((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysign(HUGE_VAL, c) * a;
					im_ = copysign(HUGE_VAL, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysign(isinf(a) ? 1.0 : 0.0, a);
					b = copysign(isinf(b) ? 1.0 : 0.0, b);
					re_ = copysign(HUGE_VAL, ( a * c + b * d ));
					im_ = copysign(HUGE_VAL, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysign(isinf(c) ? 1.0 : 0.0, c);
					d = copysign(isinf(d) ? 1.0 : 0.0, d);
					re_ = 0.0 * ( a * c + b * d );
					im_ = 0.0 * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<double>&
		complex<double>::operator/=(const complex<long double>& rhs)
		{
			int ilogbw = 0;
			double a = re_;
			double b = im_;
			double c = (double)rhs.real();
			double d = (double)rhs.imag();
			double logbw = logb(fmax(fabs(c), fabs(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbn(c, -ilogbw);
				d = scalbn(d, -ilogbw);
			}
			double denom = c * c + d * d;
			re_ = scalbn((a * c + b * d) / denom, -ilogbw);
			im_ = scalbn((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysign(HUGE_VAL, c) * a;
					im_ = copysign(HUGE_VAL, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysign(isinf(a) ? 1.0 : 0.0, a);
					b = copysign(isinf(b) ? 1.0 : 0.0, b);
					re_ = copysign(HUGE_VAL, ( a * c + b * d ));
					im_ = copysign(HUGE_VAL, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysign(isinf(c) ? 1.0 : 0.0, c);
					d = copysign(isinf(d) ? 1.0 : 0.0, d);
					re_ = 0.0 * ( a * c + b * d );
					im_ = 0.0 * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator/=(const complex& rhs)
		{
			int ilogbw = 0;
			long double a = re_;
			long double b = im_;
			long double c = rhs.real();
			long double d = rhs.imag();
			long double logbw = logbl(fmaxl(fabsl(c), fabsl(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbnl(c, -ilogbw);
				d = scalbnl(d, -ilogbw);
			}
			long double denom = c * c + d * d;
			re_ = scalbnl((a * c + b * d) / denom, -ilogbw);
			im_ = scalbnl((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysignl(HUGE_VALL, c) * a;
					im_ = copysignl(HUGE_VALL, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysignl(isinf(a) ? 1.0L : 0.0L, a);
					b = copysignl(isinf(b) ? 1.0L : 0.0L, b);
					re_ = copysignl(HUGE_VALL, ( a * c + b * d ));
					im_ = copysignl(HUGE_VALL, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysignl(isinf(c) ? 1.0L : 0.0L, c);
					d = copysignl(isinf(d) ? 1.0L : 0.0L, d);
					re_ = 0.0L * ( a * c + b * d );
					im_ = 0.0L * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator/=(const complex<float>& rhs)
		{
			int ilogbw = 0;
			long double a = re_;
			long double b = im_;
			long double c = rhs.real();
			long double d = rhs.imag();
			long double logbw = logbl(fmaxl(fabsl(c), fabsl(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbnl(c, -ilogbw);
				d = scalbnl(d, -ilogbw);
			}
			long double denom = c * c + d * d;
			re_ = scalbnl((a * c + b * d) / denom, -ilogbw);
			im_ = scalbnl((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysignl(HUGE_VALL, c) * a;
					im_ = copysignl(HUGE_VALL, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysignl(isinf(a) ? 1.0L : 0.0L, a);
					b = copysignl(isinf(b) ? 1.0L : 0.0L, b);
					re_ = copysignl(HUGE_VALL, ( a * c + b * d ));
					im_ = copysignl(HUGE_VALL, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysignl(isinf(c) ? 1.0L : 0.0L, c);
					d = copysignl(isinf(d) ? 1.0L : 0.0L, d);
					re_ = 0.0L * ( a * c + b * d );
					im_ = 0.0L * ( b * c - a * d );
				}
			}
			return *this;
		}

		template <>
		complex<long double>&
		complex<long double>::operator/=(const complex<double>& rhs)
		{
			int ilogbw = 0;
			long double a = re_;
			long double b = im_;
			long double c = rhs.real();
			long double d = rhs.imag();
			long double logbw = logbl(fmaxl(fabsl(c), fabsl(d)));
			if (isfinite(logbw))
			{
				ilogbw = (int)logbw;
				c = scalbnl(c, -ilogbw);
				d = scalbnl(d, -ilogbw);
			}
			long double denom = c * c + d * d;
			re_ = scalbnl((a * c + b * d) / denom, -ilogbw);
			im_ = scalbnl((b * c - a * d) / denom, -ilogbw);

			// Recover infinities and zeros that computed
			// as NaN+iNaN; the only cases are non-zero/zero,
			// infinite/finite, and finite/infinite, ...

			if (isnan(re_) && isnan(im_))
			{
				if ((denom == 0) && (!isnan(a) || !isnan(b)))
				{
					re_ = copysignl(HUGE_VALL, c) * a;
					im_ = copysignl(HUGE_VALL, c) * b;
				}
				else if ((isinf(a) || isinf(b)) && isfinite(c) && isfinite(d))
				{
					a = copysignl(isinf(a) ? 1.0L : 0.0L, a);
					b = copysignl(isinf(b) ? 1.0L : 0.0L, b);
					re_ = copysignl(HUGE_VALL, ( a * c + b * d ));
					im_ = copysignl(HUGE_VALL, ( b * c - a * d ));
				}
				else if (isinf(logbw) && isfinite(a) && isfinite(b))
				{
					c = copysignl(isinf(c) ? 1.0L : 0.0L, c);
					d = copysignl(isinf(d) ? 1.0L : 0.0L, d);
					re_ = 0.0L * ( a * c + b * d );
					im_ = 0.0L * ( b * c - a * d );
				}
			}
			return *this;
		}

	#endif // _MSL_CX_LIMITED_RANGE

#endif // !_MSL_NO_MEMBER_TEMPLATE
/*
template <>
complex<int>
pow<int>(const complex<int>& x, int y)
{
	complex<int> result(1);
	for (int i = 0; i < y; ++i)
		result *= x;
	return result;
}
*/
#ifndef _MSL_NO_CPP_NAMESPACE
	}
#endif

#endif // _No_Floating_Point

// hh 971220 fixed MOD_INCLUDE
// mf 980130 merged in division algorithm
// hh 980408 wrapped in #ifndef _No_Floating_Point
// hh 990120 changed name of MSIPL flags
