#include "xstl/xstl.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

GENERATE_SOA_LAYOUT(SimpleSoALayout,
                    SOA_COLUMN(float, x),
                    SOA_COLUMN(float, y),
                    SOA_COLUMN(float, z),
                    SOA_SCALAR(int, id))

using SimpleSoA = SimpleSoALayout<>;

TEST_CASE("Test a simple SoA functionality") {
  std::byte* buffer;
  int elements = 10;
  buffer = reinterpret_cast<std::byte*>(
      aligned_alloc(SimpleSoA::alignment, SimpleSoA::computeDataSize(elements)));
  SimpleSoA soa(buffer, elements);
  auto t = SimpleSoA::View{soa};
  t.id() = 42;
  for (int i = 0; i < elements; ++i) {
    t.x()[i] = static_cast<float>(i);
    t.y()[i] = static_cast<float>(i) + 1.0f;
    t.z()[i] = static_cast<float>(i) + 2.0f;
  }

  for (int i = 0; i < elements; ++i) {
    CHECK(t.x()[i] == static_cast<float>(i));
    CHECK(t.y()[i] == static_cast<float>(i) + 1.0f);
    CHECK(t.z()[i] == static_cast<float>(i) + 2.0f);
    CHECK(t.id() == 42);
  }

  free(buffer);
}