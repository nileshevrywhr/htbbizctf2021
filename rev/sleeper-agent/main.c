
undefined8 main(undefined8 param_1,undefined8 param_2,size_t *param_3,uchar *param_4,size_t param_5)

{
  int intVar;
  code *code_type;
  size_t *outlen;
  size_t *outlen_00;
  size_t *outlen_01;
  undefined one_six [16];

  intVar = decrypt((EVP_PKEY_CTX *)(ulong)secretlen5, secret5, param_3, param_4, param_5);
  one_six = dlsym(0xffffffffffffffff, intVar);
  ptracee = SUB168(one_six, 0);

  intVar = decrypt((EVP_PKEY_CTX *)(ulong)secretlen0, (uchar *)&secret0, SUB168(one_six >> 0x40, 0), param_4, param_5);
  code_type = (code *)dlsym(0xffffffffffffffff, intVar);
  (*code_type)();

  intVar = decrypt((EVP_PKEY_CTX *)(ulong)secretlen3, secret3, outlen, param_4, param_5);
  code_type = (code *)dlsym(0xffffffffffffffff, intVar);
  (*code_type)();

  intVar = decrypt((EVP_PKEY_CTX *)(ulong)secretlen3, secret3, outlen_00, param_4, param_5);
  code_type = (code *)dlsym(0xffffffffffffffff, intVar);
  (*code_type)();

  intVar = decrypt((EVP_PKEY_CTX *)(ulong)secretlen2, secret2, outlen_01, param_4, param_5);
  one_six = dlsym(0xffffffffffffffff, intVar);

  intVar = decrypt((EVP_PKEY_CTX *)(ulong)secretlen4, secret4, SUB168(one_six >> 0x40, 0), param_4, param_5);
  (*SUB168(one_six, 0))(intVar);

  return 0;
}
