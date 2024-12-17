#if !defined(__8A328F38_DDB3_4605_8C72_CFDDB24C688A__)
#define __8A328F38_DDB3_4605_8C72_CFDDB24C688A__

#include "xs.h"

#ifdef __cplusplus
extern "C" {
#endif

XS_EXTERN char *xs_ffx_malloc(size_t len);
XS_EXTERN void xs_ffx_free(void **p);
XS_EXTERN int test_x264_encoder(const char *input_file,
                                const char *output_file);
XS_EXTERN int test_x265_encoder(const char *input_file,
                                const char *output_file);

XS_EXTERN int xs_ffx_screen_recording(void);
#ifdef __cplusplus
}
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 19 Nov 2024 07:31:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8A328F38_DDB3_4605_8C72_CFDDB24C688A__