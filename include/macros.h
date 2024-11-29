#ifndef MACROS_H
#define MACROS_H

#define __FUNCTION_BEGIN_TIME__ \
std::uint64_t _____begin_time_____ = GetTickCount64();

#define __FUNCTION_END_TIME__(r) \
do{\
LOG_INFO("{}({}) total time({}) ms.", __FUNCTION__, r,GetTickCount64() - _____begin_time_____);\
} while (0);

#define __CONSOLE_CODE_SEGMENT_BEGIN__ \
std::uint64_t _____console_code_segment_begin_time_____ = GetTickCount64()


#define __CONSOLE_CODE_SEGMENT_END__(name) \
std::cout<<name<<": total("<<GetTickCount64() - _____console_code_segment_begin_time_____ <<")(ms)"<< std::endl

#define __CODE_SEGMENT_BEGIN__ \
std::uint64_t _____console_code_segment_begin_time_____ = GetTickCount64()

#define __CODE_SEGMENT_END__(name) \
std::cout<<name<<": total("<<GetTickCount64() - _____console_code_segment_begin_time_____ <<")(ms)"<< std::endl


#define __NAME__(value) (#value)

#define ISNUL_POINT(pt) ((pt.x == 0) && (pt.y == 0))
#define ISNUL_POSITION(pos) ((pos.x == 0) && (pos.y == 0) &&(pos.cx==0) &&(pos.cy==0))
#define ISNUL_RECT(rt) \
(((rt.left == 0) && (rt.top == 0) && (rt.right == 0) && (rt.bottom == 0) || (rt.left<0 && rt.top<0 && rt.right<0 && rt.bottom<0)) || \
(rt.right-rt.left<=0) || (rt.bottom - rt.top <=0))

#define RECT_AREA(rt) ((rt.right - rt.left) * (rt.bottom - rt.top))
#define RECT_EQUAL(rt1,rt2) ((rt1.left==rt2.left)&&(rt1.top == rt2.top)&&(rt1.right == rt2.right)&&(rt1.bottom == rt2.bottom))
#define RECT_WIDTH(rt) (rt.right-rt.left)
#define RECT_HEIGHT(rt) (rt.bottom - rt.top)
#define POINT_EQUAL(pt1,pt2) ((pt1.x==pt2.x)&&(pt1.y==pt2.y))

#define MEMCPY_S(to, to_size,from, from_size) \
do{\
if(!from || from_size <= 0 || to_size<=0 || !to)\
break;\
memcpy(to, from, from_size > to_size ? to_size : from_size);\
} while (0);

#define WMEMCPY_S(to, to_size,from, from_size) \
do{\
if(!from || from_size <= 0 || to_size<=0 || !to)\
break;\
wmemcpy(to, from, from_size > to_size ? to_size : from_size);\
} while (0);


#define SK_FREE_PTR(p)                                                         \
  do {                                                                         \
    if (!p)                                                                    \
      break;                                                                   \
    free(p);                                                                   \
    p = nullptr;                                                               \
  } while (0);

#ifndef SK_DELETE_PTR
#define SK_DELETE_PTR(p)                                                       \
  do {                                                                         \
    if (!p)                                                                    \
      break;                                                                   \
    delete p;                                                                  \
    p = nullptr;                                                               \
  } while (0);
#endif

#ifndef SK_RELEASE_PTR
#define SK_RELEASE_PTR(p)                                                      \
  do {                                                                         \
    if (!p)                                                                    \
      break;                                                                   \
    p->Release();                                                              \
    p = nullptr;                                                               \
  } while (0);
#endif


#define SK_WIN_HANDLE_CLOSE(h) \
do{\
if (!h)\
break;\
CloseHandle(h);\
h = NULL;\
} while (0);

#define BOUNDING2RECT(bounding,rect) \
do{\
rect.left = static_cast<long>(bounding.x);\
rect.top = static_cast<long>(bounding.y);\
rect.right = static_cast<long>(bounding.x + bounding.cx);\
rect.bottom = static_cast<long>(bounding.y+ bounding.cy);\
} while (0);

#define RECT2BOUNDING(rect,bounding) \
do{\
bounding.x = rect.left;\
bounding.y = rect.top;\
bounding.cx = RECT_WIDTH(rect);\
bounding.cy = RECT_HEIGHT(rect);\
} while (0);

#define CVBOUNDING2RECT(bounding,rect) \
do{\
rect.left = static_cast<long>(bounding.x);\
rect.top = static_cast<long>(bounding.y);\
rect.right = static_cast<long>(bounding.x + bounding.width);\
rect.bottom = static_cast<long>(bounding.y+ bounding.height);\
} while (0);

#define RECT2CVBOUNDING(rect,bounding) \
do{\
bounding.x = rect.left;\
bounding.y = rect.top;\
bounding.width = RECT_WIDTH(rect);\
bounding.height = RECT_HEIGHT(rect);\
} while (0);

#define RECT2CVRECT(rect,bounding) RECT2CVBOUNDING(rect,bounding)
#define CVRECT2RECT(bounding,rect) CVBOUNDING2RECT(bounding,rect)
#define OCRBOUNDING2RECT(bounding,rect) CVBOUNDING2RECT(bounding,rect)
#define POSITION2RECT(pos,rect) BOUNDING2RECT(pos,rect)
#define RECT2POSITION(rect,pos) RECT2BOUNDING(rect,pos)
#endif // MACROS_H