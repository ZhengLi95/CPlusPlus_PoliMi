# REQUEST AND CONNECTION CLASSES

Read all the codes, write down the output.

Notice that: class `Request` uses a value-like memory management, so when an instance `a` is created from an instance `b` through copy-constructor or copy-operator, a new array of char is created in memory and all the values of `b` are copied into `a`. For this reason, any modification applied to `a` do not affect `b` and vice versa.

On contrary, class Connection uses a pointer-like memory management by exploiting reference counting. When an instance `c` is created from an instance `d`, they will share all their data (i.e., `count` and `priority`) and modifications on one of those instances will affect the other.