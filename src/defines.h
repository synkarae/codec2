/*---------------------------------------------------------------------------*\

  FILE........: defines.h                                                     
  AUTHOR......: David Rowe 
  DATE CREATED: 23/4/93                                                       
                                                                             
  Defines and structures used throughout the codec.			     
                                                                             
\*---------------------------------------------------------------------------*/

/*
  Copyright (C) 2009 David Rowe

  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1, as
  published by the Free Software Foundation.  This program is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

/*
Copyright (c) 2014, Robert C. Taylor (Synkarae)
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*/

#ifndef __DEFINES__
#define __DEFINES__

/*---------------------------------------------------------------------------*\
                                                                             
				DEFINES                                       
                                                                             
\*---------------------------------------------------------------------------*/

/* General defines */

#define N          80		/* number of samples per frame          */
#define MAX_AMP    80		/* maximum number of harmonics          */
#define PI         3.141592654	/* mathematical constant                */
#define TWO_PI     6.283185307	/* mathematical constant                */
#define FS         8000		/* sample rate in Hz                    */
#define MAX_STR    256          /* maximum string size                  */

#define NW         279          /* analysis window size                 */
#define FFT_ENC    512		/* size of FFT used for encoder         */
#define FFT_DEC    512	    	/* size of FFT used in decoder          */
#define TW         40		/* Trapezoidal synthesis window overlap */
#define V_THRESH   6.0          /* voicing threshold in dB              */

#define LPC_ORD    10		/* phase modelling LPC order            */

/* Pitch estimation defines */

#define M        320		/* pitch analysis frame size            */
#define P_MIN    20		/* minimum pitch                        */
#define P_MAX    160		/* maximum pitch                        */

/*---------------------------------------------------------------------------*\
                                                                             
				TYPEDEFS                                      
                                                                             
\*---------------------------------------------------------------------------*/

/* Structure to hold model parameters for one frame */


#ifdef MATH_Q16_16
#include "libfixmath/fixmath.h"
#  define scalar fix16_t
#else
# ifndef scalar
/*  default is float */
#   define scalar float
# endif
#endif



#ifdef MATH_Q16_16
#  define s_add(a, b) (fix16_sadd(a,b))
#  define s_mul(a, b) (fix16_smul(a,b))
#  define s_div(q, r) (fix16_sdiv(q, r))
#  define s_sub(a, b) (fix16_ssub(a, b))
#  define fl_to_numb(a) (fix16_from_float(a))
#  define fl_from_numb(a) (fix16_to_float(a))
#  define s_log10(a) (fix16_log(a)/fix16_log(10))
#  define s_powf(x, y) (fix16_exp(s_mul(y,fix16_log(x))))
#  define numb_to_int(x) (fix16_to_int(x))
#  define s_sqrt(x)  (fix16_sqrt(x))
#  define s_abs(x)  (fix16_abs(x))
#  define s_atan2(y, x) (fix16_atan2(y, x))
#  define s_cos(x) (fix16_cos(x))
#  define s_sin(x) (fix16_sin(x))
#  define int_to_numb(x) (fix16_from_int(x))
# else
#  define s_add(a, b) (a + b)
#  define s_mul(a, b) (a * b)
#  define s_div(q, r) (q / r)
#  define s_sub(a, b) (a - b)
#  define fl_to_numb(a) (a)
#  define fl_from_numb(a) (a)
#  define s_log10(a) (log10f(a))
#  define s_powf(x, y) (powf(x, y))
#  define numb_to_int(x) ((int)x)
#  define s_sqrt(x)  (sqrtf(x))
#  define s_abs(x)  (fabsf(x))
#  define s_atan2(y, x) (atan2f(y,x))
#  define s_cos(x) (cosf(x))
#  define s_sin(x) (sinf(x))
#  define int_to_numb(x) (x)
# endif

typedef struct {
  scalar Wo;		/* fundamental frequency estimate in radians  */
  int   L;		/* number of harmonics                        */
  scalar A[MAX_AMP+1];	/* amplitiude of each harmonic                */
  scalar phi[MAX_AMP+1];	/* phase of each harmonic                     */
  int   voiced;	        /* non-zero if this frame is voiced           */
} MODEL;

/* describes each codebook  */

struct lsp_codebook {
    int			k;        /* dimension of vector	*/
    int			log2m;    /* number of bits in m	*/
    int			m;        /* elements in codebook	*/
    const scalar	*	cb;	  /* The elements		*/
};

extern const struct lsp_codebook lsp_cb[];
extern const struct lsp_codebook lsp_cbd[];
extern const struct lsp_codebook lsp_cbvq[];
extern const struct lsp_codebook lsp_cbjnd[];
extern const struct lsp_codebook lsp_cbdt[];
extern const struct lsp_codebook lsp_cbjvm[];
extern const struct lsp_codebook lsp_cbvqanssi[];
extern const struct lsp_codebook ge_cb[];

#endif
