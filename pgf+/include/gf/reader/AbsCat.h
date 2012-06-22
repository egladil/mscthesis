//
//  AbsCat.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__AbsCat_h
#define pgf__AbsCat_h

#include <string>
#include <vector>

#include <gf/reader/Hypo.h>
#include <gf/reader/WeightedIdent.h>

namespace gf {
    namespace reader {
        
        class AbsCat {
        private:
            /* final */ std::string name;
            /* final */ std::vector<Hypo> hypos;
            /* final */ std::vector<WeightedIdent> functions;
            
        public:
            AbsCat(const std::string& name, const std::vector<Hypo>& hypos, const std::vector<WeightedIdent>& functions);
            virtual ~AbsCat();
            
            virtual const std::string& name() const;
            virtual const std::vector<Hypo>& getHypos() const;
            virtual const std::WeightedIdent> getFunctions() const;
            
            virtual std::string toString() const;
        };
        
    }
}

#endif
