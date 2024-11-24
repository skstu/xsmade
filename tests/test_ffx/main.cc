#include <stl.hpp>
#include <system.h>
#include <ffx.h>
#include <fmt/format.h>

int main(int argc, char **argv) {
  xs_sys_startup();

  xs_ffx_screen_recording();

  xs_sys_shutdown();
  return 0;
}
#if 0
  xs_ffx_screen_recording();
#endif
#if 0     
  xs_image_stream_t *stream = nullptr;
  int rscreenshot = xs_sys_capturescreen(xs_position_t{0, 0, 100, 100},
                                         xs_image_stream_type_t::PNG, &stream);                          
  xs_sys_image_stream_destroy(&stream);
  int r265 =
      test_x265_encoder(R"(C:\Users\k34ub\Desktop\testMKV\SDRSample.mkv)",
                        R"(C:\Users\k34ub\Desktop\testMKV\SDRSampleH265.mp4)");
  int r264 =
      test_x264_encoder(R"(C:\Users\k34ub\Desktop\testMKV\SDRSample.mkv)",
                        R"(C:\Users\k34ub\Desktop\testMKV\SDRSampleH264.mp4)");
#endif
#if 0
 std::atomic_bool exit = false;
  std::atomic_uint64_t img_index = 0;
  stl::tfThreads threads;
  std::vector<std::string> imgs;
  threads.emplace_back([&]() {
    do {
      xs_image_stream_t *stream = nullptr;
      xs_sys_capturescreen(xs_position_t{0, 0, 1024, 768},
                           xs_image_stream_type_t::PNG, &stream);
      if (stream && stream->len > 0 && stream->buffer) {
        imgs.emplace_back(std::string(stream->buffer, stream->len));
      }
      xs_sys_image_stream_destroy(&stream);
      if (exit.load())
        break;
      std::this_thread::sleep_for(std::chrono::milliseconds(15));
    } while (1);
  });

#if 0

        img_index++;
        stl::File::WriteFile(
            fmt::format(R"(C:\Users\k34ub\Desktop\capturescreen_s\{}.jpg)",
                        img_index.load()),
            std::string(stream->buffer, stream->len));

#endif

  std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000));
  exit.store(true);
  for (auto &t : threads)
    t.join();

  size_t total_img = imgs.size();
  threads.clear();
#endif