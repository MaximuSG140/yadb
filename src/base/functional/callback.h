#ifndef BASE_FUNCTIONAL_CALLBACK_H_
#define BASE_FUNCTIONAL_CALLBACK_H_

#include <memory>
#include <type_traits>

#include "base/functional/callable_holder.h"
#include "base/functional/callback_forward.h"
#include "base/functional/callback_traits.h"

namespace base {

namespace internal {

template <typename CallbackTraits,
          typename ReturnType,
          typename... ArgumentTypes>
class CallbackBase {
 public:
  template <typename FunctorType>
  explicit CallbackBase(FunctorType&& functor)
      : holder_(CallbackTraits::MakeCallableHolder(
            std::forward<FunctorType>(functor))) {
  }

 protected:
  // Invokes callback with given arguments.
  ReturnType Invoke(ArgumentTypes&&... args) {
    auto holder = CallbackTraits::GetCallableHolderForInvoke(holder_);
    if (!holder) {
      return;
    }

    return holder->Invoke(std::forward<ArgumentTypes>(args)...);
  }

 private:
  typename CallbackTraits::FunctionHolder holder_;
};

}  // namespace internal

template <typename ReturnType, typename... ArgumentTypes>
class OnceCallback<ReturnType(ArgumentTypes...)>
    : public internal::CallbackBase<internal::CallbackTraits<
          OnceCallback<ReturnType(ArgumentTypes...)>>> {
 public:
  using Base = internal::CallbackBase<
      internal::CallbackTraits<OnceCallback<ReturnType(ArgumentTypes...)>>>;
  using Base::Base;

  ReturnType Invoke(ArgumentTypes&&... args) && {
    return Base::Invoke(std::forward<ArgumentTypes>(args)...);
  }
};

template <typename ReturnType, typename... ArgumentTypes>
class RepeatingCallback<ReturnType(ArgumentTypes...)>
    : public internal::CallbackBase<internal::CallbackTraits<
          RepeatingCallback<ReturnType(ArgumentTypes...)>>> {
 public:
  using Base = internal::CallbackBase<
      internal::CallbackTraits<RepeatingCallback<ReturnType(ArgumentTypes...)>>>;
  using Base::Base;

  ReturnType Invoke(ArgumentTypes&&... args) const& {
    return Base::Invoke(std::forward<ArgumentTypes>(args)...);
  }
};

}  // namespace base

#endif  // BASE_FUNCTIONAL_CALLBACK_H_