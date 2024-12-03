#include "ffx.h"

using namespace std;

/* initialize the resources */
ScreenRecorder::ScreenRecorder() {
  avdevice_register_all();
  // FFmpeg no longer requires explicit registration functions in FFmpeg 5.x
  cout << "\nall required functions are registered successfully";
}

/* uninitialize the resources */
ScreenRecorder::~ScreenRecorder() {
  avformat_close_input(&pAVFormatContext);
  if (!pAVFormatContext) {
    cout << "\nfile closed successfully";
  } else {
    cout << "\nunable to close the file";
    exit(1);
  }

  avformat_free_context(pAVFormatContext);
  if (!pAVFormatContext) {
    cout << "\navformat free successfully";
  } else {
    cout << "\nunable to free avformat context";
    exit(1);
  }
}

int ScreenRecorder::CaptureVideoFrames() {
  int flag;
  int frameFinished; // When you decode a single packet, you still don't have
                     // enough information to have a frame.
  int frame_index = 0;
  value = 0;

  // Allocate memory for packet and frame
  pAVPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
  av_init_packet(pAVPacket);

  pAVFrame = av_frame_alloc();
  if (!pAVFrame) {
    cout << "\nUnable to allocate AVFrame resources.";
    exit(1);
  }

  outFrame = av_frame_alloc(); // Allocate an AVFrame for output
  if (!outFrame) {
    cout << "\nUnable to allocate AVFrame resources for outFrame.";
    exit(1);
  }

  // Allocate memory for the output buffer (video buffer)
  int video_outbuf_size;
  int nbytes = av_image_get_buffer_size(outAVCodecContext->pix_fmt,
                                        outAVCodecContext->width,
                                        outAVCodecContext->height, 32);
  uint8_t *video_outbuf = (uint8_t *)av_malloc(nbytes);
  if (!video_outbuf) {
    cout << "\nUnable to allocate memory for video output buffer.";
    exit(1);
  }

  // Fill the output frame with the allocated buffer
  value = av_image_fill_arrays(outFrame->data, outFrame->linesize, video_outbuf,
                               AV_PIX_FMT_YUV420P, outAVCodecContext->width,
                               outAVCodecContext->height, 1);
  if (value < 0) {
    cout << "\nError in filling image array for outFrame.";
    exit(1);
  }

  // Create the software scaler context for converting the frame format
  SwsContext *swsCtx_ = NULL;

  // Ensure pAVCodecContext is valid and initialized with valid parameters
  if (!pAVCodecContext || pAVCodecContext->width <= 0 ||
      pAVCodecContext->height <= 0 ||
      pAVCodecContext->pix_fmt == AV_PIX_FMT_NONE) {
    cout << "\nInvalid pAVCodecContext parameters!";
    exit(1);
  }

  swsCtx_ = sws_getContext(
      pAVCodecContext->width, pAVCodecContext->height, pAVCodecContext->pix_fmt,
      outAVCodecContext->width, outAVCodecContext->height,
      outAVCodecContext->pix_fmt, SWS_BICUBIC, NULL, NULL, NULL);

  if (!swsCtx_) {
    cout << "\nError creating sws context. Unable to scale the image.";
    exit(1); // Exit if swsContext creation failed
  }

  int ii = 0;
  int no_frames = 100;
  cout << "\nEnter the number of frames to capture: ";
  cin >> no_frames;

  AVPacket outPacket;
  int j = 0;
  int got_picture;

  // Loop through and read the video frames
  while (av_read_frame(pAVFormatContext, pAVPacket) >= 0) {
    if (ii++ == no_frames)
      break;

    if (pAVPacket->stream_index == VideoStreamIndx) {
      // Send the packet to the decoder
      value = avcodec_send_packet(pAVCodecContext, pAVPacket);
      if (value < 0) {
        cout << "Unable to decode video frame.";
        continue;
      }

      // Receive the decoded frame
      if (value == 0) { // Frame successfully decoded
        // Scale the image if necessary
        sws_scale(swsCtx_, pAVFrame->data, pAVFrame->linesize, 0,
                  pAVCodecContext->height, outFrame->data, outFrame->linesize);

        av_init_packet(&outPacket);
        outPacket.data = NULL; // Packet data will be allocated by the encoder
        outPacket.size = 0;

        // Send the frame to the encoder
        value = avcodec_send_frame(outAVCodecContext, outFrame);
        if (value >= 0) {
          // Receive the encoded packet
          value = avcodec_receive_packet(outAVCodecContext, &outPacket);
          if (value == 0) { // Frame encoded successfully
            // Rescale PTS and DTS if necessary
            if (outPacket.pts != AV_NOPTS_VALUE)
              outPacket.pts = av_rescale_q(outPacket.pts, video_st->time_base,
                                           video_st->time_base);
            if (outPacket.dts != AV_NOPTS_VALUE)
              outPacket.dts = av_rescale_q(outPacket.dts, video_st->time_base,
                                           video_st->time_base);

            printf("Write frame %3d (size= %2d)\n", j++, outPacket.size / 1000);
            // Write the encoded frame to the output file
            if (av_write_frame(outAVFormatContext, &outPacket) != 0) {
              cout << "\nError writing video frame.";
              exit(1);
            }

            // Free the packet after writing
            av_packet_unref(&outPacket);
          }
        }
      }
    }

    // Free the packet after decoding
    av_packet_unref(pAVPacket);
  }

  // Write the trailer at the end of the video
  value = av_write_trailer(outAVFormatContext);
  if (value < 0) {
    cout << "\nError writing AV trailer.";
    exit(1);
  }

  // Free the video output buffer memory
  av_freep(&video_outbuf);

  return 0;
}

