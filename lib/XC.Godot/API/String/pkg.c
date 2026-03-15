#pragma once
#include <Godot.pkg.h>

#define module godot, API, String

moduleValuesDef(FuncNames,
	.NewWithLatin1Chars		= "string_new_with_latin1_chars",
	.NewWithUtf8Chars		= "string_new_with_utf8_chars",
	.NewWithUtf16Chars		= "string_new_with_utf16_chars",
	.NewWithUtf32Chars		= "string_new_with_utf32_chars",
	.NewWithWideChars		= "string_new_with_wide_chars",
	.NewWithLatin1CharsAndLen	= "string_new_with_latin1_chars_and_len",
	.NewWithUtf8CharsAndLen		= "string_new_with_utf8_chars_and_len2",
	.NewWithUtf16CharsAndLen	= "string_new_with_utf16_chars_and_len2",
	.NewWithUtf32CharsAndLen	= "string_new_with_utf32_chars_and_len",
	.NewWithWideCharsAndLen		= "string_new_with_wide_chars_and_len",
	.ToLatin1Chars			= "string_to_latin1_chars",
	.ToUtf8Chars			= "string_to_utf8_chars",
	.ToUtf16Chars			= "string_to_utf16_chars",
	.ToUtf32Chars			= "string_to_utf32_chars",
	.ToWideChars			= "string_to_wide_chars",
	.OpIndex			= "string_operator_index",
	.OpIndexConst			= "string_operator_index_const",
	.OpPlusEqString			= "string_operator_plus_eq_string",
	.OpPlusEqChar			= "string_operator_plus_eq_char",
	.OpPlusEqCstr			= "string_operator_plus_eq_cstr",
	.OpPlusEqWcstr			= "string_operator_plus_eq_wcstr",
	.OpPlusEqC32str			= "string_operator_plus_eq_c32str",
	.Resize			        = "string_resize"
)

export(
SUBMODULE(), 
VALUES(FuncNames), 
	load
)

#undef module
