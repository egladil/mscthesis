//
//  AbsCat.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__AbsCat_h
#define pgf__AbsCat_h

#include <string>
#include <vector>

#include <gf/RefBase.h>
#include <gf/RefBase.h>
#include <gf/reader/Hypo.h>
#include <gf/reader/WeightedIdent.h>

namespace gf {
    namespace reader {
        
        class AbsCat : public gf::RefBase {
        private:
            /* final */ std::string name;
            /* final */ std::vector<Hypo*> hypos;
            /* final */ std::vector<WeightedIdent*> functions;
            
        public:
            /**
             * Create an AbsCat object.
             * It is the callers responsibility to increase the reference count
             * on any provided objects as the constructor takes ownership of the
             * provided reference. 
             */
            AbsCat(const std::string& name, const std::vector<Hypo*>& hypos, const std::vector<WeightedIdent*>& functions);
            virtual ~AbsCat();
            
            virtual const std::string& getName() const;
            virtual const std::vector<Hypo*>& getHypos() const;
            virtual const std::vector<WeightedIdent*>& getFunctions() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
