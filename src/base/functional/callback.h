#ifndef BASE_FUNCTIONAL_CALLBACK_H_
#define BASE_FUNCTIONAL_CALLBACK_H_

#include <type_traits>

namespace base {

// This class is used to achieve callback functionality.
// It wraps any functor, which could be invoked with arguments, specified in ArgumentTypes template argument, and will return object of type ReturnType.
template<typename ReturnType, typename... ArgumentTypes>
class OnceCallback {
  public:
  template<typename FunctorType>
  explicit OnceCallback(FunctorType&& functor) {
  }
};

}  // namespace base

#endif  // BASE_FUNCTIONAL_CALLBACK_H_