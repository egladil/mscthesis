//
//  WeightedIdent.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers University of Technology. All rights reserved.
//

#ifndef pgf__WeightedIdent_h
#define pgf__WeightedIdent_h

#include <string>

#include <gf/RefBase.h>

namespace gf {
    namespace reader {
        
        class WeightedIdent : public gf::RefBase {
        private:
            /* final */ double weight;
            /* final */ std::string ident;
            
        public:
            WeightedIdent(const std::string& ident, double weight);
            virtual ~WeightedIdent();
            
            virtual const std::string& getIdent() const;
            virtual double getWeight() const;
        };
        
    }
}

#endif
