#include "jsonnetcc.h"

Jsonnetcc::Jsonnetcc() {
  Init();
}
Jsonnetcc::~Jsonnetcc() {
  UnInit();
}
void Jsonnetcc::Init() {
  do {
    ready_.store(true);
  } while (0);
}
void Jsonnetcc::UnInit() {
  ready_.store(false);
}
bool Jsonnetcc::Ready() const {
  return ready_.load();
}
#if 0

#if 0
{
   "concat_array": [
      1,
      2,
      3,
      4
   ],
   "concat_string": "1234",
   "equality1": false,
   "equality2": true,
   "ex1": 1.6666666666666665,
   "ex2": 3,
   "ex3": 1.6666666666666665,
   "ex4": true,
   "obj": {
      "a": 1,
      "b": 3,
      "c": 4
   },
   "obj_member": true,
   "str1": "The value of self.ex2 is 3.",
   "str2": "The value of self.ex2 is 3.",
   "str3": "ex1=1.67, ex2=3.00",
   "str4": "ex1=1.67, ex2=3.00",
   "str5": "ex1=1.67\nex2=3.00\n"
}
#endif
    jsonnet::Jsonnet jobj;
    if (!jobj.init())
      break;
    std::string jOutput;
    if (!jobj.evaluateSnippet("666.jsonnet", R"({
  concat_array: [1, 2, 3] + [4],
  concat_string: '123' + 4,
  equality1: 1 == '1',
  equality2: [{}, { x: 3 - 1 }]
             == [{}, { x: 2 }],
  ex1: 1 + 2 * 3 / (4 + 5),
  // Bitwise operations first cast to int.
  ex2: self.ex1 | 3,
  // Modulo operator.
  ex3: self.ex1 % 2,
  // Boolean logic
  ex4: (4 > 3) && (1 <= 3) || false,
  // Mixing objects together
  obj: { a: 1, b: 2 } + { b: 3, c: 4 },
  // Test if a field is in an object
  obj_member: 'foo' in { foo: 1 },
  // String formatting
  str1: 'The value of self.ex2 is '
        + self.ex2 + '.',
  str2: 'The value of self.ex2 is %g.'
        % self.ex2,
  str3: 'ex1=%0.2f, ex2=%0.2f'
        % [self.ex1, self.ex2],
  // By passing self, we allow ex1 and ex2 to
  // be extracted internally.
  str4: 'ex1=%(ex1)0.2f, ex2=%(ex2)0.2f'
        % self,
  // Do textual templating of entire files:
  str5: |||
    ex1=%(ex1)0.2f
    ex2=%(ex2)0.2f
  ||| % self,
})",
                              &jOutput))
      break;
    std::string ver = jsonnet::Jsonnet::version();
    MessageBoxA(nullptr, jOutput.c_str(), nullptr, MB_TOPMOST);
    std::cout << jOutput << std::endl;
    log_info("jsonnet version '{}'", ver);
    log_info(jOutput);
    std::cout << fmt::format("jsonnet version '{}'", ver) << std::endl;

#endif

//////////////////////////////////////////////////////////////////////////////////////////
static Jsonnetcc *__gpJsonnetcc = nullptr;
Jsonnetcc *Jsonnetcc::Create() {
  if (!__gpJsonnetcc)
    __gpJsonnetcc = new Jsonnetcc();
  return __gpJsonnetcc;
}
void Jsonnetcc::Destroy() {
  SK_DELETE_PTR(__gpJsonnetcc);
}

#ifdef __cplusplus
extern "C" {
#endif
SHARED_API void *interface_init(void *data, unsigned long len) {
  Jsonnetcc::Create();
  if (!__gpJsonnetcc->Ready()) {
    Jsonnetcc::Destroy();
  }
  return dynamic_cast<IJsonnetcc *>(__gpJsonnetcc);
}
SHARED_API void interface_uninit() {
  Jsonnetcc::Destroy();
}
#ifdef __cplusplus
}
#endif
