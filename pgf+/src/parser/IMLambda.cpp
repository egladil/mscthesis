//
//  IMLambda.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/IMLambda.h>

namespace gf {
    namespace parser {
        
        IMLambda::IMLambda(const std::vector<std::pair<bool, std::string> >& variables, IMTree* body)
            : variables(variables), body(body) {
        }
        
        IMLambda::~IMLambda() {
            gf::release(body);
        }
        
        gf::Tree* IMLambda::toAbstract(const std::vector<std::string>& args) const {
            gf::Tree* ret;
            std::vector<std::string> newArgs;
            
            for (std::vector<std::pair<bool, std::string> >::const_reverse_iterator it = variables.rbegin(); it != variables.rend(); it++) {
                newArgs.push_back(it->second);
            }
            newArgs.insert(newArgs.end(), args.begin(), args.end());
            
            ret = body->toAbstract(newArgs);
            for (std::vector<std::pair<bool, std::string> >::const_reverse_iterator it = variables.rbegin(); it != variables.rend(); it++) {
                ret = new gf::Lambda(it->second, ret);
            }
            
            
            return ret;
        }
        
        const std::vector<std::pair<bool, std::string> >& IMLambda::getVariables() const {
            return variables;
        }
        
        IMTree* IMLambda::getBody() const {
            return body;
        }
    }
}