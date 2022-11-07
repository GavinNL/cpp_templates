#!/bin/env python3

# To use domain sockets, you will need
#
#  git clone https://github.com/hvishwanath/msgpack-rpc-python
#  cd msgpack-rpc-python
#  pip3 install .
# 

import msgpackrpc.udsaddress
from msgpackrpc.transport import uds

client = msgpackrpc.Client(msgpackrpc.udsaddress.UDSAddress("./build/mysocket"), builder=uds)
result = client.call('add', 9, 8)  # = > 
print(result)

