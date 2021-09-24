//
// Created by Cyril on 17/09/2021.
//

#include <stdio.h>
#include <cmsis_os.h>
#include <vertices.h>
#include <string.h>
#include "vertices_client.h"

static ret_code_t
vertices_evt_handler(vtc_evt_t *evt);

/***
 * The binary data is taken from a 64-byte binary file encapsulating the private and public keys
 * in binary format.
 * It has been generated using the Unix example available in the Vertices SDK repo, using the \c -n flag:
 * $ ./unix_example -n
 * You can then copy \c private_key.bin and \c public_b32.txt into the example's \c main directory
 * /!\ this is not a safe way to handle keys in production.
 */
extern const uint8_t signature_keys_start[] asm("_binary_private_key_bin_start");
extern const uint8_t signature_key_end[] asm("_binary_private_key_bin_end");

extern const uint8_t account_address_b32_start[] asm("_binary_public_b32_txt_start");
extern const uint8_t account_address_b32_end[] asm("_binary_public_b32_txt_end");

static provider_info_t providers =
    {
        .url = (char *) SERVER_URL,
        .port = SERVER_PORT,
        .header = (char *) SERVER_TOKEN_HEADER,
        .cert_pem = SERVER_CA
    };

/// We store anything related to the account into the below structure
/// The private key is used outside of the Vertices library:
///    you don't have to pass the private key to the SDK as signing is done outside
typedef struct
{
    unsigned char private_key[ADDRESS_LENGTH];  //!< 32-bytes private key
    account_info_t *vtc_account;               //!< pointer to Vertices account data
} account_t;

// Alice's account is used to send data, keys will be retrived from config/key_files.txt
static account_t alice_account = {.private_key = {0}, .vtc_account = NULL};
// Bob is receiving the money 😎
static account_t bob_account = {.private_key = {0}, .vtc_account = NULL};

static ret_code_t
vertices_evt_handler(vtc_evt_t *evt)
{
    ret_code_t err_code = VTC_SUCCESS;

    printf("💥 Evt: %u\r\n", evt->type);

    return err_code;
}

static void
load_existing_account()
{
    char public_b32[PUBLIC_B32_STR_MAX_LENGTH] = {0};

    // Account address length (remove 1 char: `\n`)
    size_t len = account_address_b32_end - account_address_b32_start - 1;

    // copy keys from Flash
    memcpy(alice_account.private_key, signature_keys_start, ADDRESS_LENGTH);
    memcpy(public_b32, account_address_b32_start, len);

    // let's compute the Algorand public address
    ret_code_t err_code = vertices_account_new_from_b32(public_b32, &alice_account.vtc_account);
    VTC_ASSERT(err_code);

    printf("💳 Alice's account %s", alice_account.vtc_account->public_b32);
}

static vertex_t m_vertex = {
    .provider = &providers,
    .vertices_evt_handler = vertices_evt_handler};
/**
  * @brief  IOTA client task
  * @param  arg Task arg
  * @retval None
  */
_Noreturn void
vertices_wallet_run(void const *arg)
{
    printf("Vertices wallet, let's go!\r\n");

    // create new vertex
    ret_code_t err_code = vertices_new(&m_vertex);
    VTC_ASSERT(err_code);

    // making sure the provider is accessible
    vertices_ping();
    VTC_ASSERT(err_code);

    provider_version_t version = {0};
    err_code = vertices_version(&version);
    if (err_code == VTC_ERROR_OFFLINE)
    {
        printf("Version might not be accurate: old value is being used\r\n");
    }
    else
    {
        VTC_ASSERT(err_code);
    }

    printf("🏎 Running on %s v.%u.%u.%u\r\n",
           version.network,
           version.major,
           version.minor,
           version.patch);

    load_existing_account();

    while (1)
    {
        printf("👋\r\n");
        osDelay(1000);
    }
}
