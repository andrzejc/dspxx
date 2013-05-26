/**
 * @file dsp++/simd.h
 * @brief Support for SIMD instructions
 */
#ifndef DSP_SIMD_H_INCLUDED
#define DSP_SIMD_H_INCLUDED
#pragma once

#include <dsp++/export.h>

namespace dsp { namespace simd {

	//! @brief Processor architecture flags, not really useful in runtime - use DSP_ARCH_XXX macros in <dsp++/platform.h> instead.
	enum arch {
		arch_unknown = 			0x0000,		//!<
		arch_x86 = 				0x0001,   	//!< 32-bit x86 (IA32)
		arch_x86_64 = 			0x0002, 	//!< 64-bit x86 (x86-64 aka AMD64)
		arch_ppc =				0x0004,		//!< PowerPC
		// TODO add flags for other architectures, esp. ARM
	};

	//! @brief Query the architecture of the runtime environment (for which the code was compiled on, not the actual processor).
	//! @note If the code is compiled for x86 (32 bit executable) and is running on x86-64 processor, this will return {@link arch_x86}.
	//! This is intentional, as you can't use 64-bit instructions in 32-bit executable anyway.
	//! @return Combination of {@link arch} flags describing processor architecture.
	DSPXX_API int get_architecture();

	//! @brief SIMD feature flags.
	//! @note For various architectures the same bits may have different meaning. It's by design, as code sections for different architectures
	//! normally will have to be #ifdef'ed (you'll get compile time errors otherwise).
	//! @todo Add flags for other architectures when needed.
	enum feat {
		feat_x86_mmx = 			0x00000001,	//!< MMX instruction set @see http://en.wikipedia.org/wiki/MMX_(instruction_set)
		feat_x86_sse = 			0x00000002,	//!< SSE instruction set (Katmai new instructions) @see http://en.wikipedia.org/wiki/Streaming_SIMD_Extensions
		feat_x86_sse2 =			0x00000004, //!< SSE2 instruction set @see http://en.wikipedia.org/wiki/SSE2
		feat_x86_sse3 = 		0x00000008, //!< SSE3 instruction set (Prescott new instructions) @see http://en.wikipedia.org/wiki/Prescott_New_Instructions
		feat_x86_ssse3 = 		0x00000010, //!< Supplemental SSE3 instructions @see http://en.wikipedia.org/wiki/SSSE3
		feat_x86_fma3 = 		0x00000020, //!< FMA3 instruction set @see http://en.wikipedia.org/wiki/FMA_instruction_set
		feat_x86_sse4_1 =		0x00000040, //!< Penryn SSE 4.1 @see http://en.wikipedia.org/wiki/SSE4.1#SSE4.1
		feat_x86_sse4_2 =		0x00000080, //!< Nehalem SSE 4.2 @see http://en.wikipedia.org/wiki/SSE4.2#SSE4.2
		feat_x86_avx = 			0x00000100, //!< Advanced Vector Extensions @see http://en.wikipedia.org/wiki/Advanced_Vector_Extensions

		feat_x86_xop = 			0x00000200,	//!< AMD XOP @see http://en.wikipedia.org/wiki/XOP_instruction_set @note Not detected yet!
		feat_x86_fma4 =			0x00000400,	//!< AMD FMA4 @see http://en.wikipedia.org/wiki/FMA4_instruction_set @note Not detected yet!
		// leaving 5 bits reserved for other x86 features
		feat_ppc_altivec =		0x00010000,	//!< PowerPC AltiVec instructions @see http://en.wikipedia.org/wiki/AltiVec @note Not detected yet!
		// and now ARM features...
	};

	//! @brief Allows testing SIMD support of the processor in the runtime, so that alternative execution paths may be used depending on available features.
	//! @return Combination of {@link feat} flags describing available SIMD features.
	DSPXX_API int get_features();

} }

#endif /* DSP_SIMD_H_INCLUDED */