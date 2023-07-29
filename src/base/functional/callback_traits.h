#ifndef BASE_FUNCTIONAL_CALLBACK_TRAITS_H
#define BASE_FUNCTIONAL_CALLBACK_TRAITS_H

#include <memory>

#include "base/functional/callable_holder.h"
#include "base/functional/callback_forward.h"

namespace base::internal {

// TODO: convert to concepts for clearer error messages.
template<template<typename> typename Callback>
struct CallbackTraits;

template<typename ReturnType, typename... ArgumentTypes>
struct CallbackTraits<OnceCallback<ReturnType(ArgumentTypes...)>> {
  using FunctionHolder =
      std::unique_ptr<CallableHolder<ReturnType, ArgumentTypes...>>;

  template<typename FunctorType>
  static StorageType MakeCallableHolder(FunctorType&& functor) {
    return std::make_unique<
        CallableHolderImpl<FunctorType, ReturnType, ArgumentTypes...>>;
  }

  static StorageType GetCallableHolderForInvoke(StorageType& stored_callable) {
    return std::move(stored_callable);
  }
};

template<typename ReturnType, typename... ArgumentTypes>
struct CallbackTraits<RepeatingCallback<ReturnType(ArgumentTypes...)>> {
  using FunctionHolder =
      std::shared_ptr<CallableHolder<ReturnType, ArgumentTypes...>>;

  template <typename FunctorType>
  static StorageType MakeCallableHolder(FunctorType&& functor) {
    return std::make_shared<
        CallableHolderImpl<FunctorType, ReturnType, ArgumentTypes...>>(
        std::forward<FunctorType>(functor));
  }

  static StorageType GetCallableHolderForInvoke(StorageType& stored_callable) {
    return stored_callable;
  }
};

}  // namespace base::internal

#endif // BASE_FUNCTIONAL_CALLBACK_TRAITS_H