/// @file dsp++/algorithm.h
/// @brief Various unassorted algorithms loosely complementing these found in &lt;algorithm&gt;.
#ifndef DSP_ALGORITHM_H_INCLUDED
#define DSP_ALGORITHM_H_INCLUDED

#include <dsp++/config.h>
#include <dsp++/concept_checks.h>

#include <iterator>
#include <functional>

namespace dsp {

/// @brief Copy at most n elements from the [src_begin, src_end) sequence into sequence starting at dest.
/// The source and destination sequences must not overlap.
/// @param src_begin start of sequence to copy.
/// @param src_end end of sequence to copy.
/// @param dest the destination of copy operation.
/// @param n maximum number of elements to copy.
/// @return number of copied elements, min(src_end - src_begin, n).
/// @tparam InputIterator type of the src_begin and src_end iterators, which must conform to
/// input iterator concept.
/// @tparam OutputIterator type of the dest iterator, which must conform to output iterator concept
/// and its value type must be convertible to the value type of InputIterator.
template<class InputIterator, class Size, class OutputIterator> inline
DSP_CONCEPT_REQUIRES(((boost::InputIterator<InputIterator>))
	((boost::OutputIterator<OutputIterator, typename std::iterator_traits<InputIterator>::value_type>))
	((boost::Integer<Size>)),
(Size))
copy_at_most_n(InputIterator src_begin, InputIterator src_end, Size n, OutputIterator dest)
{
	Size i;
	for (i = 0; (i < n) && (src_begin != src_end); ++i, ++dest, ++src_begin)
		*dest = *src_begin;
	return i;
}

/// @brief Copy n elements from the [src, src + n) sequence into [dest, dest + n). The source and destination
/// sequences must not overlap.
/// @param src start of sequence to copy.
/// @param n number of elements to copy.
/// @param dest the destination of copy operation.
/// @return dest + n.
/// @tparam InputIterator type of the src iterator, which must conform to
/// input iterator concept.
/// @tparam OutputIterator type of the dest iterator, which must conform to output iterator concept
/// and its value type must be convertible to the value type of InputIterator.
template<class InputIterator, class Size, class OutputIterator> inline
DSP_CONCEPT_REQUIRES(((boost::InputIterator<InputIterator>))
	((boost::OutputIterator<OutputIterator, typename std::iterator_traits<InputIterator>::value_type>))
	((boost::Integer<Size>)),
(OutputIterator))
copy_n(InputIterator src, Size n, OutputIterator dest)
{
	for (Size i = 0; i < n; ++i, ++dest, ++src)
		*dest = *src;
	return dest;
}

/// @brief Base class for simple, sample-based algorithms which work by transforming input samples into
/// output samples in one-to-one manner. Such algorithm will have an `sample_type operator()(sample_type in)`
/// function which takes input sample and returns transformed output sample. This class is a specialization
/// of @p std::unary_function stereotype with input and output types being the same - {@link sample_type}.
/// @tparam Sample type of input and output sample.
template<class Sample>
struct sample_based_transform
{
	using result_type = Sample;
	using argument_type = Sample;
	//! @brief Type of input/output sample.
	typedef Sample sample_type;
};

/// @brief "static_cast" turned functional - functor whose sole purpose is to cast input value to specific type,
/// possibly ensuring compilability and getting the intent clear.
/// @tparam To the type the input is getting casted to.
template<class To>
struct static_caster
{
	template<class From>
	To operator()(From val) {return static_cast<To>(val);}

	To operator()(To val) {return val;}
};

}

#endif /* DSP_ALGORITHM_H_INCLUDED */
