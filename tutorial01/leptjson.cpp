#include "leptjson.h"
#include <cassert>

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

struct lept_context {
    std::string json;
};

static void lept_parse_whitespace (lept_context& c) {
    size_t pos = 0;
    const std::string& ref_json = c.json;
    while (pos < ref_json.size() && ref_json[pos] == ' ' || ref_json[pos] == '\t' || ref_json[pos] == '\n' || ref_json[pos] == '\r') {
        pos++;
    }
    c.json = ref_json.substr(pos);
}

static int lept_parse_null(lept_context& c, lept_value& v) {
    do {
        assert(c.json[0] == 'n');
        c.json.erase(0, 1);
    } while(false);
    if (c.json[0] != 'u' || c.json[1] != 'l' || c.json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c.json.erase(0, 3);
    v.type = lept_type::LEPT_NULL;
    return LEPT_PARSE_OK;
}

static int lept_parse_true(lept_context& c, lept_value& v) {
    do {
        assert(c.json[0] == 't');
        c.json.erase(0, 1);
    } while(false);
    if (c.json[0] != 'r' && c.json[1] != 'u' && c.json[2] != 'e') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c.json.erase(0, 3);
    v.type = lept_type::LEPT_TRUE;
    return LEPT_PARSE_OK;
}

static int lept_parse_false(lept_context& c, lept_value& v) {
    do {
        assert(c.json[0] == 'f');
        c.json.erase(0, 1);
    } while(false);
    if (c.json[0] != 'a' && c.json[1] != 'l' && c.json[2] != 's' && c.json[3] != 'e') {
        return LEPT_PARSE_INVALID_VALUE;
    }
    c.json.erase(0, 4);
    v.type = lept_type::LEPT_FALSE;
    return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context& c, lept_value& v) {
    switch (c.json[0]) {
        case 'n':  return lept_parse_null(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        case 't':  return lept_parse_true(c, v);
        case 'f':  return lept_parse_false(c, v);
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_value& v, std::string json)  {
    lept_context c;
    int ret;
    c.json = json;
    v.type = lept_type::LEPT_NULL;
    lept_parse_whitespace(c);
    if ((ret = lept_parse_value(c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(c);
        if (c.json[0] != '\0')
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

lept_type lept_get_type(const lept_value& v) {
    return v.type;
}
