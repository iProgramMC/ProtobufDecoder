## Protobuf Decoder (C++11)

This single header C++11 library allows decoding of binary blobs generated using protobuf.

Since protobuf is a lossy protocol, not all of the input data can be recovered.  Namely,
there may be ambiguity in determining whether something is a string, an array of bytes,
or an embedded message blob.

### Disclaimer

Since this project is so new, it's bound to have bugs.  Report them to me!

### Observations

This library uses exceptions for the decoding process.  This might be a turn-off for some people.

### License

This project is licensed under the MIT license.  See LICENSE.txt for details.

### Examples

Encoding example:
```cpp
using namespace Protobuf;

ObjectBaseMessage* pObj = new ObjectBaseMessage();
pObj->AddObject(new ObjectString(1, "Hello");
pObj->AddObject(new ObjectString(2, "World");

std::vector<uint8_t> data;
pObj->Encode(data);
```

Decoding example:
```cpp
using namespace Protobuf;

const char data[] = "\x0A\x0C\x48\x65\x6C\x6C\x6F\x2C\x20\x77\x6F\x72\x6C\x64";
size_t dataSize = sizeof(data) - 1;

ObjectBaseMessage* pObj = new ObjectBaseMessage();
DecodeBlock(data, dataSize, pObj);
```

### Available Types

This protobuf implementation supports the following types in both the encode and decode process:
- `varint` (`ObjectVarInt`)
- `fixed64` (`ObjectFixed64`)
- `fixed32` (`ObjectFixed32`)
- `string` (`ObjectString`)
- `bytes` (`ObjectBytes`)
- `message` (`ObjectMessage`)

### Remarks

- `ObjectBaseMessage` is the root message type.  Use `ObjectMessage` inside of other message objects.

- All pointers are managed by `new` and `delete`. Do not pass pointers to variables global or from the stack.

### Error Codes

The following error codes may be thrown during the decoding process (use `catch(Protobuf::ErrorCode)`):
- `ERROR_OUTOFBOUNDS` - The message buffer is incomplete, and the implementation successfully avoided an out of bounds read.
- `ERROR_VARINTTOOBIG` - A varint field within the message is too big to decode using the built-in routines. Note that while
  the implementation can probably decode varints bigger than can fit inside of a `uint64_t`, they will be cut off because they're returned through one.
- `ERROR_UNKNOWNTAG` - An unsupported tag was found within the message.  For example, groups are not supported.

The following error codes may be thrown when adding an object:
- `ERROR_CANTADDROOTMSG` - An attempt to insert an object of type `ObjectBaseMessage` into a message object was made.

The following error codes may be thrown when using the `MergeWith` function:
- `ERROR_SUPPOSEDTOBEUNIQUE` - The relevant field number was marked "unique", yet the source message includes multiple payloads.

### Note about copying objects

To keep the design simple, it is not possible to create copies of a protobuf object.  You will have to write your own code to
clone the protobuf object, if needed.

### Note about dirtying

The protobuf implementation supports a dirty entry tracking system.  When an entry is modified, it is marked dirty.
The `EncodeDirty()` method does not clear the dirty flag. To do that, one must use the `MarkClean()` method.

###### Copyright (C) 2024 iProgramInCpp.  Licensed under the MIT license.
