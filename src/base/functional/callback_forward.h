#ifndef BASE_FUNCTIONAL_CALLBACK_FORWARD_H_
#define BASE_FUNCTIONAL_CALLBACK_FORWARD_H_

namespace base {

// Theese classes are used to achieve callback functionality.
// They wrap any functor, which could be invoked with arguments,
// specified in Signature, and will return object of type defined in signature.

// The |OnceCallback| class is used to guarantee, that callback will be called
// only once. After being invoked, |OnceCallback| becomes null.
// Usage of this class should be preferred over |RepeatingCallback| due to more
// strict invariants.
template<typename Signature>
class OnceCallback;

// This callback type can be invoked any number of times.
template<typename Signature>
class RepeatingCallback;

}  // namespace base

#endif // BASE_FUNCTIONAL_CALLBACK_FORWARD_H_
