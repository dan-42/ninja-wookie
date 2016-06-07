## primitive types
add_new_test("apdu-types-tag"                       "./test_tag.cpp")
add_new_test("apdu-types-null"                      "./test_null.cpp")
add_new_test("apdu-types-boolean"                   "./test_boolean.cpp")
add_new_test("apdu-types-unsigned-integer"          "./test_unsigned_integer.cpp")
add_new_test("apdu-types-signed-integer"            "./test_signed_integer.cpp")
add_new_test("apdu-types-real"                      "./test_real.cpp")
add_new_test("apdu-types-double-presision"          "./test_double_presision.cpp")
add_new_test("apdu-types-octet-string"              "./test_octet_string.cpp")
add_new_test("apdu-types-character-string"          "./test_character_string.cpp")
add_new_test("apdu-types-bit-string"                "./test_bit_string.cpp")
add_new_test("apdu-types-date"                      "./test_date.cpp")
add_new_test("apdu-types-time"                      "./test_time.cpp")
add_new_test("apdu-types-enumerated"                "./test_enumerated.cpp")

add_new_test("apdu-types-unknown-data"              "./test_unknown_data.cpp")

## constructed types out of primitives
add_new_test("apdu-types-error"                     "./test_error.cpp")
