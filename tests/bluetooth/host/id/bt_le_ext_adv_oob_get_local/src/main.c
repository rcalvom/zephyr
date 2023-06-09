/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "testing_common_defs.h"

#include <zephyr/bluetooth/hci.h>
#include <zephyr/fff.h>
#include <zephyr/kernel.h>

#include <host/hci_core.h>
#include <host/id.h>
#include <mocks/conn.h>
#include <mocks/conn_expects.h>
#include <mocks/smp.h>
#include <mocks/smp_expects.h>

DEFINE_FFF_GLOBALS;

static void fff_reset_rule_before(const struct ztest_unit_test *test, void *fixture)
{
	memset(&bt_dev, 0x00, sizeof(struct bt_dev));

	SMP_FFF_FAKES_LIST(RESET_FAKE);
	CONN_FFF_FAKES_LIST(RESET_FAKE);
}

ZTEST_RULE(fff_reset_rule, fff_reset_rule_before, NULL);

ZTEST_SUITE(bt_le_ext_adv_oob_get_local, NULL, NULL, NULL, NULL, NULL);

/*
 *  Get LE local Out Of Band information while privacy isn't enabled
 *
 *  Constraints:
 *   - Valid references are used for the advertise parameters and the OOB references
 *   - 'CONFIG_BT_PRIVACY' bit isn't enabled
 *
 *  Expected behaviour:
 *   - Address is copied to the passed OOB reference
 */
ZTEST(bt_le_ext_adv_oob_get_local, test_get_local_out_of_band_information_no_privacy)
{
	int err;
	struct bt_le_oob oob = {0};
	struct bt_le_ext_adv adv = {0};

	Z_TEST_SKIP_IFDEF(CONFIG_BT_PRIVACY);

	atomic_set_bit(bt_dev.flags, BT_DEV_READY);

	/* ENOTSUP error should not affect the return value of bt_le_ext_adv_oob_get_local() */
	bt_smp_le_oob_generate_sc_data_fake.return_val = -ENOTSUP;

	bt_addr_le_copy(&bt_dev.id_addr[BT_ID_DEFAULT], BT_RPA_LE_ADDR);

	err = bt_le_ext_adv_oob_get_local(&adv, &oob);

	if (IS_ENABLED(CONFIG_BT_SMP)) {
		expect_single_call_bt_smp_le_oob_generate_sc_data(&oob.le_sc_data);
	}

	zassert_ok(err, "Unexpected error code '%d' was returned", err);
	zassert_mem_equal(&oob.addr, BT_RPA_LE_ADDR, sizeof(bt_addr_le_t),
			  "Incorrect address was set");
}

/*
 *  Get LE local Out Of Band information while privacy is enabled
 *
 *  Constraints:
 *   - Valid references are used for the advertise parameters and the OOB references
 *   - 'CONFIG_BT_PRIVACY' bit is enabled
 *
 *  Expected behaviour:
 *   - Address is copied to the passed OOB reference
 */
ZTEST(bt_le_ext_adv_oob_get_local, test_get_local_out_of_band_information_privacy_enabled)
{
	int err;
	struct bt_le_oob oob = {0};
	struct bt_le_ext_adv adv = {0};

	Z_TEST_SKIP_IFNDEF(CONFIG_BT_PRIVACY);

	/* ENOTSUP error should not affect the return value of bt_le_ext_adv_oob_get_local() */
	bt_smp_le_oob_generate_sc_data_fake.return_val = -ENOTSUP;

	atomic_set_bit(bt_dev.flags, BT_DEV_READY);
	atomic_clear_bit(adv.flags, BT_ADV_USE_IDENTITY);
	bt_addr_le_copy(&adv.random_addr, BT_RPA_LE_ADDR);

	err = bt_le_ext_adv_oob_get_local(&adv, &oob);

	if (IS_ENABLED(CONFIG_BT_SMP)) {
		expect_single_call_bt_smp_le_oob_generate_sc_data(&oob.le_sc_data);
	}

	zassert_ok(err, "Unexpected error code '%d' was returned", err);
	zassert_mem_equal(&oob.addr, BT_RPA_LE_ADDR, sizeof(bt_addr_le_t),
			  "Incorrect address was set");
}
