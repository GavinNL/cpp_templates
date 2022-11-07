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
