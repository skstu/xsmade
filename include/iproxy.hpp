#if !defined(__EE38B74D_CE8F_4B6F_BE1C_3A56D00E8B08__)
#define __EE38B74D_CE8F_4B6F_BE1C_3A56D00E8B08__

class IProxyService {
public:
	virtual bool Start() = 0;
	virtual void Stop() = 0;
	virtual void SetConfig(const char*,size_t) = 0;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 05 Sep 2025 03:12:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__EE38B74D_CE8F_4B6F_BE1C_3A56D00E8B08__