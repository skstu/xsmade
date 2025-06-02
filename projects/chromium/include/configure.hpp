#if !defined(__8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__)
#define __8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__
namespace chromium {
typedef unsigned short policy_id_t;
typedef policy_id_t browser_id_t;
typedef unsigned long long request_id_t;
constexpr char16_t project_dirname_chromium[] = u"Chromium";
constexpr char16_t project_dirname_default_user_data[] = u"chromium";
constexpr char16_t project_dirname_components[] = u"components";
constexpr char16_t project_dirname_extensions[] = u"extensions";
constexpr char16_t project_dirname_route[] = u"route";
constexpr char16_t project_dirname_tmp[] = u"tmp";
constexpr char16_t project_dirname_cache[] = u"cache";
constexpr char16_t project_dirname_configures[] = u"configures";
constexpr char16_t project_filename_configure[] = u"configure.json";
constexpr char16_t project_filename_tmpcfgpath[] = u"cfgpath.cfg";
class IConfigure final {
public:
  enum class Type : unsigned int {
    BrwCreate = 0x0,
    BrwDestory = 0x1,
    BrwInputEvent = 0x2,
    BrwCommandEvent = 0x3,
    BrwRequest = 0xA,
    BrwResponse = BrwRequest,
  };
  typedef class Request final {
  public:
    inline Request();
    inline ~Request();
    inline Request(const Request &obj);
    inline void operator<<(const rapidjson::Value &v);
    inline void operator=(const Request &obj);

  public:
    //!@ browser id | browser process id
    request_id_t id = 0;
    unsigned long command = 0;
    bool enable = false;
  } Response;
  class Server final {
  public:
    inline Server();
    inline ~Server();
    inline void operator=(const Server &obj) {
      pipe = obj.pipe;
      tcp = obj.tcp;
      udp = obj.udp;
      enable = obj.enable;
    }
    inline void operator<<(const rapidjson::Value &);

  public:
    bool enable = false;
    std::string pipe;
    std::string tcp;
    std::string udp;
  };
  class Command final {
  public:
    enum class Type : unsigned int {
      Unknown = 0,
      Home = 1,
      GoForward = 2,
      GoBack = 3,
      Reload = 4,
      Stop = 5,
      CloseWindow = 6,
      NewTabToRight = 7,
      CloseTab = 8,
      RestoreTab = 9,
      CopyURL = 10,
      OpenURL = 11,
    };
    enum class OpenURLDispositionType : unsigned int {
      UNKNOWN,
      CURRENT_TAB,
      // Indicates that only one tab with the url should exist in the same
      // window.
      SINGLETON_TAB,
      NEW_FOREGROUND_TAB,
      NEW_BACKGROUND_TAB,
      NEW_POPUP,
      NEW_WINDOW,
      SAVE_TO_DISK,
      OFF_THE_RECORD,
      IGNORE_ACTION,
      // Activates an existing tab containing the url, rather than navigating.
      // This is similar to SINGLETON_TAB, but searches across all windows from
      // the current profile and anonymity (instead of just the current one);
      // closes the current tab on switching if the current tab was the NTP with
      // no session history; and behaves like CURRENT_TAB instead of
      // NEW_FOREGROUND_TAB when no existing tab is found.
      SWITCH_TO_TAB,
      // Creates a new document picture-in-picture window showing a child
      // WebView.
      NEW_PICTURE_IN_PICTURE,
      // Update when adding a new disposition.
      MAX_VALUE = NEW_PICTURE_IN_PICTURE,
    };

  public:
    inline Command();
    inline ~Command();
    inline void operator<<(const rapidjson::Value &v) {
      do {
        if (!v.IsObject())
          break;
        if (v.HasMember("enable") && v["enable"].IsBool()) {
          enable = v["enable"].GetBool();
        }
        if (v.HasMember("type") && v["type"].IsInt()) {
          type = (Command::Type)v["type"].GetInt();
        }
        if (v.HasMember("url") && v["url"].IsString()) {
          url = v["url"].GetString();
        }
        if (v.HasMember("open_url_disposition_type") &&
            v["open_url_disposition_type"].IsUint()) {
          open_url_disposition_type =
              (Command::OpenURLDispositionType)v["open_url_disposition_type"]
                  .GetUint();
        }
      } while (0);
    }
    inline void operator=(const Command &cd) {
      enable = cd.enable;
      type = cd.type;
      url = cd.url;
      open_url_disposition_type = cd.open_url_disposition_type;
    }

  public:
    bool enable = false;
    Command::Type type = Command::Type::Unknown;
    std::string url;
    OpenURLDispositionType open_url_disposition_type =
        OpenURLDispositionType::UNKNOWN;
  };
  class Input final {
  public:
    enum class ResultCode : int {
      CfgInvalid = -12,
      KeyCodeUnknown = -11,
      UrlInvalid = -10,
      UnsupportedType = -9,
      RenderWidgetHostInvalid = -8,
      RenderFrameHostNotActivated = -7,
      RenderFrameHostInvalid = -6,
      WebContentsInvalid = -5,
      TabStripModelInvalid = -4,
      InvalidType = -3,
      CfgNotEnabled = -2,
      Unknown = -1,
      Success = 0,
    };
    // @generated_from: blink.mojom.EventType
    enum class Type : int {
      kUndefined = -1,
      kTypeFirst = -1,
      kMouseDown = 0,
      kMouseTypeFirst = 0,
      kMouseUp = 1,
      kMouseMove = 2,
      kMouseEnter = 3,
      kMouseLeave = 4,
      kContextMenu = 5,
      kMouseTypeLast = 5,
      kMouseWheel = 6,
      kRawKeyDown = 7,
      kKeyboardTypeFirst = 7,
      kKeyDown = 8,
      kKeyUp = 9,
      kChar = 10,
      kKeyboardTypeLast = 10,
      kGestureScrollBegin = 11,
      kGestureTypeFirst = 11,
      kGestureScrollEnd = 12,
      kGestureScrollUpdate = 13,
      kGestureFlingStart = 14,
      kGestureFlingCancel = 15,
      kGesturePinchBegin = 16,
      kGesturePinchTypeFirst = 16,
      kGesturePinchEnd = 17,
      kGesturePinchUpdate = 18,
      kGesturePinchTypeLast = 18,
      kGestureBegin = 19,
      kGestureTapDown = 20,
      kGestureShowPress = 21,
      kGestureTap = 22,
      kGestureTapCancel = 23,
      kGestureShortPress = 24,
      kGestureLongPress = 25,
      kGestureLongTap = 26,
      kGestureTwoFingerTap = 27,
      kGestureTapUnconfirmed = 28,
      kGestureDoubleTap = 29,
      kGestureEnd = 30,
      kGestureTypeLast = 30,
      kTouchStart = 31,
      kTouchTypeFirst = 31,
      kTouchMove = 32,
      kTouchEnd = 33,
      kTouchCancel = 34,
      kTouchScrollStarted = 35,
      kTouchTypeLast = 35,
      kPointerDown = 36,
      kPointerTypeFirst = 36,
      kPointerUp = 37,
      kPointerMove = 38,
      kPointerRawUpdate = 39,
      kPointerCancel = 40,
      kPointerCausedUaAction = 41,
      kPointerTypeLast = 41,
      kTypeLast = 41,
      kMinValue = -1,
      kMaxValue = 41,
    };
    // The modifier constants cannot change their values since pepper
    // does a 1-1 mapping of its values; see
    // content/renderer/pepper/event_conversion.cc
    //
    // A Java counterpart will be generated for this enum.
    // GENERATED_JAVA_ENUM_PACKAGE: org.chromium.blink_public.web
    // GENERATED_JAVA_CLASS_NAME_OVERRIDE: WebInputEventModifier
    enum class Modifiers : int {
      // modifiers for all events:
      kShiftKey = 1 << 0,
      kControlKey = 1 << 1,
      kAltKey = 1 << 2,
      kMetaKey = 1 << 3,

      // modifiers for keyboard events:
      kIsKeyPad = 1 << 4,
      kIsAutoRepeat = 1 << 5,

      // modifiers for mouse events:
      kLeftButtonDown = 1 << 6,
      kMiddleButtonDown = 1 << 7,
      kRightButtonDown = 1 << 8,

      // Toggle modifers for all events.
      kCapsLockOn = 1 << 9,
      kNumLockOn = 1 << 10,

      kIsLeft = 1 << 11,
      kIsRight = 1 << 12,

      // Indicates that an event was generated on the touch screen while
      // touch accessibility is enabled, so the event should be handled
      // by accessibility code first before normal input event processing.
      kIsTouchAccessibility = 1 << 13,

      kIsComposing = 1 << 14,

      kAltGrKey = 1 << 15,
      kFnKey = 1 << 16,
      kSymbolKey = 1 << 17,

      kScrollLockOn = 1 << 18,

      // Whether this is a compatibility event generated due to a
      // native touch event. Mouse events generated from touch
      // events will set this.
      kIsCompatibilityEventForTouch = 1 << 19,

      kBackButtonDown = 1 << 20,
      kForwardButtonDown = 1 << 21,

      // Represents movement as a result of content changing under the cursor,
      // not actual physical movement of the pointer
      kRelativeMotionEvent = 1 << 22,

      // Indication this event was injected by the devtools.
      // TODO(dtapuska): Remove this flag once we are able to bind callbacks
      // in event sending.
      kFromDebugger = 1 << 23,

      // Indicates this event is targeting an OOPIF, and the iframe or one of
      // its
      // ancestor frames moved within its embedding page's viewport recently.
      kTargetFrameMovedRecently = 1 << 24,

      // TODO(szager): This is the same as kTargetFrameMovedRecently, but it
      // overrides that value for iframes that are using IntersectionObserver V2
      // features (i.e. occlusion detection). The purpose of this distinction is
      // to preserve existing behavior for IOv2-using iframes while dialing in
      // the
      // feature parameters for kDiscardInputEventsToRecentlyMovedFrames, which
      // is
      // broader in scope. At the end of that process, this flag should be
      // removed
      // in favor of kTargetFrameMovedRecently.
      kTargetFrameMovedRecentlyForIOv2 = 1 << 25,

      // When an event is forwarded to the main thread, this modifier will tell
      // if
      // the event was already handled by the compositor thread or not. Based on
      // this, the decision of whether or not the main thread should handle this
      // event for the scrollbar can then be made.
      kScrollbarManipulationHandledOnCompositorThread = 1 << 26,

      // The set of non-stateful modifiers that specifically change the
      // interpretation of the key being pressed. For example; IsLeft,
      // IsRight, IsComposing don't change the meaning of the key
      // being pressed. NumLockOn, ScrollLockOn, CapsLockOn are stateful
      // and don't indicate explicit depressed state.
      kKeyModifiers = kSymbolKey | kFnKey | kAltGrKey | kMetaKey | kAltKey |
                      kControlKey | kShiftKey,

      kNoModifiers = 0,
    };

    // @generated_from: blink.mojom.Button
    enum class Button : int {
      kNoButton = -1,
      kLeft = 0,
      kMiddle = 1,
      kRight = 2,
      kBarrel = 2,
      kBack = 3,
      kForward = 4,
      kEraser = 5,
      kMinValue = -1,
      kMaxValue = 5,
    };

    enum class Buttons : unsigned int {
      kNoButton = 0,
      kLeft = 1 << 0,
      kRight = 1 << 1,
      kMiddle = 1 << 2,
      kBack = 1 << 3,
      kForward = 1 << 4,
      kEraser = 1 << 5
    };

    // The rail mode for a wheel event specifies the axis on which scrolling is
    // expected to stick. If this axis is set to Free, then scrolling is not
    // stuck to any axis.
    enum class RailsMode : int {
      kRailsModeFree = 0,
      kRailsModeHorizontal = 1,
      kRailsModeVertical = 2,
    };

    // @generated_from: blink.mojom.DispatchType
    enum class DispatchType : int {
      kBlocking = 0,
      kEventNonBlocking = 1,
      kListenersNonBlockingPassive = 2,
      // @generated_from:
      // blink.mojom.DispatchType.kListenersForcedNonBlockingDueToFling
      kListenersForcedNonBlockingDueToFling = 3,
      kMinValue = 0,
      kMaxValue = 3,
    };
    enum class EventDeviceId : int {
      // Device ID for Touch, Mouse and Key Events.
      ED_UNKNOWN_DEVICE = -1,
      // Device ID for events injected through a remote connection (like CRD).
      ED_REMOTE_INPUT_DEVICE = -2,
    };

    // Pointing device type.
    enum class PointerType : int {
      kUnknown,
      kMouse,
      kPen,
      kTouch,
      kEraser,
      kMaxValue = kEraser,
    };

    // @generated_from: blink.mojom.GestureDevice
    enum class GestureDevice : int {
      kUninitialized = 0,
      kTouchpad = 1,
      kTouchscreen = 2,
      kSyntheticAutoscroll = 3,
      kScrollbar = 4,
      kMinValue = 0,
      kMaxValue = 4,
    };

    enum class ScrollGranularity : unsigned char {
      kScrollByPrecisePixel = 0,
      kFirstScrollGranularity = kScrollByPrecisePixel,
      kScrollByPixel,
      kScrollByLine,
      kScrollByPage,
      kScrollByDocument,
      kMaxValue = kScrollByDocument
    };

    enum class MouseWheelEventPhase : int {
      // No phase information is avaiable.
      kPhaseNone = 0,
      // This wheel event is the beginning of a scrolling sequence.
      kPhaseBegan = 1 << 0,
      // Shows that scrolling is ongoing but the scroll delta for this wheel
      // event
      // is zero.
      kPhaseStationary = 1 << 1,
      // Shows that a scroll is ongoing and the scroll delta for this wheel
      // event
      // is non-zero.
      kPhaseChanged = 1 << 2,
      // This wheel event is the last event of a scrolling sequence.
      kPhaseEnded = 1 << 3,
      // A wheel event with phase cancelled shows that the scrolling sequence is
      // cancelled.
      kPhaseCancelled = 1 << 4,
      // A wheel event with phase may begin shows that a scrolling sequence may
      // start.
      kPhaseMayBegin = 1 << 5,
      // A wheel event with momentum phase blocked shows that a scrolling
      // sequence
      // will not be followed by a momentum fling. This should only ever be set
      // on
      // the momentum phase of an event.
      kPhaseBlocked = 1 << 6,
    };

    // A hint at the outcome of a wheel event should it not get canceled.
    enum class MouseWheelEventAction : int {
      // When the wheel event would result in page zoom,
      kPageZoom = 0,
      // When the wheel event would scroll but the direction is not (known to
      // be)
      // fixed to a certain axis,
      kScroll,
      // When the wheel event would scroll along X axis,
      kScrollHorizontal,
      // When the wheel event would scroll along Y axis,
      kScrollVertical
    };

