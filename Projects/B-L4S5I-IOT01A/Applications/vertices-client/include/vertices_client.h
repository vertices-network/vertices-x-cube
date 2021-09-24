//
// Created by Cyril on 17/09/2021.
//

#ifndef VERTICES_STM32CUBE_PROJECTS_B_L4S5I_IOT01A_APPLICATIONS_VERTICES_CLIENT_VERTICES_CLIENT_H
#define VERTICES_STM32CUBE_PROJECTS_B_L4S5I_IOT01A_APPLICATIONS_VERTICES_CLIENT_VERTICES_CLIENT_H

#include <stdbool.h>

#define SERVER_URL          "https://api.testnet.algoexplorer.io/"
#define SERVER_PORT         443
#define SERVER_TOKEN_HEADER ""
#define SERVER_CA           "-----BEGIN CERTIFICATE-----\n" \
                            "MIIG7DCCBpOgAwIBAgIQBwRRRV4x+191YBZgYpg67zAKBggqhkjOPQQDAjBKMQsw\n" \
                            "CQYDVQQGEwJVUzEZMBcGA1UEChMQQ2xvdWRmbGFyZSwgSW5jLjEgMB4GA1UEAxMX\n" \
                            "Q2xvdWRmbGFyZSBJbmMgRUNDIENBLTMwHhcNMjEwNDI3MDAwMDAwWhcNMjIwNDI2\n" \
                            "MjM1OTU5WjBvMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQG\n" \
                            "A1UEBxMNU2FuIEZyYW5jaXNjbzEZMBcGA1UEChMQQ2xvdWRmbGFyZSwgSW5jLjEY\n" \
                            "MBYGA1UEAxMPYWxnb2V4cGxvcmVyLmlvMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcD\n" \
                            "QgAEFngxZPCjKqVCKSaq9oCQUF0r5oskSbAfBxgZThLPoje3Mfw3eYpwmapyUITZ\n" \
                            "gVJxacfq+kuM0wKo08BauVPkQaOCBTQwggUwMB8GA1UdIwQYMBaAFKXON+rrsHUO\n" \
                            "lGeItEX62SQQh5YfMB0GA1UdDgQWBBSKdCcy6obn8MXQF7bIGuIi92R/JjCCAfkG\n" \
                            "A1UdEQSCAfAwggHsghoqLmJpb2NoYWluLmFsZ29leHBsb3Jlci5pb4IVKi5wYzIu\n" \
                            "YWxnb2V4cGxvcmVyLmlvghUqLnBjNy5hbGdvZXhwbG9yZXIuaW+CD2FsZ29leHBs\n" \
                            "b3Jlci5pb4IZKi5iZXRhbmV0LmFsZ29leHBsb3Jlci5pb4IVKi5wYzUuYWxnb2V4\n" \
                            "cGxvcmVyLmlvghUqLnBjMS5hbGdvZXhwbG9yZXIuaW+CFSoucGM4LmFsZ29leHBs\n" \
                            "b3Jlci5pb4IbKi5hbGdvbG90dG8uYWxnb2V4cGxvcmVyLmlvgh0qLmRldi50ZXN0\n" \
                            "bmV0LmFsZ29leHBsb3Jlci5pb4IRKi5hbGdvZXhwbG9yZXIuaW+CGSoudGVzdG5l\n" \
                            "dC5hbGdvZXhwbG9yZXIuaW+CHSouZGV2LmJldGFuZXQuYWxnb2V4cGxvcmVyLmlv\n" \
                            "ghUqLnBjNC5hbGdvZXhwbG9yZXIuaW+CFSoucGM5LmFsZ29leHBsb3Jlci5pb4IV\n" \
                            "Ki5kZXYuYWxnb2V4cGxvcmVyLmlvghsqLmhlbXB0cmF4eC5hbGdvZXhwbG9yZXIu\n" \
                            "aW+CFSoucGM2LmFsZ29leHBsb3Jlci5pb4IVKi5wYzMuYWxnb2V4cGxvcmVyLmlv\n" \
                            "ghYqLnBjMTAuYWxnb2V4cGxvcmVyLmlvMA4GA1UdDwEB/wQEAwIHgDAdBgNVHSUE\n" \
                            "FjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwewYDVR0fBHQwcjA3oDWgM4YxaHR0cDov\n" \
                            "L2NybDMuZGlnaWNlcnQuY29tL0Nsb3VkZmxhcmVJbmNFQ0NDQS0zLmNybDA3oDWg\n" \
                            "M4YxaHR0cDovL2NybDQuZGlnaWNlcnQuY29tL0Nsb3VkZmxhcmVJbmNFQ0NDQS0z\n" \
                            "LmNybDA+BgNVHSAENzA1MDMGBmeBDAECAjApMCcGCCsGAQUFBwIBFhtodHRwOi8v\n" \
                            "d3d3LmRpZ2ljZXJ0LmNvbS9DUFMwdgYIKwYBBQUHAQEEajBoMCQGCCsGAQUFBzAB\n" \
                            "hhhodHRwOi8vb2NzcC5kaWdpY2VydC5jb20wQAYIKwYBBQUHMAKGNGh0dHA6Ly9j\n" \
                            "YWNlcnRzLmRpZ2ljZXJ0LmNvbS9DbG91ZGZsYXJlSW5jRUNDQ0EtMy5jcnQwDAYD\n" \
                            "VR0TAQH/BAIwADCCAX0GCisGAQQB1nkCBAIEggFtBIIBaQFnAHYAKXm+8J45OSHw\n" \
                            "VnOfY6V35b5XfZxgCvj5TV0mXCVdx4QAAAF5FAIs1gAABAMARzBFAiEAlPk/EorL\n" \
                            "SmKql07ukjsnoTbvhvJ9wjKw+70/UEj6TTECIENTiwTm2G/V8gzLI9Xxsu/FnE1S\n" \
                            "uXjUOgSZ90xY/CT3AHYAIkVFB1lVJFaWP6Ev8fdthuAjJmOtwEt/XcaDXG7iDwIA\n" \
                            "AAF5FAIsIAAABAMARzBFAiAG9SP8PDBcPaZb4AaFTCwfz3ykTAgH9GHiJfmm7r9F\n" \
                            "JwIhAOaxa0/7+e7kNkLJy7YJ+NNz5xaHyvfaLpSN4W+G825iAHUAQcjKsd8iRkoQ\n" \
                            "xqE6CUKHXk4xixsD6+tLx2jwkGKWBvYAAAF5FAItDAAABAMARjBEAiAIRYEzEaSX\n" \
                            "oDpIETvhdYVdTLNJNSEqbGzd2f095J+5WAIgKL11el8JtIWRxUMpowkNpvnybkZh\n" \
                            "wruVxTo4VJr+zGIwCgYIKoZIzj0EAwIDRwAwRAIgTzTIpE9YtFVBN/tVBwNpZBap\n" \
                            "sFA26GTpXVoExfQkS70CIClfBd8NpVc9JYvazFHnBh4Vt+F5xPbsP9ea7siK2z/B\n" \
                            "-----END CERTIFICATE-----\n" \
                            "-----BEGIN CERTIFICATE-----\n" \
                            "MIIDzTCCArWgAwIBAgIQCjeHZF5ftIwiTv0b7RQMPDANBgkqhkiG9w0BAQsFADBa\n" \
                            "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\n" \
                            "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\n" \
                            "MDEyNzEyNDgwOFoXDTI0MTIzMTIzNTk1OVowSjELMAkGA1UEBhMCVVMxGTAXBgNV\n" \
                            "BAoTEENsb3VkZmxhcmUsIEluYy4xIDAeBgNVBAMTF0Nsb3VkZmxhcmUgSW5jIEVD\n" \
                            "QyBDQS0zMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEua1NZpkUC0bsH4HRKlAe\n" \
                            "nQMVLzQSfS2WuIg4m4Vfj7+7Te9hRsTJc9QkT+DuHM5ss1FxL2ruTAUJd9NyYqSb\n" \
                            "16OCAWgwggFkMB0GA1UdDgQWBBSlzjfq67B1DpRniLRF+tkkEIeWHzAfBgNVHSME\n" \
                            "GDAWgBTlnVkwgkdYzKz6CFQ2hns6tQRN8DAOBgNVHQ8BAf8EBAMCAYYwHQYDVR0l\n" \
                            "BBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1UdEwEB/wQIMAYBAf8CAQAwNAYI\n" \
                            "KwYBBQUHAQEEKDAmMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5j\n" \
                            "b20wOgYDVR0fBDMwMTAvoC2gK4YpaHR0cDovL2NybDMuZGlnaWNlcnQuY29tL09t\n" \
                            "bmlyb290MjAyNS5jcmwwbQYDVR0gBGYwZDA3BglghkgBhv1sAQEwKjAoBggrBgEF\n" \
                            "BQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzALBglghkgBhv1sAQIw\n" \
                            "CAYGZ4EMAQIBMAgGBmeBDAECAjAIBgZngQwBAgMwDQYJKoZIhvcNAQELBQADggEB\n" \
                            "AAUkHd0bsCrrmNaF4zlNXmtXnYJX/OvoMaJXkGUFvhZEOFp3ArnPEELG4ZKk40Un\n" \
                            "+ABHLGioVplTVI+tnkDB0A+21w0LOEhsUCxJkAZbZB2LzEgwLt4I4ptJIsCSDBFe\n" \
                            "lpKU1fwg3FZs5ZKTv3ocwDfjhUkV+ivhdDkYD7fa86JXWGBPzI6UAPxGezQxPk1H\n" \
                            "goE6y/SJXQ7vTQ1unBuCJN0yJV0ReFEQPaA1IwQvZW+cwdFD19Ae8zFnWSfda9J1\n" \
                            "CZMRJCQUzym+5iPDuI9yP+kHyCREU3qzuWFloUwOxkgAyXVjBYdwRVKD05WdRerw\n" \
                            "6DEdfgkfCv4+3ao8XnTSrLE=\n" \
                            "-----END CERTIFICATE-----\n" \
                            ""

#define ACCOUNT_RECEIVER    "NBRUQXLMEJDQLHE5BBEFBQ3FF4F3BZYWCUBBQM67X6EOEW2WHGS764OQXE"

#define APP_ID 16037129

bool
app_needs_root_ca(void);

_Noreturn void
vertices_wallet_run(void const *arg);

#endif //VERTICES_STM32CUBE_PROJECTS_B_L4S5I_IOT01A_APPLICATIONS_VERTICES_CLIENT_VERTICES_CLIENT_H
