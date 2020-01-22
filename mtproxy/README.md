# pymtproxy

#### Python vsersion of [JSMTProxy](https://github.com/mtProtoProxy/JSMTProxy)

## Requirements:
- python3.5+
- openssl

### Optional:
###### makes asyncio 2-4x faster.
	pip install uvloop
## Usages:
#### First alter the config.json
###### default setting is:
	{
        "port":39999,
        "secret_key":"0123456789abcdef0123456789abcdef"
	}
#### Second
	cd your_download_dir/pymtproxy
	python3 pymtproxy
