#include "server.h"
#if ENABLE_FFCODEC
FFCodec::FFCodec(const std::string &outputFilePath)
    : outputFilePath_(outputFilePath) {
  Init();
}

FFCodec::~FFCodec() {
  UnInit();
}
void FFCodec::Init() {
}
void FFCodec::UnInit() {
}
bool FFCodec::setUpEncoder(std::string filename, int width, int height, int fps,
                           int bitrate) {
  frameNumber = 0;

  fmt_ctx = nullptr;
  avformat_alloc_output_context2(&fmt_ctx, nullptr, "mp4", filename.c_str());
  if (!fmt_ctx) {
    fprintf(stderr, "Could not allocate output context\n");
    return false;
  }

  // Find the video encoder
  const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (!codec) {
    fprintf(stderr, "Could not find encoder\n");
    avformat_free_context(fmt_ctx);
    return false;
  }

  // Create a new stream
  stream = avformat_new_stream(fmt_ctx, nullptr);
  if (!stream) {
    fprintf(stderr, "Could not create stream\n");
    avformat_free_context(fmt_ctx);
    return false;
  }

  // Allocate and configure the codec context
  codec_ctx = avcodec_alloc_context3(codec);
  if (!codec_ctx) {
    fprintf(stderr, "Could not allocate codec context\n");
    avformat_free_context(fmt_ctx);
    return false;
  }

  codec_ctx->bit_rate = bitrate;
  codec_ctx->width = width;
  codec_ctx->height = height;
  codec_ctx->time_base = {1, fps};
  codec_ctx->framerate = {fps, 1};
  codec_ctx->gop_size = 10;
  codec_ctx->max_b_frames = 0;
  codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

  // Set the profile to high
  av_opt_set(codec_ctx->priv_data, "profile", "high", 0);

  // disable frame skipping and set rate control mode to off
  int res = av_opt_set(codec_ctx->priv_data, "allow_skip_frames", "0", 0);
  res = av_opt_set(codec_ctx->priv_data, "rc_mode", "off", 0);

  // Some formats want stream headers to be separate
  if (fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER) {
    codec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  }

  // Open the codec
  if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
    fprintf(stderr, "Could not open codec\n");
    avcodec_free_context(&codec_ctx);
    avformat_free_context(fmt_ctx);
    return false;
  }

  // Set codec parameters for the stream
  avcodec_parameters_from_context(stream->codecpar, codec_ctx);
  stream->time_base = codec_ctx->time_base;

  // Open the output file
  if (!(fmt_ctx->oformat->flags & AVFMT_NOFILE)) {
    if (avio_open(&fmt_ctx->pb, filename.c_str(), AVIO_FLAG_WRITE) < 0) {
      fprintf(stderr, "Could not open output file '%s'\n", filename.c_str());
      avcodec_free_context(&codec_ctx);
      avformat_free_context(fmt_ctx);
      return false;
    }
  }

  // Write the stream header
  if (avformat_write_header(fmt_ctx, nullptr) < 0) {
    fprintf(stderr, "Error occurred when opening output file\n");
    avcodec_free_context(&codec_ctx);
    avformat_free_context(fmt_ctx);
    return false;
  }

  // Allocate and initialize a frame
  frame = av_frame_alloc();
  if (!frame) {
    fprintf(stderr, "Could not allocate video frame\n");
    avcodec_free_context(&codec_ctx);
    avformat_free_context(fmt_ctx);
    return false;
  }
  frame->format = codec_ctx->pix_fmt;
  frame->width = codec_ctx->width;
  frame->height = codec_ctx->height;

  if (av_frame_get_buffer(frame, 0) < 0) {
    fprintf(stderr, "Could not allocate frame data\n");
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
    avformat_free_context(fmt_ctx);
    return false;
  }

  pkt = av_packet_alloc();
  if (!pkt) {
    fprintf(stderr, "Could not allocate AVPacket\n");
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
    avformat_free_context(fmt_ctx);
    return false;
  }
  return true;
}

