#include "test/common.h"

TEST_IMPL(point_normalize) {
  static const uint8_t x[] = {
    0x49, 0xe7, 0xcc, 0xf7, 0x7d, 0xfa, 0xf9, 0x9a,
    0xd2, 0x7e, 0x75, 0xf4, 0x44, 0x20, 0x67, 0x6c,
    0x80, 0x41, 0x4c, 0xcb, 0x15, 0xb7, 0xec, 0xb3,
    0x46, 0x8f, 0x6b, 0x78, 0x93, 0x8a, 0x41, 0x22
  };
  static const uint8_t z[] = {
    0xde, 0xde, 0x5e, 0x40, 0xdb, 0x21, 0x36, 0x5c,
    0x92, 0x48, 0xc8, 0x4f, 0xc0, 0xf9, 0xa0, 0x99,
    0xe3, 0x4c, 0x1d, 0x9d, 0x22, 0xdc, 0xed, 0x8b,
    0x10, 0xf4, 0xa5, 0x68, 0x21, 0xb5, 0x74, 0x4a
  };
  static const uint8_t expected[] = {
    0x81, 0x48, 0xf9, 0xce, 0xc1, 0x3b, 0x1e, 0xa1,
    0x8c, 0xa6, 0x1b, 0x01, 0x31, 0x94, 0x88, 0x59,
    0xd6, 0x9e, 0xea, 0x48, 0x8f, 0x9a, 0x30, 0x53,
    0x0d, 0x2e, 0x30, 0xd6, 0x21, 0x0a, 0x75, 0x3a
  };

  uint8_t bin[32];
  curve25519_point_t p;

  curve25519_point_init_ex(&p, x, z);
  curve25519_point_normalize(&p);

  CHECK_EQ(p.normalized, 1, "normalize() result should be normalized");
  CHECK(curve25519_num_is_one(&p.z), "normalized point's z must be one");

  curve25519_num_to_bin(bin, &p.x);
  check_equal_data(bin, expected, sizeof(bin), "x should match");
}
