//
//  testutil.h
//  pgf+test
//
//  Created by Emil Djupfeldt on 2012-06-27.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf_test_testutil_h
#define pgf_test_testutil_h

#include <dlfcn.h>
#include <string>
#include <vector>

#include <gf/reader/AbsCat.h>
#include <gf/reader/AbsFun.h>
#include <gf/reader/Eq.h>
#include <gf/reader/Expr.h>
#include <gf/reader/Hypo.h>
#include <gf/reader/Type.h>
#include <gf/reader/WeightedIdent.h>

static inline std::string getAppDir() {
    Dl_info info;
    std::string path;
    size_t pos;
    
    if (dladdr((void*) &getAppDir, &info) == 0) {
        return "";
    }
    
    path = info.dli_fname;
    
#ifdef DEBUG
    fprintf(stderr, "Full path: %s\n", path.c_str());
#endif
    
    pos = path.rfind('/');
    if (pos == std::string::npos) {
        return "";
    }
    
    path = path.substr(0, pos + 1);
    
    
#ifdef DEBUG
    fprintf(stderr, "Directory: %s\n", path.c_str());
#endif
    
    return path;
}

static inline gf::reader::Type* mkType(const std::string& type) {
    return new gf::reader::Type(std::vector<gf::reader::Hypo*>(), type, std::vector<gf::reader::Expr*>());
}

static inline gf::reader::Type* mkType(const std::vector<std::string>& argTypes, const std::string& returnType) {
    std::vector<gf::reader::Hypo*> hypos;
    
    for (std::vector<std::string>::const_iterator it = argTypes.begin(); it != argTypes.end(); it++) {
        hypos.push_back(new gf::reader::Hypo(true, "_", mkType(*it)));
    }
    
    return new gf::reader::Type(hypos, returnType, std::vector<gf::reader::Expr*>());
}

static inline gf::reader::AbsFun* mkFunction(const std::string& name, const std::vector<std::string>& argTypes, const std::string& returnType) {
    uint32_t arity;
    gf::reader::Type* type;
    
    arity = (uint32_t) argTypes.size();
    type = mkType(argTypes, returnType);
    
    return new gf::reader::AbsFun(name, type, arity, std::vector<gf::reader::Eq*>(), 0);
}

static inline gf::reader::AbsCat* mkCategory(const std::string& name, const std::vector<std::string>& functions) {
    std::vector<gf::reader::WeightedIdent*> funs;
    
    for (std::vector<std::string>::const_iterator it = functions.begin(); it != functions.end(); it++) {
        funs.push_back(new gf::reader::WeightedIdent(*it, 1.0 / functions.size()));
    }
    
    return new gf::reader::AbsCat(name, std::vector<gf::reader::Hypo*>(), funs);
}


#endif
