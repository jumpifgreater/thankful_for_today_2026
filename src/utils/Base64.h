#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace base64
{
    inline constexpr char table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    inline std::string encode(const uint8_t* data, size_t size)
    {
        std::string result;
        result.reserve(((size + 2) / 3) * 4);

        size_t i = 0;

        while (i + 2 < size)
        {
            uint32_t n =
                (static_cast<uint32_t>(data[i]) << 16) |
                (static_cast<uint32_t>(data[i + 1]) << 8) |
                static_cast<uint32_t>(data[i + 2]);

            result += table[(n >> 18) & 0x3F];
            result += table[(n >> 12) & 0x3F];
            result += table[(n >> 6) & 0x3F];
            result += table[n & 0x3F];

            i += 3;
        }

        if (i < size)
        {
            uint32_t n = static_cast<uint32_t>(data[i]) << 16;

            if (i + 1 < size)
                n |= static_cast<uint32_t>(data[i + 1]) << 8;

            result += table[(n >> 18) & 0x3F];
            result += table[(n >> 12) & 0x3F];

            if (i + 1 < size)
                result += table[(n >> 6) & 0x3F];
            else
                result += '=';

            result += '=';
        }

        return result;
    }

    inline std::string encode(const std::vector<uint8_t>& data)
    {
        return encode(data.data(), data.size());
    }

    inline std::string encode(const std::string& data)
    {
        return encode(
            reinterpret_cast<const uint8_t*>(data.data()),
            data.size()
        );
    }

    inline uint8_t decode_char(char c)
    {
        if (c >= 'A' && c <= 'Z')
            return c - 'A';

        if (c >= 'a' && c <= 'z')
            return c - 'a' + 26;

        if (c >= '0' && c <= '9')
            return c - '0' + 52;

        if (c == '+')
            return 62;

        if (c == '/')
            return 63;

        return 0;
    }

    inline std::vector<uint8_t> decode(const std::string& input)
    {
        if (input.empty())
            return {};

        if (input.size() % 4 != 0)
            throw std::runtime_error("Invalid Base64 length");

        std::vector<uint8_t> result;
        result.reserve((input.size() / 4) * 3);

        for (size_t i = 0; i < input.size(); i += 4)
        {
            char a = input[i];
            char b = input[i + 1];
            char c = input[i + 2];
            char d = input[i + 3];

            uint32_t n =
                (static_cast<uint32_t>(decode_char(a)) << 18) |
                (static_cast<uint32_t>(decode_char(b)) << 12);

            result.push_back((n >> 16) & 0xFF);

            if (c != '=')
            {
                n |= static_cast<uint32_t>(decode_char(c)) << 6;
                result.push_back((n >> 8) & 0xFF);

                if (d != '=')
                {
                    n |= static_cast<uint32_t>(decode_char(d));
                    result.push_back(n & 0xFF);
                }
            }
        }

        return result;
    }

    inline std::string decode_string(const std::string& input)
    {
        auto bytes = decode(input);

        return std::string(
            reinterpret_cast<const char*>(bytes.data()),
            bytes.size()
        );
    }
}