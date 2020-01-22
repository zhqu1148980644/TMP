#!/usr/bin/env python
#
# Copyright 2015 clowwindy
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

from __future__ import absolute_import, division, print_function, \
    with_statement

import sys
from ctypes import c_char_p, c_int, c_long, byref, \
    create_string_buffer, c_void_p

sys.path.append(r'../')

import util

__all__ = ['ciphers']

libcrypto = None
loaded = False
libsodium = None

buf = None
buf_size = 2048

ctx_cleanup = None

CIPHER_ENC_UNCHANGED = -1


def to_bytes(s):
    if bytes != str:
        if type(s) == str:
            return s.encode('utf-8')
    return s


def load_openssl(crypto_path=None):
    global loaded, libcrypto, libsodium, buf, ctx_cleanup

    crypto_path = dict(crypto_path) if crypto_path else dict()
    path = crypto_path.get('openssl', None)
    libcrypto = util.find_library(('crypto', 'eay32'),
                                  'EVP_get_cipherbyname',
                                  'libcrypto', path)

    if libcrypto is None:
        raise Exception('libcrypto(OpenSSL) not found with path %s' % path)

    libcrypto.EVP_get_cipherbyname.restype = c_void_p
    libcrypto.EVP_CIPHER_CTX_new.restype = c_void_p

    libcrypto.EVP_CipherInit_ex.argtypes = (c_void_p, c_void_p, c_char_p,
                                            c_char_p, c_char_p, c_int)
    libcrypto.EVP_CIPHER_CTX_ctrl.argtypes = (c_void_p, c_int, c_int, c_void_p)

    libcrypto.EVP_CipherUpdate.argtypes = (c_void_p, c_void_p, c_void_p,
                                           c_char_p, c_int)

    libcrypto.EVP_CipherFinal_ex.argtypes = (c_void_p, c_void_p, c_void_p)

    try:
        libcrypto.EVP_CIPHER_CTX_cleanup.argtypes = (c_void_p,)
        ctx_cleanup = libcrypto.EVP_CIPHER_CTX_cleanup
    except AttributeError:
        libcrypto.EVP_CIPHER_CTX_reset.argtypes = (c_void_p,)
        ctx_cleanup = libcrypto.EVP_CIPHER_CTX_reset
    libcrypto.EVP_CIPHER_CTX_free.argtypes = (c_void_p,)
    if hasattr(libcrypto, 'OpenSSL_add_all_ciphers'):
        libcrypto.OpenSSL_add_all_ciphers()

    buf = create_string_buffer(buf_size)
    loaded = True


def load_cipher(cipher_name):
    func_name = b'EVP_' + cipher_name.replace(b'-', b'_')
    if bytes != str:
        func_name = str(func_name, 'utf-8')
    cipher = getattr(libcrypto, func_name, None)
    if cipher:
        cipher.restype = c_void_p
        return cipher()
    return None


class OpenSSLCryptoBase(object):
    """
    OpenSSL crypto base class
    """

    def __init__(self, cipher_name, crypto_path=None):
        self._ctx = None
        self._cipher = None
        if not loaded:
            load_openssl(crypto_path)
        cipher_name = to_bytes(cipher_name)
        cipher = libcrypto.EVP_get_cipherbyname(cipher_name)
        if not cipher:
            cipher = load_cipher(cipher_name)
        if not cipher:
            raise Exception('cipher %s not found in libcrypto' % cipher_name)
        self._ctx = libcrypto.EVP_CIPHER_CTX_new()
        self._cipher = cipher
        if not self._ctx:
            raise Exception('can not create cipher context')

    def encrypt_once(self, data):
        return self.update(data)

    def decrypt_once(self, data):
        return self.update(data)

    def update(self, data):
        """
        Encrypt/decrypt data
        :param data: str
        :return: str
        """
        global buf_size, buf
        cipher_out_len = c_long(0)
        l = len(data)
        if buf_size < l:
            buf_size = l * 2
            buf = create_string_buffer(buf_size)
        libcrypto.EVP_CipherUpdate(
            self._ctx, byref(buf),
            byref(cipher_out_len), c_char_p(data), l
        )
        # buf is copied to a str object when we access buf.raw
        return buf.raw[:cipher_out_len.value]

    def __del__(self):
        self.clean()

    def clean(self):
        if self._ctx:
            ctx_cleanup(self._ctx)
            libcrypto.EVP_CIPHER_CTX_free(self._ctx)
            self._ctx = None


