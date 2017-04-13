Initialize Client


The INITUSER sample sets up the default cryptographic client. This sample
(or its equivalent) must be run prior to running the other cryptography
samples, so that they will work correctly.

The following operations are performed:

1. A default key container is created.
2. A digital signature key pair is created within the key container.
3. A key exchange key pair is created within the key container.

These operations only need to be done once, unless the operating system
is reinstalled. If the default key container and key pairs have already
been created, this sample performs no operations.

The INITUSER sample uses the following CryptoAPI functions:

    CryptAcquireContext
    CryptGetProvParam
    CryptGenKey
    CryptGetUserKey
    CryptDestroyKey
    CryptReleaseContext
