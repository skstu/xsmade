#if !defined(__547E3EEF_E3DB_4D78_8DC1_86C7D47053D2__)
#define __547E3EEF_E3DB_4D78_8DC1_86C7D47053D2__
namespace chromium {
enum class ErrorCode : int {
  NotFound = -1,
  BadRequest = -2,
  Unauthorized = -3,
  Forbidden = -4,
  InternalServerError = -5,
  ServiceUnavailable = -6,
  InterfaceNotSupported = -7,
  InvalidBrowserID = -8,
  CreateBrowserEnvFailed = -9,
  BrwProcessOpenFailed = -10,
  InvalidConfigureData = -11,
  RequestParseError = -12,
  ServiceBusy = -13,
  ServiceNotReady = -14,
  UnknownError = -9999,
  Success = 0,
  Done = 1,
  AlreadyRunning = 2,
};

inline const char *ErrorCodeToString(ErrorCode code) {
  switch (code) {
  case ErrorCode::Success:
    return "Success";
  case ErrorCode::Done:
    return "Done";
  case ErrorCode::AlreadyRunning:
    return "Already running";
  case ErrorCode::BrwProcessOpenFailed:
    return "BrwProcessOpenFailed";
  case ErrorCode::InvalidBrowserID:
    return "Invalid browser id";
  case ErrorCode::InterfaceNotSupported:
    return "Interface not supported";
  case ErrorCode::NotFound:
    return "Not Found";
  case ErrorCode::CreateBrowserEnvFailed:
    return "Create browser env failed.";
  case ErrorCode::BadRequest:
    return "Bad Request";
  case ErrorCode::Unauthorized:
    return "Unauthorized";
  case ErrorCode::Forbidden:
    return "Forbidden";
  case ErrorCode::InternalServerError:
    return "Internal Server Error";
  case ErrorCode::ServiceUnavailable:
    return "Service Unavailable";
  default:
    return "Unknown Error";
  }
}
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 31 May 2025 04:50:09 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__547E3EEF_E3DB_4D78_8DC1_86C7D47053D2__