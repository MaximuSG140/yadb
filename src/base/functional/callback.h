#ifndef BASE_FUNCTIONAL_CALLBACK_H_
#define BASE_FUNCTIONAL_CALLBACK_H_

#include <memory>
#include <type_traits>

#include "base/functional/functor_holder.h"
#include "functor_holder.h"

namespace base {

template<typename Signature>
class OnceCallback;


// This class is used to achieve callback functionality.
// It wraps any functor, which could be invoked with arguments,
// specified in ArgumentTypes template argument, and will return
// object of type ReturnType.
template<typename ReturnType, typename... ArgumentTypes>
class OnceCallback<ReturnType(ArgumentTypes...)> {
 public:
  template <typename FunctorType>
  explicit OnceCallback(FunctorType&& functor)
      : holder_(MakeFunctorHolder<FunctorType, ReturnType, ArgumentTypes...>(
            std::forward<FunctorType>(functor))) {}

  ReturnType Invoke(ArgumentTypes&&... args) && {
    auto holder = std::move(holder_);
    if (!holder) {
      return;
    }

    return holder->Invoke(std::forward<ArgumentTypes>(args)...);
  }

 private:
  std::unique_ptr<FunctorHolder<ReturnType, ArgumentTypes...>> holder_;
};

}  // namespace base

#endif  // BASE_FUNCTIONAL_CALLBACK_H_