#ifndef BASE_FUNCTIONAL_FUNCTOR_TRAITS_H_
#define BASE_FUNCTIONAL_FUNCTOR_TRAITS_H_

#include <utility>

namespace base {

// Class FunctorTraits can be used to define custom ways to handle different
// functor properties.
// Those include calling a functor with provided arguments and receiving functor
// return type.
template<typename FunctorType>
struct FunctorTraits {
  template<typename ReturnType, typename... ArgumentTypes>
  ReturnType Call(FunctorType& functor, ArgumentTypes&&... args) {
    return functor(std::forward<ArgumentTypes>(args)...);
  }

  template <typename... ArgumentTypes>
  using ReturnType =
      decltype(std::declval<FunctorType>()(std::declval<ArgumentTypes>()...));
};

}  // namespace base

#endif  // BASE_FUNCTIONAL_FUNCTOR_TRAITS_H_
