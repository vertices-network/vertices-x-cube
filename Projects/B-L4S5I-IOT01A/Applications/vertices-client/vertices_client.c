//
// Created by Cyril on 17/09/2021.
//

#include <stdio.h>
#include <cmsis_os.h>
#include <vertices.h>
#include <string.h>
#include "vertices_client.h"
#include <sodium.h>
#include <mbedtls/base64.h>
#include <vertices_log.h>

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

#ifndef AMOUNT_SENT
#define AMOUNT_SENT 100
#endif

static ret_code_t
vertices_evt_handler(vtc_evt_t *evt)
{
    ret_code_t err_code = VTC_SUCCESS;

    switch (evt->type)
    {
        case VTC_EVT_TX_READY_TO_SIGN:
        {
            signed_transaction_t *tx = NULL;
            err_code = vertices_event_tx_get(evt->bufid, &tx);
            if (err_code == VTC_SUCCESS)
            {
                LOG_INFO("About to sign tx: data length %u", tx->payload_body_length);

                // libsodium wants to have private and public keys concatenated
                unsigned char keys[crypto_sign_ed25519_SECRETKEYBYTES] = {0};
                memcpy(keys, alice_account.private_key, sizeof(alice_account.private_key));
                memcpy(&keys[32],
                       alice_account.vtc_account->public_key,
                       ADDRESS_LENGTH);

                // prepend "TX" to the payload before signing
                unsigned char to_be_signed[tx->payload_body_length + 2];
                to_be_signed[0] = 'T';
                to_be_signed[1] = 'X';
                memcpy(&to_be_signed[2],
                       &tx->payload[tx->payload_header_length],
                       tx->payload_body_length);

                // sign the payload
                crypto_sign_ed25519_detached(tx->signature,
                                             0, to_be_signed, tx->payload_body_length + 2, keys);

                char b64_signature[128] = {0};
                size_t b64_signature_len = sizeof(b64_signature);

                mbedtls_base64_encode((uint8_t *) b64_signature,
                                      sizeof(b64_signature),
                                      &b64_signature_len,
                                      tx->signature,
                                      sizeof(tx->signature));
                LOG_INFO("Signature %s (%u bytes)", b64_signature, b64_signature_len);

                // let's push the new state
                evt->type = VTC_EVT_TX_SENDING;
                err_code = vertices_event_schedule(evt);
            }
        }
            break;

        case VTC_EVT_TX_SENDING:
        {
            // nothing to be done on our side
        }
            break;

        default:
        {
            LOG_INFO("Unhandled event: %u", evt->type);
        }
            break;
    }
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

    LOG_INFO("💳 Alice's account %s", alice_account.vtc_account->public_b32);
}

static vertex_t m_vertex = {
    .provider = &providers,
    .vertices_evt_handler = vertices_evt_handler};
/**
  * @brief  Vertices client task
  * @param  arg Task arg
  * @retval None
  */
_Noreturn void
vertices_wallet_run(void const *arg)
{
    LOG_INFO("Vertices Wallet example task");

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
        LOG_INFO("Version might not be accurate: old value is being used");
    }
    else
    {
        VTC_ASSERT(err_code);
    }

    LOG_INFO("🏎 Running on %s v.%u.%u.%u",
           version.network,
           version.major,
           version.minor,
           version.patch);

    load_existing_account();

    // we want at least 1.001 Algo available
    while (alice_account.vtc_account->amount < 1001000)
    {
        LOG_INFO("🙄 %lu Algos available on account. "
               "It's too low to pass a transaction, consider adding Algos",
               (int32_t) alice_account.vtc_account->amount / 1.e6);
        LOG_INFO("👉 Go to https://bank.testnet.algorand.network/, "
               "dispense Algos to: %s",
               alice_account.vtc_account->public_b32);
        LOG_INFO("😎 Then wait for a few seconds for transaction to pass...");
        LOG_INFO("⏳ Retrying in 1 minute");

        osDelay(60000);

        vertices_account_update(alice_account.vtc_account);
    }

    LOG_INFO("🤑 %lu.%lu Algos on Alice's account (%s)",
           (int32_t) alice_account.vtc_account->amount / 1000000,
           (int32_t) alice_account.vtc_account->amount % 1000000,
           alice_account.vtc_account->public_b32);

    // create account from b32 address
    //      Note: creating a receiver account is not mandatory to send money to the account
    //      but we can use it to load the public key from the account address
    err_code = vertices_account_new_from_b32(ACCOUNT_RECEIVER, &bob_account.vtc_account);
    VTC_ASSERT(err_code);

    // send assets from Alice's account to Bob's account
    char notes[] = "Alice sent algos to Bob from B-L4S5I-IOT01A";

    err_code =
        vertices_transaction_pay_new(alice_account.vtc_account,
                                     (char *) bob_account.vtc_account->public_b32,
                                     AMOUNT_SENT,
                                     notes);
    VTC_ASSERT(err_code);

    // get application information (global states)
    LOG_INFO("Application %u, global states", APP_ID);

    app_values_t app_kv = {0};
    err_code = vertices_application_get(APP_ID, &app_kv);
    VTC_ASSERT(err_code);
    for (uint32_t i = 0; i < app_kv.count; ++i)
    {
        if (app_kv.values[i].type == VALUE_TYPE_INTEGER)
        {
            LOG_INFO("%s: %llu", app_kv.values[i].name, app_kv.values[i].value_uint);
        }
        else if (app_kv.values[i].type == VALUE_TYPE_BYTESLICE)
        {
            LOG_INFO("%s: %s", app_kv.values[i].name, app_kv.values[i].value_slice);
        }
    }

    // send application call
    app_values_t kv = {0};
    kv.count = 1;
    kv.values[0].type = VALUE_TYPE_INTEGER;
    kv.values[0].value_uint = 32;

    err_code = vertices_transaction_app_call(alice_account.vtc_account, APP_ID, &kv);
    VTC_ASSERT(err_code);

    while (1)
    {
        size_t queue_size = 1;
        while (queue_size && err_code == VTC_SUCCESS)
        {
            err_code = vertices_event_process(&queue_size);
        }

        osDelay(1000);
    }
}