  public:
    inline Input();
    inline ~Input();
    inline void operator=(const Input &);
    inline void operator<<(const rapidjson::Value &);
    // Returns true if the WebInputEvent |type| is a mouse event.
    inline bool IsMouseEventType() const;
    inline bool IsMouseWheelEventType() const;
    // Returns true if the WebInputEvent |type| is a keyboard event.
    inline bool IsKeyboardEventType() const;
    // Returns true if the WebInputEvent |type| is a touch event.
    inline bool IsTouchEventType() const;
    // Returns true if the WebInputEvent is a gesture event.
    inline bool IsGestureEventType() const;
    // Returns true if the WebInputEvent |type| is a pointer event.
    inline bool IsPointerEventType() const;
    // Returns true if the WebInputEvent |type| will potentially be considered
    // part of a "web interaction" for responsiveness metrics, e.g.
    // Interaction-to-Next-Paint (INP). This, for example, includes clicks and
    // key presses, but excludes continuous input like scrolling.
    //
    // This list includes `WebInputEvent::Type`s that can result in dispatching
    // relevant events [1] considered by blink::ResponsivenessMetrics (see
    // IsEventTypeForInteractionId() in window_performance.cc). For example the
    // handling of kPointerUp, kMouseUp, and kTouchEnd `WebInputEvent::Type` raw
    // events can all lead to dispatching a "pointerup" event, which is used in
    // computing responsiveness metrics.
    //
    // [1] Note this excludes some events that are used for responsiveness
    // metrics state tracking, e.g. "pointercancel".
    inline bool IsWebInteractionEvent() const;

    inline bool IsGestureScroll() const;

    // Returns true if the WebInputEvent |type| is a pinch gesture event.
    inline bool IsPinchGestureEventType() const;

    // Returns true if the WebInputEvent |type| is a fling gesture event.
    inline bool IsFlingGestureEventType() const;

  public:
    bool enable = false;
    Input::Type type = Input::Type::kUndefined;
    Input::ScrollGranularity delta_units =
        Input::ScrollGranularity::kScrollByPixel;
    Input::GestureDevice source_device = Input::GestureDevice::kUninitialized;
    Input::PointerType pointer_type = Input::PointerType::kUnknown;
    // - For pointerup/down events, the button of pointing device that triggered
    // the event.
    // - For other events, the button that was depressed during the move event.
    // If multiple buttons were depressed, one of the depressed buttons
    // (platform dependent).
    Input::Button button = Input::Button::kNoButton;
    unsigned int dom_key;
    // A pointer id of each touch pointer. Every time when a pointer is
    // pressed the screen, it will be assigned to a new pointer id.
    unsigned int pointer_id = 0;
    Input::Modifiers modifiers = Input::Modifiers::kNoModifiers;
    int pointer_count = 1;
    int index = 0;
    // Tilt of a pen stylus from surface normal as plane angles in degrees,
    // Values lie in [-90,90]. A positive tiltX is to the right and a positive
    // tiltY is towards the user.
    int tilt_x = 0;
    int tilt_y = 0;
    float global_x = 0.0f;
    float global_y = 0.0f;
    float dx = 0.0f;
    float dy = 0.0f;
    float dx_hint = 0.0f;
    float dy_hint = 0.0f;
    float scale = 1.0f;
    float anchor_x = 0.0f;
    float anchor_y = 0.0f;
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    // Adds an additional point to the touch list, returning the point's
    float x = 0.0f;
    float y = 0.0f;
    float radius_x = 0.0f;
    float radius_y = 0.0f;
    float rotation_angle = 0.0f;
    // The valid range is [0,1], with NaN meaning pressure is not supported by
    // the input device.
    float force = 0.0f;
    // The normalized tangential pressure (or barrel pressure), typically set by
    // an additional control of the stylus, which has a range of [-1,1], where 0
    // is the neutral position of the control. Always 0 if the device does not
    // support it.
    float tangential_pressure = 0.0f;

    float delta_x = 0.0f;
    float delta_y = 0.0f;
    float wheel_ticks_x = 0.0f;
    float wheel_ticks_y = 0.0f;

    float acceleration_ratio_x = 1.0f;
    float acceleration_ratio_y = 1.0f;

    Input::MouseWheelEventPhase phase = Input::MouseWheelEventPhase::kPhaseNone;
    Input::MouseWheelEventPhase momentum_phase =
        Input::MouseWheelEventPhase::kPhaseNone;

    Input::RailsMode rails_mode = Input::RailsMode::kRailsModeFree;

    // Whether the event is blocking, non-blocking, all event
    // listeners were passive or was forced to be non-blocking.
    DispatchType dispatch_type = DispatchType::kBlocking;

    // The expected result of this wheel event (if not canceled).
    Input::MouseWheelEventAction event_action =
        Input::MouseWheelEventAction::kPageZoom;

    // True when phase information is added in mouse_wheel_phase_handler based
    // on its timer.
    bool has_synthetic_phase = false;

    // True if this event should be ignored (e.g. in the browser) if it's not
    // handled by the renderer. This happens for RawKeyDown events that are
    // created while IME is active and is necessary to prevent backspace from
    // doing "history back" if it is hit in ime mode. Currently, it's only used
    // by Linux and Mac ports.
    bool skip_if_unhandled = false;

    // This identifies whether this event was tagged by the system as being a
    // "system key" event (see
    // https://docs.microsoft.com/en-us/windows/desktop/inputdev/wm-syskeydown
    // for details). Other platforms don't have this concept, but it's just
    // easier to leave it always false than ifdef.
    bool is_system_key = false;

    // Whether the event forms part of a browser-handled keyboard shortcut.
    // This can be used to conditionally suppress Char events after a
    // shortcut-triggering RawKeyDown goes unhandled.
    bool is_browser_shortcut = false;

    // The clockwise rotation of a pen stylus around its own major axis, in
    // degrees in the range [0,359]. Always 0 if the device does not support it.
    int twist = 0;

    unsigned int click_count = 1;

    int movement_x = 0;
    int movement_y = 0;

    // True if this event has raw movement value from OS.
    // TODO(crbug.com/982379): Figure out how to avoid using this boolean.
    bool is_raw_movement_event = false;

    // Contains unique device id for pen on supported devices.
    int device_id = -1;

    // |text| is the text generated by this keystroke.  |unmodified_text| is
    // |text|, but unmodified by an concurrently-held modifiers (except
    // shift).  This is useful for working out shortcut keys.  Linux and
    // Windows guarantee one character per event.  The Mac does not, but in
    // reality that's all it ever gives.  We're generous, and cap it a bit
    // longer.
    // const size_t kTextLengthCap = 4;
    std::vector<char16_t /*size=4!*/> text = {};
    std::vector<char16_t /*size=4!*/> unmodified_text = {};
  };
  class Policy final {
  public:
    inline Policy();
    inline ~Policy();

  public:
    policy_id_t id = 0;
  };
  class HomePage final {
  public:
    inline HomePage();
    inline ~HomePage();

  public:
    bool enable = false;
    std::string url;
    bool open_new_tab = false;
  };
  class Frame final {
  public:
    class Resolution final {
    public:
      inline Resolution();
      inline ~Resolution();
      inline void operator=(const Resolution &);

    public:
      unsigned int width = 0;
      unsigned int height = 0;
    };

  public:
    inline Frame();
    inline ~Frame();

  public:
    bool enable = false;
    Resolution resolution;
  };
  class Proxy final {
  public:
    enum class SocksType : unsigned char {
      Default = 0,
      SocksH = 1,
      SocksA = 2,
    };
    enum class Type : unsigned long {
      HTTP = 0,
      HTTPS = 1,
      SOCKS4 = 2,
      SOCKS5 = 3,
    };

  public:
    inline Proxy();
    inline ~Proxy();

  public:
    bool enable = false;
    Type type = Type::HTTP;
    SocksType socks_type = SocksType::Default;
    std::string host;
    unsigned short port = 80;
    std::string username;
    std::string password;
    std::string address;
    std::string credentials_url;
  };
  class Fps final {
  public:
    class Hash final {
    public:
      inline Hash();
      inline ~Hash();

    public:
      bool enable = false;
      bool random = false;
      double base = 0.0;
      double from = 0.0;
      double to = 0.0;

    public:
      inline void operator<<(const std::string &);
    };
    class ThridParty final {
    public:
      class ScreenSize final {
      public:
        inline ScreenSize();
        inline ~ScreenSize();
        inline void operator=(const ScreenSize &obj) {
          width = obj.width;
          height = obj.height;
        }

      public:
        unsigned int width = 1920;
        unsigned int height = 1080;
      };
      class Tls final {
      public:
        inline Tls();
        inline ~Tls();
        inline void operator=(const Tls &obj) {
          enabled = obj.enabled;
          seed = obj.seed;
        }

      public:
        bool enabled = true;
        unsigned long long seed = 1130449385;
      };
      class Webrtc final {
      public:
        inline Webrtc();
        inline ~Webrtc();
        inline void operator=(const Webrtc &obj) {
          enabled = obj.enabled;
          localIP = obj.localIP;
          publicIP = obj.publicIP;
        }

      public:
        bool enabled = true;
        std::string localIP;
        std::string publicIP;
      };

      class Storage final {
      public:
        inline Storage();
        inline ~Storage();
        inline void operator=(const Storage &obj) {
          quota = obj.quota;
          usage = obj.usage;
          enabled = obj.enabled;
        }

      public:
        unsigned long long quota = 77310667161;
        int usage = 0;
        bool enabled = true;
      };

      class FontsFull final { //!@ "fontsFull": [],
      public:
        inline FontsFull();
        inline ~FontsFull();
        inline void operator=(const FontsFull &obj) {
        }

      public:
      };

      class AudioNoise final {
      public:
        inline AudioNoise();
        inline ~AudioNoise();
        inline void operator=(const AudioNoise &obj) {
          enabled = obj.enabled;
          sumStep = obj.sumStep;
          freqStep = obj.freqStep;
          sumNoise = obj.sumNoise;
          freqNoise = obj.freqNoise;
          gainNoise = obj.gainNoise;
          timeDomainNoise = obj.timeDomainNoise;
        }

      public:
        bool enabled = true;
        int sumStep = 3;
        int freqStep = 3;
        double sumNoise = 0.00000006500532991952443;
        double freqNoise = 0.000004;
        double gainNoise = 0.0000049999999999999996;
        double timeDomainNoise = 0.000002;
      };
      class Canvas final {
      public:
        inline Canvas();
        inline ~Canvas();
        inline void operator=(const Canvas &obj) {
          enabled = obj.enabled;
          alpha = obj.alpha;
          widthRandPercent = obj.widthRandPercent;
          heightRandPercent = obj.heightRandPercent;
          colorDisturbedValue = obj.colorDisturbedValue;
        }

      public:
        bool enabled = true;
        int alpha = 2;
        float widthRandPercent = 0.1;
        float heightRandPercent = 0.4;
        int colorDisturbedValue = 2;
      };
      class ClientHints final {
      public:
        inline ClientHints();
        inline ~ClientHints();
        inline void operator=(const ClientHints &obj) {
          bit = obj.bit;
          arch = obj.arch;
          wow64 = obj.wow64;
          isMobile = obj.isMobile;
          platform = obj.platform;
          fullVersion = obj.fullVersion;
          platformVersion = obj.platformVersion;
          model = obj.model;
        }

      public:
        std::string bit;
        std::string arch;
        std::string model;
        bool wow64 = false;
        bool isMobile = false;
        std::string platform;
        std::string fullVersion;
        //"brandVersions": [],
        std::string platformVersion;
      };

      class ClientRects final {
      public:
        inline ClientRects();
        inline ~ClientRects();
        inline void operator=(const ClientRects &obj) {
          enabled = obj.enabled;
          scale = obj.scale;
        }

      public:
        double scale = 1.0015135571877196;
        bool enabled = true;
      };

      class Geolocation final {
      public:
        inline Geolocation();
        inline ~Geolocation();
        inline void operator=(const Geolocation &obj) {
          enabled = obj.enabled;
          latitude = obj.latitude;
          longitude = obj.longitude;
          accuracy = obj.accuracy;
        }

      public:
        bool enabled = true;
        double latitude = 31.2304;
        double longitude = 121.4737;
        double accuracy = 1000.0;
      };
      class MediaDevice final {
      public:
        class AudioOutputs final {
        public:
          inline AudioOutputs();
          inline ~AudioOutputs();
          inline void operator=(const AudioOutputs &obj) {
            label = obj.label;
            groupId = obj.groupId;
            deviceId = obj.deviceId;
          }

        public:
          std::string label;
          std::string groupId = "5b0ebeb5d54c97754ae6d4e4a55d212508f8a0bd3060a6"
                                "641c00b3e8e79c1cae";
          std::string deviceId;
        };

      public:
        inline MediaDevice();
        inline ~MediaDevice();
        inline void operator=(const MediaDevice &obj) {
          enabled = obj.enabled;
          audio = obj.audio;
          audioOutputs = obj.audioOutputs;
        }

      public:
        bool enabled = true;
        bool audio = true;
        /*
"audioInputs": [],
"videoInputs": [],
*/
        std::vector<AudioOutputs> audioOutputs;
      };
      class SpeechVoice final {
      public:
        class Voices final {
        public:
          inline Voices();
          inline ~Voices();
          inline Voices(const Voices &obj);
          inline void operator=(const Voices &obj);

        public:
          std::string lang;
          std::string name;
          bool default_ = true;
          std::string voiceURI;
          std::string localService;
        };

      public:
        inline SpeechVoice();
        inline ~SpeechVoice();
        inline void operator=(const SpeechVoice &obj) {
          enabled = obj.enabled;
          voices = obj.voices;
        }

      public:
        std::vector<Voices> voices;
        bool enabled = true;
      };

      class WebglCustomConfig final {
      public:
        inline WebglCustomConfig();
        inline ~WebglCustomConfig();
        inline void operator=(const WebglCustomConfig &obj) {
          webglCustomEnabled = obj.webglCustomEnabled;
          webglVendor = obj.webglVendor;
          webglRenderer = obj.webglRenderer;
        }

      public:
        bool webglCustomEnabled = true;
        std::string webglVendor = "Google Inc.";
        std::string webglRenderer =
            "ANGLE (Intel(R) UHD Graphics 730 Direct3D11 vs_5_0 ps_5_0)";
      };
      class PermissionSimulation final {
      public:
        inline PermissionSimulation();
        inline ~PermissionSimulation();
        inline void operator=(const PermissionSimulation &obj) {
          maxDelay = obj.maxDelay;
          minDelay = obj.minDelay;
          oddsGrant = obj.oddsGrant;
          oddsCancel = obj.oddsCancel;
          oddsRefuse = obj.oddsRefuse;
        }

      public:
        int maxDelay = 4;
        float minDelay = 2.5;
        int oddsGrant = 90;
        int oddsCancel = 5;
        int oddsRefuse = 5;
      };

    public:
      inline ThridParty();
      inline ~ThridParty();
      inline void operator=(const ThridParty &);
      inline bool operator<<(const rapidjson::Value &);

