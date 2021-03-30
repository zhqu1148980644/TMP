# coding=utf-8
import asyncio
import hashlib
import json
import os

from openssl import OpenSSLStreamCrypto

TG_SERVERS = ["149.154.175.50", "149.154.167.51", "149.154.175.100", "149.154.167.91", "149.154.171.5"]


class MTProxy(asyncio.Protocol):

    def __init__(self, config):
        super().__init__()
        self.loop = asyncio.get_event_loop()
        self.init = True
        self.config = config
        self.tg_servers = TG_SERVERS
        self.to_local_queue = asyncio.Queue()
        self.to_sender_queue = asyncio.Queue()

    def connection_made(self, transport):
        self.transport = transport
        asyncio.ensure_future(self.start_send())

    def data_received(self, data):
        if self.init:
            secret_bytes = bytes.fromhex(config.get("secret_key", "0123456789abcdef0123456789abcdef"))
            buf64 = data[:64]

            decrypt_key, decrypt_iv, encrypt_key, encrypt_iv = MTProxy.generate_key_iv(buf64=buf64)

            decrypt_key = hashlib.sha256(decrypt_key + secret_bytes).digest()
            encrypt_key = hashlib.sha256(encrypt_key + secret_bytes).digest()

            self.decryptor = OpenSSLStreamCrypto("aes-256-ctr", key=decrypt_key, iv=decrypt_iv, op=0)
            self.encryptor = OpenSSLStreamCrypto("aes-256-ctr", key=encrypt_key, iv=encrypt_iv, op=1)

            decrypted_data = self.decryptor.decrypt(buf64)
            self.dcID = abs(int.from_bytes(decrypted_data[60:62], "little", signed=True)) - 1
            for i in range(4):
                if decrypted_data[56 + i] != 0xef:
                    self.transport.close()
            if self.dcID > 4 or self.dcID < 0:
                self.transport.close()

            asyncio.ensure_future(self.create_sender(self.dcID))
            data = data[64:]
            self.init = False

        decrypted_data = self.decryptor.decrypt(data)
        self.to_sender_queue.put_nowait(decrypted_data)

    async def create_sender(self, dcid):
        remote_addr = self.tg_servers[dcid], 443
        _, self.sender = await self.loop.create_connection(lambda: SenderProtocol(self), *remote_addr)

    async def start_send(self):
        while True:
            data = await self.to_local_queue.get()
            encrypted_data = self.encryptor.encrypt(data)
            self.transport.write(encrypted_data)

    @classmethod
    def generate_key_iv(cls, buf64):
        key_iv = buf64[8:56]
        # key's length:32bytes , iv's length:16bytes
        decrypt_key, decrypt_iv = key_iv[:32], key_iv[32:]
        # reverse bytes sequence
        key_iv = key_iv[::-1]
        encrypt_key, encrypt_iv = key_iv[:32], key_iv[32:]

        return decrypt_key, decrypt_iv, encrypt_key, encrypt_iv


class SenderProtocol(asyncio.Protocol):

    def __init__(self, client):
        super().__init__()
        self.client = client
        self.handshaked = asyncio.Event()

    def connection_made(self, transport):
        self.transport = transport
        self.handshake()
        asyncio.ensure_future(self.start_send())

    def data_received(self, data):
        decrypted_data = self.decryptor.decrypt(data)

        self.client.to_local_queue.put_nowait(decrypted_data)

    def handshake(self):
        random_buf = os.urandom(64)
        check_list = [0x44414548, 0x54534f50, 0x20544547, 0x4954504f, 0xeeeeeeee]
        while True:
            tmp1 = (random_buf[3] < 24) | (random_buf[2] < 16) | (random_buf[1] < 8) | (random_buf[0])
            tmp2 = (random_buf[7] < 24) | (random_buf[6] < 16) | (random_buf[5] < 8) | (random_buf[4])
            if random_buf[0] != 0xef and (tmp1 not in check_list) and tmp2 != 0x00000000:
                tmp_bytes_list = list(random_buf)
                tmp_bytes_list[56] = tmp_bytes_list[57] = tmp_bytes_list[58] = tmp_bytes_list[59] = 0xef
                random_buf = bytes(tmp_bytes_list)
                break
            random_buf = os.urandom(64)
        # Be careful, The order of these variables is reversed compared to client's.
        encrypt_key, encrypt_iv, decrypt_key, decrypt_iv = MTProxy.generate_key_iv(buf64=random_buf)

        self.decryptor = OpenSSLStreamCrypto("aes-256-ctr", key=decrypt_key, iv=decrypt_iv, op=0)
        self.encryptor = OpenSSLStreamCrypto("aes-256-ctr", key=encrypt_key, iv=encrypt_iv, op=1)

        encrypted_data = self.encryptor.encrypt(random_buf)

        encrypted_data = random_buf[:56] + encrypted_data[56:]
        self.transport.write(encrypted_data)

        self.handshaked.set()

    async def start_send(self):
        await self.handshaked.wait()
        while True:
            data = await self.client.to_sender_queue.get()
            encrypted_data = self.encryptor.encrypt(data)

            self.transport.write(encrypted_data)


try:
    config = json.loads(open("config.json", 'r').read())
except Exception as e:
    config = {"port": 443, "secret_key": "0123456789abcdef0123456789abcdef"}

port = config.get("port", 443)

try:
    import uvloop

    asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
except Exception as e:
    pass

loop = asyncio.get_event_loop()
local_addr = "0.0.0.0", port
coro = loop.create_server(lambda: MTProxy(config), *local_addr)
server = loop.run_until_complete(coro)
print('server created ', *local_addr)
try:
    loop.run_forever()
except KeyboardInterrupt as e:
    print('all tasks cancelled')
    print(asyncio.gather(asyncio.Task.all_tasks()).cancel())
