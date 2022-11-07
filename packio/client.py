#!/bin/env python3

#
#
# you'll need to install this: 
#
#   pip3 install --user msgpack-rpc-python
#   
#   https://github.com/msgpack-rpc/msgpack-rpc-python
# 
import msgpackrpc

client = msgpackrpc.Client(msgpackrpc.Address("localhost", 43845))
result = client.call('multiply', 4,6)  # = > 3
print(result)



# To use domain sockets, youwill need'
#
#  git clone https://github.com/hvishwanath/msgpack-rpc-python
#  cd msgpack-rpc-python
#  pip3 install .
# 

import msgpackrpc.udsaddress
from msgpackrpc.transport import uds

client = msgpackrpc.Client(msgpackrpc.udsaddress.UDSAddress("./build/mysocket"), builder=uds)
result = client.call('multiply', 666, 777)  # = > 
print(result)

