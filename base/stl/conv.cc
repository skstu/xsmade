#include "stl.hpp"
using namespace std;
using namespace stl;
#if 0
std::wstring Conv::U8StringToWString(const std::string& input) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(input);
}

std::u16string Conv::U8StringToU16String(const std::string& input) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.from_bytes(reinterpret_cast<const char*>(input.data()), reinterpret_cast<const char*>(input.data() + input.size()));
}

std::string Conv::U16StringToU8String(const std::u16string& input) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.to_bytes(input);
	//result = std::u8string(reinterpret_cast<const char8_t*>(u8str.c_str()), u8str.length());
}
std::u32string Conv::U8StringToU32String(const std::string& input) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	return converter.from_bytes(reinterpret_cast<const char*>(input.data()),
		reinterpret_cast<const char*>(input.data() + input.length()));
}
std::string Conv::U32StringToU8String(const std::u32string& input) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
	return convert.to_bytes(input);
	//result = std::u8string(reinterpret_cast<const char8_t*>(u8str.c_str()), u8str.length());
}
std::u32string Conv::U16StringToU32String(const std::u16string& input) {
	auto u8 = U16StringToU8String(input);
	return U8StringToU32String(u8);
}
std::u16string Conv::U32StringToU16String(const std::u32string& input) {
	auto u8 = U32StringToU8String(input);
	return U8StringToU16String(u8);
}
#endif