/* establishing the connection between camera or screen through its respective
 * folder */
int ScreenRecorder::openCamera() {
  value = 0;
  options = NULL;
  pAVFormatContext = NULL;

  pAVFormatContext = avformat_alloc_context(); // Allocate an AVFormatContext.

  // Windows specific: gdigrab for screen capture
  const AVInputFormat *pAVInputFormat = av_find_input_format("gdigrab");
  if (!pAVInputFormat)
    return -1;
  // const AVInputFormat *pAVInputFormat = av_find_input_format("dshow");
  value = avformat_open_input(
      &pAVFormatContext, "desktop", pAVInputFormat,
      NULL); // "desktop" refers to the whole screen in gdigrab
  if (value != 0) {
    cout << "\nerror in opening input device";
    exit(1);
  }

  // set frame per second
  value = av_dict_set(&options, "framerate", "30", 0);
  if (value < 0) {
    cout << "\nerror in setting dictionary value";
    exit(1);
  }

  value = av_dict_set(&options, "preset", "medium", 0);
  if (value < 0) {
    cout << "\nerror in setting preset values";
    exit(1);
  }

  if (value < 0) {
    cout << "\nunable to find the stream information";
    exit(1);
  }

  VideoStreamIndx = -1;

  for (int i = 0; i < pAVFormatContext->nb_streams; i++) {
    if (pAVFormatContext->streams[i]->codecpar->codec_type ==
        AVMEDIA_TYPE_VIDEO) {
      VideoStreamIndx = i;
      break;
    }
  }

  if (VideoStreamIndx == -1) {
    cout << "\nunable to find the video stream index. (-1)";
    exit(1);
  }

  pAVCodecContext = avcodec_alloc_context3(NULL);
  if (!pAVCodecContext) {
    cout << "\nunable to allocate codec context";
    exit(1);
  }
  value = avcodec_parameters_to_context(
      pAVCodecContext, pAVFormatContext->streams[VideoStreamIndx]->codecpar);
  if (value < 0) {
    cout << "\nunable to copy codec parameters to context";
    exit(1);
  }
  const AVCodec *pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
  if (pAVCodec == NULL) {
    cout << "\nunable to find the decoder";
    exit(1);
  }

  value = avcodec_open2(
      pAVCodecContext, pAVCodec,
      NULL); // Initialize the AVCodecContext to use the given AVCodec.
  if (value < 0) {
    cout << "\nunable to open the av codec";
    exit(1);
  }
  return 0;
}

