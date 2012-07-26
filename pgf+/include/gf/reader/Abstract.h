//
//  Abstract.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__Abstract_h
#define pgf__Abstract_h

#include <string>
#include <map>
#include <vector>

#include <gf/RefBase.h>
#include <gf/reader/AbsCat.h>
#include <gf/reader/AbsFun.h>
#include <gf/reader/RLiteral.h>

namespace gf {
    namespace reader {
        
        class Abstract : public gf::RefBase {
        private:
            /* final */ std::string name;
            /* final */ std::map<std::string, RLiteral*> flags;
            /* final */ std::vector<AbsFun*> absFuns;
            /* final */ std::vector<AbsCat*> absCats;
            /* final */ std::map<std::string, AbsCat*> categories;
            /* final */ std::map<std::string, AbsFun*> functions;
            
        public:
            /**
             * Create an Abstract object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            Abstract(const std::string& name, const std::map<std::string, RLiteral*>& flags, const std::vector<AbsFun*>& absFuns, const std::vector<AbsCat*>& absCats);
            virtual ~Abstract();
            
            virtual const std::string& getName() const;
            virtual const std::string& getStartCategory() const;
            
            /**
             * Returns all the functions whose return type
             * is returnType. 
             * @param returnType the return type to search for
             * @return a list of matching functions
             **/
            virtual std::vector<AbsFun*> getFunctions(const std::string& returnType) const;
            
            virtual const std::vector<AbsFun*>& getAbsFuns() const;
            virtual const std::vector<AbsCat*>& getAbsCats() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