bool FFCodec::encodeFromFolder(std::string folder, std::string prefix,
                               int numberOfFrames) {
  std::string filename;

  for (int i = 1; i < numberOfFrames; i++) {
    filename = folder + prefix + std::to_string(i) + std::string(".png");

    frame = read_png_to_avframe(filename.c_str());

    frame->pts = i;
    i++;

    // Send the frame to the encoder
    if (avcodec_send_frame(codec_ctx, frame) < 0) {
      fprintf(stderr, "Error sending frame to encoder\n");
      return false;
    }

    // Receive the encoded packet
    while (avcodec_receive_packet(codec_ctx, pkt) == 0) {
      pkt->stream_index = stream->index;
      av_packet_rescale_ts(pkt, codec_ctx->time_base, stream->time_base);
      pkt->pos = -1;

      if (av_interleaved_write_frame(fmt_ctx, pkt) < 0) {
        fprintf(stderr, "Error writing packet\n");
        return false;
      }
      av_packet_unref(pkt);
    }
  }

  return false;
}

bool FFCodec::addFrame(const uint8_t *data, int src_linesize) {
  // expects the data to be represented in RGBA format (8888)

  AVFrame *frameRGB = av_frame_alloc();
  if (!frameRGB) {
    return false;
  }
  frameRGB->width = codec_ctx->width;
  frameRGB->height = codec_ctx->height;
  frameRGB->format = AV_PIX_FMT_RGB32;
  av_frame_get_buffer(frameRGB, 0);

  uint8_t *dst = frameRGB->data[0];
  int dst_linesize = frameRGB->linesize[0];

  for (int y = 0; y < codec_ctx->height; ++y) {
    memcpy(dst + y * dst_linesize, data + y * src_linesize, src_linesize);
  }

  // convert rgb to YUV
  int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, codec_ctx->width,
                                          codec_ctx->height, 32);
  uint8_t *bufferYUV = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
  av_image_fill_arrays(frame->data, frame->linesize, bufferYUV,
                       AV_PIX_FMT_YUV420P, codec_ctx->width, codec_ctx->height,
                       32);

  SwsContext *sws_ctx_yuv =
      sws_getContext(codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB32,
                     codec_ctx->width, codec_ctx->height, AV_PIX_FMT_YUV420P,
                     SWS_BILINEAR, nullptr, nullptr, nullptr);

  sws_scale(sws_ctx_yuv, frameRGB->data, frameRGB->linesize, 0,
            codec_ctx->height, frame->data, frame->linesize);

  frame->pts = frameNumber;
  frameNumber++;

  // Send the frame to the encoder
  if (avcodec_send_frame(codec_ctx, frame) < 0) {
    fprintf(stderr, "Error sending frame to encoder\n");
    return false;
  }

  // Receive the encoded packet
  while (avcodec_receive_packet(codec_ctx, pkt) == 0) {
    pkt->stream_index = stream->index;
    av_packet_rescale_ts(pkt, codec_ctx->time_base, stream->time_base);
    pkt->pos = -1;

    if (av_interleaved_write_frame(fmt_ctx, pkt) < 0) {
      fprintf(stderr, "Error writing packet\n");
      return false;
    }
    av_packet_unref(pkt);
  }
  return true;
}

bool FFCodec::encodeTestVideo() {
  for (int i = 0; i < 300; i++) {
    fflush(stdout);

    // Make sure the frame data is writable
    if (av_frame_make_writable(frame) < 0) {
      fprintf(stderr, "Frame not writable\n");
      break;
    }

    // Fill the frame with arbitrary data (e.g., a color pattern)
    for (int y = 0; y < codec_ctx->height; y++) {
      for (int x = 0; x < codec_ctx->width; x++) {
        frame->data[0][y * frame->linesize[0] + x] = x + y + i * 3; // Y plane
      }
    }
    for (int y = 0; y < codec_ctx->height / 2; y++) {
      for (int x = 0; x < codec_ctx->width / 2; x++) {
        frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2; // U plane
        frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;  // V plane
      }
    }

    frame->pts = i;

    // Send the frame to the encoder
    if (avcodec_send_frame(codec_ctx, frame) < 0) {
      fprintf(stderr, "Error sending frame to encoder\n");
      return false;
    }

    // Receive the encoded packet
    while (avcodec_receive_packet(codec_ctx, pkt) == 0) {
      pkt->stream_index = stream->index;
      av_packet_rescale_ts(pkt, codec_ctx->time_base, stream->time_base);
      pkt->pos = -1;

      if (av_interleaved_write_frame(fmt_ctx, pkt) < 0) {
        fprintf(stderr, "Error writing packet\n");
        return false;
      }
      av_packet_unref(pkt);
    }
  }
  return true;
}

