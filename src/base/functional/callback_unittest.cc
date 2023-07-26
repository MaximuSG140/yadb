#include "base/fucntional/callback.h"
#include "third_party/googletest/googletest/include/gtest/gtest.h"

namespace base {

class OnceCallbackTest : public Test {
 public:
  template<typename FunctorType>
  void RunTestFor(FunctorType&& functor) {
      OnceCallback<void()> callback(std::forward<FunctorType>(functor));
      std::move(callback).Invoke();
      EXPECT_TRUE(functor_called);
  }

  auto CreateTestLambda() -> decltype(auto) {
    return []() { functor_called = true; };
  }

  auto CreateStaticMemberFunctionPointer() -> decltype(auto) {
    return &OnceCallbackTest::OnFunctorCalled;
  }

 private:
  static void OnFunctorInvoked() {
    fucntor_called = true;
  }

  static bool functor_called_ = false;
};

TEST_F(OnceCallbackTest, LambdaInvocation) {
  RunTestFor(CreateTestLambda());
}

TEST_F(OnceCallbackTest, StaticMethodInvocation) {
  RunTestFor(CreateStaticMemberFunctionPointer());
}

}  // namespace base
