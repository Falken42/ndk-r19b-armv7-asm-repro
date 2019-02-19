#include <cstdint>
#include <atomic>

typedef int32_t s32;
typedef uint8_t u8;
typedef uint32_t u32;
typedef u32 uint;

template <typename T>
class Atomic
{
public:
 Atomic(const T &val);

 bool cmpxchg_weak(T &expected, T desired);

 Atomic & operator ++(void);
 Atomic & operator --(void);

 template <typename U>
 friend bool operator > (const Atomic &lhs, const U &rhs)
 {
  return (lhs.mVal > static_cast<T>(rhs));
 }

private:
 std::atomic<T> mVal;
};

template <typename T>
inline bool Atomic<T>::cmpxchg_weak(T &expected, T desired)
{
 return mVal.compare_exchange_weak(expected, desired);
}

template <typename T>
inline Atomic<T> &Atomic<T>::operator ++(void)
{
 T expected = mVal.load();
 while (!cmpxchg_weak(expected, expected + 1));
 return *this;
}

template <typename T>
inline Atomic<T> &Atomic<T>::operator --(void)
{
 T expected = mVal.load();
 while (!cmpxchg_weak(expected, expected - 1));
 return *this;
}

template <typename T, uint TStackCount = 32>
class Array
{
private:
 T mLocal[TStackCount];
};

class Mutex
{
public:
 void lock(void);
 void unlock(void);

private:
// pthread_mutex_t mMutex;
};

class AutoMutex
{
public:
 AutoMutex(Mutex &mutex);
 ~AutoMutex(void);

 void lock(void);
 void unlock(void);

private:
 Mutex &    mMutex;
 Atomic<uint> mLockCount;
};

inline AutoMutex::AutoMutex(Mutex &mutex) : mMutex(mutex), mLockCount(0)
{
 lock();
}

inline AutoMutex::~AutoMutex(void)
{
 unlock();
}

inline void AutoMutex::lock(void)
{
 // mMutex.lock();
 ++mLockCount;
}

inline void AutoMutex::unlock(void)
{
 if (mLockCount > 0)
 {
  --mLockCount;
  // mMutex.unlock();
 }
}

class CommandData
{
public:
 u8 data[32];
};

class CommandQueue
{
private:
 Array<CommandData> mBuffer;
};

class IMTRenderer
{
public:
void flush(void);
void submit(const CommandQueue &cmd);

private:
 Mutex mMarkerMutex;
};

void IMTRenderer::flush(void)
{
 AutoMutex mtx(mMarkerMutex);
 CommandQueue cmd;
 submit(cmd);
}