bool FFCodec::closeEncoder() {
  // Flush the encoder
  avcodec_send_frame(codec_ctx, nullptr);
  while (avcodec_receive_packet(codec_ctx, pkt) == 0) {
    pkt->stream_index = stream->index;
    av_packet_rescale_ts(pkt, codec_ctx->time_base, stream->time_base);
    pkt->pos = -1;

    if (av_interleaved_write_frame(fmt_ctx, pkt) < 0) {
      fprintf(stderr, "Error writing packet\n");
      return false;
    }
    av_packet_unref(pkt);
  }

  // Write the trailer
  av_write_trailer(fmt_ctx);

  // Clean up
  av_packet_free(&pkt);
  av_frame_free(&frame);
  avcodec_free_context(&codec_ctx);
  if (!(fmt_ctx->oformat->flags & AVFMT_NOFILE)) {
    avio_closep(&fmt_ctx->pb);
  }
  avformat_free_context(fmt_ctx);

  return true;
}

AVFrame *FFCodec::read_png_to_avframe(const char *filename) {
  // Open the image file
  AVFormatContext *fmt_ctx = nullptr;
  if (avformat_open_input(&fmt_ctx, filename, nullptr, nullptr) != 0) {
    fprintf(stderr, "Could not open input file '%s'\n", filename);
    return nullptr;
  }

  // Find stream
  if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
    fprintf(stderr, "Could not find stream information\n");
    avformat_close_input(&fmt_ctx);
    return nullptr;
  }

  // Find the decoder for the image stream
  const AVCodec *codec = nullptr;
  int stream_index =
      av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
  if (stream_index < 0) {
    fprintf(stderr, "Could not find a video stream in the input file\n");
    avformat_close_input(&fmt_ctx);
    return nullptr;
  }

  AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
  avcodec_parameters_to_context(codec_ctx,
                                fmt_ctx->streams[stream_index]->codecpar);
  if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
    fprintf(stderr, "Could not open codec\n");
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&fmt_ctx);
    return nullptr;
  }

  // Allocate a frame to hold the decoded image
  AVFrame *frameRGB = av_frame_alloc();
  if (!frameRGB) {
    fprintf(stderr, "Could not allocate frame\n");
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&fmt_ctx);
    return nullptr;
  }

  // Read and decode the image
  AVPacket *packet = av_packet_alloc();
  packet->data = nullptr;
  packet->size = 0;
  int response = 0;

  while (av_read_frame(fmt_ctx, packet) >= 0) {
    if (packet->stream_index == stream_index) {
      response = avcodec_send_packet(codec_ctx, packet);
      if (response < 0) {
        fprintf(stderr, "Error while sending packet to decoder!\n");
        av_packet_unref(packet);
        break;
      }

      response = avcodec_receive_frame(codec_ctx, frameRGB);
      if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
        av_packet_unref(packet);
        continue;
      } else if (response < 0) {
        fprintf(stderr, "Error while receiving frame from decoder!\n");
        av_packet_unref(packet);
        break;
      }

      // Successfully decoded the image, stop reading further
      av_packet_unref(packet);
      break;
    }
    av_packet_unref(packet);
  }

  // Allocate a frame to hold the yuv420p converted image
  AVFrame *frameYUV = av_frame_alloc();
  if (!frameYUV) {
    fprintf(stderr, "Could not allocate frame\n");
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&fmt_ctx);
    return nullptr;
  }
  frameYUV->width = frameRGB->width;
  frameYUV->height = frameRGB->height;
  frameYUV->format = AV_PIX_FMT_YUV420P;

  // convert rgb to YUV
  int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, codec_ctx->width,
                                          codec_ctx->height, 32);
  uint8_t *bufferYUV = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
  av_image_fill_arrays(frameYUV->data, frameYUV->linesize, bufferYUV,
                       AV_PIX_FMT_YUV420P, codec_ctx->width, codec_ctx->height,
                       32);

  SwsContext *sws_ctx_yuv =
      sws_getContext(codec_ctx->width, codec_ctx->height, AV_PIX_FMT_RGB24,
                     codec_ctx->width, codec_ctx->height, AV_PIX_FMT_YUV420P,
                     SWS_BILINEAR, nullptr, nullptr, nullptr);

  sws_scale(sws_ctx_yuv, frameRGB->data, frameRGB->linesize, 0,
            codec_ctx->height, frameYUV->data, frameYUV->linesize);

  // Cleanup
  av_packet_unref(packet);
  // av_frame_unref(frame);
  avcodec_free_context(&codec_ctx);
  avformat_close_input(&fmt_ctx);

  return frameYUV;
}
#endif