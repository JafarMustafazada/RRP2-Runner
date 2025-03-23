#pragma once
#include "jdevtools/sha256hmac.h"
#include <string>
#include <vector>
#include <unordered_map>
typedef unsigned char BYTE;

namespace jdevtools {
	static const char BASE64_URL_ALPHABET[] = 
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789-_"
    ;

    static std::string base64urlEncode(const std::vector<BYTE>& data);
    static std::string base64urlEncode(const std::string &input);
    static std::string base64urlDecode(const std::string &input);
    static std::string createJWT(const std::string& secret, const std::string& payload, 
        const std::string& header, std::string(&hmac_sha2)(const std::string&, const std::string&))
    ;
    static std::string createJWT(const std::string& secret, const std::string& payload);


    std::string base64urlEncode(const std::vector<BYTE>& data) {
        std::string encoded;
        int val = 0, valb = -6;
        for (BYTE c : data) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                encoded.push_back(BASE64_URL_ALPHABET[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        return encoded;
    }
    
	std::string base64urlEncode(const std::string &input) {
		std::string encoded;
		int val = 0, valb = -6;
		
		for (BYTE c : input) {
			val = (val << 8) | c;
			valb += 8;
			while (valb >= 0) {
				encoded.push_back(BASE64_URL_ALPHABET[(val >> valb) & 0x3F]);
				valb -= 6;
			}
		}

		if (valb > -6) { 
			encoded.push_back(BASE64_URL_ALPHABET[((val << 8) >> (valb + 8)) & 0x3F]);
		}

		return encoded; // No padding per RFC 4648
	}

	std::string base64urlDecode(const std::string &input) {
		std::vector<int> T(256, -1);
        
		for (size_t i = 0; i < std::strlen(BASE64_URL_ALPHABET); i++) {
			T[BASE64_URL_ALPHABET[i]] = i;
		}

		std::string decoded;
		int val = 0, valb = -8;
		
		for (BYTE c : input) {
			if (T[c] == -1) break; // Ignore invalid characters
			val = (val << 6) | T[c];
			valb += 6;
			if (valb >= 0) {
				decoded.push_back(char((val >> valb) & 0xFF));
				valb -= 8;
			}
		}

		return decoded;
	}

    // class jdevjson {
    // public:
    //     class jsonode {
    //         bool isarray = false;
    //         bool isnumber = false;
    //     };
    // private:
    //     std::unordered_map<std::std::string, jsonode> raw;
    // };

    std::string createJWT(const std::string& secret, const std::string& payload, 
        const std::string& header, std::string(&hmac_sha2)(const std::string&, const std::string&)) {
        // std::string payload = R"({"userId":123,"role":"admin","iat":1710979200})";
        // vector<BYTE> headerBytes(header.begin(), header.end());
        // vector<BYTE> payloadBytes(payload.begin(), payload.end());
        // string encodedHeader = base64UrlEncode(headerBytes);
        // string encodedPayload = base64UrlEncode(payloadBytes);

        std::string encodedHeader = base64urlEncode(header);
        std::string encodedPayload = base64urlEncode(payload);
        std::string message = encodedHeader + "." + encodedPayload;
        
        // vector<BYTE> signature = hmac_sha256(secret, message);
        // std::string encodedSignature = base64UrlEncode(signature);

        std::string encodedSignature = hmac_sha2(secret, message);
        return message + "." + encodedSignature;
    }

    std::string createJWT(const std::string& secret, const std::string& payload) {
        std::string header = R"({"alg":"HS256","typ":"JWT"})";
        return createJWT(secret, payload, header, jdevtools::hmac_sha256);
    }
}