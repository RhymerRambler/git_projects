#include<functional>

// A user-defined wrapper over a container, that accepts a transform function
// applies the transform function when operator [] is invoked
// So, this is like the views in the std::ranges library
template <typename Cont,
          typename Fn=std::function<typename Cont::value_type(typename Cont::value_type)>>
class TransformView
{
  public:
    TransformView(Cont& c, Fn f) : mCont(c), mFn(f) {
    }
    using value_type = typename Cont::value_type;
    value_type operator [](int i) {
      return mFn(mCont[i]);
    }
  private:
    Cont& mCont;
    Fn mFn;
};