    public:
      ThridParty::PermissionSimulation permissionSimulation;
      ThridParty::WebglCustomConfig webglCustomConfig;
      ThridParty::SpeechVoice speechVoice;
      ThridParty::MediaDevice mediaDevice;
      ThridParty::Geolocation geolocation;
      ThridParty::ClientRects clientRects;
      ThridParty::ClientHints clientHints;
      ThridParty::Canvas canvas;
      ThridParty::AudioNoise audioNoise;
      std::set<std::string> languages;
      ThridParty::Tls tls;
      ThridParty::Webrtc webrtc;
      ThridParty::ScreenSize screenSize;
      ThridParty::FontsFull fontsFull;
      ThridParty::Storage storage;
      std::string id;
      unsigned int cpu = 2;
      std::string dnt = "0";
      int colorDepth = 24;
      std::string appCodeName = "Mozilla";
      std::string userDataDir = "";
      int windowWidth = 1920;
      int windowHeight = 937;
      int batteryLevel = 1;
      unsigned int deviceMemory = 8;
      std::string acceptLanguage = "zh-CN,zh;q=0.9";
      bool batteryCharging = true;
      float devicePixelRatio = 1;
      bool fontsFullEnabled = false;
      int batteryChargingTime = 0;
      int windowTitleBarHeight = 103;
      int batteryDischargingTime = -1;
      std::string appName = "Netscape";
      std::string fontDir = "";
      std::string product = "Gecko";
      std::string platform = "Win32";
      std::string timezone = "Asia/Shanghai";
      std::string userAgent = "Mozilla/5.0 (Windows NT 10.0; WOW64) "
                              "AppleWebKit/537.36 (KHTML, like "
                              "Gecko) Chrome/86.0.4240.198 Safari/537.36";
      std::string appVersion = "5.0 (Windows NT 10.0; WOW64) "
                               "AppleWebKit/537.36 (KHTML, like "
                               "Gecko) Chrome/86.0.4240.198 Safari/537.36";
      std::string socks5 = "";
      std::string vendor = "Google Inc.";
    };
    class Navigator final {
    public:
      class Plugins final {
      public:
        class Plugin final {
        public:
          class MimeType final {
          public:
            inline MimeType();
            inline ~MimeType();
            inline bool operator<(const MimeType &) const;
            inline bool operator==(const MimeType &) const;
            inline void operator=(const MimeType &);

          public:
            std::string key; //!@ type
            std::string type;
            std::string suffixes;
          };

        public:
          inline Plugin();
          inline ~Plugin();
          inline bool operator<(const Plugin &) const;
          inline bool operator==(const Plugin &) const;
          inline void operator=(const Plugin &);
          inline Plugin(const Plugin &);

        public:
          bool enable = false;
          std::string key; //!@ name
          std::string name;
          std::string description;
          std::set<MimeType> mimeTypes;
        };

      public:
        inline Plugins();
        inline ~Plugins();
        std::set<Plugin> plugins;
        bool enable = false;
        bool pdfViewerEnabled = true;
        bool javaEnabled = false;
      };

    public:
      inline Navigator();
      inline ~Navigator();
      inline void operator<<(const rapidjson::Value &);

    public:
      Plugins plugins;
    };
    class Timezone final {
    public:
      class Source final {
      public:
        inline Source(const unsigned int &, const std::string &);
        inline ~Source();

      public:
        const unsigned int id;
        const std::string name;
        short offset = 0;
        std::string description;
      };

    public:
      inline Timezone();
      inline ~Timezone();

    public:
      bool enable = false;
      Hash hash;
      std::map<unsigned int, Source> sources;
    };
    class Canvas final {
    public:
      inline Canvas();
      inline ~Canvas();

    public:
      bool enable = false;
      Hash hash;
    };
    class WebRTC final {
    public:
      enum class ProtectionType : unsigned int {
        Default = 0,
        WebRTCIPHandlingProtected = 1,
        CustomIPAddrProtected = 2,
      };

      enum class WebRTCIPHandlingProtectedType : unsigned int {
        kWebRTCIPHandlingDefault = 0,
        kWebRTCIPHandlingDefaultPublicAndPrivateInterfaces = 1,
        kWebRTCIPHandlingDefaultPublicInterfaceOnly = 2,
        kWebRTCIPHandlingDisableNonProxiedUdp = 3,
      };

    public:
      inline WebRTC();
      inline ~WebRTC();
      inline void operator=(const WebRTC &);
      inline void operator<<(const rapidjson::Value &);

    public:
      bool enable = false;
      ProtectionType protection_type = ProtectionType::Default;
      std::string ip = "203.0.113.1";
      unsigned short port = 8888;
      WebRTCIPHandlingProtectedType webrtc_ip_handling_protected_type =
          WebRTCIPHandlingProtectedType::kWebRTCIPHandlingDefault;
    };
    class Webgl final {
    public:
      class ContextAttributes final {
      public:
        inline ContextAttributes();
        inline ~ContextAttributes();
        inline void operator=(const ContextAttributes &);

      public:
        bool alpha = true;
        bool antialias = true;
        bool depth = true;
        bool desynchronized = false;
        bool failIfMajorPerformanceCaveat = false;
        bool powerPreference = false;
        bool premultipliedAlpha = true;
        bool preserveDrawingBuffer = false;
        bool stencil = false;
        bool xrCompatible = false;
      };
      class ShaderPrecisionFormat final {
      public:
        enum class SharedType : unsigned int {
          Unknown = 0,
          FRAGMENT_SHADER = 0x8B30,
          VERTEX_SHADER = 0x8B31,
        };
        enum class FormatType : unsigned int {
          Unknown = 0,
          LOW_FLOAT = 0x8DF0,
          MEDIUM_FLOAT = 0x8DF1,
          HIGH_FLOAT = 0x8DF2,
          LOW_INT = 0x8DF3,
          MEDIUM_INT = 0x8DF4,
          HIGH_INT = 0x8DF5,
        };

        class Format final {
        public:
          inline Format();
          inline ~Format();
          inline void operator=(const Format &);

        public:
          int rangeMin = 0;
          int rangeMax = 0;
          int precision = 0;
        };
        class FRAGMENT_SHADER final {
        public:
          inline FRAGMENT_SHADER();
          inline ~FRAGMENT_SHADER();
          void operator=(const FRAGMENT_SHADER &);

        public:
          Format LOW_FLOAT;
          Format MEDIUM_FLOAT;
          Format HIGH_FLOAT;
          Format LOW_INT;
          Format MEDIUM_INT;
          Format HIGH_INT;
        };

        class VERTEX_SHADER final {
        public:
          inline VERTEX_SHADER();
          inline ~VERTEX_SHADER();
          void operator=(const VERTEX_SHADER &);

        public:
          Format LOW_FLOAT;
          Format MEDIUM_FLOAT;
          Format HIGH_FLOAT;
          Format LOW_INT;
          Format MEDIUM_INT;
          Format HIGH_INT;
        };

      public:
        inline ShaderPrecisionFormat();
        inline ~ShaderPrecisionFormat();
        void operator=(const ShaderPrecisionFormat &);

      public:
        FRAGMENT_SHADER gl_fragment_shader;
        VERTEX_SHADER gl_vertex_shader;
      };

    public:
      inline Webgl();
      inline ~Webgl();

    public:
      bool enable = false;
      Hash hash;
      std::string vendor;
      std::string renderer;
      std::string driver_version;
      std::string version;
      std::map<unsigned int, std::string> parameters;
      std::set<std::string> enabledExtensions;
      ContextAttributes contextAttributes;
      ShaderPrecisionFormat shaderPrecisionFormat;
    };
    class Audio final {
    public:
      inline Audio();
      inline ~Audio();

    public:
      bool enable = false;
      Hash hash;
    };
    class Font final {
    public:
      class Keyword final {
      public:
        inline Keyword();
        inline ~Keyword();
        inline Keyword(const std::string &kv);
        inline Keyword(const std::string &k, const std::string &v);
        inline bool operator<(const Keyword &) const;
        inline bool operator==(const Keyword &) const;

      public:
        std::string key;
        std::string value;
      };

    public:
      inline Font();
      inline ~Font();

    public:
      bool enable = false;
      Hash hash;
      std::set<Keyword> keywords;
    };
    class Screen final {
    public:
      inline Screen();
      inline ~Screen();

    public:
      int height = 0;
      int width = 0;
      int colorDepth = 0;
      int pixelDepth = 0;
      int availLeft = 0;
      int availTop = 0;
      int availHeight = 0;
      int availWidth = 0;
      double devicePixelRatio = 1.0;
      bool enable = false;
    };

  public:
    inline Fps();
    inline ~Fps();

  public:
    bool enable = false;
    std::string enable_do_not_track = "null";
    std::string platform = "Win32";
    std::string userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                            "AppleWebKit/537.36 (KHTML, "
                            "like Gecko) Chrome/130.0.0.0 Safari/537.36";
    unsigned short hardwareConcurrency = 2;
    unsigned long long deviceMemory = 2147483648;
    Font font;
    Canvas canvas;
    Webgl webgl;
    WebRTC webrtc;
    Audio audio;
    Screen screen;
    Timezone timezone;
    Navigator navigator;
    ThridParty thrid_party;
  };

  class Jss final {
  public:
    inline Jss();
    inline ~Jss();

