// Copyright 2018 Daniel Parker
// Distributed under Boost license

#if defined(_MSC_VER)
#include "windows.h" // test no inadvertant macro expansions
#endif
#include <jsoncons/json.hpp>
#include <jsoncons/json_encoder.hpp>
#include <jsoncons/json_cursor.hpp>
#include <catch/catch.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>

using namespace jsoncons;

TEST_CASE("json_cursor string_value test")
{
    std::string s = R"("Tom")";
    std::istringstream is(s);

    json_cursor cursor(is);
    REQUIRE_FALSE(cursor.done());

    SECTION("test 1")
    {
        CHECK(cursor.current().event_type() == staj_event_type::string_value);
        CHECK(cursor.current().get<std::string>() == std::string("Tom"));
        CHECK((cursor.current().get<jsoncons::string_view>() == jsoncons::string_view("Tom")));
        cursor.next();
        CHECK(cursor.done());
    }
}

TEST_CASE("json_cursor string_value as<int> test")
{
    std::string s = R"("-100")";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    CHECK(cursor.current().get<int>() == -100);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor string_value as<unsigned> test")
{
    std::string s = R"("100")";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    CHECK(cursor.current().get<int>() == 100);
    CHECK(cursor.current().get<unsigned>() == 100);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor null_value test")
{
    std::string s = "null";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::null_value);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor bool_value test")
{
    std::string s = "false";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::bool_value);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor int64_value test")
{
    std::string s = "-100";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::int64_value);
    CHECK(cursor.current().get<int>() == -100);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor uint64_value test")
{
    std::string s = "100";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    CHECK(cursor.current().get<int>() == 100);
    CHECK(cursor.current().get<unsigned>() == 100);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor string_value as bignum test")
{
    std::string s = "-18446744073709551617";
    std::istringstream is("\""+s+"\"");

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    CHECK(s == cursor.current().get<std::string>());
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor bigint value as bignum")
{
    std::string s = "-18446744073709551617";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    CHECK(cursor.current().tag() == semantic_tag::bigint);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor double_value test")
{
    std::string s = "100.0";
    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::double_value);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor array_value test")
{
    std::string s = R"(
    [
        {
            "enrollmentNo" : 100,
            "firstName" : "Tom",
            "lastName" : "Cochrane",
            "mark" : 55              
        },
        {
            "enrollmentNo" : 101,
            "firstName" : "Catherine",
            "lastName" : "Smith",
            "mark" : 95},
        {
            "enrollmentNo" : 102,
            "firstName" : "William",
            "lastName" : "Skeleton",
            "mark" : 60              
        }
    ]
    )";

    std::istringstream is(s);

    json_cursor cursor(is);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::begin_array);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::begin_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::end_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::begin_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::end_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::begin_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::end_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::end_array);
    cursor.next();
    CHECK(cursor.done());
}

TEST_CASE("json_cursor object_value test")
{
    std::string s = R"(
        {
            "enrollmentNo" : 100,
            "firstName" : "Tom",
            "lastName" : "Cochrane",
            "mark" : 55              
        }
    )";

    json_cursor cursor(s);

    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::begin_object);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::string_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::key);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::uint64_value);
    cursor.next();
    REQUIRE_FALSE(cursor.done());
    CHECK(cursor.current().event_type() == staj_event_type::end_object);
    cursor.next();
    CHECK(cursor.done());
}

struct remove_mark_filter
{
    bool reject_next_ = false;

    bool operator()(const staj_event& event, const ser_context&) 
    {
        if (event.event_type()  == staj_event_type::key &&
            event.get<jsoncons::string_view>() == "mark")
        {
            reject_next_ = true;
            return false;
        }
        else if (reject_next_)
        {
            reject_next_ = false;
            return false;
        }
        else
        {
            return true;
        }
    }
};

TEST_CASE("json_cursor with filter tests")
{
    std::string s = R"(
    [
        {
            "enrollmentNo" : 100,
            "firstName" : "Tom",
            "lastName" : "Cochrane",
            "mark" : 55              
        },
        {
            "enrollmentNo" : 101,
            "firstName" : "Catherine",
            "lastName" : "Smith",
            "mark" : 95},
        {
            "enrollmentNo" : 102,
            "firstName" : "William",
            "lastName" : "Skeleton",
            "mark" : 60              
        }
    ]
    )";

    json_cursor cursor(s);

    auto filtered_c = cursor | remove_mark_filter();

    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::begin_array);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::begin_object);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::uint64_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::string_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::string_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::end_object);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::begin_object);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::uint64_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::string_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::string_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::end_object);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::begin_object);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::uint64_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::string_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::key);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::string_value);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::end_object);
    filtered_c.next();
    REQUIRE_FALSE(filtered_c.done());
    CHECK(filtered_c.current().event_type() == staj_event_type::end_array);
    filtered_c.next();
    CHECK(filtered_c.done());
}

namespace {
namespace ns {

    struct book
    {
        std::string author;
        std::string title;
        double price;

        book() :
            price(0)
        {
        }

        book(const std::string& author, 
             const std::string& title, 
             double price) : 
            author(author), title(title), price(price)
        {
        }

        friend std::ostream& operator<<(std::ostream& os, const book& b)
        {
            std::cout << "author: " << b.author << ", title: " << b.title << ", price: " << b.price << "\n";
            return os;
        }
    };

} // namespace ns
} // namespace

JSONCONS_ALL_MEMBER_TRAITS(ns::book,author,title,price)

TEST_CASE("staj event as object")
{
    std::vector<ns::book> books;
    books.emplace_back("Haruki Murakami",
                       "Kafka on the Shore",
                       25.17);
    books.emplace_back("Charles Bukowski",
                       "Women: A Novel",
                       12.0);

    std::string buffer;
    encode_json_pretty(books, buffer);

    SECTION("test 1")
    {
        json_cursor cursor(buffer);
        REQUIRE_FALSE(cursor.done());
        CHECK(cursor.current().event_type() == staj_event_type::begin_array);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::begin_object);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::key);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::string_value);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::key);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::double_value);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::key);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::string_value);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::end_object);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::begin_object);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::key);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::string_value);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::key);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::double_value);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::key);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::string_value);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::end_object);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::end_array);
        cursor.next();
        CHECK(cursor.done());
    }
    SECTION("test 2")
    {
        json document = json::parse(buffer);

        json_cursor cursor(buffer);
        REQUIRE_FALSE(cursor.done());
        CHECK(cursor.current().event_type() == staj_event_type::begin_array);
        cursor.next();
        CHECK(cursor.current().event_type() == staj_event_type::begin_object);

        json_decoder<json> decoder;
        cursor.read_to(decoder);
        json j0 = decoder.get_result();
        CHECK((j0 == document[0]));

        cursor.next();

        json_decoder<json> decoder2;
        cursor.read_to(decoder2);
        json j1 = decoder2.get_result();
        CHECK((j1 == document[1]));
    }
}

