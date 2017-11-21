/*
 * Copyright (C) 2015 BlueKitchen GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 4. Any redistribution, use, or modification is done solely for
 *    personal benefit and not for any commercial purpose or for
 *    monetary gain.
 *
 * THIS SOFTWARE IS PROVIDED BY BLUEKITCHEN GMBH AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHIAS
 * RINGWALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Please inquire about commercial licensing options at 
 * contact@bluekitchen-gmbh.com
 *
 */

#define __BTSTACK_FILE__ "main.c"

#ifndef WICED_HAVE_MBEDTLS

// pre 5.2
#include "wiced_security.h"

static aes_context_t wiced_aes128_context;

void btstack_aes128_calc(const uint8_t * key, const uint8_t * plaintext, uint8_t * result);
void btstack_aes128_calc(const uint8_t * key, const uint8_t * plaintext, uint8_t * result){
    aes_setkey_enc(&wiced_aes128_context, key, 128);
    aes_crypt_ecb(&wiced_aes128_context, AES_ENCRYPT , plaintext, result);
}

#else

// 5.2+
#include <string.h>
#include "mbedtls/aes.h"

static aes_context_t wiced_aes128_context;

void btstack_aes128_calc(const uint8_t * key, const uint8_t * plaintext, uint8_t * result);
void btstack_aes128_calc(const uint8_t * key, const uint8_t * plaintext, uint8_t * result){
    memset(&wiced_aes128_context, 0, sizeof(aes_context_t));
    mbedtls_aes_setkey_enc(&wiced_aes128_context, key, 128);
    mbedtls_aes_crypt_ecb(&wiced_aes128_context, AES_ENCRYPT, plaintext, result);
}

#endif


