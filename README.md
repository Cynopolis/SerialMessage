# Welcome!

The point of this library is to allow anyone to recieve and parse numerical data over a serial message. 

The format of an acceptable message is:
`!aaa...,bbb...,c...,...;`

IE: `!128,4096,1;`
All arguments in the message must be an integer and can be no bigger than a 32-bit int. (Negative numbers are also accepted).

All messages must also begin with an `!` and end with an `;`.

Setting up a Message object is easy and all message objects are more or less interchangeable. (There are some caveats to this especially regarding TelnetMessage and its complexity)

Simply create a message object like the SerialMessage one below:

`SerialMessage<100, 5> message(&Serial);`

Also be sure to call the Init() function for the corresponding Message object. This is **required** in order for the message object to function.

For the `TelnetMessage` object you will need to provide a callback function. it is strongly reocmmended that you use this one:
`[](String data){wifiMessage.SetString(data.c_str());}`

All message objects take in a `<MAX_BUFFER_SIZE, MAX_NUMBER_OF_ARGUMENTS>` as part of their definition. This allows you to choose how much memory you want to statically allocate to one of these objects at compile time. If you know that you are going to be sending huge messages with lots of arguments then you should increase the buffer size and number of arguments to something large. If either of these values are too small, then the values that the message object will recieve will be truncated and could result in invalid messages.