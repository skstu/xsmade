#if !defined(__516B6780_EE2B_497B_B0A1_4C45F3A3DD5B__)
#define __516B6780_EE2B_497B_B0A1_4C45F3A3DD5B__

#include <ffx.h>
#include <system.h>
#include <stl.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/avfft.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
// #include <libavfilter/avfiltergraph.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/opt.h>
#include <libavutil/common.h>
#include <libavutil/channel_layout.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavutil/time.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
#include <libavutil/file.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libpostproc/postprocess.h>
#include <libavutil/ffversion.h>
}

class ScreenRecorder {
private:
  AVInputFormat *pAVInputFormat;
  AVOutputFormat *output_format;

  AVCodecContext *pAVCodecContext;

  AVFormatContext *pAVFormatContext;

  AVFrame *pAVFrame;
  AVFrame *outFrame;

  AVCodec *pAVCodec;
  AVCodec *outAVCodec;

  AVPacket *pAVPacket;

  AVDictionary *options;

  AVOutputFormat *outAVOutputFormat;
  AVFormatContext *outAVFormatContext;
  AVCodecContext *outAVCodecContext;

  AVStream *video_st;
  AVFrame *outAVFrame;

  const char *dev_name;
  const char *output_file;

  double video_pts;

  int out_size;
  int codec_id;
  int value;
  int VideoStreamIndx;

public:
  ScreenRecorder();
  ~ScreenRecorder();

  /* function to initiate communication with display library */
  int openCamera();
  int init_outputfile();
  int CaptureVideoFrames();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 19 Nov 2024 06:09:35 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__516B6780_EE2B_497B_B0A1_4C45F3A3DD5B__