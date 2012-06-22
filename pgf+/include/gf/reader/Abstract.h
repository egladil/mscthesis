//
//  Abstract.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__Abstract_h
#define pgf__Abstract_h

#include <string>
#include <map>
#include <vector>

#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class Abstract {
        private:
            /* final */ std::string name;
            /* final */ std::map<std::string, RLiteral> flags;
            /* final */ std::vector<AbsFun> absFuns;
            /* final */ std::vector<AbsCat> absCats;
            /* final */ std::map<std::string, AbsCat> categories;
            /* final */ std::map<std::string, AbsFun> functions;
            
        public:
            Abstract(const std::string& name, const std::map<std::string, RLiteral> flags, const std::vector<AbsFun> absFuns, std::vector<AbsCat> absCats);
            virtual ~Abstract();
            
            virtual const std::string& name() const;
            virtual const std::string& startcat() const;
            
            /**
             * Returns all the functions whose return type
             * is returnType. 
             * @param returnType the return type to search for
             * @return a list of matching functions
             **/
            virtual std::vector<AbsFun> functions(const std::string& returnType) const;
            
            virtual const std::vector<AbsFun>& getAbsFuns() const;
            virtual const std::vector<AbsFun>& getAbsCats() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
