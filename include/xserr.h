#if !defined(__533973DF_1B2B_4CC9_8911_A862F3DEC534__)
#define __533973DF_1B2B_4CC9_8911_A862F3DEC534__

#define XS__OK (-0)
#define XS__NO (-1)
#define XS__DONE (1)
//! system [ -1000 ~ -1999]
//! component [ -2000 ~ -2999 ]
//! plugin [ -3000 ~ -3999 ]
//! base [-10000~ -19999 ]
#define XS__EBASINIT (-10001)
#define XS__EBASUNINIT (-10002)
#define XS__EBASFREE (-10003)
#define XS__WALREADYRUNNING (-20001)
#define XS__EUNKN (-50000)
#define XS__EOF (-65533)

#define XS_ERRNO_MAP(XX)                                                       \
  XX(OK, "ok ")                                                                \
  XX(NO, "no ")                                                                \
  XX(DONE, "done ")                                                            \
  XX(EBASINIT, "base init error")                                              \
  XX(EBASUNINIT, "base uninit error")                                          \
  XX(EBASFREE, "base free error")                                              \
  XX(WALREADYRUNNING, "AlreadyRunning")                                        \
  XX(EUNKN, "unknown error")

typedef enum {
#define XX(code, _) XS_##code = XS__##code,
  XS_ERRNO_MAP(XX)
#undef XX
      XS_ERRNO_MAX = XS__EOF - 1
} xs_errno_t;

static const char *xs__unknown_err_code(int err) {
  char buf[256];
  char *copy = NULL;

  // snprintf(buf, sizeof(buf), "Unknown system error %d", err);
  sprintf(buf, "Unknown system error %d", err);
  do {
    size_t len = strlen(buf) + 1;
    char *m = (char *)malloc(len);
    if (m == NULL)
      break;
    copy = (char *)memcpy(m, buf, len);
  } while (0);

  return copy != NULL ? copy : "Unknown system error";
}

#define XS_ERR_NAME_GEN(name, _)                                               \
  case XS_##name:                                                              \
    return #name;
static const char *xs_err_name(int err) {
  switch (err) { XS_ERRNO_MAP(XS_ERR_NAME_GEN) }
  return xs__unknown_err_code(err);
}
#undef XS_ERR_NAME_GEN

#define XS_STRERROR_GEN(name, msg)                                             \
  case XS_##name:                                                              \
    return msg;
static const char *xs_strerror(int err) {
  switch (err) { XS_ERRNO_MAP(XS_STRERROR_GEN) }
  return xs__unknown_err_code(err);
}
#undef XS_STRERROR_GEN

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 04 Dec 2024 13:14:02 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__533973DF_1B2B_4CC9_8911_A862F3DEC534__
