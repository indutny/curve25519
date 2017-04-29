#include "test/common.h"

static test_field_single_vector_t inv_vectors[] = {
  {
    .num = {
      0xbf, 0xa8, 0x63, 0x8b, 0x3e, 0xf7, 0x8a, 0xd7,
      0xc6, 0xf1, 0x29, 0x6e, 0x06, 0x9d, 0x8f, 0xc0,
      0x7b, 0xde, 0x8e, 0xbf, 0xb7, 0x31, 0xc4, 0xd2,
      0x55, 0x4a, 0xec, 0x8c, 0x3a, 0x62, 0x70, 0x4e
    },
    .expected = {
      0x4f, 0xcf, 0x53, 0x11, 0xef, 0x6f, 0x3d, 0x1d,
      0xa9, 0x59, 0xe1, 0x15, 0xdb, 0xf7, 0x95, 0x12,
      0x32, 0x78, 0x25, 0xfb, 0xa1, 0x53, 0xe2, 0x3c,
      0x89, 0x4e, 0xb4, 0x45, 0xf6, 0xec, 0xfd, 0x74
    },
    .description = "random data"
  },
  {
    .num = {
      0x91, 0xc0, 0x08, 0x1d, 0xa9, 0xf7, 0xa6, 0xdf,
      0x5e, 0x94, 0x5b, 0x36, 0x4d, 0xcc, 0xd3, 0xf8,
      0xdf, 0x4b, 0xac, 0xa3, 0xdf, 0xa5, 0xe7, 0x70,
      0xc0, 0x4e, 0x0e, 0xd2, 0x02, 0xea, 0x43, 0x5d
    },
    .expected = {
      0xda, 0xee, 0x99, 0x8d, 0x0d, 0xac, 0xf3, 0x45,
      0xc8, 0xc9, 0x7c, 0x35, 0x4d, 0x5c, 0xf1, 0xa9,
      0x24, 0x71, 0x2f, 0x05, 0x37, 0x23, 0x9a, 0x32,
      0xdd, 0xaa, 0x17, 0x32, 0x09, 0xee, 0x9a, 0x23
    },
    .description = "random data #2"
  },
  {
    .num = {
      0x90, 0x67, 0x53, 0xc5, 0x0b, 0xba, 0x82, 0x38,
      0xb1, 0x71, 0x3d, 0xdf, 0x8f, 0x73, 0x91, 0x54,
      0x08, 0x4f, 0xf9, 0x13, 0x07, 0x95, 0x92, 0x52,
      0xf0, 0x11, 0x9d, 0x86, 0xb9, 0xb0, 0xcc, 0x24
    },
    .expected = {
      0xe3, 0x1a, 0xde, 0x3a, 0x8d, 0x52, 0xc0, 0xec,
      0xd0, 0x6b, 0xcc, 0xfc, 0x07, 0xf4, 0x88, 0x02,
      0x46, 0xe0, 0xa3, 0x4e, 0x9f, 0x8a, 0x37, 0xcd,
      0xce, 0xc4, 0xfe, 0x61, 0x6b, 0xda, 0x5f, 0x72
    },
    .description = "random data #3"
  },
  {
    .num = {
      0xe9, 0x5d, 0xeb, 0x70, 0x2f, 0x8f, 0x4e, 0x27,
      0xff, 0xfb, 0x2f, 0xa0, 0xf8, 0x45, 0x92, 0x39,
      0x8b, 0x2a, 0x54, 0xac, 0x17, 0xa6, 0xbb, 0x56,
      0xc3, 0x63, 0x56, 0x68, 0xe7, 0xce, 0x00, 0x8f
    },
    .expected = {
      0x74, 0xc0, 0x5e, 0x16, 0xd4, 0xa2, 0x86, 0xe9,
      0x57, 0x3a, 0x76, 0x5c, 0x2e, 0x7a, 0x4e, 0xa6,
      0x8c, 0xb4, 0xfc, 0x23, 0x0d, 0x32, 0x85, 0x51,
      0xe8, 0xdd, 0x1f, 0x79, 0x13, 0x25, 0xa4, 0x39
    },
    .description = "non-normalized input"
  }
};

TEST_IMPL(field_inv) {
  unsigned int i;

  for (i = 0; i < ARRAY_SIZE(inv_vectors); i++) {
    curve25519_num_t num;
    curve25519_num_t original;
    uint8_t bin[32];

    curve25519_num_from_bin(&original, inv_vectors[i].num);
    curve25519_num_copy(&num, &original);
    curve25519_num_inv(&num, &num);
    curve25519_num_to_bin(bin, &num);

    check_equal_data(bin, inv_vectors[i].expected, sizeof(bin),
                     inv_vectors[i].description);

    /* Second inverse */
    curve25519_num_copy(&num, &original);
    curve25519_num_inv(&num, &num);
    curve25519_num_inv(&num, &num);

    curve25519_num_normalize(&num);
    curve25519_num_normalize(&original);
    CHECK_EQ(curve25519_num_cmp(&num, &original), 0, "double inverse");
  }
}
