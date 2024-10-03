#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <string>

enum class lept_type { // JSON中对应的类型
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
};

class lept_value {
public:
    lept_type type;
};

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

int lept_parse(lept_value& v, const std::string json);

lept_type lept_get_type(const lept_value& v);

#endif /* LEPTJSON_H__ */
