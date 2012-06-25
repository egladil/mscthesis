//
//  string.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-25.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__string_h
#define pgf__string_h

#include <sstream>
#include <string>
#include <vector>

namespace gf {
    
    static inline std::vector<std::string> split(const std::string& str, char ch) {
        std::vector<std::string> ret;
        size_t last;
        size_t next;
        
        last = 0;
        while (true) {
            next = str.find(ch, last);
            if (next == std::string::npos) {
                ret.push_back(str.substr(last));
                break;
            }
            
            ret.push_back(str.substr(last, next - last));
            last = next + 1;
        }
        
        return ret;
    }
    
    static inline bool isWhiteSpace(char ch) {
        return ch == '\r' || ch == '\n' || ch == '\t' || ch == ' ';
    }
    
    static inline std::string trim(const std::string& str) {
        size_t start;
        size_t end;
        
        for (start = 0; start < str.size() ; start++) {
            if (!isWhiteSpace(str.at(start))) {
                break;
            }
        }
        
        for (end = str.size(); end > start; end--) {
            if (!isWhiteSpace(str.at(end - 1))) {
                end--;
                break;
            }
        }
                
        
        return str.substr(start, end - start);
    }
    
    template<class T> inline std::string toString(const T& t) {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }
    
    static inline std::string convIso88591toUtf8(const std::string& str) {
        std::string ret;
        
        for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
            char ch = *it;
            
            if (ch < 0x80) {
                ret+= ch;
            } else if (ch < 0xc0) {
                ret+= (char) 0xc2;
                ret+= (char) ((ch & 0x3f) + 0x80);
            } else {
                ret+= (char) 0xc3;
                ret+= (char) ((ch & 0x3f) + 0x80);
            }
        }
        
        return ret;
    }
    
}

#endif
