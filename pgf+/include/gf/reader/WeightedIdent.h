//
//  WeightedIdent.h
//  pgf+
//
//  Created by Emil Djupfeldt on 2012-06-22.
//  Copyright (c) 2012 Chalmers. All rights reserved.
//

#ifndef pgf__WeightedIdent_h
#define pgf__WeightedIdent_h

#include <string>

namespace gf {
    namespace reader {
        
        class WeightedIdent {
        private:
            /* final */ double weight;
            /* final */ std::string ident;
            
        public:
            WeightedIdent(const std::string& ident, double weight);
            virtual ~WeightedIdent();
            
            virtual const std::string& ident() const;
            virtual double weight() const;
        };
        
    }
}

#endif
