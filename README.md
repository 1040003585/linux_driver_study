# linux_driver_study

```
.
├── ch06_01--hello_world
│   ├── hello_world.c
│   ├── hello_world.ko
│   ├── Makefile
│   └── readme.txt
├── ch06_01--module_init
│   ├── song4--EXPORT_SYMBOL
│   │   ├── EXPORT_SYMBOL.c
│   │   ├── EXPORT_SYMBOL.ko
│   │   ├── Makefile
│   │   ├── Module.symvers
│   │   └── readme.txt
│   ├── song4--EXPORT_SYMBOL_another
│   │   ├── EXPORT_SYMBOL_another.c
│   │   ├── EXPORT_SYMBOL_another.ko
│   │   ├── Makefile
│   │   ├── Module.symvers
│   │   └── readme.txt
│   ├── song4--module_param
│   │   ├── Makefile
│   │   ├── module_param.c
│   │   ├── module_param.ko
│   │   ├── Module.symvers
│   │   └── readme.txt
│   └── song4--try_module_get
│       ├── 1.try_module_get
│       │   ├── Makefile
│       │   ├── readme.txt
│       │   ├── try_module_get.c
│       │   └── try_module_get.ko
│       ├── 2.module_put
│       │   ├── Makefile
│       │   ├── module_put.c
│       │   ├── module_put.ko
│       │   └── readme.txt
│       ├── 3.try_module_get2
│       │   ├── Makefile
│       │   ├── readme.txt
│       │   ├── try_module_get2.c
│       │   └── try_module_get2.ko
│       ├── 4.try_module_get_at_device
│       │   ├── Makefile
│       │   ├── readme.txt
│       │   ├── try_module_get_at_device.c
│       │   └── try_module_get_at_device.ko
│       └── 5.try_module_get_at_two_module
│           ├── client
│           │   ├── Makefile
│           │   ├── Module.symvers
│           │   ├── readme.txt
│           │   ├── try_module_get_client.c
│           │   └── try_module_get_client.ko
│           └── server
│               ├── Makefile
│               ├── Module.symvers
│               ├── readme.txt
│               ├── try_module_get_server.c
│               └── try_module_get_server.ko
├── ch06_02--misc_register
│   ├── Makefile
│   ├── misc_register.c
│   ├── misc_register.ko
│   └── readme.txt
├── ch06_03--file_operations
│   ├── file_operations.c
│   ├── file_operations.ko
│   ├── Makefile
│   └── readme.txt
├── ch06_04--word_count
│   ├── Makefile
│   ├── readme.txt
│   ├── word_count.c
│   └── word_count.ko
├── ch06_05--word_count_userspace
│   ├── Makefile
│   ├── readme.txt
│   ├── userspace
│   ├── userspace.c
│   ├── word_count_userspace.c
│   └── word_count_userspace.ko
└── README.md

```
