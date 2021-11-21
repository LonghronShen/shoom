#if defined(_MSC_VER) || (defined(__BORLANDC__) && __BORLANDC__ >= 0x0650) || \
    (defined(__COMO__) && __COMO_VERSION__ >= 400) /* ??? */                  \
    || (defined(__DMC__) && __DMC__ >= 0x700)      /* ??? */                  \
    || (defined(__clang__) && __clang_major__ >= 3) ||                        \
    (defined(__GNUC__) &&                                                     \
     (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)))
#pragma once
#endif

#ifndef DACB06CE_B52C_403E_A6AA_E49B079829B3
#define DACB06CE_B52C_403E_A6AA_E49B079829B3

#include <cstddef>
#include <cstdint>
#include <string>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif  // _WIN32

namespace shoom {

enum ShoomError {
  kOK = 0,
  kErrorCreationFailed = 100,
  kErrorMappingFailed = 110,
  kErrorOpeningFailed = 120,
};

class Shm {
 public:
  // path should only contain alpha-numeric characters, and is normalized
  // on linux/macOS.
  explicit Shm(std::string path, std::size_t size);

  // create a shared memory area and open it for writing
  inline ShoomError Create() { return CreateOrOpen(true); };

  // open an existing shared memory for reading
  inline ShoomError Open() { return CreateOrOpen(false); };

  inline std::size_t Size() { return size_; };
  inline const std::string& Path() { return path_; }
  inline std::uint8_t* Data() { return data_; }

  ~Shm();

 private:
  ShoomError CreateOrOpen(bool create);

  std::string path_;
  std::uint8_t* data_ = nullptr;
  std::size_t size_ = 0;

#if defined(_WIN32)
  HANDLE handle_;
#else
  int fd_ = -1;
#endif
};
}  // namespace shoom

#endif /* DACB06CE_B52C_403E_A6AA_E49B079829B3 */