  public:
    bool enable = false;
    std::map<std::string, std::string> source;
  };

private:
  inline void Final();

public:
  inline IConfigure();
  inline IConfigure(const std::string &protocol_buffer);
  inline ~IConfigure();
  inline std::string Serialization() const;
  inline void operator<<(const std::string &protocol_buffer);
  inline void operator=(const std::string &protocol_buffer);
  inline void operator+=(const std::string &protocol_buffer);
  inline void operator=(const IConfigure &cfg) = delete;
  inline const std::string &GetSuperMAC() const {
    return super_mac;
  }
  inline bool InvalidPolicId() const {
    return !(policy.id > 0 && policy.id < 0xFF);
  }
  inline policy_id_t GetPolicyId() const {
    return policy.id;
  }
  inline browser_id_t GetBrwId() const {
    return GetPolicyId();
  }
  inline request_id_t GetReqId() const {
    return reqid;
  }
  inline const bool &Enable() const {
    return enable;
  }
  inline const IConfigure::Type &GetType() const {
    return type;
  }

public:
  unsigned long long reqid = 0;
  bool enable = false;
  Type type = Type::BrwCreate;
  Input input;
  Command command;
  Fps fps;
  Jss jss;
  Frame frame;
  std::map<std::string, std::string> startup_args;
  std::map<std::string, std::string> startup_envs;
  rapidjson::Document doc;
  Policy policy;
  Server server;
  Proxy proxy;
  std::set<std::string> startup_urls;
  HomePage homepage;
  std::string search_engine;
  Request request;
  bool fps_use3rd = false;
  std::string super_mac = "";
};
inline IConfigure::IConfigure() {
}
inline IConfigure::IConfigure(const std::string &protocol_buffer) {
  *this << protocol_buffer;
}
inline IConfigure::~IConfigure() {
}
inline IConfigure::Policy::Policy() {
}
inline IConfigure::Policy::~Policy() {
}
inline IConfigure::Command::Command() {
}
inline IConfigure::Command::~Command() {
}
inline IConfigure::Input::Input() {
}
inline IConfigure::Input::~Input() {
}
inline bool IConfigure::Input::IsMouseEventType() const {
  bool result = false;
  do {
    if (type != Input::Type::kMouseDown && type != Input::Type::kMouseUp &&
        type != Input::Type::kMouseMove && type != Input::Type::kMouseEnter &&
        type != Input::Type::kMouseLeave && type != Input::Type::kContextMenu &&
        type != Input::Type::kMouseWheel)
      break;
    result = true;
  } while (0);
  return result;
}
inline bool IConfigure::Input::IsMouseWheelEventType() const {
  return type == Input::Type::kMouseWheel;
}
inline bool IConfigure::Input::IsKeyboardEventType() const {
  return Input::Type::kKeyboardTypeFirst <= type &&
         type <= Input::Type::kKeyboardTypeLast;
}
inline bool IConfigure::Input::IsTouchEventType() const {
  return Input::Type::kTouchTypeFirst <= type &&
         type <= Input::Type::kTouchTypeLast;
}
inline bool IConfigure::Input::IsGestureEventType() const {
  return Input::Type::kGestureTypeFirst <= type &&
         type <= Input::Type::kGestureTypeLast;
}
inline bool IConfigure::Input::IsPointerEventType() const {
  return Input::Type::kPointerTypeFirst <= type &&
         type <= Input::Type::kPointerTypeLast;
}
inline bool IConfigure::Input::IsWebInteractionEvent() const {
  return type == Input::Type::kMouseDown || type == Input::Type::kMouseUp ||
         type == Input::Type::kKeyDown || type == Input::Type::kRawKeyDown ||
         type == Input::Type::kKeyUp || type == Input::Type::kChar ||
         type == Input::Type::kGestureTapDown ||
         type == Input::Type::kGestureTap ||
         type == Input::Type::kPointerDown || type == Input::Type::kPointerUp ||
         type == Input::Type::kTouchStart || type == Input::Type::kTouchEnd;
}
inline bool IConfigure::Input::IsGestureScroll() const {
  switch (type) {
  case Input::Type::kGestureScrollBegin:
  case Input::Type::kGestureScrollUpdate:
  case Input::Type::kGestureScrollEnd:
    return true;
  default:
    return false;
  }
}
inline bool IConfigure::Input::IsPinchGestureEventType() const {
  return Input::Type::kGesturePinchTypeFirst <= type &&
         type <= Input::Type::kGesturePinchTypeLast;
}
inline bool IConfigure::Input::IsFlingGestureEventType() const {
  return Input::Type::kGestureFlingStart <= type &&
         type <= Input::Type::kGestureFlingCancel;
}
inline void IConfigure::Input::operator=(const Input &rhs) {
  enable = rhs.enable;
  type = rhs.type;
  delta_units = rhs.delta_units;
  source_device = rhs.source_device;
  pointer_type = rhs.pointer_type;
  dom_key = rhs.dom_key;
  pointer_id = rhs.pointer_id;
  modifiers = rhs.modifiers;
  pointer_count = rhs.pointer_count;
  index = rhs.index;
  tilt_x = rhs.tilt_x;
  tilt_y = rhs.tilt_y;
  global_x = rhs.global_x;
  global_y = rhs.global_y;
  dx = rhs.dx;
  dy = rhs.dy;
  dx_hint = rhs.dx_hint;
  dy_hint = rhs.dy_hint;
  scale = rhs.scale;
  anchor_x = rhs.anchor_x;
  anchor_y = rhs.anchor_y;
  velocity_x = rhs.velocity_x;
  velocity_y = rhs.velocity_y;
  x = rhs.x;
  y = rhs.y;
  radius_x = rhs.radius_x;
  radius_y = rhs.radius_y;
  rotation_angle = rhs.rotation_angle;
  force = rhs.force;
  tangential_pressure = rhs.tangential_pressure;
}
inline void IConfigure::Input::operator<<(const rapidjson::Value &inputObj) {
  do {
    if (!inputObj.IsObject())
      break;
    if (inputObj.HasMember("enable") && inputObj["enable"].IsBool())
      enable = inputObj["enable"].GetBool();

    if (inputObj.HasMember("type") && inputObj["type"].IsInt())
      type = static_cast<Input::Type>(inputObj["type"].GetInt());

    if (inputObj.HasMember("delta_units") && inputObj["delta_units"].IsInt())
      delta_units =
          static_cast<ScrollGranularity>(inputObj["delta_units"].GetInt());

    if (inputObj.HasMember("source_device") &&
        inputObj["source_device"].IsInt())
      source_device =
          static_cast<GestureDevice>(inputObj["source_device"].GetInt());

    if (inputObj.HasMember("pointer_type") && inputObj["pointer_type"].IsInt())
      pointer_type =
          static_cast<PointerType>(inputObj["pointer_type"].GetInt());

    if (inputObj.HasMember("dom_key") && inputObj["dom_key"].IsUint())
      dom_key = inputObj["dom_key"].GetUint();

    if (inputObj.HasMember("pointer_id") && inputObj["pointer_id"].IsUint())
      pointer_id = inputObj["pointer_id"].GetUint();

    if (inputObj.HasMember("modifiers") && inputObj["modifiers"].IsInt())
      modifiers = static_cast<Input::Modifiers>(inputObj["modifiers"].GetInt());

    if (inputObj.HasMember("pointer_count") &&
        inputObj["pointer_count"].IsInt())
      pointer_count = inputObj["pointer_count"].GetInt();

    if (inputObj.HasMember("index") && inputObj["index"].IsInt())
      index = inputObj["index"].GetInt();

    if (inputObj.HasMember("tilt_x") && inputObj["tilt_x"].IsInt())
      tilt_x = inputObj["tilt_x"].GetInt();

    if (inputObj.HasMember("tilt_y") && inputObj["tilt_y"].IsInt())
      tilt_y = inputObj["tilt_y"].GetInt();

    if (inputObj.HasMember("global_x") && inputObj["global_x"].IsDouble())
      global_x = inputObj["global_x"].GetDouble();

    if (inputObj.HasMember("global_y") && inputObj["global_y"].IsDouble())
      global_y = inputObj["global_y"].GetDouble();

    if (inputObj.HasMember("dx") && inputObj["dx"].IsDouble())
      dx = inputObj["dx"].GetDouble();

    if (inputObj.HasMember("dy") && inputObj["dy"].IsDouble())
      dy = inputObj["dy"].GetDouble();

    if (inputObj.HasMember("dx_hint") && inputObj["dx_hint"].IsDouble())
      dx_hint = inputObj["dx_hint"].GetDouble();

    if (inputObj.HasMember("dy_hint") && inputObj["dy_hint"].IsDouble())
      dy_hint = inputObj["dy_hint"].GetDouble();

    if (inputObj.HasMember("scale") && inputObj["scale"].IsDouble())
      scale = inputObj["scale"].GetDouble();

    if (inputObj.HasMember("anchor_x") && inputObj["anchor_x"].IsDouble())
      anchor_x = inputObj["anchor_x"].GetDouble();

    if (inputObj.HasMember("anchor_y") && inputObj["anchor_y"].IsDouble())
      anchor_y = inputObj["anchor_y"].GetDouble();

    if (inputObj.HasMember("velocity_x") && inputObj["velocity_x"].IsDouble())
      velocity_x = inputObj["velocity_x"].GetDouble();

    if (inputObj.HasMember("velocity_y") && inputObj["velocity_y"].IsDouble())
      velocity_y = inputObj["velocity_y"].GetDouble();

    if (inputObj.HasMember("x") && inputObj["x"].IsDouble())
      x = inputObj["x"].GetDouble();

    if (inputObj.HasMember("y") && inputObj["y"].IsDouble())
      y = inputObj["y"].GetDouble();

    if (inputObj.HasMember("radius_x") && inputObj["radius_x"].IsDouble())
      radius_x = inputObj["radius_x"].GetDouble();

    if (inputObj.HasMember("radius_y") && inputObj["radius_y"].IsDouble())
      radius_y = inputObj["radius_y"].GetDouble();

    if (inputObj.HasMember("rotation_angle") &&
        inputObj["rotation_angle"].IsDouble())
      rotation_angle = inputObj["rotation_angle"].GetDouble();

    if (inputObj.HasMember("force") && inputObj["force"].IsDouble())
      force = inputObj["force"].GetDouble();

    if (inputObj.HasMember("tangential_pressure") &&
        inputObj["tangential_pressure"].IsDouble())
      tangential_pressure = inputObj["tangential_pressure"].GetDouble();

    if (inputObj.HasMember("delta_x") && inputObj["delta_x"].IsDouble())
      delta_x = inputObj["delta_x"].GetDouble();

    if (inputObj.HasMember("delta_y") && inputObj["delta_y"].IsDouble())
      delta_y = inputObj["delta_y"].GetDouble();

    if (inputObj.HasMember("wheel_ticks_x") &&
        inputObj["wheel_ticks_x"].IsDouble())
      wheel_ticks_x = inputObj["wheel_ticks_x"].GetDouble();

    if (inputObj.HasMember("wheel_ticks_y") &&
        inputObj["wheel_ticks_y"].IsDouble())
      wheel_ticks_y = inputObj["wheel_ticks_y"].GetDouble();

    if (inputObj.HasMember("acceleration_ratio_x") &&
        inputObj["acceleration_ratio_x"].IsDouble())
      acceleration_ratio_x = inputObj["acceleration_ratio_x"].GetDouble();

    if (inputObj.HasMember("acceleration_ratio_y") &&
        inputObj["acceleration_ratio_y"].IsDouble())
      acceleration_ratio_y = inputObj["acceleration_ratio_y"].GetDouble();

    if (inputObj.HasMember("phase") && inputObj["phase"].IsInt())
      phase =
          static_cast<Input::MouseWheelEventPhase>(inputObj["phase"].GetInt());

    if (inputObj.HasMember("momentum_phase") &&
        inputObj["momentum_phase"].IsInt())
      momentum_phase = static_cast<Input::MouseWheelEventPhase>(
          inputObj["momentum_phase"].GetInt());

    if (inputObj.HasMember("rails_mode") && inputObj["rails_mode"].IsInt())
      rails_mode =
          static_cast<Input::RailsMode>(inputObj["rails_mode"].GetInt());

    if (inputObj.HasMember("dispatch_type") &&
        inputObj["dispatch_type"].IsInt())
      dispatch_type =
          static_cast<Input::DispatchType>(inputObj["dispatch_type"].GetInt());

    if (inputObj.HasMember("event_action") && inputObj["event_action"].IsInt())
      event_action = static_cast<Input::MouseWheelEventAction>(
          inputObj["event_action"].GetInt());

    if (inputObj.HasMember("has_synthetic_phase") &&
        inputObj["has_synthetic_phase"].IsBool())
      has_synthetic_phase = inputObj["has_synthetic_phase"].GetBool();

    if (inputObj.HasMember("skip_if_unhandled") &&
        inputObj["skip_if_unhandled"].IsBool())
      skip_if_unhandled = inputObj["skip_if_unhandled"].GetBool();

    if (inputObj.HasMember("is_system_key") &&
        inputObj["is_system_key"].IsBool())
      is_system_key = inputObj["is_system_key"].GetBool();

    if (inputObj.HasMember("is_browser_shortcut") &&
        inputObj["is_browser_shortcut"].IsBool())
      is_browser_shortcut = inputObj["is_browser_shortcut"].GetBool();

    if (inputObj.HasMember("twist") && inputObj["twist"].IsInt())
      twist = inputObj["twist"].GetInt();

    if (inputObj.HasMember("click_count") && inputObj["click_count"].IsUint())
      click_count = inputObj["click_count"].GetUint();

    if (inputObj.HasMember("movement_x") && inputObj["movement_x"].IsInt())
      movement_x = inputObj["movement_x"].GetInt();

    if (inputObj.HasMember("movement_y") && inputObj["movement_y"].IsInt())
      movement_y = inputObj["movement_y"].GetInt();

    if (inputObj.HasMember("is_raw_movement_event") &&
        inputObj["is_raw_movement_event"].IsBool())
      is_raw_movement_event = inputObj["is_raw_movement_event"].GetBool();

    if (inputObj.HasMember("device_id") && inputObj["device_id"].IsInt())
      device_id = inputObj["device_id"].GetInt();

    if (inputObj.HasMember("button") && inputObj["button"].IsInt())
      button = static_cast<Input::Button>(inputObj["button"].GetInt());
#if 0
				if (inputObj.HasMember("text") && inputObj["text"].IsString() &&
					inputObj["text"].GetStringLength() > 0) {
					text.clear();
					std::string tmp = inputObj["text"].GetString();
					for (auto& c : tmp) {
						text.push_back(c);
						if (text.size() >= 4)
							break;
					}
				}
				if (inputObj.HasMember("unmodified_text") &&
					inputObj["unmodified_text"].IsString() &&
					inputObj["unmodified_text"].GetStringLength() > 0) {
					unmodified_text.clear();
					std::string tmp = inputObj["unmodified_text"].GetString();
					for (auto& c : tmp) {
						unmodified_text.push_back(c);
						if (unmodified_text.size() >= 4)
							break;
					}
				}
#endif

  } while (0);
}
inline IConfigure::HomePage::HomePage() {
}
inline IConfigure::HomePage::~HomePage() {
}
inline IConfigure::Frame::Frame() {
}
inline IConfigure::Frame::~Frame() {
}
inline IConfigure::Frame::Resolution::Resolution() {
}
inline IConfigure::Frame::Resolution::~Resolution() {
}
inline void IConfigure::Frame::Resolution::operator=(const Resolution &rhs) {
  width = rhs.width;
  height = rhs.height;
}
inline IConfigure::Server::Server() {
}
inline IConfigure::Server::~Server() {
}
void IConfigure::Server::operator<<(const rapidjson::Value &serverObj) {
  do {
    if (!serverObj.IsObject())
      break;
    if (serverObj.HasMember("enable") && serverObj["enable"].IsBool())
      enable = serverObj["enable"].GetBool();
    if (serverObj.HasMember("pipe") && serverObj["pipe"].IsString() &&
        serverObj["pipe"].GetStringLength() > 0) {
      pipe = serverObj["pipe"].GetString();
    }
    if (serverObj.HasMember("tcp") && serverObj["tcp"].IsString() &&
        serverObj["tcp"].GetStringLength() > 0) {
      tcp = serverObj["tcp"].GetString();
    }
    if (serverObj.HasMember("udp") && serverObj["udp"].IsString() &&
        serverObj["udp"].GetStringLength() > 0) {
      udp = serverObj["udp"].GetString();
    }
  } while (0);
}
inline IConfigure::Proxy::Proxy() {
}
inline IConfigure::Proxy::~Proxy() {
}
inline IConfigure::Fps::Fps() {
}
inline IConfigure::Fps::~Fps() {
}
inline IConfigure::Fps::Navigator::Navigator() {
}
inline IConfigure::Fps::Navigator::~Navigator() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugins() {
}
inline IConfigure::Fps::Navigator::Plugins::~Plugins() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::Plugin() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::~Plugin() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::Plugin(
    const Plugin &other) {
  key = other.key;
  name = other.name;
  description = other.description;
  mimeTypes = other.mimeTypes;
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::operator<(
    const Plugin &rhs) const {
  return key.compare(rhs.key) < 0;
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::operator==(
    const Plugin &rhs) const {
  return key.compare(rhs.key) == 0;
}
inline void
IConfigure::Fps::Navigator::Plugins::Plugin::operator=(const Plugin &rhs) {
  key = rhs.key;
  name = rhs.name;
  description = rhs.description;
  mimeTypes = rhs.mimeTypes;
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::MimeType() {
}
inline IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::~MimeType() {
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::operator<(
    const MimeType &rhs) const {
  return key.compare(rhs.key) < 0;
}
inline bool IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::operator==(
    const MimeType &rhs) const {
  return key.compare(rhs.key) == 0;
}

inline void IConfigure::Fps::Navigator::Plugins::Plugin::MimeType::operator=(
    const MimeType &rhs) {
  key = rhs.key;
  type = rhs.type;
  suffixes = rhs.suffixes;
}
inline IConfigure::Fps::Screen::Screen() {
}
inline IConfigure::Fps::Screen::~Screen() {
}
inline IConfigure::Fps::Timezone::Timezone() {
}
inline IConfigure::Fps::Timezone::~Timezone() {
}
inline IConfigure::Fps::Timezone::Source::Source(const unsigned int &id_,
                                                 const std::string &name_)
    : id(id_), name(name_) {
}
inline IConfigure::Fps::Timezone::Source::~Source() {
}
inline IConfigure::Fps::Audio::Audio() {
}
inline IConfigure::Fps::Audio::~Audio() {
}
inline IConfigure::Fps::Canvas::Canvas() {
}
inline IConfigure::Fps::Canvas::~Canvas() {
}
inline IConfigure::Fps::WebRTC::WebRTC() {
}
inline IConfigure::Fps::WebRTC::~WebRTC() {
}
inline void IConfigure::Fps::WebRTC::operator=(const WebRTC &rhs) {
  enable = rhs.enable;
  protection_type = rhs.protection_type;
  ip = rhs.ip;
  port = rhs.port;
  webrtc_ip_handling_protected_type = rhs.webrtc_ip_handling_protected_type;
}
inline void
IConfigure::Fps::WebRTC::operator<<(const rapidjson::Value &webrtcObj) {
  do {
    if (!webrtcObj.IsObject())
      break;
    if (webrtcObj.HasMember("enable") && webrtcObj["enable"].IsBool())
      enable = webrtcObj["enable"].GetBool();

    if (webrtcObj.HasMember("protection_type") &&
        webrtcObj["protection_type"].IsUint())
      protection_type = static_cast<WebRTC::ProtectionType>(
          webrtcObj["protection_type"].GetUint());

    if (webrtcObj.HasMember("ip") && webrtcObj["ip"].IsString())
      ip = webrtcObj["ip"].GetString();

    if (webrtcObj.HasMember("port") && webrtcObj["port"].IsUint())
      port = static_cast<unsigned short>(webrtcObj["port"].GetUint());

    if (webrtcObj.HasMember("webrtc_ip_handling_protected_type") &&
        webrtcObj["webrtc_ip_handling_protected_type"].IsUint()) {
      webrtc_ip_handling_protected_type =
          static_cast<WebRTCIPHandlingProtectedType>(
              webrtcObj["webrtc_ip_handling_protected_type"].GetUint());
    }
  } while (0);
}
inline IConfigure::Fps::Webgl::Webgl() {
}
inline IConfigure::Fps::Webgl::~Webgl() {
}
inline IConfigure::Fps::Webgl::ContextAttributes::ContextAttributes() {
}
inline IConfigure::Fps::Webgl::ContextAttributes::~ContextAttributes() {
}
inline void IConfigure::Fps::Webgl::ContextAttributes::operator=(
    const ContextAttributes &rhs) {
  alpha = rhs.alpha;
  antialias = rhs.antialias;
  depth = rhs.depth;
  desynchronized = rhs.desynchronized;
  failIfMajorPerformanceCaveat = rhs.failIfMajorPerformanceCaveat;
  powerPreference = rhs.powerPreference;
  premultipliedAlpha = rhs.premultipliedAlpha;
  preserveDrawingBuffer = rhs.preserveDrawingBuffer;
  stencil = rhs.stencil;
  xrCompatible = rhs.xrCompatible;
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::ShaderPrecisionFormat() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::~ShaderPrecisionFormat() {
}
inline void IConfigure::Fps::Webgl::ShaderPrecisionFormat::operator=(
    const ShaderPrecisionFormat &rhs) {
  gl_fragment_shader = rhs.gl_fragment_shader;
  gl_vertex_shader = rhs.gl_vertex_shader;
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::FRAGMENT_SHADER::
    FRAGMENT_SHADER() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::FRAGMENT_SHADER::
    ~FRAGMENT_SHADER() {
}
inline void
IConfigure::Fps::Webgl::ShaderPrecisionFormat::FRAGMENT_SHADER::operator=(
    const FRAGMENT_SHADER &rhs) {
  LOW_FLOAT = rhs.LOW_FLOAT;
  MEDIUM_FLOAT = rhs.MEDIUM_FLOAT;
  HIGH_FLOAT = rhs.HIGH_FLOAT;
  LOW_INT = rhs.LOW_INT;
  MEDIUM_INT = rhs.MEDIUM_INT;
  HIGH_INT = rhs.HIGH_INT;
}

inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::VERTEX_SHADER::
    VERTEX_SHADER() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::VERTEX_SHADER::
    ~VERTEX_SHADER() {
}
inline void
IConfigure::Fps::Webgl::ShaderPrecisionFormat::VERTEX_SHADER::operator=(
    const VERTEX_SHADER &rhs) {
  LOW_FLOAT = rhs.LOW_FLOAT;
  MEDIUM_FLOAT = rhs.MEDIUM_FLOAT;
  HIGH_FLOAT = rhs.HIGH_FLOAT;
  LOW_INT = rhs.LOW_INT;
  MEDIUM_INT = rhs.MEDIUM_INT;
  HIGH_INT = rhs.HIGH_INT;
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::Format::Format() {
}
inline IConfigure::Fps::Webgl::ShaderPrecisionFormat::Format::~Format() {
}
inline void IConfigure::Fps::Webgl::ShaderPrecisionFormat::Format::operator=(
    const Format &rhs) {
  rangeMin = rhs.rangeMin;
  rangeMax = rhs.rangeMax;
  precision = rhs.precision;
}
inline IConfigure::Fps::Font::Font() {
}
inline IConfigure::Fps::Font::~Font() {
}
inline IConfigure::Fps::Font::Keyword::Keyword() {
}
inline IConfigure::Fps::Font::Keyword::~Keyword() {
}
inline IConfigure::Fps::Font::Keyword::Keyword(const std::string &k,
                                               const std::string &v) {
  key = k;
  value = v;
}
inline IConfigure::Fps::Font::Keyword::Keyword(const std::string &kv) {
  key = kv;
  value = kv;
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);
}
inline bool
IConfigure::Fps::Font::Keyword::operator<(const Keyword &rhs) const {
  return key.compare(rhs.key) < 0;
}
inline bool
IConfigure::Fps::Font::Keyword::operator==(const Keyword &rhs) const {
  return key.compare(rhs.key) == 0;
}
inline IConfigure::Fps::Hash::Hash() {
}
inline IConfigure::Fps::Hash::~Hash() {
}
inline IConfigure::Jss::Jss() {
}
inline IConfigure::Jss::~Jss() {
}
inline void
IConfigure::Fps::Navigator::operator<<(const rapidjson::Value &navigatorObj) {
  do {
    if (!navigatorObj.IsObject())
      break;
    if (navigatorObj.ObjectEmpty())
      break;
    if (!navigatorObj.HasMember("plugins"))
      break;
    if (!navigatorObj["plugins"].IsObject())
      break;
    auto &pluginsObj = navigatorObj["plugins"];
    if (pluginsObj.HasMember("enable") && pluginsObj["enable"].IsBool()) {
      plugins.enable = pluginsObj["enable"].GetBool();
    }
    if (pluginsObj.HasMember("pdfViewerEnabled") &&
        pluginsObj["pdfViewerEnabled"].IsBool()) {
      plugins.pdfViewerEnabled = pluginsObj["pdfViewerEnabled"].GetBool();
    }
    if (pluginsObj.HasMember("javaEnabled") &&
        pluginsObj["javaEnabled"].IsBool()) {
      plugins.javaEnabled = pluginsObj["javaEnabled"].GetBool();
    }
    if (pluginsObj.HasMember("pluginArray") &&
        pluginsObj["pluginArray"].IsArray()) {
      for (auto itPluginArray = pluginsObj["pluginArray"].Begin();
           itPluginArray != pluginsObj["pluginArray"].End(); ++itPluginArray) {
        if (!itPluginArray->IsObject())
          break;
        auto &pluginObj = *itPluginArray;
        Plugins::Plugin plugin;
        if (pluginObj.HasMember("name") && pluginObj["name"].IsString()) {
          plugin.name = pluginObj["name"].GetString();
          plugin.key = plugin.name;
          std::transform(plugin.key.begin(), plugin.key.end(),
                         plugin.key.begin(), ::tolower);
        }
        if (pluginObj.HasMember("description") &&
            pluginObj["description"].IsString()) {
          plugin.description = pluginObj["description"].GetString();
        }
        if (pluginObj.HasMember("mimeTypes") &&
            pluginObj["mimeTypes"].IsArray()) {
          for (auto itMimeTypes = pluginObj["mimeTypes"].Begin();
               itMimeTypes != pluginObj["mimeTypes"].End(); ++itMimeTypes) {
            if (!itMimeTypes->IsObject())
              break;
            auto &mimeTypeObj = *itMimeTypes;
            Plugins::Plugin::MimeType mimeType;
            if (mimeTypeObj.HasMember("type") &&
                mimeTypeObj["type"].IsString()) {
              mimeType.type = mimeTypeObj["type"].GetString();
              mimeType.key = mimeType.type;
              std::transform(mimeType.key.begin(), mimeType.key.end(),
                             mimeType.key.begin(), ::tolower);
            }
            if (mimeTypeObj.HasMember("suffixes") &&
                mimeTypeObj["suffixes"].IsString()) {
              mimeType.suffixes = mimeTypeObj["suffixes"].GetString();
            }
            if (mimeType.key.empty())
              continue;
            plugin.mimeTypes.emplace(mimeType);
          }
        }
        if (plugin.key.empty())
          continue;
        plugins.plugins.emplace(plugin);
      }
    }
  } while (0);
}
inline void
IConfigure::Fps::Hash::operator<<(const std::string &protocol_buffer) {
  do {
    if (protocol_buffer.empty())
      break;
    rapidjson::Document docHash;
    if (docHash.Parse(protocol_buffer.data(), protocol_buffer.size())
            .HasParseError())
      break;
    if (!docHash.IsObject())
      break;
    if (docHash.HasMember("random") && docHash["random"].IsBool())
      random = docHash["random"].GetBool();
    if (docHash.HasMember("base") && docHash["base"].IsNumber()) {
      if (docHash["base"].IsInt()) {
        base = docHash["base"].GetInt() * 1.0;
      } else if (docHash["base"].IsUint()) {
        base = docHash["base"].GetUint() * 1.0;
      } else if (docHash["base"].IsInt64()) {
        base = docHash["base"].GetInt64() * 1.0;
      } else if (docHash["base"].IsUint64()) {
        base = docHash["base"].GetUint64() * 1.0;
      } else if (docHash["base"].IsDouble()) {
        base = docHash["base"].GetDouble();
      }
    }
    if (docHash.HasMember("from") && docHash["from"].IsNumber()) {
      if (docHash["from"].IsInt()) {
        from = docHash["from"].GetInt() * 1.0;
      } else if (docHash["from"].IsUint()) {
        from = docHash["from"].GetUint() * 1.0;
      } else if (docHash["from"].IsInt64()) {
        from = docHash["from"].GetInt64() * 1.0;
      } else if (docHash["from"].IsUint64()) {
        from = docHash["from"].GetUint64() * 1.0;
      } else if (docHash["from"].IsDouble()) {
        from = docHash["from"].GetDouble();
      }
    }
    if (docHash.HasMember("to") && docHash["to"].IsNumber()) {
      if (docHash["to"].IsInt()) {
        to = docHash["to"].GetInt() * 1.0;
      } else if (docHash["to"].IsUint()) {
        to = docHash["to"].GetUint() * 1.0;
      } else if (docHash["to"].IsInt64()) {
        to = docHash["to"].GetInt64() * 1.0;
      } else if (docHash["to"].IsUint64()) {
        to = docHash["to"].GetUint64() * 1.0;
      } else if (docHash["to"].IsDouble()) {
        to = docHash["to"].GetDouble();
      }
    }
  } while (0);
}
inline void IConfigure::operator<<(const std::string &protocol_buffer) {
  *this = protocol_buffer;
}
inline void IConfigure::operator+=(const std::string &protocol_buffer) {
}
inline void IConfigure::operator=(const std::string &protocol_buffer) {
  bool success = false;
  do {
    if (protocol_buffer.empty())
      break;
    if (doc.Parse(protocol_buffer.data(), protocol_buffer.size())
            .HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (doc.ObjectEmpty())
      break;
    do { //!@ .enable
      if (!doc.HasMember("enable"))
        break;
      if (!doc["enable"].IsBool())
        break;
      enable = doc["enable"].GetBool();
    } while (0);
    do { //!@ .rerquest
      if (!doc.HasMember("request"))
        break;
      if (!doc["request"].IsObject())
        break;
      auto &requestObj = doc["request"];
      request << requestObj;
    } while (0);
    do { //!@ .fps_use3rd
      if (!doc.HasMember("fps_use3rd"))
        break;
      if (!doc["fps_use3rd"].IsBool())
        break;
      fps_use3rd = doc["fps_use3rd"].GetBool();
    } while (0);
    do { //!@ .reqid
      if (!doc.HasMember("reqid"))
        break;
      if (!doc["reqid"].IsUint64())
        break;
      reqid = doc["reqid"].GetUint64();
    } while (0);
    do { //!@ .type
      if (!doc.HasMember("type"))
        break;
      if (!doc["type"].IsUint())
        break;
      type = static_cast<Type>(doc["type"].GetUint());
    } while (0);
    do { //!@ .server
      if (!doc.HasMember("server"))
        break;
      if (!doc["server"].IsObject())
        break;
      server << doc["server"];
    } while (0);
    do { //!@ .command
      if (!doc.HasMember("command"))
        break;
      if (!doc["command"].IsObject())
        break;
      command << doc["command"];
    } while (0);
    do { //!@ .input
      if (!doc.HasMember("input"))
        break;
      if (!doc["input"].IsObject())
        break;
      input << doc["input"];
    } while (0);
    do { //!@ .startup_urls
      if (!doc.HasMember("startup_urls"))
        break;
      if (!doc["startup_urls"].IsArray())
        break;
      for (auto it = doc["startup_urls"].Begin();
           it != doc["startup_urls"].End(); ++it) {
        if (!it->IsString())
          break;
        if (it->GetStringLength() <= 0)
          continue;
        startup_urls.emplace(it->GetString());
      }
    } while (0);
    do { //!@ .frame
      if (!doc.HasMember("frame"))
        break;
      if (!doc["frame"].IsObject())
        break;
      auto &frameObj = doc["frame"];
      if (frameObj.HasMember("enable") && frameObj["enable"].IsBool()) {
        frame.enable = frameObj["enable"].GetBool();
      }
      if (frameObj.HasMember("resolution") &&
          frameObj["resolution"].IsObject()) {
        auto &resolutionObj = frameObj["resolution"];
        if (resolutionObj.HasMember("width") &&
            resolutionObj["width"].IsUint()) {
          frame.resolution.width = resolutionObj["width"].GetUint();
        }
        if (resolutionObj.HasMember("height") &&
            resolutionObj["height"].IsUint()) {
          frame.resolution.height = resolutionObj["height"].GetUint();
        }
      }
    } while (0);
    do { //!@ .homepage
      if (!doc.HasMember("homepage"))
        break;
      if (!doc["homepage"].IsObject())
        break;
      auto &homepageObj = doc["homepage"];
      if (homepageObj.HasMember("enable") && homepageObj["enable"].IsBool()) {
        homepage.enable = homepageObj["enable"].GetBool();
      }
      if (homepageObj.HasMember("url") && homepageObj["url"].IsString()) {
        homepage.url = homepageObj["url"].GetString();
      }
      if (homepageObj.HasMember("open_new_tab") &&
          homepageObj["open_new_tab"].IsBool()) {
        homepage.open_new_tab = homepageObj["open_new_tab"].GetBool();
      }
    } while (0);
    do { //!@ .search_engine
      if (!doc.HasMember("search_engine"))
        break;
      if (!doc["search_engine"].IsString())
        break;
      if (doc["search_engine"].GetStringLength() <= 0)
        break;
      search_engine = doc["search_engine"].GetString();
    } while (0);

    do { //!@ .policy
      if (!doc.HasMember("policy"))
        break;
      if (!doc["policy"].IsObject())
        break;
      auto &policyObj = doc["policy"];
      if (!policyObj.HasMember("id"))
        break;
      if (!policyObj["id"].IsUint())
        break;
      policy.id = static_cast<decltype(policy.id)>(policyObj["id"].GetUint());
    } while (0);
    do { //!@ .proxy
      if (!doc.HasMember("proxy"))
        break;
      if (!doc["proxy"].IsObject())
        break;
      auto &proxyObj = doc["proxy"];
      if (proxyObj.HasMember("enable") && proxyObj["enable"].IsBool()) {
        proxy.enable = proxyObj["enable"].GetBool();
      }
      if (!proxyObj.HasMember("credentials_url"))
        break;
      if (!proxyObj["credentials_url"].IsString())
        break;
      proxy.credentials_url = proxyObj["credentials_url"].GetString();
      std::regex url_regex(
          R"(^(http[s]?|socks[4-5](h|a)?):\/\/([^:]+):([^@]+)@([^:]+):(\d+)$)");
      std::smatch url_match;
      if (!std::regex_match(proxy.credentials_url, url_match, url_regex)) {
        proxy.address = proxy.credentials_url;
        break;
      }
      do {
        if (url_match.size() != 7)
          break;
        std::string protocol;
        if (std::string(url_match[1]).find("https") != std::string::npos) {
          protocol = "https";
          proxy.type = Proxy::Type::HTTPS;
        } else if (std::string(url_match[1]).find("http") !=
                   std::string::npos) {
          protocol = "http";
          proxy.type = Proxy::Type::HTTP;
        } else if (std::string(url_match[1]).find("socks4") !=
                   std::string::npos) {
          protocol = "socks4";
          proxy.type = Proxy::Type::SOCKS4;
        } else if (std::string(url_match[1]).find("socks5") !=
                   std::string::npos) {
          protocol = "socks5";
          proxy.type = Proxy::Type::SOCKS5;
        }
        if (protocol.empty())
          break;
        if (url_match[2].matched) {
          const std::string tmp(url_match[2]);
          if (tmp.find("h") != std::string::npos) {
            proxy.socks_type = Proxy::SocksType::SocksH;
          } else if (tmp.find("a") != std::string::npos) {
            proxy.socks_type = Proxy::SocksType::SocksA;
          }
        }
        if (url_match[3].matched)
          proxy.username = url_match[3];
        if (url_match[4].matched)
          proxy.password = url_match[4];
        if (url_match[5].matched)
          proxy.host = url_match[5];
        if (url_match[6].matched)
          proxy.port = static_cast<decltype(proxy.port)>(
              atoi(std::string(url_match[6]).c_str()));
        if (!protocol.empty() && !proxy.host.empty()) {
          proxy.address.clear();
          proxy.address.append(protocol)
              .append("://")
              .append(proxy.host)
              .append(":")
              .append(std::to_string(proxy.port));
        }
      } while (0);

    } while (0);
    do { //!@ .startup_envs
      if (!doc.HasMember("startup_envs"))
        break;
      if (!doc["startup_envs"].IsArray())
        break;

      for (auto it = doc["startup_envs"].Begin();
           it != doc["startup_envs"].End(); ++it) {
        if (!it->IsObject())
          break;
        auto &obj = *it;
        std::string key, value;
        if (obj.HasMember("key") && obj["key"].IsString() &&
            obj["key"].GetStringLength() > 0) {
          key = obj["key"].GetString();
          /*do {
                          if (key.empty())
                                          break;
                          if (*key.begin() == '-')
                                          key.erase(key.begin());
                          else
                                          break;
          } while (1);*/
          // std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        }
        if (obj.HasMember("value") && obj["value"].IsString() &&
            obj["value"].GetStringLength() > 0) {
          value = obj["value"].GetString();
        }
        if (!key.empty() && !value.empty()) {
          startup_envs.emplace(key, value);
        }
      }
    } while (0);
    do { //!@ .startup_args
      if (!doc.HasMember("startup_args"))
        break;
      if (!doc["startup_args"].IsArray())
        break;

      for (auto it = doc["startup_args"].Begin();
           it != doc["startup_args"].End(); ++it) {
        if (!it->IsObject())
          break;
        auto &obj = *it;
        std::string key, value;
        if (obj.HasMember("key") && obj["key"].IsString() &&
            obj["key"].GetStringLength() > 0) {
          key = obj["key"].GetString();
          /*do {
                          if (key.empty())
                                          break;
                          if (*key.begin() == '-')
                                          key.erase(key.begin());
                          else
                                          break;
          } while (1);*/
          // std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        }
        if (obj.HasMember("value") && obj["value"].IsString() &&
            obj["value"].GetStringLength() > 0) {
          value = obj["value"].GetString();
        }
        if (!key.empty()) {
          startup_args.emplace(key, value);
        }
      }
    } while (0);
    do { //!@ .jss
      if (!doc.HasMember("jss"))
        break;
      if (!doc["jss"].IsObject())
        break;
      auto &jssObj = doc["jss"];
      if (jssObj.HasMember("enable") && jssObj["enable"].IsBool()) {
        jss.enable = jssObj["enable"].GetBool();
      }
      if (jssObj.HasMember("source") && jssObj["source"].IsObject()) {
        for (auto it = jssObj["source"].MemberBegin();
             it != jssObj["source"].MemberEnd(); ++it) {
          if (!it->name.IsString())
            break;
          if (!it->value.IsString())
            break;
          if (it->value.GetStringLength() <= 0)
            continue;
          std::string name = it->name.GetString();
          std::transform(name.begin(), name.end(), name.begin(), ::tolower);
          jss.source.emplace(name, it->value.GetString());
        }
      }

    } while (0);
    do { //!@ .fps
      if (!doc.HasMember("fps"))
        break;
      if (!doc["fps"].IsObject())
        break;
      auto &fpsObj = doc["fps"];
      do { //!@ .fps.enable
        if (!fpsObj.HasMember("enable"))
          break;
        if (!fpsObj["enable"].IsBool())
          break;
        fps.enable = fpsObj["enable"].GetBool();
      } while (0);
      do {
        if (!fpsObj.HasMember("3rd"))
          break;
        if (!fpsObj["3rd"].IsObject())
          break;
        fps.thrid_party << fpsObj["3rd"];
      } while (0);
      do { //!@ .fps.enable_do_not_track
        if (!fpsObj.HasMember("enable_do_not_track"))
          break;
        if (!fpsObj["enable_do_not_track"].IsString())
          break;
        fps.enable_do_not_track = fpsObj["enable_do_not_track"].GetString();
      } while (0);
      do { //!@ .fps.platform
        if (!fpsObj.HasMember("platform"))
          break;
        if (!fpsObj["platform"].IsString())
          break;
        fps.platform = fpsObj["platform"].GetString();
      } while (0);
      do { //!@ .fps.userAgent
        if (!fpsObj.HasMember("userAgent"))
          break;
        if (!fpsObj["userAgent"].IsString())
          break;
        if (fpsObj["userAgent"].GetStringLength() <= 0)
          break;
        fps.userAgent = fpsObj["userAgent"].GetString();
      } while (0);
      do { //!@ .fps.hardwareConcurrency
        if (!fpsObj.HasMember("hardwareConcurrency"))
          break;
        if (!fpsObj["hardwareConcurrency"].IsUint())
          break;
        fps.hardwareConcurrency =
            static_cast<decltype(fps.hardwareConcurrency)>(
                fpsObj["hardwareConcurrency"].GetUint());
      } while (0);
      do { //!@ .fps.deviceMemory
        if (!fpsObj.HasMember("deviceMemory"))
          break;
        if (!fpsObj["deviceMemory"].IsUint64())
          break;
        fps.deviceMemory = fpsObj["deviceMemory"].GetUint64();
      } while (0);
      do { //!@ .fps.navigator
        if (!fpsObj.HasMember("navigator"))
          break;
        if (!fpsObj["navigator"].IsObject())
          break;
        fps.navigator << fpsObj["navigator"];

      } while (0);
      do { //!@ .fps.font
        if (!fpsObj.HasMember("font"))
          break;
        if (!fpsObj["font"].IsObject())
          break;
        if (fpsObj["font"].HasMember("enable") &&
            fpsObj["font"]["enable"].IsBool())
          fps.font.enable = fpsObj["font"]["enable"].GetBool();
        if (fpsObj["font"].HasMember("keywords") &&
            fpsObj["font"]["keywords"].IsArray()) {
          for (auto it = fpsObj["font"]["keywords"].Begin();
               it != fpsObj["font"]["keywords"].End(); ++it) {
            if (!it->IsString())
              break;
            if (it->GetStringLength() <= 0)
              continue;
            Fps::Font::Keyword keyword;
            keyword.value = it->GetString();
            keyword.key = keyword.value;
            std::transform(keyword.key.begin(), keyword.key.end(),
                           keyword.key.begin(), ::tolower);
            fps.font.keywords.emplace(keyword);
          }
        }
        if (fpsObj["font"].HasMember("hash") &&
            fpsObj["font"]["hash"].IsObject()) {
          fps.font.hash << Json::toString(fpsObj["font"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.timezone
        if (!fpsObj.HasMember("timezone"))
          break;
        if (!fpsObj["timezone"].IsObject())
          break;
        if (fpsObj["timezone"].HasMember("enable") &&
            fpsObj["timezone"]["enable"].IsBool())
          fps.timezone.enable = fpsObj["timezone"]["enable"].GetBool();
        if (fpsObj["timezone"].HasMember("hash") &&
            fpsObj["timezone"]["hash"].IsObject()) {
          fps.timezone.hash << Json::toString(fpsObj["timezone"]["hash"]);
        }
        if (fpsObj["timezone"].HasMember("source") &&
            fpsObj["timezone"]["source"].IsObject()) {
          for (auto it = fpsObj["timezone"]["source"].MemberBegin();
               it != fpsObj["timezone"]["source"].MemberEnd(); ++it) {
            do {
              auto &keyObj = it->name;
              auto &valObj = it->value;
              if (!keyObj.IsString())
                continue;
              if (!valObj.IsObject())
                continue;
              if (!valObj.HasMember("id") || !valObj["id"].IsUint())
                break;
              Fps::Timezone::Source source(valObj["id"].GetUint(),
                                           keyObj.GetString());
              if (!valObj.HasMember("offset") || !valObj["offset"].IsInt())
                break;
              source.offset = static_cast<decltype(source.offset)>(
                  valObj["offset"].GetInt());
              if (!valObj.HasMember("description") &&
                  !valObj["description"].IsString())
                break;
              source.description = valObj["description"].GetString();
              fps.timezone.sources.emplace(source.id, source);
            } while (0);
          }
        }
      } while (0);
      do { //!@ .fps.canvas
        if (!fpsObj.HasMember("canvas"))
          break;
        if (!fpsObj["canvas"].IsObject())
          break;
        if (fpsObj["canvas"].HasMember("enable") &&
            fpsObj["canvas"]["enable"].IsBool())
          fps.canvas.enable = fpsObj["canvas"]["enable"].GetBool();
        if (fpsObj["canvas"].HasMember("hash") &&
            fpsObj["canvas"]["hash"].IsObject()) {
          fps.canvas.hash << Json::toString(fpsObj["canvas"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.audio
        if (!fpsObj.HasMember("audio"))
          break;
        if (!fpsObj["audio"].IsObject())
          break;
        if (fpsObj["audio"].HasMember("enable") &&
            fpsObj["audio"]["enable"].IsBool())
          fps.audio.enable = fpsObj["audio"]["enable"].GetBool();
        if (fpsObj["audio"].HasMember("hash") &&
            fpsObj["audio"]["hash"].IsObject()) {
          fps.audio.hash << Json::toString(fpsObj["audio"]["hash"]);
        }
      } while (0);
      do { //!@ .fps.webrtc
        if (!fpsObj.HasMember("webrtc"))
          break;
        if (!fpsObj["webrtc"].IsObject())
          break;
        fps.webrtc << fpsObj["webrtc"];
      } while (0);
      do { //!@ .fps.webgl
        if (!fpsObj.HasMember("webgl"))
          break;
        if (!fpsObj["webgl"].IsObject())
          break;
        if (fpsObj["webgl"].HasMember("enable") &&
            fpsObj["webgl"]["enable"].IsBool())
          fps.webgl.enable = fpsObj["webgl"]["enable"].GetBool();
        if (fpsObj["webgl"].HasMember("hash") &&
            fpsObj["webgl"]["hash"].IsObject()) {
          fps.webgl.hash << Json::toString(fpsObj["webgl"]["hash"]);
        }
        if (fpsObj["webgl"].HasMember("vendor") &&
            fpsObj["webgl"]["vendor"].IsString()) {
          fps.webgl.vendor = fpsObj["webgl"]["vendor"].GetString();
        }
        if (fpsObj["webgl"].HasMember("renderer") &&
            fpsObj["webgl"]["renderer"].IsString()) {
          fps.webgl.renderer = fpsObj["webgl"]["renderer"].GetString();
        }
        if (fpsObj["webgl"].HasMember("driver_version") &&
            fpsObj["webgl"]["driver_version"].IsString()) {
          fps.webgl.driver_version =
              fpsObj["webgl"]["driver_version"].GetString();
        }
        if (fpsObj["webgl"].HasMember("version") &&
            fpsObj["webgl"]["version"].IsString()) {
          fps.webgl.version = fpsObj["webgl"]["version"].GetString();
        }
        if (fpsObj["webgl"].HasMember("shaderPrecisionFormat") &&
            fpsObj["webgl"]["shaderPrecisionFormat"].IsObject()) {
          for (auto it = fpsObj["webgl"]["shaderPrecisionFormat"].MemberBegin();
               it != fpsObj["webgl"]["shaderPrecisionFormat"].MemberEnd();
               ++it) {
            if (!it->name.IsString())
              break;
            if (!it->value.IsObject())
              break;
            if (it->name.GetStringLength() <= 0)
              continue;
            std::string name = it->name.GetString();
            Fps::Webgl::ShaderPrecisionFormat::SharedType sharedType =
                Fps::Webgl::ShaderPrecisionFormat::SharedType(
                    strtoul(name.c_str(), nullptr, 16));
            switch (sharedType) {
            case Fps::Webgl::ShaderPrecisionFormat::SharedType::FRAGMENT_SHADER:
            case Fps::Webgl::ShaderPrecisionFormat::SharedType::VERTEX_SHADER:
              for (auto it2 = it->value.MemberBegin();
                   it2 != it->value.MemberEnd(); ++it2) {
                if (!it2->name.IsString())
                  continue;
                if (!it2->value.IsObject())
                  continue;
                if (it2->name.GetStringLength() <= 0)
                  continue;
                if (!it2->value.HasMember("rangeMin") ||
                    !it2->value["rangeMin"].IsInt())
                  continue;
                if (!it2->value.HasMember("rangeMax") ||
                    !it2->value["rangeMax"].IsInt())
                  continue;
                if (!it2->value.HasMember("precision") ||
                    !it2->value["precision"].IsInt())
                  continue;

                std::string name2 = it2->name.GetString();
                Fps::Webgl::ShaderPrecisionFormat::FormatType format_type =
                    Fps::Webgl::ShaderPrecisionFormat::FormatType(
                        strtoul(name2.c_str(), nullptr, 16));
                switch (format_type) {
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::LOW_FLOAT:
                  if (sharedType == Fps::Webgl::ShaderPrecisionFormat::
                                        SharedType::FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_FLOAT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_FLOAT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_FLOAT
                        .precision = it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_FLOAT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_FLOAT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_FLOAT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::
                    MEDIUM_FLOAT:
                  if (sharedType == Fps::Webgl::ShaderPrecisionFormat::
                                        SharedType::FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_FLOAT.rangeMin =
                        it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_FLOAT.rangeMax =
                        it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_FLOAT.precision =
                        it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader
                        .MEDIUM_FLOAT.rangeMin =
                        it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader
                        .MEDIUM_FLOAT.rangeMax =
                        it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader
                        .MEDIUM_FLOAT.precision =
                        it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::HIGH_FLOAT:
                  if (sharedType == Fps::Webgl::ShaderPrecisionFormat::
                                        SharedType::FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .HIGH_FLOAT.rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .HIGH_FLOAT.rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .HIGH_FLOAT.precision =
                        it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_FLOAT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_FLOAT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_FLOAT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::LOW_INT:
                  if (sharedType == Fps::Webgl::ShaderPrecisionFormat::
                                        SharedType::FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.LOW_INT
                        .precision = it2->value["precision"].GetInt();

                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.LOW_INT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::MEDIUM_INT:
                  if (sharedType == Fps::Webgl::ShaderPrecisionFormat::
                                        SharedType::FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_INT.rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_INT.rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader
                        .MEDIUM_INT.precision =
                        it2->value["precision"].GetInt();
                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.MEDIUM_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.MEDIUM_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.MEDIUM_INT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                case Fps::Webgl::ShaderPrecisionFormat::FormatType::HIGH_INT:
                  if (sharedType == Fps::Webgl::ShaderPrecisionFormat::
                                        SharedType::FRAGMENT_SHADER) {
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.HIGH_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.HIGH_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_fragment_shader.HIGH_INT
                        .precision = it2->value["precision"].GetInt();

                  } else {
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_INT
                        .rangeMin = it2->value["rangeMin"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_INT
                        .rangeMax = it2->value["rangeMax"].GetInt();
                    fps.webgl.shaderPrecisionFormat.gl_vertex_shader.HIGH_INT
                        .precision = it2->value["precision"].GetInt();
                  }
                  break;
                default:
                  break;
                }
              }
              break;
            default:
              break;
            }
          }
        }

        if (fpsObj["webgl"].HasMember("contextAttributes") &&
            fpsObj["webgl"]["contextAttributes"].IsObject()) {
          for (auto it = fpsObj["webgl"]["contextAttributes"].MemberBegin();
               it != fpsObj["webgl"]["contextAttributes"].MemberEnd(); ++it) {
            do {
              if (!it->name.IsString())
                break;
              if (!it->value.IsBool())
                break;
              if (it->name.GetStringLength() <= 0)
                break;
              std::string name = it->name.GetString();
              if (name.compare("desynchronized") == 0) {
                fps.webgl.contextAttributes.desynchronized =
                    it->value.GetBool();
              } else if (name.compare("failIfMajorPerformanceCaveat") == 0) {
                fps.webgl.contextAttributes.failIfMajorPerformanceCaveat =
                    it->value.GetBool();
              } else if (name.compare("powerPreference") == 0) {
                fps.webgl.contextAttributes.powerPreference =
                    it->value.GetBool();
              } else if (name.compare("premultipliedAlpha") == 0) {
                fps.webgl.contextAttributes.premultipliedAlpha =
                    it->value.GetBool();
              } else if (name.compare("preserveDrawingBuffer") == 0) {
                fps.webgl.contextAttributes.preserveDrawingBuffer =
                    it->value.GetBool();
              } else if (name.compare("stencil") == 0) {
                fps.webgl.contextAttributes.stencil = it->value.GetBool();
              } else if (name.compare("alpha") == 0) {
                fps.webgl.contextAttributes.alpha = it->value.GetBool();
              } else if (name.compare("antialias") == 0) {
                fps.webgl.contextAttributes.antialias = it->value.GetBool();
              } else if (name.compare("depth") == 0) {
                fps.webgl.contextAttributes.depth = it->value.GetBool();
              } else if (name.compare("xrCompatible") == 0) {
                fps.webgl.contextAttributes.xrCompatible = it->value.GetBool();
              } else {
              }
            } while (0);
          }
        }
        if (fpsObj["webgl"].HasMember("enabledExtensions") &&
            fpsObj["webgl"]["enabledExtensions"].IsArray()) {
          for (auto it = fpsObj["webgl"]["enabledExtensions"].Begin();
               it != fpsObj["webgl"]["enabledExtensions"].End(); ++it) {
            if (!it->IsString())
              break;
            if (it->GetStringLength() <= 0)
              continue;
            std::string value = it->GetString();
            std::transform(value.begin(), value.end(), value.begin(),
                           ::tolower);
            fps.webgl.enabledExtensions.emplace(value);
          }
        }
        if (fpsObj["webgl"].HasMember("parameters") &&
            fpsObj["webgl"]["parameters"].IsObject()) {
          for (auto it = fpsObj["webgl"]["parameters"].MemberBegin();
               it != fpsObj["webgl"]["parameters"].MemberEnd(); ++it) {
            do {
              if (!it->name.IsString())
                break;
              if (!it->value.IsString())
                break;
              unsigned int key = static_cast<unsigned int>(
                  strtoul(it->name.GetString(), nullptr, 10));
              std::string value;
              if (it->value.GetStringLength() > 0)
                value = it->value.GetString();
              auto f = fps.webgl.parameters.find(key);
              if (f != fps.webgl.parameters.end())
                fps.webgl.parameters.erase(f);
              fps.webgl.parameters.emplace(key, value);
            } while (0);
          }
        }
      } while (0);
      do { //!@ .fps.screen
        if (!fpsObj.HasMember("screen"))
          break;
        if (!fpsObj["screen"].IsObject())
          break;
        if (fpsObj["screen"].HasMember("enable") &&
            fpsObj["screen"]["enable"].IsBool())
          fps.screen.enable = fpsObj["screen"]["enable"].GetBool();
        if (fpsObj["screen"].HasMember("height") &&
            fpsObj["screen"]["height"].IsInt()) {
          fps.screen.height = fpsObj["screen"]["height"].GetInt();
        }
        if (fpsObj["screen"].HasMember("width") &&
            fpsObj["screen"]["width"].IsInt()) {
          fps.screen.width = fpsObj["screen"]["width"].GetInt();
        }
        if (fpsObj["screen"].HasMember("colorDepth") &&
            fpsObj["screen"]["colorDepth"].IsInt()) {
          fps.screen.colorDepth = fpsObj["screen"]["colorDepth"].GetInt();
        }
        if (fpsObj["screen"].HasMember("pixelDepth") &&
            fpsObj["screen"]["pixelDepth"].IsInt()) {
          fps.screen.pixelDepth = fpsObj["screen"]["pixelDepth"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availLeft") &&
            fpsObj["screen"]["availLeft"].IsInt()) {
          fps.screen.availLeft = fpsObj["screen"]["availLeft"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availTop") &&
            fpsObj["screen"]["availTop"].IsInt()) {
          fps.screen.availTop = fpsObj["screen"]["availTop"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availHeight") &&
            fpsObj["screen"]["availHeight"].IsInt()) {
          fps.screen.availHeight = fpsObj["screen"]["availHeight"].GetInt();
        }
        if (fpsObj["screen"].HasMember("availWidth") &&
            fpsObj["screen"]["availWidth"].IsInt()) {
          fps.screen.availWidth = fpsObj["screen"]["availWidth"].GetInt();
        }
        if (fpsObj["screen"].HasMember("devicePixelRatio") &&
            fpsObj["screen"]["devicePixelRatio"].IsDouble()) {
          fps.screen.devicePixelRatio =
              fpsObj["screen"]["devicePixelRatio"].GetDouble();
        }
      } while (0);

      Final();
    } while (0);
    success = true;
  } while (0);
  if (!success)
    doc.SetObject();
}
///////////////////////////////////////////////////////////////////////////

inline IConfigure::Fps::ThridParty::ThridParty() {
}
inline IConfigure::Fps::ThridParty::~ThridParty() {
}
inline void IConfigure::Fps::ThridParty::operator=(const ThridParty &rhs) {
  permissionSimulation = rhs.permissionSimulation;
  webglCustomConfig = rhs.webglCustomConfig;
  speechVoice = rhs.speechVoice;
  mediaDevice = rhs.mediaDevice;
  geolocation = rhs.geolocation;
  clientRects = rhs.clientRects;
  clientHints = rhs.clientHints;
  canvas = rhs.canvas;
  audioNoise = rhs.audioNoise;
  languages = rhs.languages;
  tls = rhs.tls;
  webrtc = rhs.webrtc;
  screenSize = rhs.screenSize;
  fontsFull = rhs.fontsFull;
  storage = rhs.storage;
  id = rhs.id;
  cpu = rhs.cpu;
  dnt = rhs.dnt;
  colorDepth = rhs.colorDepth;
  appCodeName = rhs.appCodeName;
  userDataDir = rhs.userDataDir;
  windowWidth = rhs.windowWidth;
  batteryLevel = rhs.batteryLevel;
  deviceMemory = rhs.deviceMemory;
  windowHeight = rhs.windowHeight;
  acceptLanguage = rhs.acceptLanguage;
  batteryCharging = rhs.batteryCharging;
  devicePixelRatio = rhs.devicePixelRatio;
  fontsFullEnabled = rhs.fontsFullEnabled;
  batteryChargingTime = rhs.batteryChargingTime;
  windowTitleBarHeight = rhs.windowTitleBarHeight;
  batteryDischargingTime = rhs.batteryDischargingTime;
  appName = rhs.appName;
  fontDir = rhs.fontDir;
  product = rhs.product;
  platform = rhs.platform;
  timezone = rhs.timezone;
  userAgent = rhs.userAgent;
  appVersion = rhs.appVersion;
  socks5 = rhs.socks5;
  vendor = rhs.vendor;
}
inline IConfigure::Fps::ThridParty::PermissionSimulation::
    PermissionSimulation() {
}
inline IConfigure::Fps::ThridParty::PermissionSimulation::
    ~PermissionSimulation() {
}
inline IConfigure::Fps::ThridParty::Storage::Storage() {
}
inline IConfigure::Fps::ThridParty::Storage::~Storage() {
}
inline IConfigure::Fps::ThridParty::FontsFull::FontsFull() {
}
inline IConfigure::Fps::ThridParty::FontsFull::~FontsFull() {
}
inline IConfigure::Fps::ThridParty::ScreenSize::ScreenSize() {
}
inline IConfigure::Fps::ThridParty::ScreenSize::~ScreenSize() {
}
inline IConfigure::Fps::ThridParty::Webrtc::Webrtc() {
}
inline IConfigure::Fps::ThridParty::Webrtc::~Webrtc() {
}
inline IConfigure::Fps::ThridParty::Tls::Tls() {
}
inline IConfigure::Fps::ThridParty::Tls::~Tls() {
}
inline IConfigure::Fps::ThridParty::AudioNoise::AudioNoise() {
}
inline IConfigure::Fps::ThridParty::AudioNoise::~AudioNoise() {
}
inline IConfigure::Fps::ThridParty::Canvas::Canvas() {
}
inline IConfigure::Fps::ThridParty::Canvas::~Canvas() {
}
inline IConfigure::Fps::ThridParty::ClientHints::ClientHints() {
}
inline IConfigure::Fps::ThridParty::ClientHints::~ClientHints() {
}
inline IConfigure::Fps::ThridParty::ClientRects::ClientRects() {
}
inline IConfigure::Fps::ThridParty::ClientRects::~ClientRects() {
}
inline IConfigure::Fps::ThridParty::Geolocation::Geolocation() {
}
inline IConfigure::Fps::ThridParty::Geolocation::~Geolocation() {
}
inline IConfigure::Fps::ThridParty::MediaDevice::AudioOutputs::AudioOutputs() {
}
inline IConfigure::Fps::ThridParty::MediaDevice::AudioOutputs::~AudioOutputs() {
}
inline IConfigure::Fps::ThridParty::MediaDevice::MediaDevice() {
}
inline IConfigure::Fps::ThridParty::MediaDevice::~MediaDevice() {
}
inline IConfigure::Fps::ThridParty::WebglCustomConfig::WebglCustomConfig() {
}
inline IConfigure::Fps::ThridParty::WebglCustomConfig::~WebglCustomConfig() {
}
inline IConfigure::Fps::ThridParty::SpeechVoice::Voices::Voices() {
}
inline IConfigure::Fps::ThridParty::SpeechVoice::Voices::~Voices() {
}
inline IConfigure::Fps::ThridParty::SpeechVoice::Voices::Voices(
    const Voices &obj) {
  *this = obj;
}
inline void
IConfigure::Fps::ThridParty::SpeechVoice::Voices::operator=(const Voices &obj) {
  lang = obj.lang;
  name = obj.name;
  default_ = obj.default_;
  voiceURI = obj.voiceURI;
  localService = obj.localService;
}

inline IConfigure::Fps::ThridParty::SpeechVoice::SpeechVoice() {
}
inline IConfigure::Fps::ThridParty::SpeechVoice::~SpeechVoice() {
}
inline bool
IConfigure::Fps::ThridParty::operator<<(const rapidjson::Value &obj) {
  bool result = false;
  do {
    if (!obj.IsObject())
      break;
    if (obj.HasMember("id") && obj["id"].IsString())
      id = obj["id"].GetString();
    if (obj.HasMember("cpu") && obj["cpu"].IsUint())
      cpu = obj["cpu"].GetUint();
    if (obj.HasMember("dnt") && obj["dnt"].IsString())
      dnt = obj["dnt"].GetString();
    if (obj.HasMember("colorDepth") && obj["colorDepth"].IsInt())
      colorDepth = obj["colorDepth"].GetInt();
    if (obj.HasMember("appCodeName") && obj["appCodeName"].IsString())
      appCodeName = obj["appCodeName"].GetString();
    if (obj.HasMember("userDataDir") && obj["userDataDir"].IsString())
      userDataDir = obj["userDataDir"].GetString();
    if (obj.HasMember("windowWidth") && obj["windowWidth"].IsInt())
      windowWidth = obj["windowWidth"].GetInt();
    if (obj.HasMember("windowHeight") && obj["windowHeight"].IsInt())
      windowHeight = obj["windowHeight"].GetInt();
    if (obj.HasMember("batteryLevel") && obj["batteryLevel"].IsInt())
      batteryLevel = obj["batteryLevel"].GetInt();
    if (obj.HasMember("deviceMemory") && obj["deviceMemory"].IsUint())
      deviceMemory = obj["deviceMemory"].GetUint();
    if (obj.HasMember("acceptLanguage") && obj["acceptLanguage"].IsString())
      acceptLanguage = obj["acceptLanguage"].GetString();
    if (obj.HasMember("batteryCharging") && obj["batteryCharging"].IsBool())
      batteryCharging = obj["batteryCharging"].GetBool();
    if (obj.HasMember("devicePixelRatio")) {
      if (obj["devicePixelRatio"].IsDouble())
        devicePixelRatio = obj["devicePixelRatio"].GetDouble();
      else if (obj["devicePixelRatio"].IsInt())
        devicePixelRatio = obj["devicePixelRatio"].GetInt() * 1.0f;
    }
    if (obj.HasMember("fontsFullEnabled") && obj["fontsFullEnabled"].IsBool())
      fontsFullEnabled = obj["fontsFullEnabled"].GetBool();
    if (obj.HasMember("batteryChargingTime") &&
        obj["batteryChargingTime"].IsInt())
      batteryChargingTime = obj["batteryChargingTime"].GetInt();
    if (obj.HasMember("windowTitleBarHeight") &&
        obj["windowTitleBarHeight"].IsInt())
      windowTitleBarHeight = obj["windowTitleBarHeight"].GetInt();
    if (obj.HasMember("batteryDischargingTime") &&
        obj["batteryDischargingTime"].IsInt())
      batteryDischargingTime = obj["batteryDischargingTime"].GetInt();
    if (obj.HasMember("appName") && obj["appName"].IsString())
      appName = obj["appName"].GetString();
    if (obj.HasMember("fontDir") && obj["fontDir"].IsString())
      fontDir = obj["fontDir"].GetString();
    if (obj.HasMember("product") && obj["product"].IsString())
      product = obj["product"].GetString();
    if (obj.HasMember("platform") && obj["platform"].IsString())
      platform = obj["platform"].GetString();
    if (obj.HasMember("timezone") && obj["timezone"].IsString())
      timezone = obj["timezone"].GetString();
    if (obj.HasMember("userAgent") && obj["userAgent"].IsString())
      userAgent = obj["userAgent"].GetString();
    if (obj.HasMember("appVersion") && obj["appVersion"].IsString())
      appVersion = obj["appVersion"].GetString();
    if (obj.HasMember("socks5") && obj["socks5"].IsString())
      socks5 = obj["socks5"].GetString();
    if (obj.HasMember("vendor") && obj["vendor"].IsString())
      vendor = obj["vendor"].GetString();
    if (obj.HasMember("tls") && obj["tls"].IsObject()) {
      auto &tlsObj = obj["tls"];
      if (tlsObj.HasMember("enabled") && tlsObj["enabled"].IsBool())
        tls.enabled = tlsObj["enabled"].GetBool();
      if (tlsObj.HasMember("seed") && tlsObj["seed"].IsUint64()) {
        tls.seed = tlsObj["seed"].GetUint64();
      }
    }
    if (obj.HasMember("webrtc") && obj["webrtc"].IsObject()) {
      auto &webrtcObj = obj["webrtc"];
      if (webrtcObj.HasMember("enabled") && webrtcObj["enabled"].IsBool())
        webrtc.enabled = webrtcObj["enabled"].GetBool();
      if (webrtcObj.HasMember("localIP") && webrtcObj["localIP"].IsString())
        webrtc.localIP = webrtcObj["localIP"].GetString();
      if (webrtcObj.HasMember("publicIP") && webrtcObj["publicIP"].IsString())
        webrtc.publicIP = webrtcObj["publicIP"].GetString();
    }
    if (obj.HasMember("storage") && obj["storage"].IsObject()) {
      auto &storageObj = obj["storage"];
      if (storageObj.HasMember("enabled") && storageObj["enabled"].IsBool())
        storage.enabled = storageObj["enabled"].GetBool();
      if (storageObj.HasMember("quota") && storageObj["quota"].IsUint64())
        storage.quota = storageObj["quota"].GetUint64();
      if (storageObj.HasMember("usage") && storageObj["usage"].IsInt())
        storage.usage = storageObj["usage"].GetInt();
    }
    if (obj.HasMember("fontsFull") && obj["fontsFull"].IsArray()) {
    }
    if (obj.HasMember("languages") && obj["languages"].IsArray()) {
      for (auto it = obj["languages"].Begin(); it != obj["languages"].End();
           ++it) {
        if (!it->IsString())
          break;
        if (it->GetStringLength() <= 0)
          continue;
        std::string value = it->GetString();
        languages.emplace(value);
      }
    }
    if (obj.HasMember("audioNoise") && obj["audioNoise"].IsObject()) {
      auto &audioNoiseObj = obj["audioNoise"];
      if (audioNoiseObj.HasMember("enabled") &&
          audioNoiseObj["enabled"].IsBool())
        audioNoise.enabled = audioNoiseObj["enabled"].GetBool();
      if (audioNoiseObj.HasMember("sumStep") &&
          audioNoiseObj["sumStep"].IsInt()) {
        audioNoise.sumStep = audioNoiseObj["sumStep"].GetInt();
      }
      if (audioNoiseObj.HasMember("freqStep") &&
          audioNoiseObj["freqStep"].IsInt()) {
        audioNoise.freqStep = audioNoiseObj["freqStep"].GetInt();
      }
      if (audioNoiseObj.HasMember("sumNoise") &&
          audioNoiseObj["sumNoise"].IsDouble()) {
        audioNoise.sumNoise = audioNoiseObj["sumNoise"].GetDouble();
      }
      if (audioNoiseObj.HasMember("freqNoise") &&
          audioNoiseObj["freqNoise"].IsDouble()) {
        audioNoise.freqNoise = audioNoiseObj["freqNoise"].GetDouble();
      }
      if (audioNoiseObj.HasMember("gainNoise") &&
          audioNoiseObj["gainNoise"].IsDouble()) {
        audioNoise.gainNoise = audioNoiseObj["gainNoise"].GetDouble();
      }

      if (audioNoiseObj.HasMember("timeDomainNoise") &&
          audioNoiseObj["timeDomainNoise"].IsDouble()) {
        audioNoise.timeDomainNoise =
            audioNoiseObj["timeDomainNoise"].GetDouble();
      }
    }
    if (obj.HasMember("canvas") && obj["canvas"].IsObject()) {
      auto &canvasObj = obj["canvas"];
      if (canvasObj.HasMember("enabled") && canvasObj["enabled"].IsBool())
        canvas.enabled = canvasObj["enabled"].GetBool();
      if (canvasObj.HasMember("alpha") && canvasObj["alpha"].IsInt())
        canvas.alpha = canvasObj["alpha"].GetInt();
      if (canvasObj.HasMember("colorDisturbedValue") &&
          canvasObj["colorDisturbedValue"].IsInt())
        canvas.colorDisturbedValue = canvasObj["colorDisturbedValue"].GetInt();
      if (canvasObj.HasMember("widthRandPercent") &&
          canvasObj["widthRandPercent"].IsDouble())
        canvas.widthRandPercent = canvasObj["widthRandPercent"].GetDouble();
      if (canvasObj.HasMember("heightRandPercent") &&
          canvasObj["heightRandPercent"].IsDouble())
        canvas.heightRandPercent = canvasObj["heightRandPercent"].GetDouble();
    }
    if (obj.HasMember("clientHints") && obj["clientHints"].IsObject()) {
      auto &clientHintsObj = obj["clientHints"];
      if (clientHintsObj.HasMember("wow64") && clientHintsObj["wow64"].IsBool())
        clientHints.wow64 = clientHintsObj["wow64"].GetBool();
      if (clientHintsObj.HasMember("isMobile") &&
          clientHintsObj["isMobile"].IsBool())
        clientHints.isMobile = clientHintsObj["isMobile"].GetBool();
      if (clientHintsObj.HasMember("bit") && clientHintsObj["bit"].IsString()) {
        clientHints.bit = clientHintsObj["bit"].GetString();
      }
      if (clientHintsObj.HasMember("arch") &&
          clientHintsObj["arch"].IsString()) {
        clientHints.arch = clientHintsObj["arch"].GetString();
      }
      if (clientHintsObj.HasMember("model") &&
          clientHintsObj["model"].IsString()) {
        clientHints.model = clientHintsObj["model"].GetString();
      }
      if (clientHintsObj.HasMember("platform") &&
          clientHintsObj["platform"].IsString()) {
        clientHints.platform = clientHintsObj["platform"].GetString();
      }
      if (clientHintsObj.HasMember("fullVersion") &&
          clientHintsObj["fullVersion"].IsString()) {
        clientHints.fullVersion = clientHintsObj["fullVersion"].GetString();
      }
      if (clientHintsObj.HasMember("platformVersion") &&
          clientHintsObj["platformVersion"].IsString()) {
        clientHints.platformVersion =
            clientHintsObj["platformVersion"].GetString();
      }
      if (clientHintsObj.HasMember("brandVersions") &&
          clientHintsObj["brandVersions"].IsArray()) {
      }
    }
    if (obj.HasMember("clientRects") && obj["clientRects"].IsObject()) {
      auto &clientRectsObj = obj["clientRects"];
      if (clientRectsObj.HasMember("enabled") &&
          clientRectsObj["enabled"].IsBool())
        clientRects.enabled = clientRectsObj["enabled"].GetBool();
      if (clientRectsObj.HasMember("scale") &&
          clientRectsObj["scale"].IsDouble())
        clientRects.scale = clientRectsObj["scale"].GetDouble();
    }
    if (obj.HasMember("geolocation") && obj["geolocation"].IsObject()) {
      auto &geolocationObj = obj["geolocation"];
      if (geolocationObj.HasMember("enabled") &&
          geolocationObj["enabled"].IsBool())
        geolocation.enabled = geolocationObj["enabled"].GetBool();
      if (geolocationObj.HasMember("accuracy") &&
          geolocationObj["accuracy"].IsDouble()) {
        geolocation.accuracy = geolocationObj["accuracy"].GetDouble();
      }
      if (geolocationObj.HasMember("latitude") &&
          geolocationObj["latitude"].IsDouble()) {
        geolocation.latitude = geolocationObj["latitude"].GetDouble();
      }
      if (geolocationObj.HasMember("longitude") &&
          geolocationObj["longitude"].IsDouble()) {
        geolocation.longitude = geolocationObj["longitude"].GetDouble();
      }
    }
    if (obj.HasMember("permissionSimulation") &&
        obj["permissionSimulation"].IsObject()) {
      auto &permissionSimulationObj = obj["permissionSimulation"];
      if (permissionSimulationObj.HasMember("maxDelay") &&
          permissionSimulationObj["maxDelay"].IsInt()) {
        permissionSimulation.maxDelay =
            permissionSimulationObj["maxDelay"].GetInt();
      }
      if (permissionSimulationObj.HasMember("oddsGrant") &&
          permissionSimulationObj["oddsGrant"].IsInt()) {
        permissionSimulation.oddsGrant =
            permissionSimulationObj["oddsGrant"].GetInt();
      }
      if (permissionSimulationObj.HasMember("oddsCancel") &&
          permissionSimulationObj["oddsCancel"].IsInt()) {
        permissionSimulation.oddsCancel =
            permissionSimulationObj["oddsCancel"].GetInt();
      }
      if (permissionSimulationObj.HasMember("oddsRefuse") &&
          permissionSimulationObj["oddsRefuse"].IsInt()) {
        permissionSimulation.oddsRefuse =
            permissionSimulationObj["oddsRefuse"].GetInt();
      }
      if (permissionSimulationObj.HasMember("minDelay") &&
          permissionSimulationObj["minDelay"].IsDouble()) {
        permissionSimulation.minDelay =
            permissionSimulationObj["minDelay"].GetDouble();
      }
    }
    if (obj.HasMember("webglCustomConfig") &&
        obj["webglCustomConfig"].IsObject()) {
      auto &webglCustomConfigObj = obj["webglCustomConfig"];
      if (webglCustomConfigObj.HasMember("webglVendor") &&
          webglCustomConfigObj["webglVendor"].IsString()) {
        webglCustomConfig.webglVendor =
            webglCustomConfigObj["webglVendor"].GetString();
      }
      if (webglCustomConfigObj.HasMember("webglRenderer") &&
          webglCustomConfigObj["webglRenderer"].IsString()) {
        webglCustomConfig.webglRenderer =
            webglCustomConfigObj["webglRenderer"].GetString();
      }
      if (webglCustomConfigObj.HasMember("webglCustomEnabled") &&
          webglCustomConfigObj["webglCustomEnabled"].IsBool()) {
        webglCustomConfig.webglCustomEnabled =
            webglCustomConfigObj["webglCustomEnabled"].GetBool();
      }
    }
    if (obj.HasMember("mediaDevice") && obj["mediaDevice"].IsObject()) {
      auto &mediaDeviceObj = obj["mediaDevice"];
      if (mediaDeviceObj.HasMember("enabled") &&
          mediaDeviceObj["enabled"].IsBool())
        mediaDevice.enabled = mediaDeviceObj["enabled"].GetBool();
    }
    if (obj.HasMember("speechVoice") && obj["speechVoice"].IsObject()) {
      // auto& speechVoiceObj = obj["speechVoice"];
    }
    result = true;
  } while (0);
  return result;
}
inline void IConfigure::Final() {
  do { //!@ fps_use3rd
    if (!fps_use3rd)
      break;
    if (fps.thrid_party.cpu > 0) {
      fps.hardwareConcurrency =
          static_cast<decltype(fps.hardwareConcurrency)>(fps.thrid_party.cpu);
    }
    if (fps.thrid_party.deviceMemory > 0) {
      fps.deviceMemory = static_cast<decltype(fps.deviceMemory)>(
          fps.thrid_party.deviceMemory * 1024 * 1024 * 1024);
    }
    if (!fps.thrid_party.userAgent.empty()) {
      fps.userAgent = fps.thrid_party.userAgent;
    }
    if (!fps.thrid_party.platform.empty()) {
      fps.platform = fps.thrid_party.platform;
    }
    if (!fps.thrid_party.dnt.empty()) {
      fps.enable_do_not_track = fps.thrid_party.dnt;
    }
    if (fps.thrid_party.devicePixelRatio > 0) {
      fps.screen.devicePixelRatio = fps.thrid_party.devicePixelRatio;
    }
    if (fps.thrid_party.windowHeight > 0) {
      fps.screen.height = fps.thrid_party.windowHeight;
    }
    if (fps.thrid_party.windowWidth > 0) {
      fps.screen.width = fps.thrid_party.windowWidth;
    }
    if (fps.thrid_party.colorDepth > 0) {
      fps.screen.colorDepth = static_cast<decltype(fps.screen.colorDepth)>(
          fps.thrid_party.colorDepth);
    }
    if (!fps.thrid_party.webglCustomConfig.webglVendor.empty()) {
      fps.webgl.parameters[37445] =
          fps.thrid_party.webglCustomConfig.webglVendor;
    }
    if (!fps.thrid_party.webglCustomConfig.webglRenderer.empty()) {
      fps.webgl.parameters[37446] =
          fps.thrid_party.webglCustomConfig.webglRenderer;
    }
    if (!fps.thrid_party.timezone.empty()) {
      for (const auto &it : fps.timezone.sources) {
        if (it.second.name == fps.thrid_party.timezone) {
          fps.timezone.enable = true;
          fps.timezone.hash.random = false;
          fps.timezone.hash.base =
              static_cast<decltype(fps.timezone.hash.base)>(it.first);
          break;
        }
      }
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////
inline IConfigure::Request::Request() {
}
inline IConfigure::Request::Request(const Request &obj) {
  *this = obj;
}
inline IConfigure::Request::~Request() {
}
inline void IConfigure::Request::operator=(const Request &obj) {
  enable = obj.enable;
  id = obj.id;
  command = obj.command;
  enable = obj.enable;
}
inline void IConfigure::Request::operator<<(const rapidjson::Value &reqObj) {
  do {
    if (!reqObj.IsObject())
      break;
    if (reqObj.HasMember("enable") && reqObj["enable"].IsBool()) {
      enable = reqObj["enable"].GetBool();
    }
    if (reqObj.HasMember("id") && reqObj["id"].IsUint64()) {
      id = reqObj["id"].GetUint64();
    }
    if (reqObj.HasMember("command") && reqObj["command"].IsUint()) {
      command = reqObj["command"].GetUint();
    }
  } while (0);
}
///////////////////////////////////////////////////////////////////////////
inline std::string IConfigure::Serialization() const {
  return Json::toString(doc);
}
} // namespace chromium
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Feb 2025 13:22:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8B6326C0_93E4_49D8_BFC7_EB6C3BA59694__