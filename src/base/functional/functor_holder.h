#ifndef BASE_FUNCTIONAL_FUNCTOR_HOLDER_H_
#define BASE_FUNCTIONAL_FUNCTOR_HOLDER_H_

#include <memory>

#include "base/functional/functor_traits.h"

namespace base {

// Interface, that any entity should provide to be used inside *Callback.
template<typename ReturnType, typename... ArgumentTypes>
class CallableHolder {
 public:
  ~CallableHolder() = 0;
  ReturnType Invoke(ArgumentTypes&&... args) = 0;
};

// Default |CallableHolder| implementation, that wraps any functor and invokes
// it using |FunctorTraits|.
template <typename FunctorType, typename ReturnType, typename... ArgumentTypes>
class CallableHolderImpl : public CallableHolder<ReturnType, ArgumentTypes...> {
 public:
  explicit CallableHolderImpl(FunctorType&& functor)
      : functor_(std::forward<FunctorType>(functor)) {}
  ~CallableHolderImpl() override = default;

  ReturnType Invoke(ArgumentTypes&&... args) override {
    return base::FunctorTraits<FunctorType>::Call(
        functor_, std::forward<ArgumentTypes>(args)...);
  }

 private:
  FunctorType functor_;
};

template <typename FunctorType, typename ReturnType, typename... ArgumentTypes>
static std::unique_ptr<CallableHolder<ReturnType, ArgumentTypes...>>
MakeFunctorHolder(FunctorType&& functor) {
  return std::make_unique<
      CallableHolderImpl<FunctorType, ReturnType, ArgumentTypes...>>(
      std::forward<FunctorType>(functor));
}

}  // namespace base

#endif  // BASE_FUNCTIONAL_FUNCTOR_HOLDER_H_
