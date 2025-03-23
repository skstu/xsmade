#if !defined(__BAD7C40E_08D9_43C6_9D8F_E6C5715A770A__)
#define __BAD7C40E_08D9_43C6_9D8F_E6C5715A770A__
#if ENABLE_FFCODEC
extern "C" {
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavcodec/avcodec.h"
#include <libswscale/swscale.h>
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#include "libavutil/pixdesc.h"
#include "libavutil/time.h"
#include "libavutil/avassert.h"
#include "libavutil/mathematics.h"
#include "libavutil/samplefmt.h"
#include "libavutil/channel_layout.h"
#include "libavutil/log.h"
#include "libavutil/error.h"
#include "libavutil/avstring.h"
#include "libavutil/frame.h"
}
class FFCodec {
public:
  FFCodec(const std::string &);
  ~FFCodec();

private:
  void Init();
  void UnInit();
public:
  bool setUpEncoder(std::string filename, int width, int height, int fps,
                    int bitrate);
  bool encodeFromFolder(std::string folder, std::string prefix,
                        int numberOfFrames);
  bool addFrame(const uint8_t *src, int src_linesize);
  bool encodeTestVideo();
  bool closeEncoder();

private:
  AVFrame *read_png_to_avframe(const char *filename);

  AVFormatContext *fmt_ctx;
  AVCodecContext *codec_ctx;
  AVStream *stream;
  AVPacket *pkt;
  AVFrame *frame;

  int frameNumber;

  const std::string outputFilePath_;
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 16 Mar 2025 09:22:04 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__BAD7C40E_08D9_43C6_9D8F_E6C5715A770A__