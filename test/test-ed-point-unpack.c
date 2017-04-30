#include "test/common.h"

TEST_IMPL(ed_point_unpack) {
  static const uint8_t point_bin[] = {
    0x9d, 0x95, 0xd6, 0x08, 0x87, 0xfe, 0x40, 0x9b,
    0x43, 0x23, 0x7f, 0x39, 0x76, 0x70, 0x9b, 0xbd,
    0x32, 0x3f, 0xdd, 0x15, 0x83, 0x6d, 0x4e, 0x47,
    0x36, 0xe8, 0xe0, 0x60, 0x73, 0xa7, 0x5e, 0x4a
  };
  static const uint8_t expected_x[] = {
    0xa4, 0xb7, 0xd6, 0x06, 0x6e, 0xaa, 0xba, 0xc6,
    0xf3, 0xe7, 0xe6, 0x19, 0x58, 0xb5, 0xc6, 0x28,
    0xfe, 0x01, 0x30, 0x02, 0x82, 0x18, 0x41, 0xc4,
    0x3b, 0xc4, 0xc6, 0xa5, 0xf9, 0xaa, 0x37, 0x78
  };
  static const uint8_t expected_y[] = {
    0x9d, 0x95, 0xd6, 0x08, 0x87, 0xfe, 0x40, 0x9b,
    0x43, 0x23, 0x7f, 0x39, 0x76, 0x70, 0x9b, 0xbd,
    0x32, 0x3f, 0xdd, 0x15, 0x83, 0x6d, 0x4e, 0x47,
    0x36, 0xe8, 0xe0, 0x60, 0x73, 0xa7, 0x5e, 0x4a
  };
  static const uint8_t expected_z[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  static const uint8_t expected_t[] = {
    0xde, 0x15, 0x2e, 0x87, 0xc4, 0x36, 0xc7, 0xee,
    0x0f, 0xa8, 0x71, 0x76, 0xd0, 0x08, 0x13, 0x1c,
    0x16, 0x78, 0x4a, 0x59, 0x4e, 0x0c, 0xc3, 0xbd,
    0xe4, 0x3e, 0x67, 0x24, 0x30, 0x17, 0x59, 0x17
  };
  curve25519_ed_point_t p;
  uint8_t bin[32];

  CHECK_EQ(curve25519_ed_point_from_bin(&p, point_bin), 0,
           "curve25519_ed_point_from_bin");
  CHECK_EQ(p.normalized, 1, "point must be normalized after unpack");

  curve25519_num_to_bin(bin, &p.x);
  check_equal_data(bin, expected_x, sizeof(bin), "unpack should give right x");

  curve25519_num_to_bin(bin, &p.y);
  check_equal_data(bin, expected_y, sizeof(bin), "unpack should give right y");

  curve25519_num_to_bin(bin, &p.z);
  check_equal_data(bin, expected_z, sizeof(bin), "unpack should give right z");

  curve25519_num_to_bin(bin, &p.t);
  check_equal_data(bin, expected_t, sizeof(bin), "unpack should give right t");
}