int ScreenRecorder::init_outputfile() {
  outAVFormatContext = NULL;
  value = 0;
  output_file = R"(C:\Users\k34ub\Desktop\capturescreen_s\output.mp4)";

  // 1. 分配输出格式上下文
  avformat_alloc_output_context2(&outAVFormatContext, NULL, NULL, output_file);
  if (!outAVFormatContext) {
    cout << "\nError in allocating AVFormatContext";
    exit(1);
  }

  // 2. 获取输出格式
  const AVOutputFormat *output_format =
      av_guess_format("mp4", output_file, NULL);
  if (!output_format) {
    cout << "\nError in guessing the video format. Try with a correct format";
    exit(1);
  }
  outAVFormatContext->oformat = output_format;

  // 3. 创建视频流
  video_st = avformat_new_stream(outAVFormatContext, NULL);
  if (!video_st) {
    cout << "\nError in creating AVFormat new stream";
    exit(1);
  }

  // 4. 分配编解码器上下文
  outAVCodecContext = avcodec_alloc_context3(NULL);
  if (!outAVCodecContext) {
    cout << "\nError in allocating the codec context";
    exit(1);
  }

  // 5. 设置视频编码器参数
  outAVCodecContext->codec_id = AV_CODEC_ID_HEVC; // 使用 H.265 编解码器（HEVC）
  outAVCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
  outAVCodecContext->pix_fmt = AV_PIX_FMT_YUV420P; // 设置像素格式为 YUV420P
  outAVCodecContext->bit_rate = 400000;            // 设置比特率
  outAVCodecContext->width = 1920;                 // 设置宽度
  outAVCodecContext->height = 1080;                // 设置高度
  outAVCodecContext->gop_size = 10;                // 设置 GOP 大小（通常为10）
  outAVCodecContext->max_b_frames = 1;             // 最大 B 帧数
  outAVCodecContext->time_base = (AVRational){1, 30}; // 每秒 30 帧

  // 6. 查找并打开编码器
  const AVCodec *outAVCodec =
      avcodec_find_encoder(AV_CODEC_ID_HEVC); // 查找 H.265 编解码器
  if (!outAVCodec) {
    cout << "\nError in finding the H.265 codec.";
    exit(1);
  }

  // 7. 打开编码器
  value = avcodec_open2(outAVCodecContext, outAVCodec, NULL);
  if (value < 0) {
    char errbuf[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(value, errbuf, sizeof(errbuf));
    cout << "\nError in opening the codec: " << errbuf;
    exit(1);
  }

  // 8. 将编码器参数传递给视频流
  value =
      avcodec_parameters_from_context(video_st->codecpar, outAVCodecContext);
  if (value < 0) {
    cout << "\nError in copying codec parameters to stream";
    exit(1);
  }

  // 9. 创建文件（确保能正确写入）
  if (!(outAVFormatContext->flags & AVFMT_NOFILE)) {
    if (avio_open2(&outAVFormatContext->pb, output_file, AVIO_FLAG_WRITE, NULL,
                   NULL) < 0) {
      cout << "\nError in creating the video file";
      exit(1);
    }
  }

  // 10. 检查是否有流
  if (!outAVFormatContext->nb_streams) {
    cout << "\nOutput file does not contain any stream";
    exit(1);
  }

  // 11. 写入文件头
  value = avformat_write_header(outAVFormatContext, NULL);
  if (value < 0) {
    cout << "\nError in writing the header context";
    exit(1);
  }

  // 12. 完成初始化
  cout << "\nOutput file initialized successfully: " << output_file << endl;

  return 0;
}

XS_EXTERN char *xs_ffx_malloc(size_t len) {
  char *result = nullptr;
  do {
    if (len <= 0)
      break;
    result = (char *)malloc(len);
  } while (0);
  return result;
}
XS_EXTERN void xs_ffx_free(void **p) {
  do {
    if (!p)
      break;
    if (!(*p))
      break;
    free(*p);
    *p = nullptr;
  } while (0);
}
XS_EXTERN int test_x264_encoder(const char *input_file,
                                const char *output_file) {
  AVFormatContext *input_fmt_ctx = NULL;
  AVCodecContext *codec_ctx = NULL;
  const AVCodec *codec = NULL;
  AVPacket packet;
  int ret;

  // 打开输入文件
  if ((ret = avformat_open_input(&input_fmt_ctx, input_file, NULL, NULL)) < 0) {
    fprintf(stderr, "Could not open input file\n");
    return ret;
  }

  // 查找输入文件的流信息
  if ((ret = avformat_find_stream_info(input_fmt_ctx, NULL)) < 0) {
    fprintf(stderr, "Could not find stream information\n");
    return ret;
  }

  // 查找视频流的解码器
  int video_stream_index = -1;
  for (int i = 0; i < input_fmt_ctx->nb_streams; i++) {
    if (input_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      break;
    }
  }
  if (video_stream_index == -1) {
    fprintf(stderr, "No video stream found\n");
    return AVERROR_STREAM_NOT_FOUND;
  }

  AVStream *video_stream = input_fmt_ctx->streams[video_stream_index];
  codec = avcodec_find_decoder(video_stream->codecpar->codec_id);
  if (!codec) {
    fprintf(stderr, "Could not find codec\n");
    return AVERROR_DECODER_NOT_FOUND;
  }

  codec_ctx = avcodec_alloc_context3(codec);
  if ((ret = avcodec_parameters_to_context(codec_ctx, video_stream->codecpar)) <
      0) {
    fprintf(stderr, "Could not copy codec parameters\n");
    return ret;
  }

  if ((ret = avcodec_open2(codec_ctx, codec, NULL)) < 0) {
    fprintf(stderr, "Could not open codec\n");
    return ret;
  }

  // 设置输出文件
  AVFormatContext *output_fmt_ctx = NULL;
  if ((ret = avformat_alloc_output_context2(&output_fmt_ctx, NULL, "mp4",
                                            output_file)) < 0) {
    fprintf(stderr, "Could not create output context\n");
    return ret;
  }

  AVStream *output_stream = avformat_new_stream(output_fmt_ctx, NULL);
  if (!output_stream) {
    fprintf(stderr, "Failed to create output stream\n");
    return AVERROR_STREAM_NOT_FOUND;
  }

  const AVCodec *x264_encoder = avcodec_find_encoder_by_name("libx264");
  if (!x264_encoder) {
    fprintf(stderr, "libx264 encoder not found\n");
    return AVERROR_ENCODER_NOT_FOUND;
  }

  AVCodecContext *output_codec_ctx = avcodec_alloc_context3(x264_encoder);
  output_codec_ctx->height = codec_ctx->height;
  output_codec_ctx->width = codec_ctx->width;
  output_codec_ctx->sample_aspect_ratio = codec_ctx->sample_aspect_ratio;
  output_codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
  output_codec_ctx->time_base = video_stream->time_base;

  // 设置输出流的编码器
  output_stream->codecpar->codec_id = x264_encoder->id;
  output_stream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
  output_stream->codecpar->width = codec_ctx->width;
  output_stream->codecpar->height = codec_ctx->height;
  output_stream->codecpar->format = AV_PIX_FMT_YUV420P;
  output_stream->time_base = video_stream->time_base;

  if ((ret = avcodec_open2(output_codec_ctx, x264_encoder, NULL)) < 0) {
    fprintf(stderr, "Could not open libx264 codec\n");
    return ret;
  }

  if ((ret = avio_open(&output_fmt_ctx->pb, output_file, AVIO_FLAG_WRITE)) <
      0) {
    fprintf(stderr, "Could not open output file\n");
    return ret;
  }

  if ((ret = avformat_write_header(output_fmt_ctx, NULL)) < 0) {
    fprintf(stderr, "Error writing header to output file\n");
    return ret;
  }

  // 从输入文件读取视频帧并编码为 H.264
  while (av_read_frame(input_fmt_ctx, &packet) >= 0) {
    if (packet.stream_index == video_stream_index) {
      ret = avcodec_send_packet(codec_ctx, &packet);
      if (ret < 0) {
        fprintf(stderr, "Error sending packet to codec\n");
        break;
      }

      AVFrame *frame = av_frame_alloc();
      ret = avcodec_receive_frame(codec_ctx, frame);
      if (ret < 0) {
        av_frame_free(&frame);
        continue;
      }

      ret = avcodec_send_frame(output_codec_ctx, frame);
      if (ret < 0) {
        av_frame_free(&frame);
        break;
      }

      ret = avcodec_receive_packet(output_codec_ctx, &packet);
      if (ret >= 0) {
        av_write_frame(output_fmt_ctx, &packet);
        av_packet_unref(&packet);
      }
      av_frame_free(&frame);
    }
    av_packet_unref(&packet);
  }

  av_write_trailer(output_fmt_ctx);
  avcodec_free_context(&codec_ctx);
  avcodec_free_context(&output_codec_ctx);
  avformat_free_context(input_fmt_ctx);
  avformat_free_context(output_fmt_ctx);

  return 0;
}

XS_EXTERN int test_x265_encoder(const char *input_file,
                                const char *output_file) {
  AVFormatContext *input_fmt_ctx = NULL;
  AVCodecContext *codec_ctx = NULL;
  const AVCodec *codec = NULL;
  AVPacket packet;
  int ret;

  // 打开输入文件
  if ((ret = avformat_open_input(&input_fmt_ctx, input_file, NULL, NULL)) < 0) {
    fprintf(stderr, "Could not open input file\n");
    return ret;
  }

  // 查找输入文件的流信息
  if ((ret = avformat_find_stream_info(input_fmt_ctx, NULL)) < 0) {
    fprintf(stderr, "Could not find stream information\n");
    return ret;
  }

  // 查找视频流的解码器
  int video_stream_index = -1;
  for (int i = 0; i < input_fmt_ctx->nb_streams; i++) {
    if (input_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      break;
    }
  }
  if (video_stream_index == -1) {
    fprintf(stderr, "No video stream found\n");
    return AVERROR_STREAM_NOT_FOUND;
  }

  AVStream *video_stream = input_fmt_ctx->streams[video_stream_index];
  codec = avcodec_find_decoder(video_stream->codecpar->codec_id);
  if (!codec) {
    fprintf(stderr, "Could not find codec\n");
    return AVERROR_DECODER_NOT_FOUND;
  }

  codec_ctx = avcodec_alloc_context3(codec);
  if ((ret = avcodec_parameters_to_context(codec_ctx, video_stream->codecpar)) <
      0) {
    fprintf(stderr, "Could not copy codec parameters\n");
    return ret;
  }

  if ((ret = avcodec_open2(codec_ctx, codec, NULL)) < 0) {
    fprintf(stderr, "Could not open codec\n");
    return ret;
  }

  // 设置输出文件
  AVFormatContext *output_fmt_ctx = NULL;
  if ((ret = avformat_alloc_output_context2(&output_fmt_ctx, NULL, "mp4",
                                            output_file)) < 0) {
    fprintf(stderr, "Could not create output context\n");
    return ret;
  }

  AVStream *output_stream = avformat_new_stream(output_fmt_ctx, NULL);
  if (!output_stream) {
    fprintf(stderr, "Failed to create output stream\n");
    return AVERROR_STREAM_NOT_FOUND;
  }

  const AVCodec *x265_encoder = avcodec_find_encoder_by_name("libx265");
  if (!x265_encoder) {
    fprintf(stderr, "libx265 encoder not found\n");
    return AVERROR_ENCODER_NOT_FOUND;
  }

  AVCodecContext *output_codec_ctx = avcodec_alloc_context3(x265_encoder);
  output_codec_ctx->height = codec_ctx->height;
  output_codec_ctx->width = codec_ctx->width;
  output_codec_ctx->sample_aspect_ratio = codec_ctx->sample_aspect_ratio;
  output_codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
  output_codec_ctx->time_base = video_stream->time_base;

  // 设置输出流的编码器
  output_stream->codecpar->codec_id = x265_encoder->id;
  output_stream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
  output_stream->codecpar->width = codec_ctx->width;
  output_stream->codecpar->height = codec_ctx->height;
  output_stream->codecpar->format = AV_PIX_FMT_YUV420P;
  output_stream->time_base = video_stream->time_base;

  if ((ret = avcodec_open2(output_codec_ctx, x265_encoder, NULL)) < 0) {
    fprintf(stderr, "Could not open libx265 codec\n");
    return ret;
  }

  if ((ret = avio_open(&output_fmt_ctx->pb, output_file, AVIO_FLAG_WRITE)) <
      0) {
    fprintf(stderr, "Could not open output file\n");
    return ret;
  }

  if ((ret = avformat_write_header(output_fmt_ctx, NULL)) < 0) {
    fprintf(stderr, "Error writing header to output file\n");
    return ret;
  }

  // 从输入文件读取视频帧并编码为 H.265
  while (av_read_frame(input_fmt_ctx, &packet) >= 0) {
    if (packet.stream_index == video_stream_index) {
      ret = avcodec_send_packet(codec_ctx, &packet);
      if (ret < 0) {
        fprintf(stderr, "Error sending packet to codec\n");
        break;
      }

      AVFrame *frame = av_frame_alloc();
      ret = avcodec_receive_frame(codec_ctx, frame);
      if (ret < 0) {
        av_frame_free(&frame);
        continue;
      }

      ret = avcodec_send_frame(output_codec_ctx, frame);
      if (ret < 0) {
        av_frame_free(&frame);
        break;
      }

      ret = avcodec_receive_packet(output_codec_ctx, &packet);
      if (ret >= 0) {
        av_write_frame(output_fmt_ctx, &packet);
        av_packet_unref(&packet);
      }
      av_frame_free(&frame);
    }
    av_packet_unref(&packet);
  }

  av_write_trailer(output_fmt_ctx);
  avcodec_free_context(&codec_ctx);
  avcodec_free_context(&output_codec_ctx);
  avformat_free_context(input_fmt_ctx);
  avformat_free_context(output_fmt_ctx);

  return 0;
}

#if defined(__OSWIN__)
// #include <windows.h>
#if 0
void CaptureScreen(HDC hdc, int width, int height, AVFrame *frame) {
  HDC hdcMem = CreateCompatibleDC(hdc);
  HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
  HGDIOBJ oldObj = SelectObject(hdcMem, hBitmap);

  // 抓取屏幕内容
  BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

  // 设置 BITMAPINFOHEADER
  BITMAPINFOHEADER bi;
  ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
  bi.biSize = sizeof(BITMAPINFOHEADER);
  bi.biWidth = width;
  bi.biHeight = -height; // 倒置 Y 轴
  bi.biPlanes = 1;
  bi.biBitCount = 24; // 每像素24位
  bi.biCompression = BI_RGB;

  // 将位图数据拷贝到 frame->data[0]
  if (!GetDIBits(hdcMem, hBitmap, 0, height, frame->data[0], (BITMAPINFO *)&bi,
                 DIB_RGB_COLORS)) {
    std::cerr << "Failed to capture screen bits!" << std::endl;
  }

  // 恢复和清理
  SelectObject(hdcMem, oldObj);
  DeleteObject(hBitmap);
  DeleteDC(hdcMem);
  }
#endif

XS_EXTERN int xs_ffx_screen_recording(void) {

  ScreenRecorder screen_record;

  screen_record.openCamera();
  screen_record.init_outputfile();
  screen_record.CaptureVideoFrames();

  auto xx = 0;
#if 0
  // 初始化FFmpeg
  avformat_network_init();

  // 屏幕尺寸设置
  int width = GetSystemMetrics(SM_CXSCREEN);
  int height = GetSystemMetrics(SM_CYSCREEN);

  // 创建视频文件
  AVFormatContext *pFormatContext = nullptr;
  if (avformat_alloc_output_context2(
          &pFormatContext, nullptr, nullptr,
          R"(C:\Users\k34ub\Desktop\capturescreen_s\output.mp4)") < 0) {
    std::cerr << "Failed to create output context!" << std::endl;
    return -1;
  }

  // 创建视频流
  AVStream *pStream = avformat_new_stream(pFormatContext, nullptr);
  if (!pStream) {
    std::cerr << "Failed to create video stream!" << std::endl;
    return -1;
  }

  // 设置视频编码器为 H.264
  const AVCodec *pCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (!pCodec) {
    std::cerr << "H.264 Codec not found!" << std::endl;
    return -1;
  }
  AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
  pCodecContext->width = width;
  pCodecContext->height = height;
  pCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
  pCodecContext->time_base = {1, 30}; // 30帧每秒
  pCodecContext->bit_rate = 400000;   // 比特率
  pCodecContext->gop_size = 12;       // 每12帧一个关键帧
  pCodecContext->max_b_frames = 2;    // 最大B帧数量

  if (avcodec_open2(pCodecContext, pCodec, nullptr) < 0) {
    std::cerr << "Failed to open codec!" << std::endl;
    return -1;
  }

  // 为视频流设置编码器
  avcodec_parameters_from_context(pStream->codecpar, pCodecContext);

  // 打开文件
  if (avio_open(&pFormatContext->pb,
                R"(C:\Users\k34ub\Desktop\capturescreen_s\output.mp4)",
                AVIO_FLAG_WRITE) < 0) {
    std::cerr << "Failed to open output file!" << std::endl;
    return -1;
  }

  // 写入文件头
  if (avformat_write_header(pFormatContext, nullptr) < 0) {
    std::cerr << "Failed to write header!" << std::endl;
    return -1;
  }

  // 捕获并编码屏幕帧
  AVFrame *yuv_frame = av_frame_alloc();
  yuv_frame->format = AV_PIX_FMT_YUV420P;
  yuv_frame->width = width;
  yuv_frame->height = height;
  av_frame_get_buffer(yuv_frame, 32);

  // 使用 GDI+ 截屏方法
  xs_image_stream_t *image_stream = nullptr;
  xs_position_t pos = {};         // 假设全屏截图
  for (int i = 0; i < 300; i++) { // 假设录制10秒，30fps
    if (0 !=
        xs_sys_capturescreen(pos, xs_image_stream_type_t::PNG, &image_stream)) {
      std::cerr << "Failed to capture screen!" << std::endl;
      return -1;
    }

    // 将截图数据解码为像素帧
    uint8_t *raw_data = reinterpret_cast<uint8_t *>(image_stream->buffer);
    SwsContext *sws_ctx = sws_getContext(
        width, height, AV_PIX_FMT_BGR24, width, height, AV_PIX_FMT_YUV420P,
        SWS_BILINEAR, nullptr, nullptr, nullptr);
    AVFrame *frame = av_frame_alloc();
    frame->format = AV_PIX_FMT_BGR24;
    frame->width = width;
    frame->height = height;
    av_image_fill_arrays(frame->data, frame->linesize, raw_data,
                         AV_PIX_FMT_BGR24, width, height, 1);

    sws_scale(sws_ctx, frame->data, frame->linesize, 0, height, yuv_frame->data,
              yuv_frame->linesize);

    // 发送帧给编码器
    if (avcodec_send_frame(pCodecContext, yuv_frame) < 0) {
      std::cerr << "Failed to send frame to encoder!" << std::endl;
      return -1;
    }

    // 从编码器接收数据包并写入文件
    AVPacket *pkt = av_packet_alloc();
    if (!pkt) {
      std::cerr << "Error allocating packet!" << std::endl;
      return -1;
    }

    while (avcodec_receive_packet(pCodecContext, pkt) == 0) {
      av_write_frame(pFormatContext, pkt);
      av_packet_unref(pkt);
    }

    av_packet_free(&pkt);
    sws_freeContext(sws_ctx);
    av_frame_free(&frame);

    // 释放截图数据
    free(image_stream->buffer);
    free(image_stream);
  }

  // 写入文件尾并清理资源
  av_write_trailer(pFormatContext);

  // 释放资源
  av_frame_free(&yuv_frame);
  avcodec_free_context(&pCodecContext);
  avformat_free_context(pFormatContext);

  std::cout << "Screen recording finished!" << std::endl;
#endif
  return 0;
}

#endif
