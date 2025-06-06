#pragma once

// hex_digits_bits is indexed on the digit:
// ie: hex_digits_bits[0] is the bits to display 0 on
// the screen stored in xbm format
static const uint8_t hex_digits_bits[][36] = {
  {
    0x7C, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0x38, 0x00, 0x3C, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x38, 0x00, 0x38, 0x00,
    0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00,
    0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0xFE, 0x00, 0xFE, 0x00, 0xFE, 0x00,
  },
  {
    0x7C, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC0, 0x01,
    0xC0, 0x01, 0xE0, 0x00, 0xF0, 0x00, 0x78, 0x00, 0x3C, 0x00, 0x1E, 0x00,
    0x0E, 0x00, 0x0F, 0x00, 0x07, 0x00, 0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01,
  },
  {
    0x7C, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC0, 0x01,
    0xC0, 0x01, 0xF8, 0x00, 0x78, 0x00, 0xF8, 0x00, 0xC0, 0x01, 0xC0, 0x01,
    0xC0, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0xE0, 0x00, 0xE0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF8, 0x00, 0xF8, 0x00,
    0xF8, 0x00, 0xFC, 0x00, 0xEC, 0x00, 0xEE, 0x00, 0xE6, 0x00, 0xFF, 0x01,
    0xFF, 0x01, 0xFF, 0x01, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x00,
  },
  {
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00,
    0x7F, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC0, 0x01, 0xC0, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0x7C, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0x07, 0x00,
    0x07, 0x00, 0x77, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x01, 0xE0, 0x00, 0xE0, 0x00, 0x70, 0x00,
    0x70, 0x00, 0x70, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00,
    0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00,
  },
  {
    0x7C, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xFE, 0x00, 0x7C, 0x00, 0xFE, 0x00, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0x7C, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x01, 0xDC, 0x01, 0xC0, 0x01,
    0xC0, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0xFE, 0x00,
    0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xF0, 0x01, 0xFC, 0x01, 0xCE, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xE7, 0x01, 0xFF, 0x01, 0xDF, 0x01, 0xCE, 0x01,
  },
  {
    0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0xE7, 0x00, 0xF7, 0x01,
    0xFF, 0x01, 0xCF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xCF, 0x01, 0xFF, 0x01, 0xF7, 0x01, 0xE7, 0x00,
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0xFE, 0x00,
    0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00,
    0x07, 0x00, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xCE, 0x01, 0xDF, 0x01,
    0xFF, 0x01, 0xE7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01,
    0xC7, 0x01, 0xC7, 0x01, 0xE7, 0x01, 0xFF, 0x01, 0xDF, 0x01, 0xCE, 0x01,
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0xFE, 0x00,
    0xFF, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFF, 0x01,
    0x07, 0x00, 0xC7, 0x01, 0xC7, 0x01, 0xFF, 0x01, 0xFE, 0x00, 0x7C, 0x00,
  },
  {
    0xE0, 0x00, 0xF0, 0x00, 0xF8, 0x00, 0x38, 0x00, 0xFE, 0x00, 0xFE, 0x00,
    0xFE, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00,
    0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00,
  }
};
