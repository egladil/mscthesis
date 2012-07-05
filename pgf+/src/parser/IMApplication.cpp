//
//  IMApplication.cpp
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-07-05.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#include <gf/parser/IMApplication.h>

namespace gf {
    namespace parser {
        
        IMApplication::IMApplication(const std::string& fun, const std::vector<IMTree*>& args)
            : fun(fun), args(args) {
        }
        
        IMApplication::~IMApplication() {
            for (std::vector<IMTree*>::iterator it = args.begin(); it != args.end(); it++) {
                gf::release(*it);
            }
        }
        
        gf::Tree* IMApplication::toAbstract(const std::vector<std::string>& args) const {
            std::vector<gf::Tree*> aargs;
            gf::Tree* ret;
            
            for (std::vector<IMTree*>::const_iterator it = this->args.begin(); it != this->args.end(); it++) {
                aargs.push_back((*it)->toAbstract(args));
            }
            
            ret = new gf::Function(fun);
            for (std::vector<gf::Tree*>::iterator it = aargs.begin(); it != aargs.end(); it++) {
                ret = new gf::Application(ret, *it);
            }
            
            return ret;
        }
        
        const std::string& IMApplication::getFunction() const {
            return fun;
        }
        
        const std::vector<IMTree*>& IMApplication::getArguments() const {
            return args;
        }
    }
}
