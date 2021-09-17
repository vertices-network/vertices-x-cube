// Copyright 2020 IOTA Stiftung
// SPDX-License-Identifier: Apache-2.0

/**
 * @brief A simple example of sending a transaction to the Tangle use wallet APIs.
 *
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_config.h"
#include "byte_buffer.h"
#include "wallet.h"

#define Mi 1000000

char const *const receiver = "a_bech32_address";
char const *const my_data = "sent from B-L4S5I-IOT01A Disco board";

void dump_addresses(iota_wallet_t *w, uint32_t start, uint32_t end) {
  byte_t addr_wit_version[IOTA_ADDRESS_BYTES];
  memset(addr_wit_version, 0, sizeof(addr_wit_version));
  char tmp_bech32_addr[100];
  memset(tmp_bech32_addr, 0, sizeof(tmp_bech32_addr));

  for (uint32_t i = start; i <= end; i++) {
    addr_wit_version[0] = ADDRESS_VER_ED25519;
    wallet_address_by_index(w, i, addr_wit_version + 1);
    address_2_bech32(addr_wit_version, "atoi", tmp_bech32_addr);
    printf("Addr[%" PRIu32 "]\n", i);
    // print ed25519 address without version filed.
    printf("\t");
    dump_hex_str(addr_wit_version + 1, ED25519_ADDRESS_BYTES);
    // print out
    printf("\t%s\n", tmp_bech32_addr);
  }
}

int wallet_send_tx (void) {
  byte_t seed[IOTA_SEED_BYTES];
  memset(seed, 0, sizeof(seed));
  // address with a version byte
  byte_t recv[IOTA_ADDRESS_BYTES];
  memset(recv, 0, sizeof(recv));
  iota_wallet_t *wallet = NULL;
  uint64_t value = 0;

  random_seed(seed);
  if ((wallet = wallet_create(seed, ACCOUNT_PATH)) == NULL) {
    printf("create wallet failed\n");
  }

  // set connected node
  wallet_set_endpoint(wallet, TEST_NODE_ENDPOINT, TEST_NODE_PORT);

  dump_addresses(wallet, 0, 5);

  // send none-valued transaction with indexation payload
  if (wallet_send(wallet, 0, NULL, 0, "iota.c\xF0\x9F\x80\x84", (byte_t *)my_data, strlen(my_data)) != 0) {
    printf("send indexation failed\n");
  }

  if (wallet_send(wallet, 0, recv + 1, 0, "iota.c\xF0\x9F\x80\x84", (byte_t *)my_data, strlen(my_data)) != 0) {
    printf("send indexation with address failed\n");
  }

  // check balance at address 0
  if (wallet_balance_by_index(wallet, 0, &value)) {
    printf("wallet get balance failed\n");
    goto done;
  }
  printf("balance: %" PRIu64 "\n", value);

  // send out 1Mi to recever address
  // convert receiver to binary
  if (address_from_bech32("atoi", receiver, recv)) {
    printf("convert receiver address failed\n");
    goto done;
  }

  // wallet_send take ed25519 address without the version field.
  if (wallet_send(wallet, 0, recv + 1, 1 * Mi, "iota.c\xF0\x9F\x80\x84", (byte_t *)my_data, strlen(my_data)) != 0) {
    printf("send tx to %s failed\n", receiver);
  }

done:
  wallet_destroy(wallet);
  return 0;
}
