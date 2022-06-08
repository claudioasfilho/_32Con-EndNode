/# _32Con-EndNode

This code is meant be used in conjunction with the _32ConpyBGAPI python example.

It is a simple Application that advertises a custom service (UUID 42d9fcd8-e368-4293-bd6a-22e694ae0ce0) and custom Characteristic (3a4855f6-2f9c-4005-815b-df746358668e) which have notifications enabled.

This device carries the typical Linux Boot up information as data. Once the Central device subscribes to the characteristic, it will push that data upstream.