class OpenSSLStreamCrypto(OpenSSLCryptoBase):
    """
    Crypto for stream modes: cfb, ofb, ctr
    """

    def __init__(self, cipher_name, key, iv, op, crypto_path=None):
        OpenSSLCryptoBase.__init__(self, cipher_name, crypto_path)
        key_ptr = c_char_p(key)
        iv_ptr = c_char_p(iv)
        r = libcrypto.EVP_CipherInit_ex(self._ctx, self._cipher, None,
                                        key_ptr, iv_ptr, c_int(op))
        if not r:
            self.clean()
            raise Exception('can not initialize cipher context')

    def encrypt(self, data):
        return self.update(data)

    def decrypt(self, data):
        return self.update(data)


ciphers = {
    'aes-128-cfb': (16, 16, OpenSSLStreamCrypto),
    'aes-192-cfb': (24, 16, OpenSSLStreamCrypto),
    'aes-256-cfb': (32, 16, OpenSSLStreamCrypto),
    'aes-128-ofb': (16, 16, OpenSSLStreamCrypto),
    'aes-192-ofb': (24, 16, OpenSSLStreamCrypto),
    'aes-256-ofb': (32, 16, OpenSSLStreamCrypto),
    'aes-128-ctr': (16, 16, OpenSSLStreamCrypto),
    'aes-192-ctr': (24, 16, OpenSSLStreamCrypto),
    'aes-256-ctr': (32, 16, OpenSSLStreamCrypto),
    'aes-128-cfb8': (16, 16, OpenSSLStreamCrypto),
    'aes-192-cfb8': (24, 16, OpenSSLStreamCrypto),
    'aes-256-cfb8': (32, 16, OpenSSLStreamCrypto),
    'aes-128-cfb1': (16, 16, OpenSSLStreamCrypto),
    'aes-192-cfb1': (24, 16, OpenSSLStreamCrypto),
    'aes-256-cfb1': (32, 16, OpenSSLStreamCrypto),
    'bf-cfb': (16, 8, OpenSSLStreamCrypto),
    'camellia-128-cfb': (16, 16, OpenSSLStreamCrypto),
    'camellia-192-cfb': (24, 16, OpenSSLStreamCrypto),
    'camellia-256-cfb': (32, 16, OpenSSLStreamCrypto),
    'cast5-cfb': (16, 8, OpenSSLStreamCrypto),
    'des-cfb': (8, 8, OpenSSLStreamCrypto),
    'idea-cfb': (16, 8, OpenSSLStreamCrypto),
    'rc2-cfb': (16, 8, OpenSSLStreamCrypto),
    'rc4': (16, 0, OpenSSLStreamCrypto),
    'seed-cfb': (16, 16, OpenSSLStreamCrypto),
}


def run_method(method):
    print(method, ': [stream]', 32)
    cipher = OpenSSLStreamCrypto(method, b'k' * 32, b'i' * 16, 1)
    decipher = OpenSSLStreamCrypto(method, b'k' * 32, b'i' * 16, 0)

    util.run_cipher(cipher, decipher)


def test_aes_128_cfb():
    run_method('aes-128-cfb')


def test_aes_256_cfb():
    run_method('aes-256-cfb')


def test_aes_128_cfb8():
    run_method('aes-128-cfb8')


def test_aes_256_ofb():
    run_method('aes-256-ofb')


def test_aes_256_ctr():
    run_method('aes-256-ctr')


def test_bf_cfb():
    run_method('bf-cfb')


def test_rc4():
    run_method('rc4')


if __name__ == '__main__':
    test_aes_128_cfb()
    test_aes_256_cfb()
    test_aes_256_ofb()
