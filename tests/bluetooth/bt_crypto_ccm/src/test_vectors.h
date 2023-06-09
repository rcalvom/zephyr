/* Copyright (c) 2023 Nordic Semiconductor ASA
 * SPDx-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdint.h>

#define NUMBER_OF_TEST 24

struct test_data {
	const uint8_t *input;
	const uint8_t *expected_output;
	const uint8_t key[16];
	uint8_t nonce[13];

	const size_t aad_len; /* Additional Authenticated Data length */
	const size_t mic_len; /* MIC length, defined as MAC in the RFC */
	const size_t input_len;
	size_t expected_output_len;
};

/* Data from RFC3610 test vectors:
 * https://www.rfc-editor.org/rfc/rfc3610
 */

const uint8_t packet_vector_1[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
				   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
				   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E};
const uint8_t packet_vector_2[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
				   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
				   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
const uint8_t packet_vector_3[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
				   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
				   0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
				   0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
const uint8_t packet_vector_4[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
				   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
				   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E};
const uint8_t packet_vector_5[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
				   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
				   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
const uint8_t packet_vector_6[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
				   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
				   0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
				   0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
const uint8_t packet_vector_7[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
				   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
				   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E};
const uint8_t packet_vector_8[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
				   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
				   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
const uint8_t packet_vector_9[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
				   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
				   0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
				   0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
const uint8_t packet_vector_10[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
				    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
				    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E};
const uint8_t packet_vector_11[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
				    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
				    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
const uint8_t packet_vector_12[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
				    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
				    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
				    0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
const uint8_t packet_vector_13[] = {0x0B, 0xE1, 0xA8, 0x8B, 0xAC, 0xE0, 0x18, 0xB1,
				    0x08, 0xE8, 0xCF, 0x97, 0xD8, 0x20, 0xEA, 0x25,
				    0x84, 0x60, 0xE9, 0x6A, 0xD9, 0xCF, 0x52, 0x89,
				    0x05, 0x4D, 0x89, 0x5C, 0xEA, 0xC4, 0x7C};
const uint8_t packet_vector_14[] = {0x63, 0x01, 0x8F, 0x76, 0xDC, 0x8A, 0x1B, 0xCB,
				    0x90, 0x20, 0xEA, 0x6F, 0x91, 0xBD, 0xD8, 0x5A,
				    0xFA, 0x00, 0x39, 0xBA, 0x4B, 0xAF, 0xF9, 0xBF,
				    0xB7, 0x9C, 0x70, 0x28, 0x94, 0x9C, 0xD0, 0xEC};
const uint8_t packet_vector_15[] = {0xAA, 0x6C, 0xFA, 0x36, 0xCA, 0xE8, 0x6B, 0x40, 0xB9,
				    0x16, 0xE0, 0xEA, 0xCC, 0x1C, 0x00, 0xD7, 0xDC, 0xEC,
				    0x68, 0xEC, 0x0B, 0x3B, 0xBB, 0x1A, 0x02, 0xDE, 0x8A,
				    0x2D, 0x1A, 0xA3, 0x46, 0x13, 0x2E};
const uint8_t packet_vector_16[] = {0xD0, 0xD0, 0x73, 0x5C, 0x53, 0x1E, 0x1B, 0xEC,
				    0xF0, 0x49, 0xC2, 0x44, 0x12, 0xDA, 0xAC, 0x56,
				    0x30, 0xEF, 0xA5, 0x39, 0x6F, 0x77, 0x0C, 0xE1,
				    0xA6, 0x6B, 0x21, 0xF7, 0xB2, 0x10, 0x1C};
const uint8_t packet_vector_17[] = {0x77, 0xB6, 0x0F, 0x01, 0x1C, 0x03, 0xE1, 0x52,
				    0x58, 0x99, 0xBC, 0xAE, 0xE8, 0x8B, 0x6A, 0x46,
				    0xC7, 0x8D, 0x63, 0xE5, 0x2E, 0xB8, 0xC5, 0x46,
				    0xEF, 0xB5, 0xDE, 0x6F, 0x75, 0xE9, 0xCC, 0x0D};
const uint8_t packet_vector_18[] = {0xCD, 0x90, 0x44, 0xD2, 0xB7, 0x1F, 0xDB, 0x81, 0x20,
				    0xEA, 0x60, 0xC0, 0x64, 0x35, 0xAC, 0xBA, 0xFB, 0x11,
				    0xA8, 0x2E, 0x2F, 0x07, 0x1D, 0x7C, 0xA4, 0xA5, 0xEB,
				    0xD9, 0x3A, 0x80, 0x3B, 0xA8, 0x7F};
const uint8_t packet_vector_19[] = {0xD8, 0x5B, 0xC7, 0xE6, 0x9F, 0x94, 0x4F, 0xB8,
				    0x8A, 0x19, 0xB9, 0x50, 0xBC, 0xF7, 0x1A, 0x01,
				    0x8E, 0x5E, 0x67, 0x01, 0xC9, 0x17, 0x87, 0x65,
				    0x98, 0x09, 0xD6, 0x7D, 0xBE, 0xDD, 0x18};
const uint8_t packet_vector_20[] = {0x74, 0xA0, 0xEB, 0xC9, 0x06, 0x9F, 0x5B, 0x37,
				    0x17, 0x61, 0x43, 0x3C, 0x37, 0xC5, 0xA3, 0x5F,
				    0xC1, 0xF3, 0x9F, 0x40, 0x63, 0x02, 0xEB, 0x90,
				    0x7C, 0x61, 0x63, 0xBE, 0x38, 0xC9, 0x84, 0x37};
const uint8_t packet_vector_21[] = {0x44, 0xA3, 0xAA, 0x3A, 0xAE, 0x64, 0x75, 0xCA, 0xA4,
				    0x34, 0xA8, 0xE5, 0x85, 0x00, 0xC6, 0xE4, 0x15, 0x30,
				    0x53, 0x88, 0x62, 0xD6, 0x86, 0xEA, 0x9E, 0x81, 0x30,
				    0x1B, 0x5A, 0xE4, 0x22, 0x6B, 0xFA};
const uint8_t packet_vector_22[] = {0xEC, 0x46, 0xBB, 0x63, 0xB0, 0x25, 0x20, 0xC3,
				    0x3C, 0x49, 0xFD, 0x70, 0xB9, 0x6B, 0x49, 0xE2,
				    0x1D, 0x62, 0x17, 0x41, 0x63, 0x28, 0x75, 0xDB,
				    0x7F, 0x6C, 0x92, 0x43, 0xD2, 0xD7, 0xC2};
const uint8_t packet_vector_23[] = {0x47, 0xA6, 0x5A, 0xC7, 0x8B, 0x3D, 0x59, 0x42,
				    0x27, 0xE8, 0x5E, 0x71, 0xE2, 0xFC, 0xFB, 0xB8,
				    0x80, 0x44, 0x2C, 0x73, 0x1B, 0xF9, 0x51, 0x67,
				    0xC8, 0xFF, 0xD7, 0x89, 0x5E, 0x33, 0x70, 0x76};
const uint8_t packet_vector_24[] = {0x6E, 0x37, 0xA6, 0xEF, 0x54, 0x6D, 0x95, 0x5D, 0x34,
				    0xAB, 0x60, 0x59, 0xAB, 0xF2, 0x1C, 0x0B, 0x02, 0xFE,
				    0xB8, 0x8F, 0x85, 0x6D, 0xF4, 0xA3, 0x73, 0x81, 0xBC,
				    0xE3, 0xCC, 0x12, 0x85, 0x17, 0xD4};

const uint8_t expected_output_1[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x58, 0x8C,
				     0x97, 0x9A, 0x61, 0xC6, 0x63, 0xD2, 0xF0, 0x66, 0xD0, 0xC2,
				     0xC0, 0xF9, 0x89, 0x80, 0x6D, 0x5F, 0x6B, 0x61, 0xDA, 0xC3,
				     0x84, 0x17, 0xE8, 0xD1, 0x2C, 0xFD, 0xF9, 0x26, 0xE0};
const uint8_t expected_output_2[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x72, 0xC9,
				     0x1A, 0x36, 0xE1, 0x35, 0xF8, 0xCF, 0x29, 0x1C, 0xA8, 0x94,
				     0x08, 0x5C, 0x87, 0xE3, 0xCC, 0x15, 0xC4, 0x39, 0xC9, 0xE4,
				     0x3A, 0x3B, 0xA0, 0x91, 0xD5, 0x6E, 0x10, 0x40, 0x09, 0x16};
const uint8_t expected_output_3[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x51, 0xB1, 0xE5, 0xF4, 0x4A, 0x19,
	0x7D, 0x1D, 0xA4, 0x6B, 0x0F, 0x8E, 0x2D, 0x28, 0x2A, 0xE8, 0x71, 0xE8, 0x38, 0xBB,
	0x64, 0xDA, 0x85, 0x96, 0x57, 0x4A, 0xDA, 0xA7, 0x6F, 0xBD, 0x9F, 0xB0, 0xC5};
const uint8_t expected_output_4[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
				     0x0A, 0x0B, 0xA2, 0x8C, 0x68, 0x65, 0x93, 0x9A, 0x9A, 0x79,
				     0xFA, 0xAA, 0x5C, 0x4C, 0x2A, 0x9D, 0x4A, 0x91, 0xCD, 0xAC,
				     0x8C, 0x96, 0xC8, 0x61, 0xB9, 0xC9, 0xE6, 0x1E, 0xF1};
const uint8_t expected_output_5[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
				     0x0A, 0x0B, 0xDC, 0xF1, 0xFB, 0x7B, 0x5D, 0x9E, 0x23, 0xFB,
				     0x9D, 0x4E, 0x13, 0x12, 0x53, 0x65, 0x8A, 0xD8, 0x6E, 0xBD,
				     0xCA, 0x3E, 0x51, 0xE8, 0x3F, 0x07, 0x7D, 0x9C, 0x2D, 0x93};
const uint8_t expected_output_6[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x6F, 0xC1,
	0xB0, 0x11, 0xF0, 0x06, 0x56, 0x8B, 0x51, 0x71, 0xA4, 0x2D, 0x95, 0x3D, 0x46, 0x9B,
	0x25, 0x70, 0xA4, 0xBD, 0x87, 0x40, 0x5A, 0x04, 0x43, 0xAC, 0x91, 0xCB, 0x94};
const uint8_t expected_output_7[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x01, 0x35, 0xD1, 0xB2, 0xC9, 0x5F,
	0x41, 0xD5, 0xD1, 0xD4, 0xFE, 0xC1, 0x85, 0xD1, 0x66, 0xB8, 0x09, 0x4E, 0x99, 0x9D,
	0xFE, 0xD9, 0x6C, 0x04, 0x8C, 0x56, 0x60, 0x2C, 0x97, 0xAC, 0xBB, 0x74, 0x90};
const uint8_t expected_output_8[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x7B, 0x75, 0x39, 0x9A, 0xC0, 0x83,
	0x1D, 0xD2, 0xF0, 0xBB, 0xD7, 0x58, 0x79, 0xA2, 0xFD, 0x8F, 0x6C, 0xAE, 0x6B, 0x6C,
	0xD9, 0xB7, 0xDB, 0x24, 0xC1, 0x7B, 0x44, 0x33, 0xF4, 0x34, 0x96, 0x3F, 0x34, 0xB4};
const uint8_t expected_output_9[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x82, 0x53, 0x1A, 0x60, 0xCC, 0x24, 0x94,
	0x5A, 0x4B, 0x82, 0x79, 0x18, 0x1A, 0xB5, 0xC8, 0x4D, 0xF2, 0x1C, 0xE7, 0xF9, 0xB7, 0x3F,
	0x42, 0xE1, 0x97, 0xEA, 0x9C, 0x07, 0xE5, 0x6B, 0x5E, 0xB1, 0x7E, 0x5F, 0x4E};
const uint8_t expected_output_10[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x07, 0x34,
	0x25, 0x94, 0x15, 0x77, 0x85, 0x15, 0x2B, 0x07, 0x40, 0x98, 0x33, 0x0A, 0xBB, 0x14,
	0x1B, 0x94, 0x7B, 0x56, 0x6A, 0xA9, 0x40, 0x6B, 0x4D, 0x99, 0x99, 0x88, 0xDD};
const uint8_t expected_output_11[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x67, 0x6B,
	0xB2, 0x03, 0x80, 0xB0, 0xE3, 0x01, 0xE8, 0xAB, 0x79, 0x59, 0x0A, 0x39, 0x6D, 0xA7,
	0x8B, 0x83, 0x49, 0x34, 0xF5, 0x3A, 0xA2, 0xE9, 0x10, 0x7A, 0x8B, 0x6C, 0x02, 0x2C};
const uint8_t expected_output_12[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xC0, 0xFF, 0xA0,
	0xD6, 0xF0, 0x5B, 0xDB, 0x67, 0xF2, 0x4D, 0x43, 0xA4, 0x33, 0x8D, 0x2A, 0xA4, 0xBE, 0xD7,
	0xB2, 0x0E, 0x43, 0xCD, 0x1A, 0xA3, 0x16, 0x62, 0xE7, 0xAD, 0x65, 0xD6, 0xDB};
const uint8_t expected_output_13[] = {0x0B, 0xE1, 0xA8, 0x8B, 0xAC, 0xE0, 0x18, 0xB1, 0x4C, 0xB9,
				      0x7F, 0x86, 0xA2, 0xA4, 0x68, 0x9A, 0x87, 0x79, 0x47, 0xAB,
				      0x80, 0x91, 0xEF, 0x53, 0x86, 0xA6, 0xFF, 0xBD, 0xD0, 0x80,
				      0xF8, 0xE7, 0x8C, 0xF7, 0xCB, 0x0C, 0xDD, 0xD7, 0xB3};
const uint8_t expected_output_14[] = {0x63, 0x01, 0x8F, 0x76, 0xDC, 0x8A, 0x1B, 0xCB, 0x4C, 0xCB,
				      0x1E, 0x7C, 0xA9, 0x81, 0xBE, 0xFA, 0xA0, 0x72, 0x6C, 0x55,
				      0xD3, 0x78, 0x06, 0x12, 0x98, 0xC8, 0x5C, 0x92, 0x81, 0x4A,
				      0xBC, 0x33, 0xC5, 0x2E, 0xE8, 0x1D, 0x7D, 0x77, 0xC0, 0x8A};
const uint8_t expected_output_15[] = {
	0xAA, 0x6C, 0xFA, 0x36, 0xCA, 0xE8, 0x6B, 0x40, 0xB1, 0xD2, 0x3A, 0x22, 0x20, 0xDD,
	0xC0, 0xAC, 0x90, 0x0D, 0x9A, 0xA0, 0x3C, 0x61, 0xFC, 0xF4, 0xA5, 0x59, 0xA4, 0x41,
	0x77, 0x67, 0x08, 0x97, 0x08, 0xA7, 0x76, 0x79, 0x6E, 0xDB, 0x72, 0x35, 0x06};
const uint8_t expected_output_16[] = {0xD0, 0xD0, 0x73, 0x5C, 0x53, 0x1E, 0x1B, 0xEC, 0xF0, 0x49,
				      0xC2, 0x44, 0x14, 0xD2, 0x53, 0xC3, 0x96, 0x7B, 0x70, 0x60,
				      0x9B, 0x7C, 0xBB, 0x7C, 0x49, 0x91, 0x60, 0x28, 0x32, 0x45,
				      0x26, 0x9A, 0x6F, 0x49, 0x97, 0x5B, 0xCA, 0xDE, 0xAF};
const uint8_t expected_output_17[] = {0x77, 0xB6, 0x0F, 0x01, 0x1C, 0x03, 0xE1, 0x52, 0x58, 0x99,
				      0xBC, 0xAE, 0x55, 0x45, 0xFF, 0x1A, 0x08, 0x5E, 0xE2, 0xEF,
				      0xBF, 0x52, 0xB2, 0xE0, 0x4B, 0xEE, 0x1E, 0x23, 0x36, 0xC7,
				      0x3E, 0x3F, 0x76, 0x2C, 0x0C, 0x77, 0x44, 0xFE, 0x7E, 0x3C};
const uint8_t expected_output_18[] = {
	0xCD, 0x90, 0x44, 0xD2, 0xB7, 0x1F, 0xDB, 0x81, 0x20, 0xEA, 0x60, 0xC0, 0x00, 0x97,
	0x69, 0xEC, 0xAB, 0xDF, 0x48, 0x62, 0x55, 0x94, 0xC5, 0x92, 0x51, 0xE6, 0x03, 0x57,
	0x22, 0x67, 0x5E, 0x04, 0xC8, 0x47, 0x09, 0x9E, 0x5A, 0xE0, 0x70, 0x45, 0x51};
const uint8_t expected_output_19[] = {
	0xD8, 0x5B, 0xC7, 0xE6, 0x9F, 0x94, 0x4F, 0xB8, 0xBC, 0x21, 0x8D, 0xAA, 0x94, 0x74,
	0x27, 0xB6, 0xDB, 0x38, 0x6A, 0x99, 0xAC, 0x1A, 0xEF, 0x23, 0xAD, 0xE0, 0xB5, 0x29,
	0x39, 0xCB, 0x6A, 0x63, 0x7C, 0xF9, 0xBE, 0xC2, 0x40, 0x88, 0x97, 0xC6, 0xBA};
const uint8_t expected_output_20[] = {
	0x74, 0xA0, 0xEB, 0xC9, 0x06, 0x9F, 0x5B, 0x37, 0x58, 0x10, 0xE6, 0xFD, 0x25, 0x87,
	0x40, 0x22, 0xE8, 0x03, 0x61, 0xA4, 0x78, 0xE3, 0xE9, 0xCF, 0x48, 0x4A, 0xB0, 0x4F,
	0x44, 0x7E, 0xFF, 0xF6, 0xF0, 0xA4, 0x77, 0xCC, 0x2F, 0xC9, 0xBF, 0x54, 0x89, 0x44};
const uint8_t expected_output_21[] = {
	0x44, 0xA3, 0xAA, 0x3A, 0xAE, 0x64, 0x75, 0xCA, 0xF2, 0xBE, 0xED, 0x7B, 0xC5, 0x09, 0x8E,
	0x83, 0xFE, 0xB5, 0xB3, 0x16, 0x08, 0xF8, 0xE2, 0x9C, 0x38, 0x81, 0x9A, 0x89, 0xC8, 0xE7,
	0x76, 0xF1, 0x54, 0x4D, 0x41, 0x51, 0xA4, 0xED, 0x3A, 0x8B, 0x87, 0xB9, 0xCE};
const uint8_t expected_output_22[] = {
	0xEC, 0x46, 0xBB, 0x63, 0xB0, 0x25, 0x20, 0xC3, 0x3C, 0x49, 0xFD, 0x70, 0x31, 0xD7,
	0x50, 0xA0, 0x9D, 0xA3, 0xED, 0x7F, 0xDD, 0xD4, 0x9A, 0x20, 0x32, 0xAA, 0xBF, 0x17,
	0xEC, 0x8E, 0xBF, 0x7D, 0x22, 0xC8, 0x08, 0x8C, 0x66, 0x6B, 0xE5, 0xC1, 0x97};
const uint8_t expected_output_23[] = {
	0x47, 0xA6, 0x5A, 0xC7, 0x8B, 0x3D, 0x59, 0x42, 0x27, 0xE8, 0x5E, 0x71, 0xE8, 0x82,
	0xF1, 0xDB, 0xD3, 0x8C, 0xE3, 0xED, 0xA7, 0xC2, 0x3F, 0x04, 0xDD, 0x65, 0x07, 0x1E,
	0xB4, 0x13, 0x42, 0xAC, 0xDF, 0x7E, 0x00, 0xDC, 0xCE, 0xC7, 0xAE, 0x52, 0x98, 0x7D};
const uint8_t expected_output_24[] = {
	0x6E, 0x37, 0xA6, 0xEF, 0x54, 0x6D, 0x95, 0x5D, 0x34, 0xAB, 0x60, 0x59, 0xF3, 0x29, 0x05,
	0xB8, 0x8A, 0x64, 0x1B, 0x04, 0xB9, 0xC9, 0xFF, 0xB5, 0x8C, 0xC3, 0x90, 0x90, 0x0F, 0x3D,
	0xA1, 0x2A, 0xB1, 0x6D, 0xCE, 0x9E, 0x82, 0xEF, 0xA1, 0x6D, 0xA6, 0x20, 0x59};

struct test_data packet_1 = {
	.input = packet_vector_1,
	.expected_output = expected_output_1,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x03, 0x02, 0x01, 0x00, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 31,
	.aad_len = 8,
	.mic_len = 8,
};

struct test_data packet_2 = {
	.input = packet_vector_2,
	.expected_output = expected_output_2,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x04, 0x03, 0x02, 0x01, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 32,
	.aad_len = 8,
	.mic_len = 8,
};

struct test_data packet_3 = {
	.input = packet_vector_3,
	.expected_output = expected_output_3,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x05, 0x04, 0x03, 0x02, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 33,
	.aad_len = 8,
	.mic_len = 8,
};

struct test_data packet_4 = {
	.input = packet_vector_4,
	.expected_output = expected_output_4,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x06, 0x05, 0x04, 0x03, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 31,
	.aad_len = 12,
	.mic_len = 8,
};

struct test_data packet_5 = {
	.input = packet_vector_5,
	.expected_output = expected_output_5,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x07, 0x06, 0x05, 0x04, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 32,
	.aad_len = 12,
	.mic_len = 8,
};

struct test_data packet_6 = {
	.input = packet_vector_6,
	.expected_output = expected_output_6,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x08, 0x07, 0x06, 0x05, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 33,
	.aad_len = 12,
	.mic_len = 8,
};

struct test_data packet_7 = {
	.input = packet_vector_7,
	.expected_output = expected_output_7,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x09, 0x08, 0x07, 0x06, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 31,
	.aad_len = 8,
	.mic_len = 10,
};

struct test_data packet_8 = {
	.input = packet_vector_8,
	.expected_output = expected_output_8,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x0A, 0x09, 0x08, 0x07, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 32,
	.aad_len = 8,
	.mic_len = 10,
};

struct test_data packet_9 = {
	.input = packet_vector_9,
	.expected_output = expected_output_9,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x0B, 0x0A, 0x09, 0x08, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 33,
	.aad_len = 8,
	.mic_len = 10,
};

struct test_data packet_10 = {
	.input = packet_vector_10,
	.expected_output = expected_output_10,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x0C, 0x0B, 0x0A, 0x09, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 31,
	.aad_len = 12,
	.mic_len = 10,
};

struct test_data packet_11 = {
	.input = packet_vector_11,
	.expected_output = expected_output_11,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x0D, 0x0C, 0x0B, 0x0A, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 32,
	.aad_len = 12,
	.mic_len = 10,
};

struct test_data packet_12 = {
	.input = packet_vector_12,
	.expected_output = expected_output_12,
	.key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD,
		0xCE, 0xCF},
	.nonce = {0x00, 0x00, 0x00, 0x0E, 0x0D, 0x0C, 0x0B, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},

	.input_len = 33,
	.aad_len = 12,
	.mic_len = 10,
};

struct test_data packet_13 = {
	.input = packet_vector_13,
	.expected_output = expected_output_13,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x41, 0x2B, 0x4E, 0xA9, 0xCD, 0xBE, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 31,
	.aad_len = 8,
	.mic_len = 8,
};

struct test_data packet_14 = {
	.input = packet_vector_14,
	.expected_output = expected_output_14,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x33, 0x56, 0x8E, 0xF7, 0xB2, 0x63, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 32,
	.aad_len = 8,
	.mic_len = 8,
};

struct test_data packet_15 = {
	.input = packet_vector_15,
	.expected_output = expected_output_15,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x10, 0x3F, 0xE4, 0x13, 0x36, 0x71, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 33,
	.aad_len = 8,
	.mic_len = 8,
};

struct test_data packet_16 = {
	.input = packet_vector_16,
	.expected_output = expected_output_16,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x76, 0x4C, 0x63, 0xB8, 0x05, 0x8E, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 31,
	.aad_len = 12,
	.mic_len = 8,
};

struct test_data packet_17 = {
	.input = packet_vector_17,
	.expected_output = expected_output_17,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0xF8, 0xB6, 0x78, 0x09, 0x4E, 0x3B, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 32,
	.aad_len = 12,
	.mic_len = 8,
};

struct test_data packet_18 = {
	.input = packet_vector_18,
	.expected_output = expected_output_18,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0xD5, 0x60, 0x91, 0x2D, 0x3F, 0x70, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 33,
	.aad_len = 12,
	.mic_len = 8,
};

struct test_data packet_19 = {
	.input = packet_vector_19,
	.expected_output = expected_output_19,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x42, 0xFF, 0xF8, 0xF1, 0x95, 0x1C, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 31,
	.aad_len = 8,
	.mic_len = 10,
};

struct test_data packet_20 = {
	.input = packet_vector_20,
	.expected_output = expected_output_20,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x92, 0x0F, 0x40, 0xE5, 0x6C, 0xDC, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 32,
	.aad_len = 8,
	.mic_len = 10,
};

struct test_data packet_21 = {
	.input = packet_vector_21,
	.expected_output = expected_output_21,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x27, 0xCA, 0x0C, 0x71, 0x20, 0xBC, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 33,
	.aad_len = 8,
	.mic_len = 10,
};

struct test_data packet_22 = {
	.input = packet_vector_22,
	.expected_output = expected_output_22,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x5B, 0x8C, 0xCB, 0xCD, 0x9A, 0xF8, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 31,
	.aad_len = 12,
	.mic_len = 10,
};

struct test_data packet_23 = {
	.input = packet_vector_23,
	.expected_output = expected_output_23,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x3E, 0xBE, 0x94, 0x04, 0x4B, 0x9A, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 32,
	.aad_len = 12,
	.mic_len = 10,
};

struct test_data packet_24 = {
	.input = packet_vector_24,
	.expected_output = expected_output_24,
	.key = {0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93,
		0xCC, 0x6B},
	.nonce = {0x00, 0x8D, 0x49, 0x3B, 0x30, 0xAE, 0x8B, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},

	.input_len = 33,
	.aad_len = 12,
	.mic_len = 10,
};

struct test_data *input_packets[NUMBER_OF_TEST] = {
	&packet_1,  &packet_2,	&packet_3,  &packet_4,	&packet_5,  &packet_6,
	&packet_7,  &packet_8,	&packet_9,  &packet_10, &packet_11, &packet_12,
	&packet_13, &packet_14, &packet_15, &packet_16, &packet_17, &packet_18,
	&packet_19, &packet_20, &packet_21, &packet_22, &packet_23, &packet_24,
};
